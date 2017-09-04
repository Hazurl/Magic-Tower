#include <Components/Renderer/Renderer.h>

const float Renderer::pixel_per_unit = 50;

sf::Sprite Renderer::PartialSprite::to_sprite() const {
    texture->setSmooth(true);
    sf::Sprite sprite(*texture);

    sprite.setScale(scale);
    sprite.setOrigin(texture_rect.width / 2, texture_rect.height / 2);
    sprite.setRotation(rotation);
    sprite.setPosition(position);

    return std::move(sprite);
}


Renderer::Renderer(haz::GameObject* go) : haz::Subscriber<Renderer>(), Component(go) {

}

Renderer::~Renderer() {
    
}

haz::Component* Renderer::clone(haz::GameObject* go) const {
    auto* r = new Renderer(go);
    r->partialSprite = partialSprite;
    return r;
}

std::vector<std::string> Renderer::pretty_strings() const {
    return {
        "Texture : " + haz::adress(partialSprite.texture),
        "TextureRect : (" + std::to_string(partialSprite.texture_rect.left) + ", " + std::to_string(partialSprite.texture_rect.top) + ") of size " + 
        "(" + std::to_string(partialSprite.texture_rect.width) + ", " + std::to_string(partialSprite.texture_rect.height) + ")",
        "Position : " + to_haz<float>(partialSprite.position).to_string(),
        "Rotation : " + std::to_string(partialSprite.rotation),
        "Scale : " + to_haz<float>(partialSprite.scale).to_string(),
    };
}

void Renderer::onEnable() {
    subscribe();
}

void Renderer::onDisable() {
    unsubscribe();
}

void Renderer::update() {

}

Renderer::PartialSprite Renderer::getPartialSprite() {
    haz::_2D::Vectorf haz_scale = transform()->globalScale();
    partialSprite.scale = {haz_scale.x * scale_factor_width, haz_scale.y * scale_factor_height};
    
    partialSprite.rotation = transform()->globalRotation();

    haz::_2D::Vectorf haz_pos = transform()->globalPosition();
    partialSprite.position = {haz_pos.x, haz_pos.y};
    
    return partialSprite;
}

void Renderer::changeTexture(sf::Texture& texture) {
    partialSprite.texture = &texture;
    partialSprite.texture_rect = {0, 0, static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y)};

    scale_factor_height = pixel_per_unit / static_cast<float>(partialSprite.texture_rect.height);
    scale_factor_width = pixel_per_unit / static_cast<float>(partialSprite.texture_rect.width);
}
