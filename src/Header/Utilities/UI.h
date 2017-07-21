#ifndef __UI
#define __UI

#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

#include "DebugMacro.h"

#define UI_SCROLL_FACTOR 25;

class UI {
public:
    class Element {
    public:
        friend UI;
        typedef std::function<void()> onClickFunc;

        typedef sf::Vector2f Position;
        struct Size { float width, height; };
        struct Marge { float left, top, right, bottom; };

        Element(std::string const& name = "");
        virtual ~Element();

        void setOnClick(onClickFunc func);
        virtual bool manageOnClick(int x, int y);
        virtual void show (UI const& ui);
        std::string getName();

        float getLeftMarge() const;
        float getTopMarge() const;
        float getBottomMarge() const;
        float getRightMarge() const;
        float getHorizontalMarge() const;
        float getVerticalMarge() const;
        
        void changeMarge (Marge marges);
        void changeMarge (float left, float top, float right, float bottom);

    private:
        Position getRelativePosition();
        Position getAbsolutePosition();

        void changeSize (float width, float height);
        virtual void updateSize ();

        void setParent(Element* new_parent);

        Size size;
        Position position;
        Marge marge;

        onClickFunc onClick = nullptr;

        Element* parent = nullptr;

        std::string name = "";
    };

    class Text : public Element {
    public:
        Text(std::string const& name = "");
        Text(std::string const& name, sf::Text text);
        Text(sf::Text text);
        ~Text();

        void setString (sf::String const& str);
        void setColor (sf::Color const& color);
        void setCharacterSize (unsigned int size);
        void setFont(sf::Font const& font);

        void show (UI const& ui);

    private:
        virtual void updateSize ();

        sf::Text text;
    };

    class Panel : public Element {
    public:
        Panel(std::string const& name = "");
        ~Panel();

        void push_back(Element* e);
        void push_front(Element* e);
        void insert(Element* e, size_t pos);
        void removeAt(size_t pos);

        Element* getElementAt(size_t pos);

        bool manageOnClick(int x, int y);
        void show (UI const& ui);

    private:
        virtual void updateSize ();

        std::vector<Element*> elems = {};
    };

    UI();
    ~UI();

    bool manageOnClick(int x, int y);
    void manageScroll(float delta);
    void show (sf::RenderWindow& window);

    void clear();
    void resetRoot(UI::Element* elem);

    void draw (sf::Text& text) const;
    void draw (sf::Sprite& sp) const;
    void draw (sf::Shape& sh) const;

private:
    Element* root = nullptr;

    sf::RenderWindow* current_window = nullptr;

    float scrollDelta = 0;
};

#endif