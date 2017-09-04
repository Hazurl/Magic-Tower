#include <Components/Camera/CameraMotionControler.h>

CameraMotionControler::CameraMotionControler(haz::GameObject* go, Camera* camera, haz::_2D::Vectorf const& position_constraint) 
    : Component(go), 
      camera(camera),
      min_x(-position_constraint.x),
      max_x(position_constraint.x),
      min_y(-position_constraint.y),
      max_y(position_constraint.y) {
}

CameraMotionControler::~CameraMotionControler() {

}

haz::Component* CameraMotionControler::clone(haz::GameObject* go) const {
    return new CameraMotionControler(go, camera, {max_x, max_y});
}

std::string CameraMotionControler::to_string() const {
    return "{ Camera " + haz::adress(camera) + " }";
}

std::vector<std::string> CameraMotionControler::pretty_strings () const {
    return {
        "Camera : " + haz::adress(camera),
        "Constraint : " + haz::_2D::Vectorf(max_x, max_y).to_string()
    };
}

void CameraMotionControler::update() {
    camera->zoom(
        haz::clamp(
            Input::getScroll() * camera_scroll_factor + camera->zoom(),
            min_zoom, 
            max_zoom
        )
    );

    // TODO : zoom in the direction of the mouse location
    
    float factor = camera_speed_factor * haz::Engine::time().deltaTime() / 1000;
    haz::_2D::Vectorf movement(
        Input::getAxis(Input::Axis::Horizontal) * factor,
        -Input::getAxis(Input::Axis::Vertical) * factor
    );

    transform()->position(
        (transform()->position() + movement)
            .clamp({min_x, min_y}, {max_x, max_y}
        )
    );
}
