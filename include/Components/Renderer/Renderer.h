#ifndef __HAZ_RENDERER
#define __HAZ_RENDERER

#include <SFML/Graphics.hpp>
#include <frameworkHaz/Interface/IDable.hpp>
#include <GameState/Camera.h>

class Renderer : private haz::IDable {
public:
    Renderer();
    virtual ~Renderer();

    virtual void draw (sf::RenderWindow& window, Camera const& camera) = 0;

    void enable();
    void disable();

    static std::vector<Renderer*> getRenderers();

private:

    static void _enable(haz::IDable::ID_t id, Renderer* r);
    static void _disable(haz::IDable::ID_t id);

    static std::map<haz::IDable::ID_t, Renderer*> renderers;

};

#endif
