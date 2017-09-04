#ifndef __HAZ_CAMERAMOTIONCONTROLER
#define __HAZ_CAMERAMOTIONCONTROLER

#include <frameworkHaz/2DGOInclude.hpp>

#include <Components/Camera/Camera.h>
#include <Components/Renderer/Renderer.h>
#include <Components/Data/Map.h>

#include <Utilities/Input.h>

class CameraMotionControler : public haz::Component {
public:
    CameraMotionControler(haz::GameObject* go, Camera* camera, haz::_2D::Vectorf const& position_constraint);
    ~CameraMotionControler();

    haz::Component* clone(haz::GameObject* go) const;
    
    std::string to_string() const;
    std::vector<std::string> pretty_strings () const;

    void update();
    
private:

    Camera* const camera;

    const float min_x, max_x, min_y, max_y;
    const float min_zoom = 0.5, max_zoom = 3;

    const float camera_scroll_factor = 0.1;
    const float camera_speed_factor = 8;

};

#endif
