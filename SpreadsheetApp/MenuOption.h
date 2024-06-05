#pragma once
#include <string>
#include <functional>

class MenuOption 
{
private:
    std::string text;
    int order;
    std::function<void()> action; 

public:
    MenuOption();
    MenuOption(const std::string& text, int order, const std::function<void()>& action);

    const std::string& getText() const;
    int getOrder() const;
    void executeAction() const;
};
