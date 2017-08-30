#ifndef __CAMERA
#define __CAMERA

#include <Utilities/Constant.h>
#include <Utilities/DebugMacro.h>
#include <frameworkHaz/Geometry/2D/Vector.hpp>

class Camera {
    GIVE_ACCESS_DEBUG()
public:
    Camera(float x = 0, float y = 0, float zoom = 1);
    ~Camera();

    void move(float x, float y);
    void moveZoom(float delta);

    float getPositionX() const;
    float getPositionY() const;
    haz::_2D::Vectorf getPosition() const;
    float getZoom() const;

    void checkPosition();
    void checkZoom();

private:
    float x, y, zoom;

    const float min_x = -SCREEN_WIDTH / 2, max_x = SCREEN_WIDTH / 2;
    const float min_y = -SCREEN_HEIGHT / 2, max_y = SCREEN_HEIGHT / 2;

    const float min_zoom = 0.5, max_zoom = 3;
};

#endif