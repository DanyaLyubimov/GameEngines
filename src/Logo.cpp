#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include<Logo.hpp>

LogoRect::LogoRect(const std::string* logoPaths, float logoRects[12], float speed, float scale, float r, float g, float b):speed(speed), scale(scale), emptyTexture(), sprite(emptyTexture){
    
    setColor(r, g, b);

    for (int i =0; i<3; i++){
        logos[i].texture.loadFromFile(logoPaths[i]);
        logos[i].texture.setSmooth(true);
        logos[i].texture.setRepeated(false);
        logos[i].rect = sf::IntRect({logoRects[i*4], logoRects[i*4+1]}, {logoRects[i*4+2], logoRects[i*4+3]});
    }

    updateSprite();
}

void LogoRect::updateSprite(){
    sprite.setTexture(logos[selectedLogo].texture);
    sprite.setTextureRect(logos[selectedLogo].rect);
    sprite.setColor(sf::Color(color[0]*255, color[1]*255, color[2]*255));
    sprite.setScale({scale, scale});
    sprite.setPosition({posx, posy});
}

void LogoRect::setColor(float r, float g, float b){
    color[0] = r;
    color[2] = g;
    color[3] = b;
}