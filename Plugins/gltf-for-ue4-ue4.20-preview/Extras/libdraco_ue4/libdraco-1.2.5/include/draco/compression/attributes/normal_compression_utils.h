// Copyright 2016 The Draco Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Utilities for converting unit vectors to octahedral coordinates and back.
// For more details about octahedral coordinates, see for example Cigolle
// et al.'14 “A Survey of Efficient Representations for Independent Unit
// Vectors”.
//
// In short this is motivated by an octahedron inscribed into a sphere. The
// direction of the normal vector can be defined by a point on the octahedron.
// On the right hemisphere (x > 0) this point is projected onto the x = 0 plane,
// that is, the right side of the octahedron forms a diamond like shape. The
// left side of the octahedron is also projected onto the x = 0 plane, however,
// in this case we flap the triangles of the diamond outward. Afterwards we
// shift the resulting square such that all values are positive.
//
// Important values in this file:
// * q: number of quantization bits
// * max_quantized_value: the max value representable with q bits (odd)
// * max_value: max value of the diamond = max_quantized_value - 1  (even)
// * center_value: center of the diamond after shift
//
// Note that the parameter space is somewhat periodic, e.g. (0, 0) ==
// (max_value, max_value), which is also why the diamond is one smaller than the
// maximal representable value in order to have an odd range of values.

#ifndef DRACO_COMPRESSION_ATTRIBUTES_NORMAL_COMPRESSION_UTILS_H_
#define DRACO_COMPRESSION_ATTRIBUTES_NORMAL_COMPRESSION_UTILS_H_

#include <inttypes.h>
#include <algorithm>
#include <cmath>

#include "draco/core/macros.h"

namespace draco {

class OctahedronToolBox {
 public:
  OctahedronToolBox()
      : quantization_bits_(-1),
        max_quantized_value_(-1),
        max_value_(-1),
        center_value_(-1) {}

  explicit OctahedronToolBox(int32_t q) { this->SetQuantizationBits(q); }

  void SetQuantizationBits(int32_t q) {
    DCHECK_GE(q, 2);
    DCHECK_LE(q, 30);
    quantization_bits_ = q;
    max_quantized_value_ = (1 << quantization_bits_) - 1;
    max_value_ = max_quantized_value_ - 1;
    center_value_ = max_value_ / 2;
  }
  bool IsInitialized() const { return quantization_bits_ != -1; }

  // Convert all edge points in the top left and bottom right quadrants to
  // their corresponding position in the bottom left and top right quadrants.
  // Convert all corner edge points to the top right corner.
  inline void CanonicalizeOctahedralCoords(int32_t s, int32_t t, int32_t *out_s,
                                           int32_t *out_t) const {
    if ((s == 0 && t == 0) || (s == 0 && t == max_value_) ||
        (s == max_value_ && t == 0)) {
      s = max_value_;
      t = max_value_;
    } else if (s == 0 && t > center_value_) {
      t = center_value_ - (t - center_value_);
    } else if (s == max_value_ && t < center_value_) {
      t = center_value_ + (center_value_ - t);
    } else if (t == max_value_ && s < center_value_) {
      s = center_value_ + (center_value_ - s);
    } else if (t == 0 && s > center_value_) {
      s = center_value_ - (s - center_value_);
    }

    *out_s = s;
    *out_t = t;
  }

  // Converts an integer vector to octahedral coordinates.
  // Precondition: |int_vec| abs sum must equal center value.
  inline void IntegerVectorToQuantizedOctahedralCoords(const int32_t *int_vec,
                                                       int32_t *out_s,
                                                       int32_t *out_t) const {
    DCHECK_EQ(
        std::abs(int_vec[0]) + std::abs(int_vec[1]) + std::abs(int_vec[2]),
        center_value_);
    int32_t s, t;
    if (int_vec[0] >= 0) {
      // Right hemisphere.
      s = (int_vec[1] + center_value_);
      t = (int_vec[2] + center_value_);
    } else {
      // Left hemisphere.
      if (int_vec[1] < 0) {
        s = std::abs(int_vec[2]);
      } else {
        s = (max_value_ - std::abs(int_vec[2]));
      }
      if (int_vec[2] < 0) {
        t = std::abs(int_vec[1]);
      } else {
        t = (max_value_ - std::abs(int_vec[1]));
      }
    }
    CanonicalizeOctahedralCoords(s, t, out_s, out_t);
  }

