#ifndef GEAROENIX_GLC3_COMMAND_BUFFER_HPP
#define GEAROENIX_GLC3_COMMAND_BUFFER_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef GX_USE_OPENGL_CLASS_3
#include "../../gl/gl-types.hpp"
#include "../../render/command/rnd-cmd-buffer.hpp"

namespace gearoenix::glc3::command {
class Buffer : public render::command::Buffer {
public:
    ~Buffer() noexcept final = default;
    gl::uint play(gl::uint bound_shader_program = static_cast<gl::uint>(-1)) const noexcept;
};
}
#endif
#endif