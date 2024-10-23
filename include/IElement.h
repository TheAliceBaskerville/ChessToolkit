#ifndef IELEMENT_H
#define IELEMENT_H

#include <optional>
#include "Coordinates.h"
#include "SFML/Graphics/Drawable.hpp"

class IElement
{
public:
    virtual ~IElement() = default;

    virtual Coordinates getPosition() = 0;
    virtual IElement& setPosition(Coordinates position) = 0;

    virtual sf::Drawable getElement() = 0;
    virtual IElement& setElement(const sf::Drawable& element) = 0;

    virtual std::optional<std::function<void()>> getFunctor() = 0;
    virtual IClickable& setFunction(const std::optional<std::function<void()>>& functor) = 0;

    virtual std::string getTag() = 0;
};

#endif