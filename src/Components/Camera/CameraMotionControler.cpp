#include <Components/Camera/CameraMotionControler.h>

CameraMotionControler::CameraMotionControler(haz::GameObject* go, Camera* camera) 
    : Component(go), camera(camera), min_x(0), max_x(camera->width()), min_y(0), max_y(camera->height()) {
    
}

CameraMotionControler::~CameraMotionControler() {

}

haz::Component* CameraMotionControler::clone(haz::GameObject* go) const {
    return new CameraMotionControler(go, camera);
}

std::string CameraMotionControler::to_string() const {
    return "{ Camera " + haz::adress(camera) + " }";
}

std::vector<std::string> CameraMotionControler::pretty_strings () const {
    return {
        "Camera : " + haz::adress(camera)
    };
}

void CameraMotionControler::update(haz::Time const& t, haz::Environement*) {
    camera->zoom(
        haz::clamp(
            Input::getScroll() * camera_scroll_factor + camera->zoom(),
            min_zoom, 
            max_zoom
        )
    );

    haz::_2D::Vectorf pos = transform()->position();
    // TODO : zoom in the direction of the mouse location
    /*if (Input::getScroll() != 0) {
        pos += haz::_2D::Vectorf { Input::getMousePosition() - pos } * Input::getScroll() / 10;
    }*/
    if (Input::isDown(Input::Button::Right))
        pos.x -= camera->zoom() * camera_speed_factor;
    if (Input::isDown(Input::Button::Left))
        pos.x += camera->zoom() * camera_speed_factor;
    if (Input::isDown(Input::Button::Up))
        pos.y += camera->zoom() * camera_speed_factor;
    if (Input::isDown(Input::Button::Down))
        pos.y -= camera->zoom() * camera_speed_factor;
    pos = pos.clamp({min_x, min_y}, {max_x, max_y});
    transform()->position(pos);
}
