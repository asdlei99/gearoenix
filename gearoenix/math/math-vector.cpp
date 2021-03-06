#include "math-vector.hpp"
#include "../core/cr-build-configuration.hpp"
#include "../core/cr-static.hpp"
#include "../system/stream/sys-stm-stream.hpp"
#include "../system/sys-log.hpp"
#include "math-matrix.hpp"
#include <cmath>

gearoenix::math::Vec2::Vec2() noexcept
    : vec { core::Real(0), core::Real(0) }
{
}

gearoenix::math::Vec2::Vec2(core::Real x, core::Real y) noexcept
    : vec { x, y }
{
}

gearoenix::math::Vec2::Vec2(core::Real e) noexcept
    : vec { e, e }
{
}

gearoenix::math::Vec2::Vec2(const Vec2& v) noexcept
    : vec { v.vec[0], v.vec[1] }
{
}

gearoenix::math::Vec2& gearoenix::math::Vec2::operator=(const Vec2& v) noexcept
{
    vec[0] = v.vec[0];
    vec[1] = v.vec[1];
    return *this;
}

gearoenix::math::Vec2 gearoenix::math::Vec2::operator+(const Vec2& a) const noexcept
{
    return Vec2(vec[0] + a.vec[0], vec[1] + a.vec[1]);
}

gearoenix::math::Vec2 gearoenix::math::Vec2::operator-(const Vec2& a) const noexcept
{
    return Vec2(vec[0] - a.vec[0], vec[1] - a.vec[1]);
}

gearoenix::math::Vec2 gearoenix::math::Vec2::operator*(const Vec2& a) const noexcept
{
    return Vec2(vec[0] * a.vec[0], vec[1] * a.vec[1]);
}

gearoenix::math::Vec2 gearoenix::math::Vec2::operator*(const core::Real& a) const noexcept
{
    return Vec2(vec[0] * a, vec[1] * a);
}

gearoenix::math::Vec2 gearoenix::math::Vec2::operator/(const Vec2& a) const noexcept
{
    return Vec2(vec[0] / a.vec[0], vec[1] / a.vec[1]);
}

void gearoenix::math::Vec2::operator+=(const Vec2& a) noexcept
{
    vec[0] += a.vec[0];
    vec[1] += a.vec[1];
}

void gearoenix::math::Vec2::operator-=(const Vec2& a) noexcept
{
    vec[0] -= a.vec[0];
    vec[1] -= a.vec[1];
}

void gearoenix::math::Vec2::operator*=(const Vec2& a) noexcept
{
    vec[0] *= a.vec[0];
    vec[1] *= a.vec[1];
}

void gearoenix::math::Vec2::operator*=(const core::Real a) noexcept
{
    vec[0] *= a;
    vec[1] *= a;
}

void gearoenix::math::Vec2::operator/=(const Vec2& a) noexcept
{
    vec[0] /= a.vec[0];
    vec[1] /= a.vec[1];
}

const gearoenix::core::Real& gearoenix::math::Vec2::operator[](const unsigned int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 1)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

gearoenix::core::Real& gearoenix::math::Vec2::operator[](const unsigned int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 1)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

const gearoenix::core::Real& gearoenix::math::Vec2::operator[](const int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 1 || i < 0)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

gearoenix::core::Real& gearoenix::math::Vec2::operator[](const int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 1 || i < 0)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

bool gearoenix::math::Vec2::operator<(const Vec2& o) const noexcept
{
    if (vec[0] < o.vec[0]) {
        return true;
    }
    if (vec[0] != o.vec[0]) {
        return false;
    }
    return vec[1] < o.vec[1];
}

bool gearoenix::math::Vec2::operator==(const Vec2& o) const noexcept
{
    return vec[0] == o.vec[0] && vec[1] == o.vec[1];
}

bool gearoenix::math::Vec2::operator>(const Vec2& o) const noexcept
{
    if (vec[0] > o.vec[0]) {
        return true;
    }
    if (vec[0] != o.vec[0]) {
        return false;
    }
    return vec[1] > o.vec[1];
}

gearoenix::core::Real gearoenix::math::Vec2::dot(const Vec2& o) const noexcept
{
    return (vec[0] * o.vec[0]) + (vec[1] * o.vec[1]);
}

gearoenix::core::Real gearoenix::math::Vec2::cross(const Vec2& o) const noexcept
{
    return vec[0] * o.vec[1] - vec[1] * o.vec[0];
}

gearoenix::math::Vec2 gearoenix::math::Vec2::operator-() const noexcept
{
    return Vec2(-vec[0], -vec[1]);
}

