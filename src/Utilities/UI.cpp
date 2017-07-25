#include <Utilities/UI.h>

UI::Element::Element(std::string const& name) : size({0, 0}), position({0, 0}), marge({0, 0, 0, 0}), name(name) {

}

UI::Element::~Element() {

}

void UI::Element::changeMarge (UI::Element::Marge marges) {
    changeMarge(marges.left, marges.top, marges.right, marges.bottom);
}

void UI::Element::changeMarge (float left, float top, float right, float bottom) {
    marge = {left, top, right, bottom};
    updateSize();
}

float UI::Element::getLeftMarge() const {
    return marge.left;
}

float UI::Element::getTopMarge() const {
    return marge.top;
}

float UI::Element::getBottomMarge() const {
    return marge.bottom;
}

float UI::Element::getRightMarge() const {
    return marge.right;
}

float UI::Element::getVerticalMarge() const {
    return getBottomMarge() + getTopMarge();
}  

float UI::Element::getHorizontalMarge() const {
    return getRightMarge() + getLeftMarge();
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


UI::Element::Position UI::Element::getRelativePosition() {
    return { position.x, position.y };
}

UI::Element::Position UI::Element::getAbsolutePosition() {
    if (parent) {
        auto parentPos = parent->getAbsolutePosition();
        auto relativePos = getRelativePosition();
        return { relativePos.x + parentPos.x, relativePos.y + parentPos.y };
    } else {
        return getRelativePosition();
    }
}

void UI::Element::changeSize (float width, float height) {
    size.width = width + getHorizontalMarge();
    size.height = height + getVerticalMarge();
    if (parent) {
        parent->updateSize();
    }
}

void UI::Element::updateSize () {
    changeSize(0, 0);
}

void UI::Element::setOnClick(UI::Element::onClickFunc func) {
    onClick = func;
}


void UI::Element::show (UI const& 
#if DEBUG > 1
                                          ui) {
    auto abs_pos = getAbsolutePosition();
    sf::RectangleShape box_collider({size.width, size.height});
    box_collider.setPosition(abs_pos);
    box_collider.setOutlineColor(sf::Color::Blue);
    box_collider.setOutlineThickness(6);
    ui.draw(box_collider);
#else
                                          ) {
#endif
}

bool UI::Element::manageOnClick(int x, int y) {
    auto abs_pos = getAbsolutePosition();
    if (abs_pos.x > x || 
        abs_pos.x + size.width < x ||
        abs_pos.y > y ||
        abs_pos.y + size.height < y)
        return false;
    
    if (onClick)
        onClick();

    return onClick != nullptr;
}

UI::Text::Text(std::string const& name) : Element(name) {
    changeMarge(5, 5, 5, 5);
}

UI::Text::~Text() {
    
}

UI::Text::Text(std::string const& name, sf::Text text) : Element(name), text(text) {
    changeMarge(5, 5, 5, 5);
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

void UI::Text::show (UI const& ui) {
    auto abs_pos = getAbsolutePosition();
    auto bounds = text.getLocalBounds();
#if DEBUG > 1
    sf::RectangleShape box_collider({size.width, size.height});
    box_collider.setPosition(abs_pos);
    box_collider.setOutlineColor(sf::Color::Red);
    box_collider.setOutlineThickness(2);
    ui.draw(box_collider);
#endif

    abs_pos.x -= bounds.left;
    abs_pos.y -= bounds.top;

    text.setPosition(abs_pos);
    ui.draw(text);
}

void UI::Text::updateSize () {
    auto bounds = text.getLocalBounds();
    changeSize(bounds.width, bounds.height);
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

    e->position.x = getLeftMarge();
    e->position.y = size.height - getBottomMarge();

    if (size.width < e->size.width)
        changeSize(e->size.width, size.height - getVerticalMarge() + e->size.height);
    else
        changeSize(size.width - getHorizontalMarge(), size.height - getVerticalMarge() + e->size.height);
}

void UI::Panel::push_front(Element* e) {
    insert(e, 0);
}

void UI::Panel::insert(Element* e, size_t pos) {
    float offset = e->size.height;
    auto it = elems.begin() + pos;

    e->position.x = (*it)->position.x;
    e->position.y = (*it)->position.y;

    for (; it != elems.end(); ++it)
        (*it)->position.y += offset;
    elems.insert(elems.begin() + pos, e);
    e->setParent(this);

    if (size.width < e->size.width)
        changeSize(e->size.width, size.height - getVerticalMarge() + offset);
    else
        changeSize(size.width - getHorizontalMarge(), size.height - getVerticalMarge() + offset);
}

void UI::Panel::removeAt(size_t pos) {
    auto to_remove = (elems.begin() + pos);
    float offset = (*to_remove)->size.height;
    auto it = elems.begin() + pos + 1;

    while(it != elems.end()) {
        (*it)->position.y -= offset;
        ++it;
    }

    delete *to_remove;
    elems.erase(to_remove);

    if (size.width == (*to_remove)->size.width) {
        float width_max = 0;
        for (auto* e : elems)
            if (width_max < e->size.width)
                width_max = e->size.width;

        changeSize(width_max, size.height - getVerticalMarge() - offset);
    } else
        changeSize(size.width - getHorizontalMarge(), size.height - getVerticalMarge() - offset);
}

bool UI::Panel::manageOnClick(int x, int y) {
    auto abs_pos = getAbsolutePosition();
    if (abs_pos.x > x || 
        abs_pos.x + size.width < x ||
        abs_pos.y > y ||
        abs_pos.y + size.height < y)
        return false;

    for (auto* e : elems)
        if (e->manageOnClick(x, y))
            return true;
    
    if (onClick)
        onClick();

    return true;
}

void UI::Panel::show (UI const& ui) {
#if DEBUG > 1
    sf::RectangleShape box_collider({size.width, size.height});
    box_collider.setPosition(getAbsolutePosition());
    box_collider.setOutlineColor(sf::Color::Green);
    box_collider.setOutlineThickness(4);
    ui.draw(box_collider);
#endif
    for (auto* e : elems)
        e->show(ui);
}

void UI::Panel::updateSize () {
    float width = 0;
    float height = 0;
    for (auto* e : elems) {
        if (e->size.width > width)
            width = e->size.width;
        e->position.y = height + getTopMarge();
        height += e->size.height;
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

    return root->manageOnClick(x, y - scrollDelta);
}

void UI::manageScroll(float delta) {
    scrollDelta += delta * UI_SCROLL_FACTOR;
    if (scrollDelta > 0)
        scrollDelta = 0;
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
    if (root) {
        current_window = &window;
        root->show(*this);
    } else
        std::cout << "NO ROOT" << std::endl;
}

void UI::draw (sf::Text& text) const {
    auto pos = text.getPosition();
    text.setPosition(pos.x, pos.y + scrollDelta);
    current_window->draw(text);
}

void UI::draw (sf::Sprite& sp) const {
    auto pos = sp.getPosition();
    sp.setPosition(pos.x, pos.y + scrollDelta);
    current_window->draw(sp);
}

void UI::draw (sf::Shape& sh) const {
    auto pos = sh.getPosition();
    sh.setPosition(pos.x, pos.y + scrollDelta);
    current_window->draw(sh);
}