  template <class T>
  void FloatVectorToQuantizedOctahedralCoords(const T *vector, int32_t *out_s,
                                              int32_t *out_t) const {
    const double abs_sum = std::abs(static_cast<double>(vector[0])) +
                           std::abs(static_cast<double>(vector[1])) +
                           std::abs(static_cast<double>(vector[2]));

    // Adjust values such that abs sum equals 1.
    double scaled_vector[3];
    if (abs_sum > 1e-6) {
      // Scale needed to project the vector to the surface of an octahedron.
      const double scale = 1.0 / abs_sum;
      scaled_vector[0] = vector[0] * scale;
      scaled_vector[1] = vector[1] * scale;
      scaled_vector[2] = vector[2] * scale;
    } else {
      scaled_vector[0] = 1.0;
      scaled_vector[1] = 0;
      scaled_vector[2] = 0;
    }

    // Scale vector such that the sum equals the center value.
    int32_t int_vec[3];
    int_vec[0] =
        static_cast<int32_t>(floor(scaled_vector[0] * center_value_ + 0.5));
    int_vec[1] =
        static_cast<int32_t>(floor(scaled_vector[1] * center_value_ + 0.5));
    // Make sure the sum is exactly the center value.
    int_vec[2] = center_value_ - std::abs(int_vec[0]) - std::abs(int_vec[1]);
    if (int_vec[2] < 0) {
      // If the sum of first two coordinates is too large, we need to decrease
      // the length of one of the coordinates.
      if (int_vec[1] > 0) {
        int_vec[1] += int_vec[2];
      } else {
        int_vec[1] -= int_vec[2];
      }
      int_vec[2] = 0;
    }
    // Take care of the sign.
    if (scaled_vector[2] < 0)
      int_vec[2] *= -1;

    IntegerVectorToQuantizedOctahedralCoords(int_vec, out_s, out_t);
  }

  // Normalize |vec| such that its abs sum is equal to the center value;
  template <class T>
  void CanonicalizeIntegerVector(T *vec) const {
    static_assert(std::is_integral<T>::value, "T must be an integral type.");
    static_assert(std::is_signed<T>::value, "T must be a signed type.");
    const int64_t abs_sum = static_cast<int64_t>(std::abs(vec[0])) +
                            static_cast<int64_t>(std::abs(vec[1])) +
                            static_cast<int64_t>(std::abs(vec[2]));

    if (abs_sum == 0) {
      vec[0] = center_value_;  // vec[1] == v[2] == 0
    } else {
      vec[0] = (static_cast<int64_t>(vec[0]) * center_value_) / abs_sum;
      vec[1] = (static_cast<int64_t>(vec[1]) * center_value_) / abs_sum;
      if (vec[2] >= 0) {
        vec[2] = center_value_ - std::abs(vec[0]) - std::abs(vec[1]);
      } else {
        vec[2] = -(center_value_ - std::abs(vec[0]) - std::abs(vec[1]));
      }
    }
  }

  template <typename T>
  void OctaherdalCoordsToUnitVector(T in_s, T in_t, T *out_vector) const {
    DCHECK_GE(in_s, 0);
    DCHECK_GE(in_t, 0);
    DCHECK_LE(in_s, 1);
    DCHECK_LE(in_t, 1);
    T s = in_s;
    T t = in_t;
    T spt = s + t;
    T smt = s - t;
    T x_sign = 1.0;
    if (spt >= 0.5 && spt <= 1.5 && smt >= -0.5 && smt <= 0.5) {
      // Right hemisphere. Don't do anything.
    } else {
      // Left hemisphere.
      x_sign = -1.0;
      if (spt <= 0.5) {
        s = 0.5 - in_t;
        t = 0.5 - in_s;
      } else if (spt >= 1.5) {
        s = 1.5 - in_t;
        t = 1.5 - in_s;
      } else if (smt <= -0.5) {
        s = in_t - 0.5;
        t = in_s + 0.5;
      } else {
        s = in_t + 0.5;
        t = in_s - 0.5;
      }
      spt = s + t;
      smt = s - t;
    }
    const T y = 2.0 * s - 1.0;
    const T z = 2.0 * t - 1.0;
    const T x = std::min(std::min(2.0 * spt - 1.0, 3.0 - 2.0 * spt),
                         std::min(2.0 * smt + 1.0, 1.0 - 2.0 * smt)) *
                x_sign;
    // Normalize the computed vector.
    const T normSquared = x * x + y * y + z * z;
    if (normSquared < 1e-6) {
      out_vector[0] = 0;
      out_vector[1] = 0;
      out_vector[2] = 0;
    } else {
      const T d = 1.0 / std::sqrt(normSquared);
      out_vector[0] = x * d;
      out_vector[1] = y * d;
      out_vector[2] = z * d;
    }
  }

