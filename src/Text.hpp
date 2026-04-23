#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

class TextObj{
public:
    char str[128];
    sf::Text text;
    sf::Font font;
    int fontSize;
    sf::Vector2f position;

    TextObj(std::string string, std::string PathToFont, sf::Vector2f position = {500,250}, int fontsize = 24);
    void updateText();

};