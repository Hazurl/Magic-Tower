#include <GameState/Camera.h>

Camera::Camera(float x, float y, float zoom) : x(x), y(y), zoom(zoom) {
    checkPosition();
    checkZoom();
}

Camera::~Camera() {

}

void Camera::move(float x, float y) {
    this->x += x;
    this->y += y;

    checkPosition();
}

void Camera::moveZoom(float delta) {
    zoom += delta * CAMERA_SCROLL_FACTOR;

    checkZoom();
}

float Camera::getPositionX() const {
    return x;
}

float Camera::getPositionY() const {
    return y;
}

haz::_2D::Vectorf Camera::getPosition() const {
    return { x, y };
}

float Camera::getZoom() const {
    return zoom;
}

void Camera::checkPosition() {
    if (x < min_x)
        x = min_x;
    else if (x > max_x)
        x = max_x;

    if (y < min_y)
        y = min_y;
    else if (y > max_y)
        y = max_y;
}

void Camera::checkZoom() {
    if (zoom < min_zoom)
        zoom = min_zoom;
    else if (zoom > max_zoom)
        zoom = max_zoom;
}