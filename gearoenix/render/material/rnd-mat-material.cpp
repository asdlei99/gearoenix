#include "rnd-mat-material.hpp"
#include "../../core/cr-end-caller.hpp"
#include "../../system/sys-file.hpp"
#include "../buffer/rnd-buf-uniform.hpp"
#include "../pipeline/rnd-pip-manager.hpp"
#include "../pipeline/rnd-pip-pipeline.hpp"
#include "../rnd-engine.hpp"
#include "rnd-mat-directional-textured-speculated-nocube-fullshadow-opaque.hpp"
#include "rnd-mat-white.hpp"

gearoenix::render::material::Material::Material(shader::Id sid, unsigned int us, Engine* e)
    : pl(e->get_pipeline_manager()->get_pipeline(sid))
    , ub(new buffer::Uniform(us, e))
{
}

gearoenix::render::material::Material::~Material()
{
    delete ub;
}

gearoenix::render::material::Material* gearoenix::render::material::Material::read(system::File* f, Engine* e, std::shared_ptr<core::EndCaller> end)
{
    shader::Id sid;
    f->read(sid);
    switch (sid) {
    case shader::WHITE:
        return new White(e);
    case shader::DIRECTIONAL_TEXTURED_SPECULATED_NOCUBE_FULLSHADOW_OPAQUE:
        return new DirectionalTexturedSpeculatedNocubeFullshadowOpaque(f, e, end);
    }
    LOGF("Unexpected");
}
