#ifndef __HAZ_HEXRENDERER
#define __HAZ_HEXRENDERER

#include <frameworkHaz/GameObject/Component/Component.hpp>
#include <frameworkHaz/GameObject/GameObject.hpp>
#include <SFML/Graphics.hpp>
#include <Components/Renderer/Renderer.h>
#include <Components/Data/Hex.h>
#include <Utilities/RessourcesLoader.h>
#include <Utilities/SceneManager.h>

#include <cmath>

class HexRenderer : public haz::Component, public Renderer {
public:
    HexRenderer(haz::GameObject* go);
    ~HexRenderer();
    
    void draw (sf::RenderWindow& window, Camera const& camera);

    haz::Component* clone(haz::GameObject* go) const;

    void onEnable();
    void onDisable();

private:

    const sf::Texture& getTexture(Hex::Type type);

    void updateSpritePosition(sf::RenderWindow& window, Camera const& camera);
    void updateSpriteTexture(sf::RenderWindow& window, Camera const& camera);
        
    sf::Sprite sp;
    Hex* hex = nullptr;

    Hex::Type last_type;
    int last_x;
    int last_y;

    static float HEIGHT_HEX_PIXELS;
    static float WIDTH_HEX_PIXELS;
};

#endif
