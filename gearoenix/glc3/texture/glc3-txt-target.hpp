#ifndef GEAROENIX_GLC3_TEXTURE_TARGET_HPP
#define GEAROENIX_GLC3_TEXTURE_TARGET_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef GX_USE_OPENGL_CLASS_3
#include "../../core/sync/cr-sync-end-caller.hpp"
#include "../../gl/gl-types.hpp"
#include "../../render/texture/rnd-txt-info.hpp"
#include "../../render/texture/rnd-txt-target.hpp"
#include <vector>

namespace gearoenix::glc3 {
namespace engine {
    class Engine;
}
namespace texture {
    class Target : public render::texture::Target {
    private:
        std::vector<gl::uint> texture_objects;
        gl::sint framebuffer = -1;
        gl::sint depth_buffer = -1;

        void state_init() const noexcept;

        Target(core::Id my_id, engine::Engine* e) noexcept;

    public:
        explicit Target(engine::Engine* e) noexcept;
        ~Target() noexcept final;
        [[nodiscard]] static std::shared_ptr<Target> construct(
            core::Id my_id,
            engine::Engine* e,
            const std::vector<render::texture::Info>& infos,
            unsigned int width,
            unsigned int heigt,
            const core::sync::EndCaller<core::sync::EndCallerIgnore>& call) noexcept;
        void bind() const noexcept;
        void bind_textures(const std::vector<gl::enumerated>& texture_units) const noexcept;
    };
}
}
#endif
#endif
