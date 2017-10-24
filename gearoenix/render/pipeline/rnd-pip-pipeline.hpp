#ifndef GEAROENIX_RENDER_PIPELINE_PIPELINE_HPP
#define GEAROENIX_RENDER_PIPELINE_PIPELINE_HPP
#include "../../core/cache/cr-cache-cached.hpp"
#include "../../core/cr-types.hpp"
#include <memory>
namespace gearoenix {
namespace core {
    class EndCaller;
}
namespace render {
    class Engine;
    namespace shader {
        class Shader;
    }
    namespace pipeline {
        class Pipeline : public core::cache::Cached {
        protected:
            Engine* eng;
            std::shared_ptr<shader::Shader> shd;

        public:
            Pipeline(core::Id sid, Engine* eng, std::shared_ptr<gearoenix::core::EndCaller> call);
            virtual ~Pipeline();
            virtual void bind() = 0;
            shader::Shader* get_shader();
        };
    }
}
}
#endif // GEAROENIX_RENDER_PIPELINE_PIPELINE_HPP
