#ifndef GEAROENIX_RENDER_WIDGET_BUTTON_HPP
#define GEAROENIX_RENDER_WIDGET_BUTTON_HPP
#include "../../math/math-vector.hpp"
#include "rnd-wdg-widget.hpp"
#include <chrono>

namespace gearoenix::physics::animation {
struct Animation;
}

namespace gearoenix::render::material {
class Unlit;
}

namespace gearoenix::render::widget {
class Text;
struct TextTheme;
struct ButtonTheme {
    math::Vec4 background_color = math::Vec4(0.4f, 0.37254902f, 0.21372549f, 1.0f);
    math::Vec4 text_color = math::Vec4(0.1f, 0.1f, 0.1f, 1.0f);
    core::Real text_scale = 0.9f;
    const TextTheme* text_theme = nullptr;
};
class Button : public Widget {
    GX_GET_CREF_PRV(std::shared_ptr<Text>, text)
    GX_GET_CREF_PRV(std::shared_ptr<material::Unlit>, background_material)
    GX_GET_CREF_PRV(ButtonTheme, theme)
protected:
    core::Real before_click_size = 1.0f;
    std::weak_ptr<physics::animation::Animation> animation;
    std::function<void()> on_click = [] {};

public:
    Button(
        core::Id my_id,
        system::stream::Stream* f,
        engine::Engine* e,
        const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept;
    Button(
        core::Id my_id,
        engine::Engine* e,
        const core::sync::EndCaller<core::sync::EndCallerIgnore>& c) noexcept;
    ~Button() noexcept final;
    void selected(const math::Vec3& point) noexcept final;
    void select_cancelled() noexcept final;
    void select_released() noexcept final;
    void set_on_click(const std::function<void()>& on_click) noexcept;
    void set_text(const std::wstring& t, const core::sync::EndCaller<core::sync::EndCallerIgnore>& c = GX_DEFAULT_IGNORED_END_CALLER) noexcept;
};
}
#endif
