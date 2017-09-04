#ifndef __HAZ_CAMERA
#define __HAZ_CAMERA

#include <frameworkHaz/2DGOInclude.hpp>

class Camera : public haz::Component {
public:
    Camera(haz::GameObject* go, float width, float height, float default_zoom = 1);
    ~Camera();
    haz::Component* clone(haz::GameObject* go) const;

    std::string to_string() const;
    std::vector<std::string> pretty_strings () const;

    void update();

    float zoom() const;
    void zoom(float zoom);

    float width() const;
    float height() const;

private:

    const float _width, _height;
    float _zoom;

};

#endif
