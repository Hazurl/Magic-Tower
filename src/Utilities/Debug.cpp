#include <Utilities/Debug.h>

Debug::Debug(GameState* gameState, Input* input) : gameState(gameState), input(input), window(sf::VideoMode(400, 800), "Debug", sf::Style::Titlebar | sf::Style::Close) {
    window.setPosition({1300, 0});

    FontLoader::load("Debug_Scene", "Font/Roboto-Regular.ttf", "roboto");
    rebuild();
}

Debug::~Debug () {
    if (window.isOpen())
        window.close();
}

void Debug::use(GameState* gameState) {
    this->gameState = gameState;
    rebuild();
}

void Debug::use(Input* input) {
    this->input = input;
    rebuild();
}

void Debug::rebuild() {
    UI::Panel* menu = new UI::Panel("Menu");
    if(gameState)
        menu->push_back(load(gameState, "gameState"));
    if(input)
        menu->push_back(load(input, "input"));

    ui.resetRoot(menu);
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
        if (event.type == sf::Event::MouseWheelScrolled) {
            ui.manageScroll(event.mouseWheelScroll.delta);
        }
    }

    window.clear(sf::Color::White);

    ui.show(window);

    window.display();
}

sf::Text Debug::createText(sf::String const& str) {
    sf::Text text;
    text.setFont(*FontLoader::get("Debug_Scene", "roboto"));
    text.setCharacterSize(24);
    text.setColor(sf::Color::Black);
    text.setString(str);

    return std::move(text);
}

UI::Panel* Debug::createCollapsablePanel(std::string const& name, sf::Text title, std::function<void(UI::Panel*)> onClickFunc) {
    UI::Panel* panel = new UI::Panel(name);
    //panel->changeMarge(0, 10, 0, 0);
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

            UI::Panel* sub_panel = new UI::Panel("list");
            sub_panel->changeMarge(15, 0, 0, 0);

            if (onClickFunc)
                onClickFunc(sub_panel);
            panel->push_back(sub_panel);
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
