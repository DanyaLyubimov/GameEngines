#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include <Config.hpp>
#include <Logo.hpp>


// class TestWindow{
//     Config config;

//     void all_work(){

//     }
// }



int main(){
    Config cfg;

    cfg.load("/home/vboxuser/GameDev/config.txt");
    cfg.printConfigs();
    
    sf::RenderWindow window(sf::VideoMode({cfg.getInt("window_size", 0), cfg.getInt("window_size", 1)}), "my window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);
    std::string logosPaths[3] = {cfg.getString("paths_to_logos", 0), cfg.getString("paths_to_logos", 1), cfg.getString("paths_to_logos", 2)};
    LogoRect logo(logosPaths, cfg.getIntVec("logos_rects").data());

    const char* logos[] = {
        "DVD",
        "CD",
        "BlueRay"
    };


    static char pause_text[20] = "Pause"; 
    sf::Vector2f center(
        window.getSize().x / 2,
        window.getSize().y / 2
    );

    // logo.sprite.setPosition(center);
    // sf::FloatRect spriteBounds = logo.sprite.getLocalBounds();
    // logo.sprite.setOrigin(spriteBounds.size / 2.f);


    sf::Font font("/home/vboxuser/GameDev/fonts/futura.ttf");


    sf::Text text(font);
    text.setString("Pause");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(center);
    

    sf::Clock deltaClock;


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
        ImGui::Combo("Select logo", &logo.selectedLogo, logos, 3);
        ImGui::NewLine();
        ImGui::InputFloat("Speed", &logo.speed);
        ImGui::NewLine();
        ImGui::InputFloat("Scale", &logo.scale);
        ImGui::NewLine();
        ImGui::SliderFloat("Red", &logo.color[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &logo.color[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &logo.color[2], 0.0f, 1.0f);
        ImGui::NewLine();
        if (ImGui::Button("Reset")){
            logo.setSpriteInitialPos();
        }
        ImGui::InputText("Pause", pause_text, 20);
        logo.updateSprite();
        text.setString(pause_text);

        ImGui::End();

        window.clear(sf::Color::Black);
        

        if(pause){
            window.draw(text);
        } else{

            logo.checkColision(window.getSize().x, window.getSize().y);

            window.draw(logo.sprite);
        }

        ImGui::SFML::Render(window);
        window.display();
        
    }
}