#ifndef GEAROENIX_GLES2_PIPELINE_SHADOW_MAPPER_RESOURCE_SET_HPP
#define GEAROENIX_GLES2_PIPELINE_SHADOW_MAPPER_RESOURCE_SET_HPP
#include "../../core/cr-build-configuration.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../render/pipeline/rnd-pip-shadow-mapper-resource-set.hpp"
#include "gles2-pip-resource-set.hpp"

namespace gearoenix::gles2::shader {
class ShadowMapper;
}

namespace gearoenix::gles2::pipeline {
class ShadowMapperResourceSet : public ResourceSet, public render::pipeline::ShadowMapperResourceSet {
public:
    explicit ShadowMapperResourceSet(const std::shared_ptr<shader::ShadowMapper>& shd) noexcept;
    void bind(gl::uint& bound_shader_program) const noexcept final;
};
}
#endif
#endif
