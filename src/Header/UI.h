#ifndef __UI
#define __UI

#include <functional>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>

class UI {
public:
    class Element {
    public:
        friend UI;
        typedef std::function<void()> onClickFunc;

        Element(std::string const& name = "");
        virtual ~Element();

        void setOnClick(onClickFunc func);
        virtual bool manageOnClick(int x, int y);
        virtual void show (sf::RenderWindow& window);
        std::string getName();

    private:
        sf::Vector2f getRelativePosition();
        sf::Vector2f getAbsolutePosition();

        void changeSize (float width, float height);
        virtual void updateSize ();

        void setParent(Element* new_parent);

        sf::FloatRect collision;

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

        void show (sf::RenderWindow& window);

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
        void show (sf::RenderWindow& window);

    private:
        virtual void updateSize ();

        std::vector<Element*> elems = {};
    };

    UI();
    ~UI();

    bool manageOnClick(int x, int y);
    void show (sf::RenderWindow& window);

    void clear();
    void resetRoot(UI::Element* elem);


private:
    Element* root = nullptr;
};

#endif