#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <comdef.h>
#include "string"
#include "Source.h"

int main()
{
    snake snake;
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(field_widht, field_height), "Snake", sf::Style::Close);

    clear_field(snake);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        movement(snake);
        if (snake.gameover) {
            sf::sleep(sf::seconds(1));
            window.close();
        }
        window.clear(sf::Color(120, 165 , 210));
        //отрисовываем поле
        draw_field(window, snake);
        keyboard(snake);
        window.display();
        level(snake);
        sf::sleep(sf::milliseconds(snake.hard_level));
    }

    return 0;
}