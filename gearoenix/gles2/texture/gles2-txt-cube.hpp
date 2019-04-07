#ifndef GEAROENIX_OPENGL_TEXTURE_CUBE_HPP
#define GEAROENIX_OPENGL_TEXTURE_CUBE_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../gl/gl-types.hpp"
#include "../../render/texture/rnd-txt-texture-cube.hpp"
#include <memory>
namespace gearoenix {
namespace system {
    class File;
}
namespace gles2 {
    namespace engine {
        class Engine;
    }
    namespace texture {
        class Cube : public render::texture::Cube {
        private:
            gl::uint texture_object;

        public:
            Cube(
                const core::Id my_id,
                const std::shared_ptr<system::stream::Stream>& file,
                const std::shared_ptr<engine::Engine>& engine,
                core::sync::EndCaller<core::sync::EndCallerIgnore> end);
            ~Cube();
            void bind(gl::enumerated texture_unit);
        };
    }
}
}
#endif
#endif
