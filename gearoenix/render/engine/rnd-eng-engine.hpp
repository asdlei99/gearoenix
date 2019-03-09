#ifndef GEAROENIX_RENDER_ENGINE_ENGINE_HPP
#define GEAROENIX_RENDER_ENGINE_ENGINE_HPP
#include "../../core/cr-build-configuration.hpp"
#include "../../core/cr-types.hpp"
#include "../../core/sync/cr-sync-end-caller.hpp"
#include "rnd-eng-type.hpp"
#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <vector>
namespace gearoenix {
namespace core {
    namespace event {
        class Event;
    }
    namespace sync {
        class Semaphore;
    }
}
namespace physics {
    class Engine;
}
namespace system {
    class Application;
    namespace stream {
        class Stream;
    }
}
namespace render {
    namespace command {
        class Buffer;
        class Manager;
    }
    namespace buffer {
        class Mesh;
        class Uniform;
        class Manager;
    }
    namespace pipeline {
        class Manager;
        class Pipeline;
    }
    namespace sampler {
        class Manager;
    }
    namespace scene {
        class Scene;
    }
    namespace shader {
        class Shader;
        class Resources;
    }
    namespace sync {
        class Semaphore;
    }
    namespace texture {
        class Texture2D;
        class Cube;
    }
    namespace engine {
        class Engine {
        protected:
            unsigned int frame_number = 0;
            const Type::Id engine_type_id;
            const std::shared_ptr<system::Application> sysapp;
            /// managers pointers are own only by this class
            std::shared_ptr<pipeline::Manager> pipeline_manager = nullptr;
            std::shared_ptr<command::Manager> command_manager = nullptr;
            std::shared_ptr<sampler::Manager> sampler_manager = nullptr;
            std::shared_ptr<buffer::Manager> buffer_manager = nullptr;
            // end of managers
            core::sync::Semaphore* load_functions_mutex;
            core::sync::Semaphore* loaded_scenes_mutex;
            core::sync::Semaphore* scene_loader_mutex;
            core::sync::Semaphore* scene_loader_signaler;
            std::thread scene_loader;
            volatile bool scene_loader_continue = true;
            void scene_loader_function();
            std::vector<std::function<void()>> scene_loader_functions;
            std::vector<std::function<void()>> load_functions;
            std::map<core::Id, std::shared_ptr<scene::Scene>> loaded_scenes;
            physics::Engine* physics_engine = nullptr;
            void do_load_functions();
            void clear();
            Engine(const std::shared_ptr<system::Application>& system_application, const Type::Id engine_type_id);

        public:
            virtual ~Engine();
            virtual void window_changed() = 0;
            virtual void update() = 0;
            virtual void terminate() = 0;
            virtual sync::Semaphore* create_semaphore() = 0;
            virtual void submit(const std::vector<std::shared_ptr<sync::Semaphore>>& p, const std::shared_ptr<command::Buffer>& c, const std::shared_ptr<sync::Semaphore>& n) = 0;
            // getters
            const pipeline::Manager* get_pipeline_manager() const;
            pipeline::Manager* get_pipeline_manager();
            const command::Manager* get_command_manager() const;
            command::Manager* get_command_manager();
            const system::Application* get_system_application() const;
            system::Application* get_system_application();
            const physics::Engine* get_physics_engine() const;
            physics::Engine* get_physics_engine();
            const buffer::Manager* get_buffer_manager() const;
            buffer::Manager* get_buffer_manager();
            // end of getters
            void add_load_function(std::function<void()> fun);
            const std::shared_ptr<scene::Scene>& get_scene(core::Id scene_id) const;
            const std::map<core::Id, std::shared_ptr<scene::Scene>>& get_all_scenes() const;
            void load_scene(core::Id scene_id, std::function<void()> on_load);
            void delete_scene(core::Id scene_id);
            Type::Id get_engine_type_id() const;
            unsigned int get_frame_number() const;
        };
    }
}
}
#endif