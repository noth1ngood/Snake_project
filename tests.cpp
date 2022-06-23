#include "Source.h"
#include <doctest.h>
TEST_CASE("add_apple")
{
    snake snake;
    int cell_count = 12;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            snake.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }
    int empty_number = rand() % cell_count;
    for (int i = 0; i < empty_number; i++)
    {
        apple_spawn(snake);
    }
    bool proverka = false;
    for (int j = 0; j < field_size_x; j++)
    {
        for (int i = 0; i < field_size_y; i++)
        {
            if (snake.field[j][i] == FIELD_CELL_TYPE_APPLE)
            {
                proverka = true;
            }
        }
    }
            CHECK(proverka);
}
TEST_CASE("add_help")
{
    snake snake;
    int cell_count = 15;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            snake.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }
    int empty_number = rand() % cell_count;
    for (int i = 0; i < empty_number; i++)
    {
        apple_spawn(snake);
    }
    bool proverka = false;
    for (int j = 0; j < field_size_x; j++)
    {
        for (int i = 0; i < field_size_y; i++)
        {
            if (snake.field[j][i] == FIELD_CELL_TYPE_APPLE)
            {
                proverka = true;
            }
        }
    }
            CHECK(proverka);
}
///ожидаю, что функция вернет false
TEST_CASE("telodvizhenia1"){
    snake snake;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            snake.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }
    for (int j = 0; j < 10; j++)
    {
        snake.field[0][j] = j + 1;
    }
    snake.field[0][5] = WALL;
    snake.snake_pos_x = 0;
    snake.snake_pos_y = 4;
    movement(snake);
    bool answer = (snake.field[1][5] > 0 and snake.field[0][11] > 0);
            CHECK(!answer);
}
TEST_CASE("telodvizhenia1"){
    snake snake;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            snake.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }
    for (int j = 0; j < 10; j++)
    {
        snake.field[0][j] = j + 1;
    }
    snake.field[0][5] = WALL;
    snake.snake_pos_x = 15;
    snake.snake_pos_y = 15;
    snake.snake_napr = SNAKE_MOVE_UP;
    movement(snake);
    bool answer = (snake.field[16][15] > 0 );
            CHECK(!answer);
}
TEST_CASE("stena"){
    snake snake;
    for (int j = 0; j < field_size_y; j++) {
        for (int i = 0; i < field_size_x; i++) {
            snake.field[j][i] = FIELD_CELL_TYPE_NONE;
        }
    }

    for (int i = 0; i < 5; i++) {
        snake.field[0][i] = WALL;
    }
    bool answer = (snake.field[0][4] == -2 and snake.field[0][3] == -2 and snake.field[0][2] == -2 and snake.field[0][1] == -2 and snake.field[0][0] == -2);
            CHECK(answer);
}
