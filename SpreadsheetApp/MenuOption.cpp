#include "MenuOption.h"

MenuOption::MenuOption()
    : text(""), order(0), action(nullptr) {}

MenuOption::MenuOption(const std::string& text, int id, const std::function<void()>& action)
    : text(text), order(order), action(action) {}

const std::string& MenuOption::getText() const 
{
    return text;
}

int MenuOption::getOrder() const 
{
    return order;
}

void MenuOption::executeAction() const 
{
    if (action)
    {
        action();
    }
}
