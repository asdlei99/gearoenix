#include "math-matrix.hpp"
#include "../core/cr-build-configuration.hpp"
#include "../system/stream/sys-stm-stream.hpp"
#include "../system/sys-log.hpp"
#include "math-vector.hpp"
#include <cmath>

gearoenix::math::Mat2x2::Mat2x2() noexcept
    : mat { 1.0f, 0.0f, 0.0f, 1.0f }
{
}

gearoenix::math::Mat2x2::Mat2x2(const core::Real dia_e) noexcept
    : mat { dia_e, 0.0f, 0.0f, dia_e }
{
}

gearoenix::math::Mat2x2::Mat2x2(
    const core::Real e0, const core::Real e1,
    const core::Real e2, const core::Real e3) noexcept
    : mat { e0, e1, e2, e3 }
{
}

bool gearoenix::math::Mat2x2::invert() noexcept
{
    const core::Real det = mat[0] * mat[3] - mat[1] * mat[2];
    if (det < GXPOSEPSILON && det > GXNEGEPSILON)
        return false;
    const core::Real tmp = mat[0];
    mat[0] = mat[3];
    mat[3] = tmp;
    mat[1] = -mat[1];
    mat[2] = -mat[2];
    const core::Real tmp1 = 1.0f / det;
    mat[0] *= tmp1;
    mat[1] *= tmp1;
    mat[2] *= tmp1;
    mat[3] *= tmp1;
    return true;
}

gearoenix::math::Vec2 gearoenix::math::Mat2x2::operator*(const Vec2& v) const noexcept
{
    return Vec2(mat[0] * v[0] + mat[1] * v[1], mat[2] * v[0] + mat[3] * v[1]);
}

gearoenix::math::Mat4x4::Mat4x4(const core::Real e) noexcept
    : mat { e,
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        e,
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        e,
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        1.0f }
{
}

gearoenix::math::Mat4x4::Mat4x4() noexcept
    : mat {
        core::Real(1),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(1),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(1),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(0),
        core::Real(1)
    }
{
}

gearoenix::math::Mat4x4::Mat4x4(
    core::Real e0, core::Real e1, core::Real e2, core::Real e3,
    core::Real e4, core::Real e5, core::Real e6, core::Real e7,
    core::Real e8, core::Real e9, core::Real e10, core::Real e11,
    core::Real e12, core::Real e13, core::Real e14, core::Real e15) noexcept
    : mat {
        e0,
        e1,
        e2,
        e3,
        e4,
        e5,
        e6,
        e7,
        e8,
        e9,
        e10,
        e11,
        e12,
        e13,
        e14,
        e15
    }
{
}

gearoenix::math::Mat4x4::Mat4x4(system::stream::Stream* const f) noexcept
    : mat {}
{
    read(f);
}

gearoenix::math::Mat4x4::Mat4x4(const Mat4x4& m) noexcept
    : mat {}
{
    for (int i = 0; i < 16; i++) {
        mat[i] = m.mat[i];
    }
}

gearoenix::math::Vec4 gearoenix::math::Mat4x4::operator*(const Vec4& v) const noexcept
{
    return Vec4(
        mat[0] * v[0] + mat[4] * v[1] + mat[8] * v[2] + mat[12] * v[3],
        mat[1] * v[0] + mat[5] * v[1] + mat[9] * v[2] + mat[13] * v[3],
        mat[2] * v[0] + mat[6] * v[1] + mat[10] * v[2] + mat[14] * v[3],
        mat[3] * v[0] + mat[7] * v[1] + mat[11] * v[2] + mat[15] * v[3]);
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::operator*(const Mat4x4& m) const noexcept
{
    Mat4x4 r;
    for (int i = 0, ri = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; j++, ri++) {
            r.mat[ri] = m.mat[i] * mat[j] + m.mat[i + 1] * mat[j + 4] + m.mat[i + 2] * mat[j + 8] + m.mat[i + 3] * mat[j + 12];
        }
    }
    return r;
}

gearoenix::math::Mat4x4& gearoenix::math::Mat4x4::operator=(const Mat4x4& m) noexcept
{
    for (int i = 0; i < 16; i++) {
        mat[i] = m.mat[i];
    }
    return *this;
}

