#include "gles2-shd-forward-pbr.hpp"
#ifdef GX_USE_OPENGL_ES2
#include "../../core/cr-function-loader.hpp"
#include "../../gl/gl-loader.hpp"
#include "../engine/gles2-eng-engine.hpp"

#define GX_GLES2_SHADER_SRC_EFFECT_UNIFORMS                                                                                              \
    "uniform vec4  effect_point_lights_color_min_radius[" GX_MAX_POINT_LIGHTS_STR "];\n"                                                 \
    "uniform vec4  effect_point_lights_position_max_radius[" GX_MAX_POINT_LIGHTS_STR "];\n"                                              \
    "uniform mat4  effect_shadow_caster_directional_lights_cascades_view_projection_bias[" GX_MAX_DIRECTIONAL_LIGHTS_CASCADES_STR "];\n" \
    "uniform vec4  effect_shadow_caster_directional_lights_color_cascades_count[" GX_MAX_DIRECTIONAL_LIGHTS_SHADOW_CASTER_STR "];\n"     \
    "uniform vec4  effect_shadow_caster_directional_lights_direction[" GX_MAX_DIRECTIONAL_LIGHTS_SHADOW_CASTER_STR "];\n"                \
    "uniform float effect_point_lights_count;\n"                                                                                         \
    "uniform float effect_shadow_caster_directional_lights_count;\n"

#define GX_GLES2_SHADER_FORWARD_PBR_VARYING \
    "varying vec3 out_pos;\n"               \
    "varying vec3 out_nrm;\n"               \
    "varying vec3 out_tng;\n"               \
    "varying vec3 out_btg;\n"               \
    "varying vec2 out_uv;\n"                \
    "varying vec3 out_directional_lights_cascades_projected[" GX_MAX_DIRECTIONAL_LIGHTS_CASCADES_STR "];\n"

