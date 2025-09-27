#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#define PI 3.14159265359

typedef uint8_t byte;

byte grid[15][12]; 
byte colliders[15][12]; 

struct Vec2 //хранения координат ячейки
{
    byte y, x;
    Vec2() {}
    Vec2(byte dy, byte dx) : x(dx), y(dy) {}
};

// Фигура тетриса
struct Piece
{
    Vec2 a, b, c, d;// коорд 4 клеток
    Piece() {}
    Piece(byte ax, byte ay, byte bx, byte by, byte cx, byte cy, byte dx, byte dy)
        : a(Vec2(ax, ay)), b(Vec2(bx, by)), c(Vec2(cx, cy)), d(Vec2(dx, dy)) {}
    Piece(Vec2 da, Vec2 db, Vec2 dc, Vec2 dd)
        : a(da), b(db), c(dc), d(dd) {}
};

// Типы фигур
enum PIECE_TYPE
{
    S, Z, L, J, SQR, I, T
};

// Создание фигуры тетриса, задавая координаты 4 ячеек
Piece CreatePiece(PIECE_TYPE type)
{
    switch (type)
    {
    case S: 
    // Возвращаем фигуру S с заданными координатами 4 ячеек
    return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(0, 4), Vec2(2, 5));
    case Z: 
    return Piece(Vec2(1, 4), Vec2(1, 5), Vec2(0, 5), Vec2(2, 4));
    case L: 
    return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 6));
    case J: 
    return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 4));
    case SQR: 
    return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(0, 5), Vec2(0, 4));
    case I: 
    return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(1, 7));
    case T: 
    return Piece(Vec2(1, 5), Vec2(1, 4), Vec2(1, 6), Vec2(0, 5));
    default: 
    break;
    }
}


//поворот фигуры 
void rotate(Piece& piece)
{
    // Устанавливаем угол поворота в 90 градусов
    float angle = 90 * (PI / 180);
    
    // Вычисляем смещения для точек B, C и D относительно точки A
    float b_offset_x = piece.b.x - piece.a.x;
    float c_offset_x = piece.c.x - piece.a.x;
    float d_offset_x = piece.d.x - piece.a.x;
    float b_offset_y = piece.b.y - piece.a.y;
    float c_offset_y = piece.c.y - piece.a.y;
    float d_offset_y = piece.d.y - piece.a.y;

    // Поворачиваем каждую точку на угол angle относительно точки A
    float pbx = piece.a.x + (b_offset_x * std::cos(angle) - b_offset_y * std::sin(angle));
    float pby = piece.a.y + (b_offset_x * std::sin(angle) + b_offset_y * std::cos(angle));
    float pcx = piece.a.x + (c_offset_x * std::cos(angle) - c_offset_y * std::sin(angle));
    float pcy = piece.a.y + (c_offset_x * std::sin(angle) + c_offset_y * std::cos(angle));
    float pdx = piece.a.x + (d_offset_x * std::cos(angle) - d_offset_y * std::sin(angle));
    float pdy = piece.a.y + (d_offset_x * std::sin(angle) + d_offset_y * std::cos(angle));

    // Проверяем, не пересекаются ли повернутые точки с какими-либо объектами или стенами
    // и не находятся ли они в крайних позициях поля
    if (colliders[(byte)pby][(byte)pbx] != 2 &&
        colliders[(byte)pcy][(byte)pcx] != 2 &&
        colliders[(byte)pdy][(byte)pdx] != 2 &&
        piece.a.x != 1 && piece.a.y != 1)
    {
        // Если все точки прошли проверку, обновляем координаты точек B, C и D
        piece.b.x = pbx;
        piece.b.y = pby;
        piece.c.x = pcx;
        piece.c.y = pcy;
        piece.d.x = pdx;
        piece.d.y = pdy;
    }
}


