#ifndef GEAROENIX_GLES3_PIPELINE_FORWARD_PBR_DIRECTIONAL_SHADOW_RESOURCE_SET_HPP
#define GEAROENIX_GLES3_PIPELINE_FORWARD_PBR_DIRECTIONAL_SHADOW_RESOURCE_SET_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef GX_USE_OPENGL_ES3
#include "../../core/sync/cr-sync-end-caller.hpp"
#include "../../render/pipeline/rnd-pip-forward-pbr-directional-shadow-resource-set.hpp"
#include "gles3-pip-resource-set.hpp"
namespace gearoenix::gles3 {
    namespace shader {
        class ForwardPbrDirectionalShadow;
    }
    namespace pipeline {
        class ForwardPbrDirectionalShadowResourceSet : public ResourceSet, public render::pipeline::ForwardPbrDirectionalShadowResourceSet {
        public:
            ForwardPbrDirectionalShadowResourceSet(const std::shared_ptr<shader::ForwardPbrDirectionalShadow>& shd);
            void bind(gl::uint& bound_shader_program) const override final;
        };
    }
}
#endif
#endif
