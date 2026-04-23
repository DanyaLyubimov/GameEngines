#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include<Logo.hpp>
#include<Config.hpp>
#include<Text.hpp>

class Window {
public:
    Config cfg;
    std::shared_ptr<LogoRect> logo;
    std::shared_ptr<TextObj> text;

    sf::RenderWindow window;
    sf::Clock deltaClock;
    const char* logosCombo[3] = {
        "DVD",
        "CD",
        "BlueRay"
    };
    bool pause = false;

    Window(std::string configPath);
    sf::Vector2f getCenterPos();
    void Initialize();

    void UpdateUserInput();
    void UpdateLogic();
    void UpdateGui();
    void Render();
    void Run();
};
