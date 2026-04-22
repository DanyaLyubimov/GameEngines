#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include <config.hpp>

struct Logo {
    sf::Texture texture;
    sf::IntRect rect;
};

int main(){
    loadConfig("/home/vboxuser/GameDev/config.txt");
    printConfigs();
    
    sf::RenderWindow window(sf::VideoMode({120, 800}), "my window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    const char* logos[] = {
        "DVD",
        "BlueRay",
        "CD"
    };

    bool shouldDraw = true;
    static int selectedLogo = 0;
    static float speed = 5.0f;
    static float scale = 0.5f;
    static char pause_text[20] = "Pause"; 
    float color[3] = {1.0f, 0.0f, 0.0f};

    Logo texture_logos[3];

    texture_logos[0].texture.loadFromFile("/home/vboxuser/GameDev/logos/DVDLogo.png");
    texture_logos[0].rect = sf::IntRect({0,100}, {540, 340});

    texture_logos[1].texture.loadFromFile("/home/vboxuser/GameDev/logos/CDLogo.png");
    texture_logos[1].rect = sf::IntRect({0,0}, {1200, 581});

    texture_logos[2].texture.loadFromFile("/home/vboxuser/GameDev/logos/BluRayLogo.png");
    texture_logos[2].rect = sf::IntRect({0,0}, {783, 522});
    
    for(auto& tex : texture_logos){
        tex.texture.setSmooth(true);
        tex.texture.setRepeated(false);
    }

    sf::Vector2f center(
        window.getSize().x / 2,
        window.getSize().y / 2
    );

    sf::Sprite sprite(texture_logos[0].texture);
    sprite.setTextureRect(texture_logos[0].rect);
    sprite.setColor(sf::Color(color[0]*255, color[1]*255, color[2]*255));
    sprite.setScale({scale, scale});
    sprite.setPosition(center);
    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.size / 2.f);


    sf::Font font("/home/vboxuser/GameDev/fonts/futura.ttf");


    sf::Text text(font);
    text.setString("Pause");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(center);
    

    sf::Clock deltaClock;


    int x = 1;
    int y = 1;
    bool pause = false;


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()){
            window.close();
            }else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                auto a = keyPressed->scancode;
                if (a == sf::Keyboard::Scancode::Escape){
                    window.close();
                }else if (a == sf::Keyboard::Scancode::Space){
                    pause = !pause;
                }
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_Always);
        ImGui::Begin("Sample window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Sample text");
        ImGui::NewLine();
        // ImGui::Checkbox("shold draw", &shouldDraw);
        ImGui::SetNextItemWidth(1000);
        ImGui::Combo("Select logo", &selectedLogo, logos, 3);
        ImGui::NewLine();
        ImGui::InputFloat("Speed", &speed);
        ImGui::NewLine();
        ImGui::InputFloat("Scale", &scale);
        ImGui::NewLine();
        ImGui::SliderFloat("Red", &color[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &color[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &color[2], 0.0f, 1.0f);
        ImGui::NewLine();
        if (ImGui::Button("Reset")){
            sprite.setPosition(center);
        }
        ImGui::InputText("Pause", pause_text, 20);
        sprite.setTexture(texture_logos[selectedLogo].texture);
        sprite.setTextureRect(texture_logos[selectedLogo].rect);
        sprite.setScale({scale, scale});
        sprite.setColor(sf::Color(color[0]*255, color[1]*255, color[2]*255));
        text.setString(pause_text);

        ImGui::End();

        window.clear(sf::Color::Black);
        

        if(pause){
            window.draw(text);
        } else{
            sprite.move({x*speed, y*speed});

            sf::FloatRect bounds = sprite.getGlobalBounds();
            

            if ((bounds.position.y + bounds.size.y >= window.getSize().y) || (bounds.position.y <= 0)){
                y = -y;
            }
            if ((bounds.position.x + bounds.size.x >= window.getSize().x )|| (bounds.position.x <= 0)){
                x = -x;
            }

            window.draw(sprite);
        }

        ImGui::SFML::Render(window);
        window.display();
        
    }
}