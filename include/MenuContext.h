#ifndef MENUCONTEXT_H
#define MENUCONTEXT_H

#include <unordered_set>
#include <memory>
#include "IElement.h"

class MenuContext {
    private:
        std::unordered_set<std::unique_ptr<IElement>> elements;
    public:
        MenuContext();
        ~MenuContext() = default;
        MenuContext& createElement(std::unique_ptr<IElement> element);
        MenuContext& deleteElement(std::unique_ptr<IElement> element);
};

#endif