void gearoenix::math::Mat4x4::operator*=(const Mat4x4& m) noexcept
{
    Mat4x4 r;
    for (int i = 0, ri = 0; i < 16; i += 4) {
        for (int j = 0; j < 4; j++, ri++) {
            r.mat[ri] = m.mat[i] * mat[j] + m.mat[i + 1] * mat[j + 4] + m.mat[i + 2] * mat[j + 8] + m.mat[i + 3] * mat[j + 12];
        }
    }
    for (int i = 0; i < 16; ++i) {
        mat[i] = r.mat[i];
    }
}

const gearoenix::core::Real& gearoenix::math::Mat4x4::operator[](const unsigned int i) const noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 15) {
        GXUNEXPECTED;
    }
#endif
    return mat[i];
}

gearoenix::core::Real& gearoenix::math::Mat4x4::operator[](const unsigned int i) noexcept
{
#ifdef GX_DEBUG_MODE
    if (i > 15) {
        GXUNEXPECTED;
    }
#endif
    return mat[i];
}

void gearoenix::math::Mat4x4::local_scale(const core::Real s) noexcept
{
    local_scale(s, s, s);
}

void gearoenix::math::Mat4x4::local_x_scale(core::Real s) noexcept
{
    mat[0] *= s;
    mat[1] *= s;
    mat[2] *= s;
    mat[3] *= s;
}

void gearoenix::math::Mat4x4::local_y_scale(core::Real s) noexcept
{
    mat[4] *= s;
    mat[5] *= s;
    mat[6] *= s;
    mat[7] *= s;
}

void gearoenix::math::Mat4x4::local_z_scale(core::Real s) noexcept
{
    mat[8] *= s;
    mat[9] *= s;
    mat[10] *= s;
    mat[11] *= s;
}

void gearoenix::math::Mat4x4::local_w_scale(core::Real s) noexcept
{
    mat[12] *= s;
    mat[13] *= s;
    mat[14] *= s;
    mat[15] *= s;
}

void gearoenix::math::Mat4x4::local_scale(const core::Real a, const core::Real b, const core::Real c) noexcept
{
    local_x_scale(a);
    local_y_scale(b);
    local_z_scale(c);
}

void gearoenix::math::Mat4x4::local_scale(const core::Real a, const core::Real b, const core::Real c, const core::Real d) noexcept
{
    local_scale(a, b, c);
    local_w_scale(d);
}

void gearoenix::math::Mat4x4::local_scale(const Vec3& s) noexcept
{
    local_scale(s[0], s[1], s[2]);
}

void gearoenix::math::Mat4x4::local_scale(const Vec4& s) noexcept
{
    local_scale(s[0], s[1], s[2], s[3]);
}

/// TODO: make global scale as clean as local scale

void gearoenix::math::Mat4x4::global_scale(const core::Real s) noexcept
{
    mat[0] *= s;
    mat[1] *= s;
    mat[2] *= s;
    mat[4] *= s;
    mat[5] *= s;
    mat[6] *= s;
    mat[8] *= s;
    mat[9] *= s;
    mat[10] *= s;
    mat[12] *= s;
    mat[13] *= s;
    mat[14] *= s;
}

void gearoenix::math::Mat4x4::global_scale(const core::Real a, const core::Real b, const core::Real c) noexcept
{
    mat[0] *= a;
    mat[4] *= a;
    mat[8] *= a;
    mat[12] *= a;

    mat[1] *= b;
    mat[5] *= b;
    mat[9] *= b;
    mat[13] *= b;

    mat[2] *= c;
    mat[6] *= c;
    mat[10] *= c;
    mat[14] *= c;
}

void gearoenix::math::Mat4x4::global_scale(const core::Real a, const core::Real b, const core::Real c, const core::Real d) noexcept
{
    mat[0] *= a;
    mat[4] *= a;
    mat[8] *= a;
    mat[12] *= a;

    mat[1] *= b;
    mat[5] *= b;
    mat[9] *= b;
    mat[13] *= b;

    mat[2] *= c;
    mat[6] *= c;
    mat[10] *= c;
    mat[14] *= c;

    mat[3] *= d;
    mat[7] *= d;
    mat[11] *= d;
    mat[15] *= d;
}

void gearoenix::math::Mat4x4::global_scale(const Vec3& s) noexcept
{
    global_scale(s[0], s[1], s[2]);
}