gearoenix::core::Real gearoenix::math::Vec2::length() const noexcept
{
    return sqrtf(square_length());
}

gearoenix::core::Real gearoenix::math::Vec2::square_length() const noexcept
{
    return dot(*this);
}

gearoenix::core::Real gearoenix::math::Vec2::distance(const Vec2& a) const noexcept
{
    const auto v = *this - a;
    return v.length();
}

gearoenix::core::Real gearoenix::math::Vec2::square_distance(const Vec2& a) const noexcept
{
    core::Real t = a.vec[0] - vec[0];
    t *= t;
    core::Real d = t;
    t = a.vec[1] - vec[1];
    t *= t;
    d += t;
    return d;
}

gearoenix::math::Vec2 gearoenix::math::Vec2::normalized() const noexcept
{
    const auto il = 1.0f / length();
    return *this * il;
}

void gearoenix::math::Vec2::normalize() noexcept
{
    const auto l = 1.0f / length();
    vec[0] *= l;
    vec[1] *= l;
}

void gearoenix::math::Vec2::read(system::stream::Stream* const f) noexcept
{
    f->read(vec[0]);
    f->read(vec[1]);
}

bool gearoenix::math::Vec2::intersect(const Vec2& s11, const Vec2& s12, const Vec2& s21, const Vec2& s22, Vec2& i) noexcept
{
    core::Real maxxs1, minxs1;
    if (s11.vec[0] > s12.vec[0]) {
        maxxs1 = s11.vec[0];
        minxs1 = s12.vec[0];
    } else {
        minxs1 = s11.vec[0];
        maxxs1 = s12.vec[0];
    }
    core::Real maxxs2, minxs2;
    if (s21.vec[0] > s22.vec[0]) {
        maxxs2 = s21.vec[0];
        minxs2 = s22.vec[0];
    } else {
        minxs2 = s21.vec[0];
        maxxs2 = s22.vec[0];
    }
    if (minxs1 > maxxs2 || minxs2 > maxxs1)
        return false;
    core::Real maxys1, minys1;
    if (s11.vec[1] > s12.vec[1]) {
        maxys1 = s11.vec[1];
        minys1 = s12.vec[1];
    } else {
        minys1 = s11.vec[1];
        maxys1 = s12.vec[1];
    }
    core::Real maxys2, minys2;
    if (s21.vec[1] > s22.vec[1]) {
        maxys2 = s21.vec[1];
        minys2 = s22.vec[1];
    } else {
        minys2 = s21.vec[1];
        maxys2 = s22.vec[1];
    }
    if (minys1 > maxys2 || minys2 > maxys1)
        return false;
    // s11 + s0 * v0 == s21 + s1 * v1
    // s21 - s11 = s0 * v0 - s1 * v1
    // d = | v0 v1 | * s
    Vec2 v0 = s12 - s11;
    Vec2 v1 = s22 - s21;
    Mat2x2 m(v0.vec[0], -v1.vec[0], v0.vec[1], -v1.vec[1]);
    if (!m.invert())
        return false;
    const Vec2 d = s21 - s11;
    const Vec2 s = m * d;
    if (s.vec[0] < 0.0f || s.vec[0] > 1.0f || s.vec[1] < 0.0f || s.vec[1] > 1.0f)
        return false;
    i = v0 * s.vec[0] + s11;
    return true;
}

const gearoenix::math::Vec3 gearoenix::math::Vec3::X(1.0f, 0.0f, 0.0f);
const gearoenix::math::Vec3 gearoenix::math::Vec3::Y(0.0f, 1.0f, 0.0f);
const gearoenix::math::Vec3 gearoenix::math::Vec3::Z(0.0f, 0.0f, 1.0f);

gearoenix::math::Vec3::Vec3() noexcept
    : vec { 0.0f, 0.0f, 0.0f }
{
}

gearoenix::math::Vec3::Vec3(const core::Real e) noexcept
    : vec { e, e, e }
{
}

gearoenix::math::Vec3::Vec3(const core::Real x, const core::Real y, const core::Real z) noexcept
    : vec { x, y, z }
{
}

gearoenix::math::Vec3::Vec3(const math::Vec2& o, const core::Real e) noexcept
    : vec { o[0], o[1], e }
{
}

gearoenix::math::Vec3::Vec3(const Vec3& v) noexcept
    : vec { v.vec[0], v.vec[1], v.vec[2] }
{
}

