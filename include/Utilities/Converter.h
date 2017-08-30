#ifndef __CONVERTER
#define __CONVERTER

#include <SFML/Graphics.hpp>
#include <frameworkHaz/2DGOInclude.hpp>

template<typename T, typename TT = T>
sf::Vector2<T> to_sfml(haz::_2D::Vector<TT> const& v) {
    return {static_cast<T>(v.x), static_cast<T>(v.y)};
}

template<typename T, typename TT = T>
haz::_2D::Vector<T> to_haz(sf::Vector2<TT> const& v) {
    return {static_cast<T>(v.x), static_cast<T>(v.y)};
}

#endif