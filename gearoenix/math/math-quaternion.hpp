#ifndef GEAROENIX_MATH_QUATERNION_HPP
#define GEAROENIX_MATH_QUATERNION_HPP
#include "../core/cr-types.hpp"
#include "math-matrix.hpp"
#include <ostream>

namespace gearoenix {
namespace math {
    struct Quat {
        core::Real x = 0.0f;
        core::Real y = 0.0f;
        core::Real z = 0.0f;
        core::Real w = 0.0f;

        Quat();
        Quat(const core::Real x, const core::Real y, const core::Real z, const core::Real w);
        Mat4x4 to_mat() const;

        friend std::ostream& operator<<(std::ostream& os, const Quat& q)
        {
            os << "Quat { x: " << q.x << ", y: " << q.y << ", z: " << q.z << ", w: " << q.w << "}";
            return os;
        }
    };
} // namespace math
} // namespace gearoenix
#endif
