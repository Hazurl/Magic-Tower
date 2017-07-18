#include "../Header/Debug.h"

Debug::Debug() : window(sf::VideoMode(400, 800), "Debug") {
    RessourcesLoader::load<sf::Font>("roboto", "Font/Roboto-Regular.ttf");
}

Debug::~Debug () {

}

void Debug::use(const Map* map) {
    this->map = map;
    ui.resetRoot(load(map));
}

UI::Panel* Debug::load(const Map* map) {
    return createCollapsablePanel("Map", createText(std::string(typeid(Map).name()).substr(1) + " map"), [map, this] (UI::Panel* panel) {
        for (auto& hex : map->hexs) {
            panel->push_back(load(&hex.second));
        }
    });
}

UI::Panel* Debug::load(const Hex* hex) {
    return createCollapsablePanel("Hex", createText("." + std::string(typeid(Hex).name()).substr(1) + " hex"), [hex, this] (UI::Panel* panel) {
        sf::Text textx = createText(". x : " + std::to_string(hex->x));
        sf::Text texty = createText(". y : " + std::to_string(hex->y));
        panel->push_back(new UI::Text("X", textx));
        panel->push_back(new UI::Text("Y", texty));
    });
}

void Debug::update() {
    if (!window.isOpen())
        return;
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            ui.clear();
            return;
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            ui.manageOnClick(event.mouseButton.x, event.mouseButton.y);
        }
    }

    window.clear(sf::Color::White);

    ui.show(window);

    window.display();
}

sf::Text Debug::createText(sf::String const& str) {
    sf::Text text;
    text.setFont(*RessourcesLoader::get<sf::Font>("roboto"));
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setString(str);

    return std::move(text);
}

UI::Panel* Debug::createCollapsablePanel(std::string const& name, sf::Text title, std::function<void(UI::Panel*)> onClickFunc) {
    UI::Panel* panel = new UI::Panel(name);
    sf::String title_str_collapse = "> " + title.getString();
    sf::String title_str_not_collapse = "v " + title.getString();
    title.setString(title_str_collapse);
    panel->push_back(new UI::Text("Title", title));
    bool collapsed = true;

    panel->setOnClick([panel, title_str_collapse, title_str_not_collapse, onClickFunc, collapsed]() mutable {
        if (collapsed) {
            collapsed = false;
            if (UI::Text* _title = dynamic_cast<UI::Text*>( panel->getElementAt(0) ) )
                _title->setString(title_str_not_collapse);

            if (onClickFunc)
                onClickFunc(panel);
        } else {
            collapsed = true;
            if (UI::Text* _title = dynamic_cast<UI::Text*>( panel->getElementAt(0) ) )
                _title->setString(title_str_collapse);
            
            while (panel->getElementAt(1) != nullptr)
                panel->removeAt(1);
        }
    });

    return panel;
}
