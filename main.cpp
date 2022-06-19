#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <comdef.h>
#include "string"

#define FIELD_CELL_TYPE_NONE 0
#define FIELD_CELL_TYPE_APPLE -1
#define WALL -2
#define HELP -3
#define SNAKE_MOVE_UP 0
#define SNAKE_MOVE_RIGHT 1
#define SNAKE_MOVE_DOWN 2
#define SNAKE_MOVE_LEFT 3
//объявляем константы, такие как размер поля(в клетках), размер клетки(в пикселях), размер окна, длина змеи вначале
//кол-во клеток по x
const int field_size_x = 55;
//кол-во клеток по y
const int field_size_y = 30;
//размер клеток в пикселях
const int cell_size = 32;
//длина змеи
int snake_len = 4;
//определяем размеры окна
const int field_widht = field_size_x * cell_size;
const int field_height = field_size_y * cell_size;
//двумерный массив, в котором хранятся координаты
int field[field_size_y][field_size_x];
//стартовая позиция змейки
int snake_pos_x = field_size_x / 2;
int snake_pos_y = field_size_y / 2;
//начальное направление змейки
int snake_napr = SNAKE_MOVE_RIGHT;
//переменная определяющая, закончилась ли игра
bool gameover = false;
//переменная типа bool, используется в level()
bool level_proverka = false;
//начальное значение сложности(time sleep)
int hard_level = 100;
int score_num = 0;
int randomcell() {
    int cell_count = 0;
    //пересчитываем свободные клетки, в которых ничего нет, то есть FIELD_CELL_TYPE_NONE
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (field[j][i] == FIELD_CELL_TYPE_NONE) {
                cell_count++;
            }
        }
    }
    //выбираем номер пустой клекти, считая от левого верхнего угла
    //путем нахождения остатка от деления рамдомного числа на выбранное
    int empty_number = rand() % cell_count;
    int cell_index = 0;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if (field[j][i] == FIELD_CELL_TYPE_NONE) {
                if (cell_index == empty_number) {
                    return j * field_size_x + i;
                }
                cell_index++;
            }
        }
    }
    return gameover = true;
}

void apple_spawn(){
    int apple_position = randomcell();
    if (apple_position != -1) {
        field[apple_position / field_size_x][apple_position % field_size_x] = FIELD_CELL_TYPE_APPLE;
    }
    if (apple_position == -1 ) {
        gameover = true;
    }
}
void help_spawn() {
    int help_position = randomcell();
    if (help_position != -1 ) {
        field[help_position / field_size_x][help_position % field_size_x] = HELP;
    }
}
void clear_field()
{
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }
    for (int i = 0; i < snake_len; i ++){
        field[snake_pos_y][snake_pos_x - i] = snake_len - i;
    }
    apple_spawn();
    help_spawn();
}

void draw_field(sf::RenderWindow &window) {

    sf::Texture body_texture;
    body_texture.loadFromFile("image/snake.png");
    sf::Sprite body;
    body.setTexture(body_texture);

    sf::Texture wall_texture;
    wall_texture.loadFromFile("image/wall.png");
    sf::Sprite wall;
    wall.setTexture(wall_texture);

    sf::Texture help_texture;
    help_texture.loadFromFile("image/cursor.png");
    sf::Sprite help;
    help.setTexture(help_texture);

    sf::Texture apple_texture;
    apple_texture.loadFromFile("image/apple.png");
    sf::Sprite apple;
    apple.setTexture(apple_texture);

    sf::Texture none_texture;
    none_texture.loadFromFile("image/none.png");
    sf::Sprite none;
    none.setTexture(none_texture);


    for (int x = 12; x < field_size_x - 12; x++) {
        field[0][x] = WALL;
        field[field_size_y - 1][x] = WALL;
    }

    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            switch (field[j][i]) {
                case FIELD_CELL_TYPE_NONE:
                    none.setPosition(i * cell_size, j * cell_size);
                    window.draw(none);
                    break;
                case WALL:
                    wall.setPosition(i * cell_size, j * cell_size);
                    window.draw(wall);
                    break;
                case FIELD_CELL_TYPE_APPLE:
                    apple.setPosition(i * cell_size, j * cell_size);
                    window.draw(apple);
                    break;
                case HELP:
                    help.setPosition(i * cell_size, j * cell_size);
                    window.draw(help);
                    break;
                default:
                    body.setPosition(i * cell_size, j * cell_size);
                    window.draw(body);
                    break;
            }
        }
    }
    sf::Font font;
    font.loadFromFile("fonts/font.otf");
    sf::Text score;
    score.setFont(font);
    score.setCharacterSize(30);
    score.setString("Score: " + std::to_string(score_num));
    score.setPosition(field_widht / 15, 1);
    window.draw(score);
}
/*
 * Функция movement() описывает движение змейки и изменение ее длины
 * snake_pos_y и snake_pos_x -- координаты головы змейки
 * snake_napr -- напрвление змейки
 */

