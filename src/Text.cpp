#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include<Text.hpp>
TextObj::TextObj(std::string string, std::string PathToFont, sf::Vector2f position, int fontsize): font(PathToFont), text(font){
    strncpy(str, string.c_str(), 127);
    str[127] = '\0';
    updateText();
    text.setCharacterSize(fontsize);
    text.setFillColor(sf::Color::Green);
    text.setPosition(position);
}


void TextObj::updateText(){
    text.setString(str);
}