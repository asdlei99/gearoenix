#include "rnd-cmr-transformation.hpp"
#include "rnd-cmr-uniform.hpp"


gearoenix::render::camera::Transformation::Transformation(const std::shared_ptr<Uniform> &uniform) noexcept : uniform(uniform) {}

gearoenix::render::camera::Transformation::~Transformation()  noexcept {}

void gearoenix::render::camera::Transformation::update_location() noexcept
{
	math::Mat4x4 translate = math::Mat4x4::translator(-(uniform->position));
	uniform->view = uniform->inversed_rotation * translate;
	update_view_projection();
}

void gearoenix::render::camera::Transformation::update_view_projection() noexcept
{
	uniform->view_projection = uniform->projection * uniform->view;
	uniform->uniform_view_projection = math::Mat4x4(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.0f, 1.0f)
		* uniform->view_projection;
}

void gearoenix::render::camera::Transformation::look_at(const math::Vec3& target, const math::Vec3& up) noexcept
{
	look_at(uniform->position, target, up);
}

void gearoenix::render::camera::Transformation::look_at(const math::Vec3 & origin, const math::Vec3 & target, const math::Vec3 & up) noexcept
{
	uniform->position = origin;
	uniform->z = (origin - target).normalized();
	uniform->x = up.cross(uniform->z);
	uniform->y = uniform->z.cross(uniform->x);
	uniform->view = math::Mat4x4::look_at(uniform->position, target, uniform->y);
	uniform->inversed_rotation = uniform->view * math::Mat4x4::translator(uniform->position);
	update_view_projection();
}

const gearoenix::math::Vec3& gearoenix::render::camera::Transformation::get_x_axis() const noexcept
{
	return uniform->x;
}

const gearoenix::math::Vec3& gearoenix::render::camera::Transformation::get_y_axis() const noexcept
{
	return uniform->y;
}

const gearoenix::math::Vec3& gearoenix::render::camera::Transformation::get_z_axis() const noexcept
{
	return uniform->z;
}

const gearoenix::math::Vec3& gearoenix::render::camera::Transformation::get_location() const noexcept
{
	return uniform->position;
}

void gearoenix::render::camera::Transformation::get_location(math::Vec3& l) const noexcept
{
	l = uniform->position;
}

void gearoenix::render::camera::Transformation::set_location(const math::Vec3& l) noexcept
{
	uniform->position = l;
	update_location();
}

void gearoenix::render::camera::Transformation::translate(const math::Vec3& vec) noexcept
{
	uniform->position += vec;
	update_location();
}

void gearoenix::render::camera::Transformation::local_x_translate(const core::Real t) noexcept
{
	uniform->position += uniform->x * t;
	update_location();
}

void gearoenix::render::camera::Transformation::local_y_translate(const core::Real t) noexcept
{
	uniform->position += uniform->y * t;
	update_location();
}

void gearoenix::render::camera::Transformation::local_z_translate(const core::Real t) noexcept
{
	uniform->position += uniform->z * t;
	update_location();
}

void gearoenix::render::camera::Transformation::global_rotate(const core::Real rad, const math::Vec3& axis, const math::Vec3& location) noexcept
{
	math::Mat4x4 rot = math::Mat4x4::rotation(axis, -rad);
	math::Mat4x4 irot = math::Mat4x4::rotation(axis, rad);
	uniform->x = irot * uniform->x;
	uniform->y = irot * uniform->y;
	uniform->z = irot * uniform->z;
	uniform->position = (irot * (uniform->position - location)) + location;
	uniform->inversed_rotation *= rot;
	update_location();
}

void gearoenix::render::camera::Transformation::global_rotate(const core::Real rad, const math::Vec3 & axis) noexcept
{
	global_rotate(rad, axis, math::Vec3(0.0f, 0.0f, 0.0f));
}

void gearoenix::render::camera::Transformation::local_rotate(const core::Real rad, const math::Vec3& vec) noexcept
{
	math::Mat4x4 rot = math::Mat4x4::rotation(vec, -rad);
	math::Mat4x4 irot = math::Mat4x4::rotation(vec, rad);
	uniform->x = irot * uniform->x;
	uniform->y = irot * uniform->y;
	uniform->z = irot * uniform->z;
	uniform->inversed_rotation *= rot;
	update_location();
}

void gearoenix::render::camera::Transformation::local_x_rotate(const core::Real rad) noexcept
{
	math::Mat4x4 rot = math::Mat4x4::rotation(uniform->x, -rad);
	math::Mat4x4 irot = math::Mat4x4::rotation(uniform->x, rad);
	uniform->y = irot * uniform->y;
	uniform->z = irot * uniform->z;
	uniform->inversed_rotation *= rot;
	update_location();
}

void gearoenix::render::camera::Transformation::local_y_rotate(const core::Real rad) noexcept
{
	math::Mat4x4 rot = math::Mat4x4::rotation(uniform->y, -rad);
	math::Mat4x4 irot = math::Mat4x4::rotation(uniform->y, rad);
	uniform->x = irot * uniform->x;
	uniform->z = irot * uniform->z;
	uniform->inversed_rotation *= rot;
	update_location();
}

void gearoenix::render::camera::Transformation::local_z_rotate(const core::Real rad) noexcept
{
	math::Mat4x4 rot = math::Mat4x4::rotation(uniform->z, -rad);
	math::Mat4x4 irot = math::Mat4x4::rotation(uniform->z, rad);
	uniform->x = irot * uniform->x;
	uniform->y = irot * uniform->y;
	uniform->inversed_rotation *= rot;
	update_location();
}

void gearoenix::render::camera::Transformation::set_orientation(const math::Quat & q) noexcept
{
	const math::Mat4x4 r = q.to_mat();
	uniform->x = r * uniform->x;
	uniform->y = r * uniform->y;
	uniform->z = r * uniform->z;
	uniform->inversed_rotation = math::Quat(q.x, q.y, q.z, -q.w).to_mat();
	update_location();
}