void gearoenix::math::Mat4x4::global_scale(const Vec4& s) noexcept
{
    global_scale(s[0], s[1], s[2], s[4]);
}

void gearoenix::math::Mat4x4::translate(const Vec3& v) noexcept
{
    mat[12] += v[0];
    mat[13] += v[1];
    mat[14] += v[2];
}

gearoenix::core::Real gearoenix::math::Mat4x4::determinant() const noexcept
{
    return (+mat[0] * (+mat[5] * (mat[10] * mat[15] - mat[11] * mat[14]) - mat[9] * (mat[6] * mat[15] - mat[7] * mat[14]) + mat[13] * (mat[6] * mat[11] - mat[7] * mat[10]))
        - mat[4] * (+mat[1] * (mat[10] * mat[15] - mat[11] * mat[14]) - mat[9] * (mat[2] * mat[15] - mat[3] * mat[14]) + mat[13] * (mat[2] * mat[11] - mat[3] * mat[10]))
        + mat[8] * (+mat[1] * (mat[6] * mat[15] - mat[7] * mat[14]) - mat[5] * (mat[2] * mat[15] - mat[3] * mat[14]) + mat[13] * (mat[2] * mat[7] - mat[3] * mat[6]))
        - mat[12] * (+mat[1] * (mat[6] * mat[11] - mat[7] * mat[10]) - mat[5] * (mat[2] * mat[11] - mat[3] * mat[10]) + mat[9] * (mat[2] * mat[7] - mat[3] * mat[6])));
}

void gearoenix::math::Mat4x4::set_location_zero() noexcept
{
    mat[12] = core::Real(0);
    mat[13] = core::Real(0);
    mat[14] = core::Real(0);
}

void gearoenix::math::Mat4x4::set_location(const Vec3& location) noexcept
{
    mat[12] = location[0];
    mat[13] = location[1];
    mat[14] = location[2];
}

void gearoenix::math::Mat4x4::get_location(Vec3& location) const noexcept
{
    location[0] = mat[12];
    location[1] = mat[13];
    location[2] = mat[14];
}

