#include <SFML/Graphics.hpp>
#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>


class GUISettings{
    ImGui::Combo combo; 
    ImGui::InputFloat speed;
    ImGui::InputFloat scale;
    ImGui::SliderFloat redSlider;
    ImGui::SliderFloat greenSlider;
    ImGui::SliderFloat blueSlider;
}