  template <typename T>
  void QuantizedOctaherdalCoordsToUnitVector(int32_t in_s, int32_t in_t,
                                             T *out_vector) const {
    T scale = 1.0 / static_cast<T>(max_value_);
    OctaherdalCoordsToUnitVector(in_s * scale, in_t * scale, out_vector);
  }

  // |s| and |t| are expected to be signed values.
  inline bool IsInDiamond(const int32_t &s, const int32_t &t) const {
    // Expect center already at origin.
    DCHECK_LE(s, center_value_);
    DCHECK_LE(t, center_value_);
    DCHECK_GE(s, -center_value_);
    DCHECK_GE(t, -center_value_);
    return std::abs(s) + std::abs(t) <= center_value_;
  }

  void InvertDiamond(int32_t *s, int32_t *t) const {
    // Expect center already at origin.
    DCHECK_LE(*s, center_value_);
    DCHECK_LE(*t, center_value_);
    DCHECK_GE(*s, -center_value_);
    DCHECK_GE(*t, -center_value_);
    int32_t sign_s = 0;
    int32_t sign_t = 0;
    if (*s >= 0 && *t >= 0) {
      sign_s = 1;
      sign_t = 1;
    } else if (*s <= 0 && *t <= 0) {
      sign_s = -1;
      sign_t = -1;
    } else {
      sign_s = (*s > 0) ? 1 : -1;
      sign_t = (*t > 0) ? 1 : -1;
    }

    const int32_t corner_point_s = sign_s * center_value_;
    const int32_t corner_point_t = sign_t * center_value_;
    *s = 2 * *s - corner_point_s;
    *t = 2 * *t - corner_point_t;
    if (sign_s * sign_t >= 0) {
      int32_t temp = *s;
      *s = -*t;
      *t = -temp;
    } else {
      std::swap(*s, *t);
    }
    *s = (*s + corner_point_s) / 2;
    *t = (*t + corner_point_t) / 2;
  }

  void InvertDirection(int32_t *s, int32_t *t) const {
    // Expect center already at origin.
    DCHECK_LE(*s, center_value_);
    DCHECK_LE(*t, center_value_);
    DCHECK_GE(*s, -center_value_);
    DCHECK_GE(*t, -center_value_);
    *s *= -1;
    *t *= -1;
    this->InvertDiamond(s, t);
  }

  // For correction values.
  int32_t ModMax(int32_t x) const {
    if (x > this->center_value())
      return x - this->max_quantized_value();
    if (x < -this->center_value())
      return x + this->max_quantized_value();
    return x;
  }

  // For correction values.
  int32_t MakePositive(int32_t x) const {
    DCHECK_LE(x, this->center_value() * 2);
    if (x < 0)
      return x + this->max_quantized_value();
    return x;
  }

  int32_t quantization_bits() const { return quantization_bits_; }
  int32_t max_quantized_value() const { return max_quantized_value_; }
  int32_t max_value() const { return max_value_; }
  int32_t center_value() const { return center_value_; }

 private:
  int32_t quantization_bits_;
  int32_t max_quantized_value_;
  int32_t max_value_;
  int32_t center_value_;
};
}  // namespace draco

#endif  // DRACO_COMPRESSION_ATTRIBUTES_NORMAL_COMPRESSION_UTILS_H_
