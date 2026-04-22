#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include <Config.hpp>

struct Logo {
    sf::Texture texture;
    sf::IntRect rect;
};

class Window {
public:
    Window(const int wWidth, const int wHeight);
    void Run();

private:
    Config config;
    const char* _logos[];
    static int _selectedLogo;
    static float _speed;
    static float _scale;
    static char _pauseText[20];
    static float _logoColor[3];


    


};