gearoenix::gles2::shader::ForwardPbr::ForwardPbr(engine::Engine* const e, const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept
    : Shader(e, c)
{
    e->get_function_loader()->load([this] {
        const std::string vertex_shader_code = GX_GLES2_SHADER_SRC_DEFAULT_VERTEX_STARTING
            "uniform mat4  camera_vp;\n" GX_GLES2_SHADER_SRC_EFFECT_UNIFORMS
            "uniform mat4  model_m;\n" GX_GLES2_SHADER_FORWARD_PBR_VARYING
            "void main()\n"
            "{\n"
            "    vec4 pos = model_m * vec4(position, 1.0);\n"
            "    out_pos = pos.xyz;\n"
            "    out_nrm = normalize((model_m * vec4(normal, 0.0)).xyz);\n"
            "    out_tng = normalize((model_m * vec4(tangent.xyz, 0.0)).xyz);\n"
            "    out_btg = cross(out_nrm, out_tng) * tangent.w;\n"
            "    out_uv = uv;\n"
            "    int effect_shadow_caster_directional_lights_count_int = int(effect_shadow_caster_directional_lights_count);\n"
#ifdef GX_IN_WEB
#define GX_DIRECTIONAL_LOOP_COUNT GX_MAX_DIRECTIONAL_LIGHTS_SHADOW_CASTER_STR
#else
#define GX_DIRECTIONAL_LOOP_COUNT "effect_shadow_caster_directional_lights_count_int"
#endif
            "    for(int diri = 0, i = 0; diri < " GX_DIRECTIONAL_LOOP_COUNT "; ++diri)\n"
            "    {\n"
#ifdef GX_IN_WEB
            "        if(diri < effect_shadow_caster_directional_lights_count_int) {\n"
#endif
            "        int effect_shadow_caster_directional_lights_cascades_count_int = int(effect_shadow_caster_directional_lights_color_cascades_count[diri].w);\n"
            "        int diff_ccc_cc = " GX_MAX_SHADOW_CASCADES_STR " - effect_shadow_caster_directional_lights_cascades_count_int;\n"
#ifdef GX_IN_WEB
#define GX_CASCADE_LOOP_COUNT GX_MAX_SHADOW_CASCADES_STR
#else
#define GX_CASCADE_LOOP_COUNT "effect_shadow_caster_directional_lights_cascades_count_int"
#endif
            "        for(int j = 0; j < " GX_CASCADE_LOOP_COUNT "; ++j, ++i)\n"
            "        {\n"
#ifdef GX_IN_WEB
            "            if(j < effect_shadow_caster_directional_lights_cascades_count_int) {\n"
#endif
#if GX_MAX_DIRECTIONAL_LIGHTS_CASCADES == 1
#define GX_SHADOW_INDEX "0"
#else
#define GX_SHADOW_INDEX "i"
#endif
            "            vec4 light_pos = effect_shadow_caster_directional_lights_cascades_view_projection_bias[" GX_SHADOW_INDEX "] * pos;\n"
            "            light_pos.xyz /= light_pos.w;\n"
            "            light_pos.z *= 0.5;\n"
            "            light_pos.z += 0.5;\n"
            "            out_directional_lights_cascades_projected[i] = light_pos.xyz;\n"
#ifdef GX_IN_WEB
            "            }\n"
#endif
            "        }\n"
#ifndef GX_IN_WEB
            "        i += diff_ccc_cc;\n"
#else
            "        }\n"
#endif
            "    }\n"
            "    gl_Position = camera_vp * pos;\n"
            "}";

        const std::string fragment_shader_code = GX_GLES2_SHADER_SRC_DEFAULT_FRAGMENT_STARTING
            "uniform float       material_alpha;\n"
            "uniform float       material_alpha_cutoff;\n"
            "uniform float       material_metallic_factor;\n"
            "uniform float       material_normal_scale;\n"
            "uniform float       material_occlusion_strength;\n"
            "uniform float       material_roughness_factor;\n"
            "uniform sampler2D   material_base_color;\n"
            "uniform sampler2D   material_metallic_roughness;\n"
            "uniform sampler2D   material_normal;\n"
            "uniform sampler2D   material_emissive;\n"
            // scenes uniform(s)
            "uniform vec3        scene_ambient_light;\n"
            "uniform vec4        scene_directional_lights_color[" GX_MAX_DIRECTIONAL_LIGHTS_STR "];\n"
            "uniform vec4        scene_directional_lights_direction[" GX_MAX_DIRECTIONAL_LIGHTS_STR "];\n"
            "uniform float       scene_directional_lights_count;\n"
            "uniform float       scene_ssao_samples_count;\n"
            "uniform float       scene_ssao_radius;\n"
            "uniform float       scene_ssao_z_tolerance;\n"
            "uniform samplerCube effect_diffuse_environment;\n"
            "uniform samplerCube effect_specular_environment;\n"
            "uniform sampler2D   effect_ambient_occlusion;\n"
            "uniform sampler2D   effect_shadow_caster_directional_lights_cascades_shadow_map[" GX_MAX_DIRECTIONAL_LIGHTS_CASCADES_STR "];\n"
            "uniform sampler2D   effect_brdflut;\n" GX_GLES2_SHADER_SRC_EFFECT_UNIFORMS
            // camera uniform(s)
            "uniform vec3        camera_position;\n" GX_GLES2_SHADER_FORWARD_PBR_VARYING
            // Normal Distribution Function Trowbridge-Reitz GGX
            "float distribution_ggx(const vec3 normal, const vec3 halfway, const float roughness) {\n"
            "    float roughness2 = roughness * roughness;\n"
            "    float nh = max(dot(normal, halfway), 0.0);\n"
            "    float nh2 = nh * nh;\n"
            "    float nom = roughness2;\n"
            "    float tmpdenom = nh2 * (roughness2 - 1.0) + 1.0;\n"
            "    float denom = GX_PI * tmpdenom * tmpdenom;\n"
            "    return nom / denom;\n"
            "}\n"
            "float geometry_schlick_ggx(const float nd, const float roughness, const float k, const float k_inv) {\n"
            "    float nom = nd;\n"
            "    float denom = nd * k_inv + k;\n"
            "    return nom / denom;\n"
            "}\n"
            "float geometry_smith(const float normal_dot_light, const float normal_dot_view, const float roughness) {\n"
            "    float k = roughness + 1.0;\n"
            "    k = (k * k) * (1.0 / 8.0);\n"
            "    float k_inv = 1.0 - k;\n"
            "    float ggx2 = geometry_schlick_ggx(normal_dot_view, roughness, k, k_inv);\n"
            "    float ggx1 = geometry_schlick_ggx(normal_dot_light, roughness, k, k_inv);\n"
            "    return ggx1 * ggx2;\n"
            "}\n"
            "vec3 fresnel_schlick(const float nv, const vec3 f0) {\n"
            "    float inv = 1.0 - nv;\n"
            "    float inv2 = inv * inv;\n"
            "    float inv4 = inv2 * inv2;\n"
            "    float inv5 = inv4 * inv;\n"
            "    return f0 + ((1.0 - f0) * inv5);\n"
            "}\n"
            // cos_theta is (n dot v)
            "vec3 fresnel_schlick_roughness(const float nv, const vec3 f0, const float roughness)\n"
            "{\n"
            "    float inv = 1.0 - nv;\n"
            "    float inv2 = inv * inv;\n"
            "    float inv4 = inv2 * inv2;\n"
            "    float inv5 = inv4 * inv;\n"
            "    return f0 + ((max(vec3(1.0 - roughness), f0) - f0) * inv5);\n"
            "}\n"
            "void main()\n"
            "{\n"
            //   material properties
            "    vec4 tmpv4 = texture2D(material_base_color, out_uv);\n"
            "    tmpv4.w *= material_alpha;\n"
            "    vec4 albedo = tmpv4;\n"
            "    if(albedo.w < material_alpha_cutoff) discard;\n"
            "	 tmpv4.xy = texture2D(material_metallic_roughness, out_uv).xy;\n"
            "    tmpv4.xy *= vec2(material_metallic_factor, material_roughness_factor);\n"
            "    float metallic = tmpv4.x;\n"
            "    float roughness = tmpv4.y;\n"
            //   TODO: in future maybe I will add ao in here
            //   input lighting data
            "    vec3 normal = mat3(out_tng, out_btg, out_nrm) * ((texture2D(material_normal, out_uv).xyz - 0.5) * 2.0 * material_normal_scale);\n"
            "    vec3 view = normalize(camera_position - out_pos);\n"
            "    vec3 reflection = reflect(-view, normal);\n"
            "    float normal_dot_view = max(dot(normal, view), 0.0);\n"
            //   calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
            //   of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
            //   TODO: in future I must bring builder fresnel factor 0 (the hard coded 0.4) from matrial uniform data
            "    vec3 f0 = mix(vec3(0.04), albedo.xyz, metallic);\n"
            //   reflectance equation
            "    vec3 lo = vec3(0.0);\n"
            "    int effect_point_lights_count_int = int(effect_point_lights_count);\n"
#ifdef GX_IN_WEB
#define GX_POINT_LIGHT_LOOP_COUNT GX_MAX_POINT_LIGHTS_STR
#else
#define GX_POINT_LIGHT_LOOP_COUNT "effect_point_lights_count_int"
#endif
            //   computing point lights
            "    for(int i = 0; i < " GX_POINT_LIGHT_LOOP_COUNT "; ++i)\n"
            "    {\n"
#ifdef GX_IN_WEB
            "        if(i < effect_point_lights_count_int) {\n"
#endif
            //       calculate per-light radiance
            "        vec3 light_vec = effect_point_lights_position_max_radius[i].xyz - out_pos;\n"
            //       TODO: in future consider max and min radius
            "        float distance = length(light_vec);\n"
            "        float distance_inv = 1.0 / distance;\n"
            "        vec3 light_direction = light_vec * distance_inv;\n"
            "        float normal_dot_light = max(dot(normal, light_direction), 0.0);\n"
            "        vec3 half_vec = normalize(view + light_direction);\n"
            "        float attenuation = distance_inv * distance_inv;\n"
            "        vec3 radiance = effect_point_lights_color_min_radius[i].xyz * attenuation;\n"
            //       Cook-Torrance BRDF
            "        float ndf = distribution_ggx(normal, half_vec, roughness);\n"
            "        float geo = geometry_smith(normal_dot_light, normal_dot_view, roughness);\n"
            "        vec3 frsn = fresnel_schlick(max(dot(half_vec, view), 0.0), f0);\n"
            "        vec3 nominator = ndf * geo * frsn;\n"
            //       0.001 to prevent divide by zero.
            "        float denominator = 4.0 * normal_dot_view * normal_dot_light + 0.001;\n"
            "        vec3 specular = nominator / denominator;\n"
            //       kS is equal to Fresnel
            "        vec3 ks = frsn;\n"
            //       for energy conservation, the diffuse and specular light can't
            //       be above 1.0 (unless the surface emits light); to preserve this
            //       relationship the diffuse component (kD) should equal 1.0 - kS.
            //       multiply kD by the inverse metalness such that only non-metals
            //       have diffuse lighting, or a linear blend if partly metal (pure metals
            //       have no diffuse light).
            "        vec3 kd = (vec3(1.0) - ks) * (1.0 - metallic);\n"
            //       scale light by NdotL
            //       add to outgoing radiance Lo
            //       note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
            "        lo += (kd * albedo.xyz / GX_PI + specular) * radiance * normal_dot_light;\n"
#ifdef GX_IN_WEB
            "        }\n"
#endif
            "    }\n"
            "    int scene_directional_lights_count_int = int(scene_directional_lights_count);\n"
#ifdef GX_IN_WEB
#define GX_DIRECTIONAL_LIGHT_LOOP_COUNT GX_MAX_DIRECTIONAL_LIGHTS_STR
#else
#define GX_DIRECTIONAL_LIGHT_LOOP_COUNT "scene_directional_lights_count_int"
#endif
            //   computing directional lights
            "    for(int i = 0; i < " GX_DIRECTIONAL_LIGHT_LOOP_COUNT "; ++i)\n"
            "    {\n"
#ifdef GX_IN_WEB
            "        if(i < scene_directional_lights_count_int) {\n"
#endif
            "        vec3 light_direction = -scene_directional_lights_direction[i].xyz;\n"
            "        float normal_dot_light = max(dot(normal, light_direction), 0.0);\n"
            "        vec3 half_vec = normalize(view + light_direction);\n"
            "        vec3 radiance = scene_directional_lights_color[i].xyz;\n"
            //       Cook-Torrance BRDF
            "        float ndf = distribution_ggx(normal, half_vec, roughness);\n"
            "        float geo = geometry_smith(normal_dot_light, normal_dot_view, roughness);\n"
            "        vec3 frsn = fresnel_schlick(max(dot(half_vec, view), 0.0), f0);\n"
            "        vec3 nominator = ndf * geo * frsn;\n"
            //       0.001 to prevent divide by zero.
            "        float denominator = 4.0 * normal_dot_view * normal_dot_light + 0.001;\n"
            "        vec3 specular = nominator / denominator;\n"
            //       kS is equal to Fresnel
            "        vec3 ks = frsn;\n"
            //       for energy conservation, the diffuse and specular light can't
            //       be above 1.0 (unless the surface emits light); to preserve this
            //       relationship the diffuse component (kD) should equal 1.0 - kS.
            //       multiply kD by the inverse metalness such that only non-metals
            //       have diffuse lighting, or a linear blend if partly metal (pure metals
            //       have no diffuse light).
            "        vec3 kd = (vec3(1.0) - ks) * (1.0 - metallic);\n"
            //       scale light by NdotL
            //       add to outgoing radiance Lo
            //       note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
            "        lo += (kd * albedo.xyz / GX_PI + specular) * radiance * normal_dot_light;\n"
#ifdef GX_IN_WEB
            "        }\n"
#endif
            "    }\n"
            "    int effect_shadow_caster_directional_lights_count_int = int(effect_shadow_caster_directional_lights_count);\n"
#ifdef GX_IN_WEB
#define GX_SHADOW_CASTER_DIRECTIONAL_LIGHT_LOOP_COUNT GX_MAX_DIRECTIONAL_LIGHTS_SHADOW_CASTER
#else
#define GX_SHADOW_CASTER_DIRECTIONAL_LIGHT_LOOP_COUNT "effect_shadow_caster_directional_lights_count_int"
#endif
            "    for(int diri = 0, lcasi = 0; diri < " GX_SHADOW_CASTER_DIRECTIONAL_LIGHT_LOOP_COUNT "; ++diri, lcasi = diri * " GX_MAX_SHADOW_CASCADES_STR ")\n"
            "    {\n"
#ifdef GX_IN_WEB
            "        if(diri < effect_shadow_caster_directional_lights_count_int) {\n"
#endif
            "        bool is_in_directional_light = true;\n"
            "        float normal_dot_light = max(dot(out_nrm, -effect_shadow_caster_directional_lights_direction[diri].xyz), 0.0);\n"
            "        float shadow_bias = 0.001;\n"
            "        if(normal_dot_light > 0.0)\n"
            "        {\n"
            "            shadow_bias = clamp(sqrt((0.000025 / (normal_dot_light * normal_dot_light)) - 0.000025), 0.001, 0.02);\n"
            "        }\n"
            "        else\n"
            "        {\n"
            "            is_in_directional_light = false;"
            "        }\n"
            "        if(is_in_directional_light)\n"
            "        {\n"
            "            int cascades_count_int = int(effect_shadow_caster_directional_lights_color_cascades_count[diri].w);\n"
#undef GX_CASCADE_LOOP_COUNT
#ifdef GX_IN_WEB
#define GX_CASCADE_LOOP_COUNT GX_MAX_SHADOW_CASCADES_STR
#else
#define GX_CASCADE_LOOP_COUNT "cascades_count_int"
#endif
            "            for(int i = 0; i < " GX_CASCADE_LOOP_COUNT "; ++i)\n"
            "            {\n"
#ifdef GX_IN_WEB
            "                if(i < cascades_count_int) {\n"
#endif
            "                vec3 lightuv = out_directional_lights_cascades_projected[i];\n"
            "                if (lightuv.x > 0.0 && lightuv.x < 1.0 && lightuv.y > 0.0 && lightuv.y < 1.0)\n"
            "                {\n"
            "                    vec2 depth_vec = texture2D(effect_shadow_caster_directional_lights_cascades_shadow_map[i], lightuv.xy).xy;\n"
            "                    float depth = depth_vec.y * 0.00390625 + depth_vec.x;\n"
            "                    if(depth + shadow_bias <= lightuv.z)\n"
            "                    {\n"
            "                        is_in_directional_light = false;\n"
            "                    }\n"
            "                    break;\n"
            "                }\n"
#ifdef GX_IN_WEB
            "                }\n"
#endif
            "            }\n"
            "        }\n"
            "        if(is_in_directional_light)\n"
            "        {\n"
            "            vec3 half_vec = normalize(view - effect_shadow_caster_directional_lights_direction[diri].xyz);\n"
            "            vec3 radiance = effect_shadow_caster_directional_lights_color_cascades_count[diri].xyz;\n"
            //           Cook-Torrance BRDF
            "            float ndf = distribution_ggx(normal, half_vec, roughness);\n"
            "            float geo = geometry_smith(normal_dot_light, normal_dot_view, roughness);\n"
            "            vec3 frsn = fresnel_schlick(max(dot(half_vec, view), 0.0), f0);\n"
            "            vec3 nominator = ndf * geo * frsn;\n"
            //           0.001 to prevent divide by zero.
            "            float denominator = 4.0 * normal_dot_view * normal_dot_light + 0.001;\n"
            "            vec3 specular = nominator / denominator;\n"
            //           kS is equal to Fresnel
            "            vec3 ks = frsn;\n"
            //           for energy conservation, the diffuse and specular light can't
            //           be above 1.0 (unless the surface emits light); to preserve this
            //           relationship the diffuse component (kD) should equal 1.0 - kS.
            //           multiply kD by the inverse metalness such that only non-metals
            //           have diffuse lighting, or a linear blend if partly metal (pure metals
            //           have no diffuse light).
            "            vec3 kd = (vec3(1.0) - ks) * (1.0 - metallic);\n"
            //           scale light by NdotL
            //           add to outgoing radiance Lo
            //           note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
            "            lo += (kd * albedo.xyz / GX_PI + specular) * radiance * normal_dot_light;\n"
            "        }\n"
#ifdef GX_IN_WEB
            "        }\n"
#endif
            "    }\n"
            //   ambient lighting (we now use IBL as the ambient term)
            "    vec3 frsn = fresnel_schlick_roughness(normal_dot_view, f0, roughness);\n"
            "    vec3 ks = frsn;\n"
            "    vec3 kd = (1.0 - ks) * (1.0 - metallic);\n"
            "    vec3 irradiance = textureCube(effect_diffuse_environment, normal).rgb;\n"
            "    vec3 diffuse = irradiance * albedo.xyz;\n"
            //   sample both the pre-filter map and the BRDF lut and combine them together as per
            //   the Split-Sum approximation to get the IBL specular part.
            "    float MAX_REFLECTION_LOD = 4.0;\n"
            "    vec3 prefiltered_color = textureCube(effect_specular_environment, reflection, roughness * MAX_REFLECTION_LOD).rgb;\n"
            "    vec2 brdf = texture2D(effect_brdflut, vec2(normal_dot_view, roughness)).rg;\n"
            "    vec3 specular = prefiltered_color * (frsn * brdf.x + brdf.y);\n"
            "    vec3 ambient = kd * diffuse + specular + scene_ambient_light * albedo.xyz;\n"
            "    tmpv4.xyz = ambient + lo;\n"
            //   HDR tonemapping
            "    tmpv4.xyz = tmpv4.xyz / (tmpv4.xyz + vec3(1.0));\n"
            //   gamma correct
            "    tmpv4.xyz = pow(tmpv4.xyz, vec3(1.0 / 2.2));\n"
            //   TODO don't forget gamma correction it can be part of scene uniform data
            "    gl_FragColor = vec4(tmpv4.xyz, albedo.w);\n"
            "}"; // 123

        set_vertex_shader(vertex_shader_code);
        set_fragment_shader(fragment_shader_code);
        link();
        GX_GLES2_SHADER_SET_TEXTURE_INDEX_STARTING
        GX_GLES2_THIS_GET_UNIFORM(material_alpha)
        GX_GLES2_THIS_GET_UNIFORM(material_alpha_cutoff)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE(material_base_color)
        //GX_GLES2_THIS_GET_UNIFORM_TEXTURE(material_emissive)
        GX_GLES2_THIS_GET_UNIFORM(material_metallic_factor)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE(material_metallic_roughness)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE(material_normal)
        GX_GLES2_THIS_GET_UNIFORM(material_normal_scale)
        //GX_GLES2_THIS_GET_UNIFORM(material_occlusion_strength)
        GX_GLES2_THIS_GET_UNIFORM(material_roughness_factor)
        GX_GLES2_THIS_GET_UNIFORM(camera_position)
        GX_GLES2_THIS_GET_UNIFORM(camera_vp)
        // TODO
        //GX_GLES2_THIS_GET_UNIFORM(effect_ambient_occlusion)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE(effect_brdflut)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE(effect_diffuse_environment)
        GX_GLES2_THIS_GET_UNIFORM(effect_point_lights_color_min_radius)
        GX_GLES2_THIS_GET_UNIFORM(effect_point_lights_position_max_radius)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE_ARRAY(effect_shadow_caster_directional_lights_cascades_shadow_map)
        GX_GLES2_THIS_GET_UNIFORM(effect_shadow_caster_directional_lights_cascades_view_projection_bias)
        GX_GLES2_THIS_GET_UNIFORM(effect_shadow_caster_directional_lights_color_cascades_count)
        GX_GLES2_THIS_GET_UNIFORM(effect_shadow_caster_directional_lights_direction)
        GX_GLES2_THIS_GET_UNIFORM(effect_shadow_caster_directional_lights_count)
        GX_GLES2_THIS_GET_UNIFORM_TEXTURE(effect_specular_environment)
        GX_GLES2_THIS_GET_UNIFORM(model_m)
        GX_GLES2_THIS_GET_UNIFORM(scene_ambient_light)
        GX_GLES2_THIS_GET_UNIFORM(scene_directional_lights_color)
        GX_GLES2_THIS_GET_UNIFORM(scene_directional_lights_direction)
        GX_GLES2_THIS_GET_UNIFORM(scene_directional_lights_count)
        // GX_GLES2_THIS_GET_UNIFORM(scene_ssao_radius)
        // GX_GLES2_THIS_GET_UNIFORM(scene_ssao_samples_count)
        // GX_GLES2_THIS_GET_UNIFORM(scene_ssao_z_tolerance)
    });
}

gearoenix::gles2::shader::ForwardPbr::~ForwardPbr() noexcept = default;

void gearoenix::gles2::shader::ForwardPbr::bind() const noexcept
{
    Shader::bind();
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(material_base_color)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(material_emissive)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(material_metallic_roughness)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(material_normal)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(effect_ambient_occlusion)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(effect_brdflut)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(effect_diffuse_environment)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_ARRAY_UNIFORM(effect_shadow_caster_directional_lights_cascades_shadow_map)
    GX_GLES2_SHADER_SET_TEXTURE_INDEX_UNIFORM(effect_specular_environment)
}
#endif
