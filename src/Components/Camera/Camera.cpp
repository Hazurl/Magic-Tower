#include <Components/Camera/Camera.h>

Camera::Camera(haz::GameObject* go, float width, float height, float default_zoom) 
    : Component(go), _width(width), _height(height), _zoom(default_zoom) {

}

Camera::~Camera() {
    
}

haz::Component* Camera::clone(haz::GameObject* go) const {
    return new Camera(go, _width, _height, _zoom);
}

std::string Camera::to_string() const {
    return "{ " + std::to_string(_zoom) + " }";
}

std::vector<std::string> Camera::pretty_strings () const {
    return {
        "Size : (" + std::to_string(_width) + ", " + std::to_string(_height) + ")",
        "Zoom : " + std::to_string(_zoom),
    };
}

void Camera::update(haz::Time const&, haz::Environement*) {

}

float Camera::zoom() const {
    return _zoom;
}

void Camera::zoom(float zoom) {
    _zoom = zoom;
}

float Camera::width() const {
    return _width;
}

float Camera::height() const {
    return _height;
}