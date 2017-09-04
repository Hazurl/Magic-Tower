#ifndef __HAZ_RENDERER
#define __HAZ_RENDERER

#include <SFML/Graphics.hpp>
#include <frameworkHaz/Interface/Subscriber.hpp>
#include <frameworkHaz/2DGOInclude.hpp>

#include <Utilities/Converter.h>

#include <cmath>

class Renderer : public haz::Subscriber<Renderer>, public haz::Component {
public:
    struct PartialSprite {
        sf::Texture* texture;
        sf::IntRect texture_rect;

        sf::Vector2f position;
        sf::Vector2f scale;
        float rotation;

        sf::Sprite to_sprite() const;
    };

    static const float pixel_per_unit;
    
    Renderer(haz::GameObject* go);
    virtual ~Renderer();

    haz::Component* clone(haz::GameObject* go) const;

    std::vector<std::string> pretty_strings() const;

    PartialSprite getPartialSprite();
    void changeTexture(sf::Texture& texture);
    
    void onEnable();
    void onDisable();

    void update() override;

    static inline std::vector<Renderer*> get () { return haz::Subscriber<Renderer>::get(); }

private: 

    PartialSprite partialSprite;

    float scale_factor_height;
    float scale_factor_width;
};

#endif