void gearoenix::math::Mat4x4::read(system::stream::Stream* const f) noexcept
{
    for (core::Real& i : mat)
        f->read(i);
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::inverted() const noexcept
{
    core::Real id = 1.0f / determinant();
    Mat4x4 result;
    result.mat[0] = id * (+mat[5] * (mat[10] * mat[15] - mat[11] * mat[14]) - mat[9] * (mat[6] * mat[15] - mat[7] * mat[14]) + mat[13] * (mat[6] * mat[11] - mat[7] * mat[10]));
    result.mat[1] = id * -(+mat[1] * (mat[10] * mat[15] - mat[11] * mat[14]) - mat[9] * (mat[2] * mat[15] - mat[3] * mat[14]) + mat[13] * (mat[2] * mat[11] - mat[3] * mat[10]));
    result.mat[2] = id * (+mat[1] * (mat[6] * mat[15] - mat[7] * mat[14]) - mat[5] * (mat[2] * mat[15] - mat[3] * mat[14]) + mat[13] * (mat[2] * mat[7] - mat[3] * mat[6]));
    result.mat[3] = id * -(+mat[1] * (mat[6] * mat[11] - mat[7] * mat[10]) - mat[5] * (mat[2] * mat[11] - mat[3] * mat[10]) + mat[9] * (mat[2] * mat[7] - mat[3] * mat[6]));
    result.mat[4] = id * -(+mat[4] * (mat[10] * mat[15] - mat[11] * mat[14]) - mat[8] * (mat[6] * mat[15] - mat[7] * mat[14]) + mat[12] * (mat[6] * mat[11] - mat[7] * mat[10]));
    result.mat[5] = id * (+mat[0] * (mat[10] * mat[15] - mat[11] * mat[14]) - mat[8] * (mat[2] * mat[15] - mat[3] * mat[14]) + mat[12] * (mat[2] * mat[11] - mat[3] * mat[10]));
    result.mat[6] = id * -(+mat[0] * (mat[6] * mat[15] - mat[7] * mat[14]) - mat[4] * (mat[2] * mat[15] - mat[3] * mat[14]) + mat[12] * (mat[2] * mat[7] - mat[3] * mat[6]));
    result.mat[7] = id * (+mat[0] * (mat[6] * mat[11] - mat[7] * mat[10]) - mat[4] * (mat[2] * mat[11] - mat[3] * mat[10]) + mat[8] * (mat[2] * mat[7] - mat[3] * mat[6]));
    result.mat[8] = id * (+mat[4] * (mat[9] * mat[15] - mat[11] * mat[13]) - mat[8] * (mat[5] * mat[15] - mat[7] * mat[13]) + mat[12] * (mat[5] * mat[11] - mat[7] * mat[9]));
    result.mat[9] = id * -(+mat[0] * (mat[9] * mat[15] - mat[11] * mat[13]) - mat[8] * (mat[1] * mat[15] - mat[3] * mat[13]) + mat[12] * (mat[1] * mat[11] - mat[3] * mat[9]));
    result.mat[10] = id * (+mat[0] * (mat[5] * mat[15] - mat[7] * mat[13]) - mat[4] * (mat[1] * mat[15] - mat[3] * mat[13]) + mat[12] * (mat[1] * mat[7] - mat[3] * mat[5]));
    result.mat[11] = id * -(+mat[0] * (mat[5] * mat[11] - mat[7] * mat[9]) - mat[4] * (mat[1] * mat[11] - mat[3] * mat[9]) + mat[8] * (mat[1] * mat[7] - mat[3] * mat[5]));
    result.mat[12] = id * -(+mat[4] * (mat[9] * mat[14] - mat[10] * mat[13]) - mat[8] * (mat[5] * mat[14] - mat[6] * mat[13]) + mat[12] * (mat[5] * mat[10] - mat[6] * mat[9]));
    result.mat[13] = id * (+mat[0] * (mat[9] * mat[14] - mat[10] * mat[13]) - mat[8] * (mat[1] * mat[14] - mat[2] * mat[13]) + mat[12] * (mat[1] * mat[10] - mat[2] * mat[9]));
    result.mat[14] = id * -(+mat[0] * (mat[5] * mat[14] - mat[6] * mat[13]) - mat[4] * (mat[1] * mat[14] - mat[2] * mat[13]) + mat[12] * (mat[1] * mat[6] - mat[2] * mat[5]));
    result.mat[15] = id * (+mat[0] * (mat[5] * mat[10] - mat[6] * mat[9]) - mat[4] * (mat[1] * mat[10] - mat[2] * mat[9]) + mat[8] * (mat[1] * mat[6] - mat[2] * mat[5]));
    return result;
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::look_at(const Vec3& position, const Vec3& target, const Vec3& up) noexcept
{
    Vec3 z = (target - position).normalized();
    Vec3 x = up.cross(z).normalized();
    Vec3 y = z.cross(x);
    Mat4x4 m;
    m.mat[0] = -(x[0]);
    m.mat[1] = y[0];
    m.mat[2] = -z[0];
    m.mat[3] = core::Real(0.0);
    m.mat[4] = -x[1];
    m.mat[5] = y[1];
    m.mat[6] = -z[1];
    m.mat[7] = core::Real(0.0);
    m.mat[8] = -x[2];
    m.mat[9] = y[2];
    m.mat[10] = -z[2];
    m.mat[11] = core::Real(0.0);
    m.mat[12] = x.dot(position);
    m.mat[13] = -(y.dot(position));
    m.mat[14] = z.dot(position);
    m.mat[15] = core::Real(1.0);
    return m;
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::rotation(const Vec3& v, const core::Real degree) noexcept
{
    const auto sinus = static_cast<core::Real>(sin(static_cast<double>(degree)));
    const auto cosinus = static_cast<core::Real>(cos(static_cast<double>(degree)));
    const core::Real oneminuscos = 1.0f - cosinus;
    const Vec3 w = v.normalized();
    const core::Real wx2 = w[0] * w[0];
    const core::Real wxy = w[0] * w[1];
    const core::Real wxz = w[0] * w[2];
    const core::Real wy2 = w[1] * w[1];
    const core::Real wyz = w[1] * w[2];
    const core::Real wz2 = w[2] * w[2];
    const core::Real wxyonemincos = wxy * oneminuscos;
    const core::Real wxzonemincos = wxz * oneminuscos;
    const core::Real wyzonemincos = wyz * oneminuscos;
    const core::Real wxsin = w[0] * sinus;
    const core::Real wysin = w[1] * sinus;
    const core::Real wzsin = w[2] * sinus;
    Mat4x4 m;
    m.mat[0] = cosinus + (wx2 * oneminuscos);
    m.mat[1] = wzsin + wxyonemincos;
    m.mat[2] = wxzonemincos - wysin;
    m.mat[3] = core::Real(0.0);
    m.mat[4] = wxyonemincos - wzsin;
    m.mat[5] = cosinus + (wy2 * oneminuscos);
    m.mat[6] = wxsin + wyzonemincos;
    m.mat[7] = core::Real(0.0);
    m.mat[8] = wysin + wxzonemincos;
    m.mat[9] = wyzonemincos - wxsin;
    m.mat[10] = cosinus + (wz2 * oneminuscos);
    m.mat[11] = core::Real(0.0);
    m.mat[12] = core::Real(0.0);
    m.mat[13] = core::Real(0.0);
    m.mat[14] = core::Real(0.0);
    m.mat[15] = core::Real(1.0);
    return m;
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::translator(const Vec3& v) noexcept
{
    Mat4x4 r;
    r.mat[0] = core::Real(1);
    r.mat[1] = core::Real(0);
    r.mat[2] = core::Real(0);
    r.mat[3] = core::Real(0);
    r.mat[4] = core::Real(0);
    r.mat[5] = core::Real(1);
    r.mat[6] = core::Real(0);
    r.mat[7] = core::Real(0);
    r.mat[8] = core::Real(0);
    r.mat[9] = core::Real(0);
    r.mat[10] = core::Real(1);
    r.mat[11] = core::Real(0);
    r.mat[12] = v[0];
    r.mat[13] = v[1];
    r.mat[14] = v[2];
    r.mat[15] = core::Real(1);
    return r;
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::orthographic(const core::Real width, const core::Real height, const core::Real near, const core::Real far) noexcept
{
    Mat4x4 r;
    r.mat[0] = core::Real(2.0f / width);
    r.mat[1] = core::Real(0.0);
    r.mat[2] = core::Real(0.0);
    r.mat[3] = core::Real(0.0);
    r.mat[4] = core::Real(0.0);
    r.mat[5] = core::Real(2.0f / height);
    r.mat[6] = core::Real(0.0);
    r.mat[7] = core::Real(0.0);
    r.mat[8] = core::Real(0.0);
    r.mat[9] = core::Real(0.0);
    r.mat[10] = core::Real(2.0f / (near - far));
    r.mat[11] = core::Real(0.0);
    r.mat[12] = core::Real(0.0);
    r.mat[13] = core::Real(0.0);
    r.mat[14] = core::Real((far + near) / (near - far));
    r.mat[15] = core::Real(1.0);
    return r;
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::perspective(const core::Real width, const core::Real height, const core::Real near, const core::Real far) noexcept
{
    Mat4x4 r;
    r.mat[0] = core::Real((2.0f * near) / width);
    r.mat[1] = core::Real(0.0);
    r.mat[2] = core::Real(0.0);
    r.mat[3] = core::Real(0.0);
    r.mat[4] = core::Real(0.0);
    r.mat[5] = core::Real((2.0f * near) / height);
    r.mat[6] = core::Real(0.0);
    r.mat[7] = core::Real(0.0);
    r.mat[8] = core::Real(0.0);
    r.mat[9] = core::Real(0.0);
    r.mat[10] = core::Real((far + near) / (near - far));
    r.mat[11] = core::Real(-1.0);
    r.mat[12] = core::Real(0.0);
    r.mat[13] = core::Real(0.0);
    r.mat[14] = core::Real((2.0f * far * near) / (near - far));
    r.mat[15] = core::Real(0.0);
    return r;
}

gearoenix::math::Mat4x4 gearoenix::math::Mat4x4::transposed() const noexcept
{
    Mat4x4 r;
    for (unsigned int i = 0; i < 16; ++i) {
        r.mat[((i & 3u) << 2) + (i >> 2)] = mat[i];
    }
    return r;
}

const gearoenix::core::Real* gearoenix::math::Mat4x4::data() const noexcept
{
    return mat;
}

gearoenix::math::Vec3 gearoenix::math::Mat4x4::project(const Vec3& v) const noexcept
{
    Vec4 v4(v, 1.0f);
    v4 = (*this) * v4;
    return v4.xyz() / v4[3];
}
