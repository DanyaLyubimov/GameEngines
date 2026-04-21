#include <SFML/Graphics.hpp>
#include <iostream>

int main(){
    sf::RenderWindow window(sf::VideoMode({1520, 800}), "my window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    sf::Texture texture("/home/vboxuser/GameDev/logos/DVDLogo.png");
    texture.setSmooth(true);
    texture.setRepeated(true);

    sf::Sprite sprite(texture);
    sprite.setTextureRect(sf::IntRect({0,100}, {540, 340}));
    sprite.setColor(sf::Color(0, 255, 0));
    sprite.setScale({0.5f, 0.5f});
    sprite.setPosition({10.f, 50.f});


    sf::Font font("/home/vboxuser/GameDev/fonts/futura.ttf");
    sf::Vector2f center(
        window.getSize().x / 2,
        window.getSize().y / 2
    );

    sf::Text text(font);
    text.setString("Pause");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(center);
    


    float x = 5.0f;
    float y = 5.0f;
    bool pause = false;


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
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

        window.clear(sf::Color::Black);

        if(pause){
            window.draw(text);
        } else{
            sprite.move({x, y});

            sf::FloatRect bounds = sprite.getGlobalBounds();
            

            if ((bounds.position.y + bounds.size.y >= window.getSize().y) || (bounds.position.y <= 0)){
                y = -y;
            }
            if ((bounds.position.x + bounds.size.x >= window.getSize().x )|| (bounds.position.x <= 0)){
                x = -x;
            }

            window.draw(sprite);
        }

        window.display();
        
    }
}