int main()
{
    // 16x16 тайлы
    sf::Texture tile_tex;
    if (!tile_tex.loadFromFile("../tetris_tile.png")) {
        std::cerr << "Failed to load image\n";
        return -1;
    }

    // Создание спрайта тайла и масштабирование
    sf::Sprite tile(tile_tex);
    tile.setScale(2.83, 2.83);

    // Вычисление размера тайла и размеров окна
    float tile_size = tile_tex.getSize().x * tile.getScale().x;
    size_t width = tile_size * 12, height = tile_size * 15; // Высота уменьшена до 15 строк

    // Настройка счетчика очков
    sf::Text score;
    sf::Font font;
    if (!font.loadFromFile("Forwa_font.TTF")) {
        std::cerr << "Failed to load font\n";
        return -1;
    }
    score.setFont(font);
    score.setCharacterSize(15);
    score.setFillColor(sf::Color::Blue);
    score.setPosition(10, height + 10); // Позиция счетчика
    sf::Vector2<float> score_scale(1.5f, 1.5f);//маштабирование текста
    score.setScale(score_scale);
    score.setString("Lines: 0");

    // Настройка окна и создание первой фигуры
    sf::RenderWindow window(sf::VideoMode(width, height + 50), "Tetris", sf::Style::Titlebar | sf::Style::Close); 
    window.setKeyRepeatEnabled(true);//для повторного ввода
    window.setFramerateLimit(60);//частота кадров

    Piece piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));

    unsigned int timer = 0, gamespeed = 10, scoreCounter = 0;
    bool isDownPressed = false;

    // Главный цикл игры
    while (window.isOpen())
    {
        srand(time(NULL));

        sf::Event event;
        // Обработка всех событий
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                window.close();// закрытие окна про esc
            }
            if (event.type == sf::Event::KeyPressed)
            {
                // Управление движением
                if (event.key.code == sf::Keyboard::Up)
                {
                    rotate(piece); // Поворот фигуры при нажатии на стрелку вверх
                }
                else if (event.key.code == sf::Keyboard::Left &&
                    piece.a.x != 0 && piece.b.x != 0 && piece.c.x != 0 && piece.d.x != 0 &&
                    (colliders[piece.a.y][piece.a.x - 1]) != 2 && (colliders[piece.b.y][piece.b.x - 1]) != 2 &&
                    (colliders[piece.c.y][piece.c.x - 1]) != 2 && (colliders[piece.d.y][piece.d.x - 1]) != 2)
                {
                    piece.a.x--;//сдвиг фигуры влево
                    piece.b.x--;
                    piece.c.x--;
                    piece.d.x--;
                }
                else if (event.key.code == sf::Keyboard::Right &&
                    piece.a.x != 11 && piece.b.x != 11 && piece.c.x != 11 && piece.d.x != 11 &&
                    (colliders[piece.a.y][piece.a.x + 1]) != 2 && (colliders[piece.b.y][piece.b.x + 1]) != 2 &&
                    (colliders[piece.c.y][piece.c.x + 1]) != 2 && (colliders[piece.d.y][piece.d.x + 1]) != 2)
                {
                    piece.a.x++;//сдвиг фигуры вправо
                    piece.b.x++;
                    piece.c.x++;
                    piece.d.x++;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    gamespeed = 1;//увеличение скорости фигур вниз
                    isDownPressed = true;
                }
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down)
            {
                gamespeed = 10;// возвращение скорости фигур при отпущенной кнопки
                isDownPressed = false;
            }
        }

        // Очистка и заполнение сетки
        for (size_t i = 0; i < 15; i++) 
        {
            for (size_t j = 0; j < 12; j++)
            {
                if (grid[i][j] == 1)
                {
                    grid[i][j] = 0;
                }
            }
        }

        grid[piece.a.y][piece.a.x] = 1;
        grid[piece.b.y][piece.b.x] = 1;
        grid[piece.c.y][piece.c.x] = 1;
        grid[piece.d.y][piece.d.x] = 1;

        window.clear();

        if (timer == gamespeed)
        {
            // Если есть коллайдеры снизу или фигура внизу экрана
            if (
                grid[piece.a.y + 1][piece.a.x] == 2 ||
                grid[piece.b.y + 1][piece.b.x] == 2 ||
                grid[piece.c.y + 1][piece.c.x] == 2 ||
                grid[piece.d.y + 1][piece.d.x] == 2 ||
                piece.a.y == 14 || piece.b.y == 14 || piece.c.y == 14 || piece.d.y == 14
                )
            {
                grid[piece.a.y][piece.a.x] = 2;
                grid[piece.b.y][piece.b.x] = 2;
                grid[piece.c.y][piece.c.x] = 2;
                grid[piece.d.y][piece.d.x] = 2;

                colliders[piece.a.y][piece.a.x] = 2;
                colliders[piece.b.y][piece.b.x] = 2;
                colliders[piece.c.y][piece.c.x] = 2;
                colliders[piece.d.y][piece.d.x] = 2;

                piece = CreatePiece(static_cast<PIECE_TYPE>((rand() % 7)));
            }
            else
            {
                grid[piece.a.y + 1][piece.a.x] = 1;
                grid[piece.b.y + 1][piece.b.x] = 1;
                grid[piece.c.y + 1][piece.c.x] = 1;
                grid[piece.d.y + 1][piece.d.x] = 1;

                piece.a.y++;
                piece.b.y++;
                piece.c.y++;
                piece.d.y++;
            }

            // Проверка на наличие линии или "тетриса"
            //проход по всем строкам
            for (size_t i = 0; i < 15; i++) 
            {
                byte blocks_in_a_row = 0;// кол-во заполненых блоков
                //просмотр коллон
                for (size_t j = 0; j < 12; j++)
                {
                    if (colliders[i][j] == 2)
                    {
                        blocks_in_a_row++;
                    }
                }
                //проверка на полную строку
                if (blocks_in_a_row == 12)
                {
                    //удаление строки 
                    for (size_t k = i; k > 0; k--)
                    {
                        for (size_t l = 0; l < 12; l++)
                        {
                            colliders[k][l] = colliders[k - 1][l];
                        }
                    }
                    scoreCounter++;// увеличение счета
                    char temp[256];
                    sprintf(temp, "Lines: %i", scoreCounter);
                    score.setString(temp);
                }
            }

            // Если игра окончена, закрыть приложение
            for (size_t i = 0; i < 12; i++)
            {
                if (colliders[0][i] == 2)
                {
                    window.close();
                }
            }

            timer = 0;
        }
        else
        {
            timer++;
        }

        // Отрисовка всех тайлов
        for (size_t i = 0; i < 15; i++) 
        {
            for (size_t j = 0; j < 12; j++)
            {
                //отрисовка падающей фигуры
                if (grid[i][j] == 1)
                {
                    sf::Sprite t = tile;
                    t.setPosition(tile_size * j, tile_size * i);
                    window.draw(t);
                }
                //отрисовка находящийся фигуры
                if (colliders[i][j] == 2)
                {
                    sf::Sprite t = tile;
                    t.setPosition(tile_size * j, tile_size * i);
                    window.draw(t);
                }
            }
        }

        // Отрисовка счетчика очков и обновление окна
        window.draw(score);
        window.display();
    }

    return 0;
}