void movement()
{
    switch (snake_napr) {
        case SNAKE_MOVE_UP:
            snake_pos_y--;
            if (snake_pos_y < FIELD_CELL_TYPE_NONE) {
                snake_pos_y = field_size_y - 1;
            }
            break;
        case SNAKE_MOVE_RIGHT:
            snake_pos_x++;
            if (snake_pos_x > field_size_x - 1) {
                snake_pos_x = FIELD_CELL_TYPE_NONE;
            }

            break;
        case SNAKE_MOVE_DOWN:
            snake_pos_y++;
            if (snake_pos_y > field_size_y - 1) {
                snake_pos_y = FIELD_CELL_TYPE_NONE;
            }
            break;
        case SNAKE_MOVE_LEFT:
            snake_pos_x--;
                if (snake_pos_x < FIELD_CELL_TYPE_NONE) {
                    snake_pos_x = field_size_x - 1;
                }
            break;
    }
    //змейка попадает в одну из ячеек поля и получает определенные измения в длине или скорости движения
    if (field[snake_pos_y][snake_pos_x] != FIELD_CELL_TYPE_NONE) {
        switch (field[snake_pos_y][snake_pos_x]) {
            case FIELD_CELL_TYPE_APPLE:
                snake_len++;
                score_num++;
                apple_spawn();
                level_proverka = true;
                break;
            case HELP:
                snake_len--;
                hard_level += 7;
                help_spawn();
                level_proverka = true;
                break;
            default:
                gameover = true;
        }
    }

    field[snake_pos_y][snake_pos_x] = snake_len + 1;
    //удаление хвоста змейки при ее движении на одну ячейку в выбранном направлении
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            if(field[j][i] > FIELD_CELL_TYPE_NONE){
                field[j][i]--;
            }

        }
    }
}
/*
 * Функция keyboard() считавыет нажатия клавиш(стрелочек) и меняет направление змейки
 * snake_napr - переменная, определяющая начальное направление змейки(в моем случае вправо)
 */
void keyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        if (snake_napr != SNAKE_MOVE_DOWN) {
            snake_napr = SNAKE_MOVE_UP;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        if (snake_napr != SNAKE_MOVE_UP) {
            snake_napr = SNAKE_MOVE_DOWN;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        if (snake_napr != SNAKE_MOVE_RIGHT) {
            snake_napr = SNAKE_MOVE_LEFT;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        if (snake_napr != SNAKE_MOVE_LEFT) {
            snake_napr = SNAKE_MOVE_RIGHT;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        gameover = true;
    }
}
/*
 * Функция определяет, с какой скоростью будет передвигаться змейка
 * snake_len --длина змейки
 * level_proverka -- переменная, которая проверяет, что змейка прибавила в длине, переменная требуется для того
 * чтобы скорость змейки не меняласть при неизменной длине
 * hard_level -- переменная, определяющаяя задержку в отрисовывании поля
 * Вся суть функции в том, что с ростом длины змейки уменьшается время сна отрисовки поля
 */
void level()
{
    if (level_proverka) {
        switch (snake_len % 4) {
            case 0://если длина 4, 8, 12, 16, ....
                hard_level -= 3;
                level_proverka = false;
            case 2://если длина 6, 10, 14, 18, ....
                hard_level -= 1;
                level_proverka = false;
        }
    }
}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(field_widht, field_height), "Snake", sf::Style::Close);

    clear_field();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        movement();
        if (gameover) {
            sf::sleep(sf::seconds(1));
            window.close();
        }
        window.clear(sf::Color(120, 165 , 210));
        //отрисовываем поле
        draw_field(window);
        keyboard();
        window.display();
        level();
        sf::sleep(sf::milliseconds(hard_level));
    }

    return 0;
}