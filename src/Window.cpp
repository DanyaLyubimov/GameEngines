#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>

#include <Window.hpp>

Window::Window(std::string configPath){
    cfg.load("/home/vboxuser/GameDev/config.txt");
    cfg.printConfigs();

    window.create(sf::VideoMode({cfg.getInt("window_size", 0), cfg.getInt("window_size", 1)}), "my window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    Initialize();

}


void Window::Initialize(){
    std::string logosPaths[3] = {cfg.getString("paths_to_logos", 0), cfg.getString("paths_to_logos", 1), cfg.getString("paths_to_logos", 2)};
    logo = std::make_shared<LogoRect>(logosPaths, cfg.getIntVec("logos_rects").data());

    //  char str[20]
    // strncpy(this->str, str.data(), 19);
    // str[19] = '\0';
    text = std::make_shared<TextObj>(cfg.getString("pause", 0).data(), cfg.getString("path_to_font", 0), getCenterPos());
}

void Window::Run(){
    while (window.isOpen())
    {
        UpdateUserInput();
        UpdateLogic();
        UpdateGui();
        Render();
    }

}

void Window::UpdateUserInput(){
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
};

void Window::UpdateLogic(){
    if (!pause){
        logo->updateSprite();
    }
    text->updateText();
};

void Window::UpdateGui(){
            ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_Always);
        ImGui::Begin("Sample window", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Sample text");
        ImGui::NewLine();
        // ImGui::Checkbox("shold draw", &shouldDraw);
        ImGui::SetNextItemWidth(1000);
        ImGui::Combo("Select logo", &logo->selectedLogo, logosCombo, 3);
        ImGui::NewLine();
        ImGui::InputFloat("Speed", &logo->speed);
        ImGui::NewLine();
        ImGui::InputFloat("Scale", &logo->scale);
        ImGui::NewLine();
        ImGui::SliderFloat("Red", &logo->color[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Green", &logo->color[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Blue", &logo->color[2], 0.0f, 1.0f);
        ImGui::NewLine();
        if (ImGui::Button("Reset")){
            logo->setSpriteInitialPos();
        }
        ImGui::InputText("Pause", text->str, 20);

        ImGui::End();
}


void Window::Render(){
    window.clear(sf::Color::Black);
    

    if(pause){
        window.draw(text->text);
    } else{

        logo->checkColision(window.getSize().x, window.getSize().y);

        window.draw(logo->sprite);
    }

    ImGui::SFML::Render(window);
    window.display();
}

sf::Vector2f Window::getCenterPos(){
    return {
        window.getSize().x / 2,
        window.getSize().y / 2
    };
}