gearoenix::math::Vec3& gearoenix::math::Vec3::operator=(const Vec3& v) noexcept
{
    vec[0] = v.vec[0];
    vec[1] = v.vec[1];
    vec[2] = v.vec[2];
    return *this;
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator+(const Vec3& a) const noexcept
{
    return Vec3(vec[0] + a.vec[0], vec[1] + a.vec[1], vec[2] + a.vec[2]);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator+(const core::Real a) const noexcept
{
    return Vec3(vec[0] + a, vec[1] + a, vec[2] + a);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator-(const Vec3& a) const noexcept
{
    return Vec3(vec[0] - a.vec[0], vec[1] - a.vec[1], vec[2] - a.vec[2]);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator-(const core::Real a) const noexcept
{
    return Vec3(vec[0] - a, vec[1] - a, vec[2] - a);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator*(const Vec3& a) const noexcept
{
    return Vec3(vec[0] * a.vec[0], vec[1] * a.vec[1], vec[2] * a.vec[2]);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator*(const core::Real a) const noexcept
{
    return Vec3(vec[0] * a, vec[1] * a, vec[2] * a);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator/(const Vec3& a) const noexcept
{
    return Vec3(vec[0] / a.vec[0], vec[1] / a.vec[1], vec[2] / a.vec[2]);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator/(const core::Real a) const noexcept
{
    const core::Real ia = 1.0f / a;
    return Vec3(vec[0] * ia, vec[1] * ia, vec[2] * ia);
}

void gearoenix::math::Vec3::operator+=(const Vec3& a) noexcept
{
    vec[0] += a.vec[0];
    vec[1] += a.vec[1];
    vec[2] += a.vec[2];
}

void gearoenix::math::Vec3::operator-=(const Vec3& a) noexcept
{
    vec[0] -= a.vec[0];
    vec[1] -= a.vec[1];
    vec[2] -= a.vec[2];
}

void gearoenix::math::Vec3::operator*=(const Vec3& a) noexcept
{
    vec[0] *= a.vec[0];
    vec[1] *= a.vec[1];
    vec[2] *= a.vec[2];
}

void gearoenix::math::Vec3::operator/=(const Vec3& a) noexcept
{
    vec[0] /= a.vec[0];
    vec[1] /= a.vec[1];
    vec[2] /= a.vec[2];
}

void gearoenix::math::Vec3::operator*=(const core::Real a) noexcept
{
    vec[0] *= a;
    vec[1] *= a;
    vec[2] *= a;
}

void gearoenix::math::Vec3::operator/=(const core::Real a) noexcept
{
    const core::Real ia = 1.0f / a;
    vec[0] *= ia;
    vec[1] *= ia;
    vec[2] *= ia;
}

const gearoenix::core::Real& gearoenix::math::Vec3::operator[](const unsigned int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 2) {
        GXLOGF("Out of range access")
    }
#endif
    return vec[i];
}

gearoenix::core::Real& gearoenix::math::Vec3::operator[](const unsigned int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 2) {
        GXLOGF("Out of range access")
    }
#endif
    return vec[i];
}

const gearoenix::core::Real& gearoenix::math::Vec3::operator[](const int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 2 || i < 0) {
        GXLOGF("Out of range access")
    }
#endif
    return vec[i];
}

gearoenix::core::Real& gearoenix::math::Vec3::operator[](const int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 2 || i < 0) {
        GXLOGF("Out of range access")
    }
#endif
    return vec[i];
}

bool gearoenix::math::Vec3::operator<(const Vec3& o) const noexcept
{
    if (vec[0] < o.vec[0]) {
        return true;
    }
    if (vec[0] != o.vec[0]) {
        return false;
    }
    if (vec[1] < o.vec[1]) {
        return true;
    }
    if (vec[1] != o.vec[1]) {
        return false;
    }
    return vec[2] < o.vec[2];
}

bool gearoenix::math::Vec3::operator==(const Vec3& o) const noexcept
{
    return vec[0] == o.vec[0] && vec[1] == o.vec[1] && vec[2] == o.vec[2];
}

bool gearoenix::math::Vec3::operator>(const Vec3& o) const noexcept
{
    if (vec[0] > o.vec[0]) {
        return true;
    }
    if (vec[0] != o.vec[0]) {
        return false;
    }
    if (vec[1] > o.vec[1]) {
        return true;
    }
    if (vec[1] != o.vec[1]) {
        return false;
    }
    return vec[2] > o.vec[2];
}

gearoenix::math::Vec2 gearoenix::math::Vec3::xy() const noexcept
{
    return Vec2(vec[0], vec[1]);
}

const gearoenix::core::Real* gearoenix::math::Vec3::data() const noexcept
{
    return vec;
}

gearoenix::math::Vec3 gearoenix::math::Vec3::operator-() const noexcept
{
    return Vec3(-vec[0], -vec[1], -vec[2]);
}

gearoenix::core::Real gearoenix::math::Vec3::length() const noexcept
{
    return sqrtf(square_length());
}

gearoenix::core::Real gearoenix::math::Vec3::square_length() const noexcept
{
    return dot(*this);
}

gearoenix::core::Real gearoenix::math::Vec3::abs_length() const noexcept
{
    return std::abs(vec[0]) + std::abs(vec[1]) + std::abs(vec[2]);
}

gearoenix::core::Real gearoenix::math::Vec3::square_distance(const Vec3& a) const noexcept
{
    core::Real t = a.vec[0] - vec[0];
    t *= t;
    core::Real d = t;
    t = a.vec[1] - vec[1];
    t *= t;
    d += t;
    t = a.vec[2] - vec[2];
    t *= t;
    d += t;
    return d;
}

gearoenix::core::Real gearoenix::math::Vec3::abs_distance(const Vec3& a) const noexcept
{
    return ((*this) - a).abs_length();
}

gearoenix::math::Vec3 gearoenix::math::Vec3::abs() const noexcept
{
    return Vec3(std::abs(vec[0]), std::abs(vec[1]), std::abs(vec[2]));
}

gearoenix::core::Real gearoenix::math::Vec3::dot(const Vec3& o) const noexcept
{
    return (vec[0] * o.vec[0]) + (vec[1] * o.vec[1]) + (vec[2] * o.vec[2]);
}

gearoenix::math::Vec3 gearoenix::math::Vec3::cross(const Vec3& o) const noexcept
{
    return Vec3((vec[1] * o.vec[2]) - (vec[2] * o.vec[1]),
        (vec[2] * o.vec[0]) - (vec[0] * o.vec[2]),
        (vec[0] * o.vec[1]) - (vec[1] * o.vec[0]));
}

gearoenix::math::Vec3 gearoenix::math::Vec3::minimum(const Vec3& o) const noexcept
{
    return Vec3(
        o[0] < vec[0] ? o[0] : vec[0],
        o[1] < vec[1] ? o[1] : vec[1],
        o[2] < vec[2] ? o[2] : vec[2]);
}

gearoenix::core::Real gearoenix::math::Vec3::minimum() const noexcept
{
    return GX_MIN(vec[0], GX_MIN(vec[1], vec[2]));
}

gearoenix::math::Vec3 gearoenix::math::Vec3::maximum(const Vec3& o) const noexcept
{
    return Vec3(
        o[0] > vec[0] ? o[0] : vec[0],
        o[1] > vec[1] ? o[1] : vec[1],
        o[2] > vec[2] ? o[2] : vec[2]);
}

gearoenix::core::Real gearoenix::math::Vec3::maximum() const noexcept
{
    return GX_MAX(vec[0], GX_MAX(vec[1], vec[2]));
}

gearoenix::math::Vec3 gearoenix::math::Vec3::normalized() const noexcept
{
    const auto ilen = 1.0f / length();
    return *this * ilen;
}

void gearoenix::math::Vec3::normalize() noexcept
{
    const auto l = 1.0f / length();
    vec[0] *= l;
    vec[1] *= l;
    vec[2] *= l;
}

void gearoenix::math::Vec3::read(system::stream::Stream* const f) noexcept
{
    f->read(vec[0]);
    f->read(vec[1]);
    f->read(vec[2]);
}

const gearoenix::math::Vec4 gearoenix::math::Vec4::X(1.0f, 0.0f, 0.0f, 0.0f);
const gearoenix::math::Vec4 gearoenix::math::Vec4::Y(0.0f, 1.0f, 0.0f, 0.0f);
const gearoenix::math::Vec4 gearoenix::math::Vec4::Z(0.0f, 0.0f, 1.0f, 0.0f);

gearoenix::math::Vec4::Vec4() noexcept
    : vec { 0.0f, 0.0f, 0.0f, 1.0f }
{
}

gearoenix::math::Vec4::Vec4(const core::Real x, const core::Real y, const core::Real z, const core::Real w) noexcept
    : vec { x, y, z, w }
{
}

gearoenix::math::Vec4::Vec4(const Vec2& v, const core::Real z, const core::Real w) noexcept
    : vec { v[0], v[1], z, w }
{
}

gearoenix::math::Vec4::Vec4(const core::Real e) noexcept
    : vec { e, e, e, e }
{
}

gearoenix::math::Vec4::Vec4(const Vec3& v, const core::Real w) noexcept
    : vec { v[0], v[1], v[2], w }
{
}

gearoenix::math::Vec3 gearoenix::math::Vec4::xyz() const noexcept
{
    return Vec3(vec[0], vec[1], vec[2]);
}

void gearoenix::math::Vec4::xyz(const Vec3& v) noexcept
{
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];
}

gearoenix::core::Real gearoenix::math::Vec4::w() const noexcept
{
    return vec[3];
}

void gearoenix::math::Vec4::w(core::Real e) noexcept
{
    vec[3] = e;
}

const gearoenix::core::Real& gearoenix::math::Vec4::operator[](const unsigned int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 3)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

gearoenix::core::Real& gearoenix::math::Vec4::operator[](const unsigned int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 3)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

const gearoenix::core::Real& gearoenix::math::Vec4::operator[](const int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 3 || i < 0)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

gearoenix::core::Real& gearoenix::math::Vec4::operator[](const int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 3 || i < 0)
        GXLOGF("Out of range access")
#endif
    return vec[i];
}

bool gearoenix::math::Vec4::operator<(const Vec4& o) const noexcept
{
    if (vec[0] < o.vec[0]) {
        return true;
    }
    if (vec[0] != o.vec[0]) {
        return false;
    }
    if (vec[1] < o.vec[1]) {
        return true;
    }
    if (vec[1] != o.vec[1]) {
        return false;
    }
    if (vec[2] < o.vec[2]) {
        return true;
    }
    if (vec[2] != o.vec[2]) {
        return false;
    }
    return vec[3] < o.vec[3];
}

bool gearoenix::math::Vec4::operator==(const Vec4& o) const noexcept
{
    return vec[0] == o.vec[0] && vec[1] == o.vec[1] && vec[2] == o.vec[2] && vec[3] == o.vec[3];
}

bool gearoenix::math::Vec4::operator>(const Vec4& o) const noexcept
{
    if (vec[0] > o.vec[0]) {
        return true;
    }
    if (vec[0] != o.vec[0]) {
        return false;
    }
    if (vec[1] > o.vec[1]) {
        return true;
    }
    if (vec[1] != o.vec[1]) {
        return false;
    }
    if (vec[2] > o.vec[2]) {
        return true;
    }
    if (vec[2] != o.vec[2]) {
        return false;
    }
    return vec[3] > o.vec[3];
}

gearoenix::math::Vec4 gearoenix::math::Vec4::operator*(const core::Real a) const noexcept
{
    return Vec4(vec[0] * a, vec[1] * a, vec[2] * a, vec[3] * a);
}

gearoenix::math::Vec4 gearoenix::math::Vec4::operator-(const Vec4& a) const noexcept
{
    return Vec4(vec[0] - a.vec[0], vec[1] - a.vec[1], vec[2] - a.vec[2], vec[3] - a.vec[3]);
}

gearoenix::core::Real gearoenix::math::Vec4::length() const noexcept
{
    return sqrtf(square_length());
}

gearoenix::core::Real gearoenix::math::Vec4::square_length() const noexcept
{
    return dot(*this);
}

gearoenix::core::Real gearoenix::math::Vec4::dot(const Vec4& o) const noexcept
{
    return (vec[0] * o.vec[0]) + (vec[1] * o.vec[1]) + (vec[2] * o.vec[2]) + (vec[3] * o.vec[3]);
}

gearoenix::math::Vec4 gearoenix::math::Vec4::cross(const Vec4& o) const noexcept
{
    return Vec4((vec[1] * o.vec[2]) - (vec[2] * o.vec[1]),
        (vec[2] * o.vec[0]) - (vec[0] * o.vec[2]),
        (vec[0] * o.vec[1]) - (vec[1] * o.vec[0]),
        vec[3] * o.vec[3]);
}

gearoenix::math::Vec4 gearoenix::math::Vec4::normalized() const noexcept
{
    const auto ilen = 1.0f / length();
    return *this * ilen;
}

void gearoenix::math::Vec4::normalize() noexcept
{
    const auto ilen = 1.0f / length();
    vec[0] *= ilen;
    vec[1] *= ilen;
    vec[2] *= ilen;
    vec[3] *= ilen;
}

void gearoenix::math::Vec4::read(system::stream::Stream* const f) noexcept
{
    f->read(vec[0]);
    f->read(vec[1]);
    f->read(vec[2]);
    f->read(vec[3]);
}

const gearoenix::core::Real* gearoenix::math::Vec4::data() const noexcept
{
    return vec;
}