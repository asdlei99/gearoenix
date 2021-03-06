#include "gles2-pip-shadow-mapper-resource-set.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../gl/gl-loader.hpp"
#include "../../render/buffer/rnd-buf-uniform.hpp"
#include "../../render/graph/node/rnd-gr-nd-shadow-mapper.hpp"
#include "../../render/mesh/rnd-msh-mesh.hpp"
#include "../buffer/gles2-buf-index.hpp"
#include "../buffer/gles2-buf-vertex.hpp"
#include "../shader/gles2-shd-shadow-mapper.hpp"
#include "../texture/gles2-txt-2d.hpp"

gearoenix::gles2::pipeline::ShadowMapperResourceSet::ShadowMapperResourceSet(const std::shared_ptr<shader::ShadowMapper>& shd) noexcept
    : gles2::pipeline::ResourceSet(shd)
{
}

void gearoenix::gles2::pipeline::ShadowMapperResourceSet::bind(gl::uint& bound_shader_program) const noexcept
{
    GX_GLES2_PIP_RES_START_DRAWING_MESH
    GX_GLES2_PIP_RES_START_SHADER(ShadowMapper, shd)
    GX_GLES2_PIP_RES_SET_TXT_2D(material_color, color)
    const auto* const node = node_uniform_buffer->get_ptr<render::graph::node::ShadowMapperUniform>();
    GX_GLES2_PIP_RES_SET_UNIFORM(effect_mvp, *(node->mvp.data()))
    GX_GLES2_PIP_RES_SET_UNIFORM(effect_alpha, node->alpha)
    GX_GLES2_PIP_RES_SET_UNIFORM(effect_alpha_cutoff, node->alpha_cutoff)
    GX_GLES2_PIP_RES_END_DRAWING_MESH
}
#endif