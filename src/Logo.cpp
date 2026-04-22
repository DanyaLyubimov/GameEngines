#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include<Logo.hpp>

LogoRect::LogoRect(const std::string* logoPaths, int logoRects[12], float speed, float scale, float r, float g, float b):speed(speed), scale(scale), emptyTexture(), sprite(emptyTexture){
    
    setColor(r, g, b);

    for (int i =0; i<3; i++){
        bool load = logos[i].texture.loadFromFile(logoPaths[i]);
        logos[i].texture.setSmooth(true);
        logos[i].texture.setRepeated(false);
        logos[i].rect = sf::IntRect({logoRects[i*4], logoRects[i*4+1]}, {logoRects[i*4+2], logoRects[i*4+3]});
        std::cout<<load<<"\n";
    }

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.size / 2.f);
    setSpriteInitialPos();

    updateSprite();
}

void LogoRect::updateSprite(){
    sprite.setTexture(logos[selectedLogo].texture);
    sprite.setTextureRect(logos[selectedLogo].rect);
    sprite.setColor(sf::Color(color[0]*255, color[1]*255, color[2]*255));
    sprite.setScale({scale, scale});
    sprite.setPosition({sprite.getPosition().x + speed*x, sprite.getPosition().y + speed*y});
}

void LogoRect::setColor(float r, float g, float b){
    color[0] = r;
    color[2] = g;
    color[3] = b;
}

void LogoRect::setSpriteInitialPos(){
    sprite.setPosition({posx, posy});
}

void LogoRect::checkColision(float wSizex, float wSizey){
    sf::FloatRect bounds = sprite.getGlobalBounds();

    if (bounds.position.y <= 0){
        y = 1;
    }

    if (bounds.position.y + bounds.size.y >= wSizey){
        y = -1;
    }

    if (bounds.position.x <= 0){
        x = 1;
    }

    if (bounds.position.x + bounds.size.x >= wSizex){
        x = -1;
    }
    //old
    // if ((bounds.position.y + bounds.size.y >= wSizey) || (bounds.position.y <= 0)){
    //     y = -y;
    // }
    // if ((bounds.position.x + bounds.size.x >= wSizex)|| (bounds.position.x <= 0)){
    //    x = -x;
    // }
}