#include <Utilities/GameEngine.h>

GameEngine::GameEngine() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Magic Tower", sf::Style::Titlebar | sf::Style::Close) {
    //window.setFramerateLimit(WINDOW_FPS);
    window.setPosition({500, 0});

    PrefabFactory::useEnvironement(&env);
}

GameEngine::~GameEngine() {

}

int GameEngine::start() {
    SceneManager::changeScene(SceneManager::Scene::Game);
    SceneManager::onNewFrame();

    haz::Time time;

    auto* m = env.instantiate("map");
    m->addComponent<Map>();
    
    env.print_to_tree();

    while (window.isOpen()) {
        time.update();

        SceneManager::onNewFrame();

        manageEvents();
        manageUpdates(time);
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
    
    sf::Vector2u screen = window.getSize();
    sf::Vector2f positionOffset = to_sfml<float>(camera.getPosition() + (to_haz<float, unsigned int>(screen) / 2.f));
    float positionFactor = camera.getZoom() * Renderer::pixel_per_unit;

    for (auto* rend : Renderer::get()) {
        auto partialSprite = rend->getPartialSprite();

        partialSprite.position = partialSprite.position * positionFactor + positionOffset;
        partialSprite.scale *= camera.getZoom();

        sf::Sprite sprite = partialSprite.to_sprite();
        auto bounds = sprite.getGlobalBounds();

        if (bounds.left < screen.x && bounds.top < screen.y && (bounds.left + bounds.width) > 0 && (bounds.top + bounds.height) > 0) {
            window.draw(sprite);
        }
    }

    window.display();
}

void GameEngine::manageUpdates(haz::Time const& time) {
    Input::updateButtonsStates(window);

    for(auto* c : env.getAllComponents()) {
        c->update(time, &env);
    }

    if (Input::isReleased(Input::Button::MouseLeft)) {
        auto mouse_screen_position = Input::getMousePosition();
        auto mouse_world_position = (mouse_screen_position - (to_haz<float, unsigned int>(window.getSize()) / 2.f) - camera.getPosition()) / (camera.getZoom() * Renderer::pixel_per_unit);
        std::cout << "mouse_screen_position : " << mouse_screen_position << std::endl;
        std::cout << "mouse_world_position : " << mouse_world_position << std::endl;
        auto hex = haz::_2D::Physic::raycast_first(&env, mouse_world_position, haz::Layers::Ground);
        if (hex) {
            hex->pretty_console();
        } else {
            std::cout << "Nothing under the mouse" << std::endl;
        }
    }

    camera.moveZoom(Input::getScroll());
}
