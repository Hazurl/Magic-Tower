#include <Utilities/GameEngine.h>

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower", sf::Style::Titlebar | sf::Style::Close) {
    //window.setFramerateLimit(WINDOW_FPS);
    window.setPosition({500, 0});
}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
    SceneManager::changeScene(SceneManager::Scene::Game);
    SceneManager::onNewFrame();

    haz::Engine::start();

    auto* map = (new haz::GameObject("map"))->addComponent<Map>();

    camera = (new haz::GameObject("camera"))->addComponent<Camera>(SCREEN_WIDTH, SCREEN_HEIGHT);
    camera->addComponent<CameraMotionControler>(camera->getComponent<Camera>(), haz::_2D::Vectorf(map->getSize(), map->getSize()));

    camera->gameobject()->pretty_console();
    haz::GameObject::findOfName("map")->getComponent<Map>()->getHexAt(0,0)->gameobject()->pretty_console();
    
    //env.print_to_tree();

    while (window.isOpen()) {
        SceneManager::onNewFrame();

        manageEvents();
        manageUpdates();
        manageDraw();
    }

    return 0;
}

void GameEngine::manageEvents() {
    Input::resetEvents();
    sf::Event e;
    while (window.pollEvent(e)) {
        switch (e.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseWheelScrolled:
            Input::onScrollEvent(e.mouseWheelScroll.delta);
            break;

        default: 
            break;
        }
    }
}

void GameEngine::manageDraw() {
    window.clear(sf::Color(50, 50, 50));
    
    sf::Vector2f cameraPos = to_sfml<float>(camera->transform()->globalPosition());
    sf::Vector2f screenOffset = sf::Vector2f {camera->width() / 2, camera->height() / 2};
    float positionFactor = camera->zoom() * Renderer::pixel_per_unit;


    for (auto* rend : Renderer::get()) {
        auto partialSprite = rend->getPartialSprite();

        partialSprite.position = (partialSprite.position - cameraPos) * positionFactor + screenOffset;
        partialSprite.scale *= camera->zoom();

        sf::Sprite sprite = partialSprite.to_sprite();
        auto bounds = sprite.getGlobalBounds();

        if (bounds.left < camera->width() && bounds.top < camera->height() && (bounds.left + bounds.width) > 0 && (bounds.top + bounds.height) > 0) {
            window.draw(sprite);
        }
    }

    window.display();
}

void GameEngine::manageUpdates() {
    Input::updateButtonsStates(window);

    haz::Engine::update();

    if (Input::isReleased(Input::Button::MouseLeft)) {
        auto mouse_screen_position = Input::getMousePosition();
        auto mouse_world_position = (mouse_screen_position - (to_haz<float, unsigned int>(window.getSize()) / 2.f) 
                                     - camera->transform()->position()) / (camera->zoom() * Renderer::pixel_per_unit);
        std::cout << "mouse_screen_position : " << mouse_screen_position << std::endl;
        std::cout << "mouse_world_position : " << mouse_world_position << std::endl;
        auto hex = haz::_2D::Physic::raycast_first(mouse_world_position, haz::Layers::Ground);
        if (hex) {
            hex->pretty_console();
        } else {
            std::cout << "Nothing under the mouse" << std::endl;
        }
    }

    if (Input::isReleased(Input::Button::Space)) {
        camera->gameobject()->pretty_console();
    }
}
