#include <Window.hpp>

int main(){
    std::string config = "/home/vboxuser/GameDev/config.txt";
    Window window(config);
    window.Run();
}