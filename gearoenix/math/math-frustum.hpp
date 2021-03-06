#ifndef GEAROENIX_MATH_FRUSTUM_HPP
#define GEAROENIX_MATH_FRUSTUM_HPP
#include "math-plane.hpp"
namespace gearoenix {
namespace math {
    struct Frustum {
        Plane planes[6];

        Frustum() = delete;
        /// These planes must face inward the frustum
        explicit Frustum(const Plane (&planes)[6]) noexcept;
        /// This is not exact but rather fast, necessarily informative and conservatively includes objects
        IntersectionStatus check_intersection(const Sphere& s) const noexcept;
        //IntersectionStatus::Type check_intersection(const Aabb3& aabb) const noexcept;
    };
}
}
#endif