#include "../Header/UI.h"

UI::Element::Element(std::string const& name) : collision({0, 0, 0, 0}), name(name) {

}

UI::Element::~Element() {

}

void UI::Element::setParent(Element* new_parent) {
    parent = new_parent;
}


std::string UI::Element::getName() {
    if (parent)
        return parent->getName() + "." + name;
    else
        return name;
}


sf::Vector2f UI::Element::getRelativePosition() {
    return { collision.left, collision.top };
}

sf::Vector2f UI::Element::getAbsolutePosition() {
    if (parent) {
        auto parentPos = parent->getAbsolutePosition();
        return { collision.left + parentPos.x, collision.top + parentPos.y };
    } else {
        return { 10, 10 };
    }
}

void UI::Element::changeSize (float width, float height) {
    collision.width = width;
    collision.height = height;
    if (parent) {
        parent->updateSize();
    }
}

void UI::Element::updateSize () {
    
}

void UI::Element::setOnClick(UI::Element::onClickFunc func) {
    onClick = func;
}


void UI::Element::show (sf::RenderWindow& window) {
    assert(("Should not be call \"UI::Element::show\"", false));
}

bool UI::Element::manageOnClick(int x, int y) {
    auto abs_pos = getAbsolutePosition();
    if (abs_pos.x > x || 
        abs_pos.x + collision.width < x ||
        abs_pos.y > y ||
        abs_pos.y + collision.height < y)
        return false;
    
    if (onClick)
        onClick();

    return onClick != nullptr;
}

UI::Text::Text(std::string const& name) : Element(name) {
    
}

UI::Text::~Text() {
    
}

UI::Text::Text(std::string const& name, sf::Text text) : Element(name), text(text) {
    updateSize();
}

void UI::Text::setString (sf::String const& str) {
    text.setString(str);
    updateSize();
}

void UI::Text::setColor (sf::Color const& color) {
    text.setColor(color);
}

void UI::Text::setCharacterSize (unsigned int size) {
    text.setCharacterSize(size);
    updateSize();
}

void UI::Text::setFont(sf::Font const& font) {
    text.setFont(font);
    updateSize();
}

void UI::Text::show (sf::RenderWindow& window) {
#if DEBUG > 1
    auto abs_pos = getAbsolutePosition();
    sf::RectangleShape box_collider({collision.width, collision.height});
    box_collider.setPosition(abs_pos);
    box_collider.setOutlineColor(sf::Color::Red);
    box_collider.setOutlineThickness(2);
    window.draw(box_collider);

    text.setPosition(abs_pos);
#else
    text.setPosition(getAbsolutePosition());
#endif
    window.draw(text);
}

void UI::Text::updateSize () {
    auto bounds = text.getLocalBounds();
    changeSize(bounds.width, 50);
}

UI::Panel::Panel(std::string const& name) : Element(name), elems({}) {

}

UI::Panel::~Panel() {
    for (auto* e : elems)
        delete e;
    elems.clear();
}

void UI::Panel::push_back(Element* e) {
    elems.push_back(e);

    e->setParent(this);

    e->collision.left = 0;
    e->collision.top = collision.height;

    if (collision.width < e->collision.width)
        changeSize(e->collision.width, collision.height + e->collision.height);
    else
        changeSize(collision.width, collision.height + e->collision.height);
}

void UI::Panel::push_front(Element* e) {
    insert(e, 0);
}

void UI::Panel::insert(Element* e, size_t pos) {
    float offset = e->collision.height;
    auto it = elems.begin() + pos;

    e->collision.left = (*it)->collision.left;
    e->collision.top = (*it)->collision.top;

    for (; it != elems.end(); ++it)
        (*it)->collision.top += offset;
    elems.insert(elems.begin() + pos, e);
    e->setParent(this);

    if (collision.width < e->collision.width)
        changeSize(e->collision.width, collision.height + offset);
    else
        changeSize(collision.width, collision.height + offset);
}

void UI::Panel::removeAt(size_t pos) {
    auto to_remove = (elems.begin() + pos);
    float offset = (*to_remove)->collision.height;
    auto it = elems.begin() + pos + 1;

    while(it != elems.end()) {
        (*it)->collision.top -= offset;
        ++it;
    }

    delete *to_remove;
    elems.erase(to_remove);

    if (collision.width == (*to_remove)->collision.width) {
        float width_max = 0;
        for (auto* e : elems)
            if (width_max < e->collision.width)
                width_max = e->collision.width;

        changeSize(width_max, collision.height - offset);
    } else
        changeSize(collision.width, collision.height - offset);
}

bool UI::Panel::manageOnClick(int x, int y) {
    auto abs_pos = getAbsolutePosition();
    if (abs_pos.x > x || 
        abs_pos.x + collision.width < x ||
        abs_pos.y > y ||
        abs_pos.y + collision.height < y)
        return false;

    for (auto* e : elems)
        if (e->manageOnClick(x, y))
            return true;
    
    if (onClick)
        onClick();

    return true;
}

void UI::Panel::show (sf::RenderWindow& window) {
#if DEBUG > 1
    sf::RectangleShape box_collider({collision.width, collision.height});
    box_collider.setPosition(getAbsolutePosition());
    box_collider.setOutlineColor(sf::Color::Green);
    box_collider.setOutlineThickness(4);
    window.draw(box_collider);
#endif
    for (auto* e : elems)
        e->show(window);
}

void UI::Panel::updateSize () {
    float width = 0;
    float height = 0;
    for (auto* e : elems) {
        if (e->collision.width > width)
            width = e->collision.width;
        e->collision.top = height;
        height += e->collision.height;
    }
    changeSize(width, height);
}

UI::Element* UI::Panel::getElementAt(size_t pos) {
    if (pos >= elems.size())
        return nullptr;
    return elems.at(pos);
}

bool UI::manageOnClick(int x, int y) {
    if (!root)
        return false;

    return root->manageOnClick(x, y);
}

UI::UI() {
    
}

UI::~UI() {
    if (root) {
        delete root;
        root = nullptr;
    }
}

void UI::clear() {
    if (root) {
        delete root;
        root = nullptr;
    }
}

void UI::resetRoot(UI::Element* elem) {
    if (root) {
        delete root;
        root = nullptr;
    }

    root = elem;
}

void UI::show (sf::RenderWindow& window) {
    if (root)
        root->show(window);
    else
        std::cout << "NO ROOT" << std::endl;
}