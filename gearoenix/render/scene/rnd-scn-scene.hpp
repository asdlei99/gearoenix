#ifndef GEAROEMIX_RENDER_SCENE_SCENE_HPP
#define GEAROEMIX_RENDER_SCENE_SCENE_HPP
#include "../../core/asset/cr-asset.hpp"
#include "../../math/math-vector.hpp"
#include <memory>
#include <vector>

namespace gearoenix {
namespace audio {
    class Audio;
}
namespace core {
    class EndCaller;
}
namespace system {
    class File;
}
namespace render {
    class Engine;
    namespace camera {
        class Camera;
    }
    namespace light {
        class Light;
        class Sun;
    }
    namespace model {
        class Model;
    }
    namespace scene {
        class Scene : public core::asset::Asset {
        private:
            std::vector<std::shared_ptr<camera::Camera>> cameras;
            std::vector<std::shared_ptr<audio::Audio>> audios;
            std::vector<std::shared_ptr<light::Light>> lights;
            std::vector<std::shared_ptr<model::Model>> models;
            Engine* e;
            unsigned int curcam = 0;
            bool renderable = false;
            math::Vec3 ambient_light = math::Vec3(0.2f, 0.2f, 0.2f);

        protected:
            Scene(system::File* f, Engine* e, std::shared_ptr<core::EndCaller> c);

        public:
            virtual void commit();
            virtual void draw();
            virtual ~Scene();
            static Scene* read(system::File* f, Engine* e, std::shared_ptr<core::EndCaller> c);
            const camera::Camera* get_current_camera() const;
            const math::Vec3& get_ambient_light() const;
            const light::Sun* get_sun() const;
            void set_renderable(bool);
        };
    }
}
}
#endif
