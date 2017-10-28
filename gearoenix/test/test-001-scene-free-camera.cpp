#include "test-001-scene-free-camera.hpp"
#ifdef TEST001
#include "../render/camera/rnd-cmr-camera.hpp"
#include "../render/rnd-engine.hpp"
#include "../render/scene/rnd-scn-scene.hpp"
#include "../system/sys-app.hpp"
#include "../system/sys-log.hpp"

TestApp::TestApp(gearoenix::system::Application* sys_app)
    : gearoenix::core::Application::Application(sys_app)
    , eng(sys_app->get_render_engine())
{
    sys_app->get_render_engine()->load_scene(0, [this](unsigned int index) {
        cam = eng->get_scene(index)->get_current_camera();
        LOGI(index << "Loaded.");
    });
}

TestApp::~TestApp() {}

void TestApp::update() {}

void TestApp::terminate() {}

void TestApp::on_zoom(gearoenix::core::Real d)
{
    cam->move_forward(d);
}

void TestApp::on_rotate(gearoenix::core::Real)
{
}

void TestApp::on_scroll(gearoenix::core::Real d)
{
    cam->move_forward(d * 0.3f);
}

void TestApp::on_mouse(MouseButton mb, ButtonAction ba, gearoenix::core::Real, gearoenix::core::Real)
{
    switch (mb) {
    case MouseButton::LEFT:
        switch (ba) {
        case ButtonAction::PRESS:
            left_mouse_down = true;
            break;
        case ButtonAction::RELEASE:
            left_mouse_down = false;
            break;
        }
        break;
    default:
        break;
    }
}

void TestApp::on_mouse_move(gearoenix::core::Real dx, gearoenix::core::Real dy)
{
    if (left_mouse_down) {
        cam->rotate_local_x(dy * 0.001f);
        cam->rotate_global_z(dx * 0.001f);
    }
}

GEAROENIX_START(TestApp)
#endif
