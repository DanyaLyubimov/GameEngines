#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include <Config.hpp>

struct Logo {
    sf::Texture texture;
    sf::IntRect rect;
};


class LogoRect{
public:
    sf::Texture emptyTexture;
    float posx = 500;
    float posy = 250; 
    float speed;
    float x = 1.0f;
    float y = 1.0f;
    float scale;
    int selectedLogo = 0;
    float color[3];
    Logo logos[3];
    sf::Sprite sprite;

    LogoRect() = default;
    LogoRect(const std::string* logoPaths, int logoRects[12], float speed = 1.0, float scale = 1.0, float r=0.0f, float g=1.0f, float b=0.0f);
    void updateSprite();
    void setColor(float r, float g, float b);
    void setSpriteInitialPos();
    void checkColision(float wSizex, float wSizey);
};