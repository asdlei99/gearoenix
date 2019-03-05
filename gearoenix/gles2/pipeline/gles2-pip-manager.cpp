#include "gles2-pip-manager.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../gles2-engine.hpp"

gearoenix::gles2::pipeline::Manager::Manager(Engine* engine)
    : render::pipeline::Manager(static_cast<render::Engine*>(engine))
{
}

gearoenix::gles2::pipeline::Manager::~Manager() {}

std::shared_ptr<gearoenix::render::pipeline::Pipeline> gearoenix::gles2::pipeline::Manager::get(const render::pipeline::Type::Id pipeline_type_id, core::sync::EndCaller<core::sync::EndCallerIgnore> end)
{
    GXUNIMPLEMENTED;
}

std::shared_ptr<gearoenix::render::pipeline::Resource> gearoenix::gles2::pipeline::Manager::create_resource(const std::vector<std::shared_ptr<render::texture::Texture>>& ts)
{
    GXUNIMPLEMENTED;
}

#endif
