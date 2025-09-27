#ifndef SFML_CLASS_H
#define SFML_CLASS_H

#endif //SFML_CLASS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;
const int UNIT_SIZE = 10;
const float SPEED = 0.1f;

using namespace sf;
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

// Виртуальный базовый класс
class Entity {
public:
    virtual void draw(RenderWindow &window) = 0; // Виртуальная функция отрисовки
    virtual ~Entity() = default; // Виртуальный деструктор
};

class Menu {
private:
    Font font;
    Text title;
    vector<Text> menuItems; // Пункты меню
    int selectedIndex;           // Текущий выбранный пункт
    RectangleShape background;   // Фон меню

    // Список пунктов меню
    const vector<string> menuOptions = {"Start Game", "Settings", "Exit"};

public:
    Menu() : selectedIndex(0) {
        // Загрузка шрифта
        if (!font.loadFromFile("../snake/texture/ArialRegular.ttf")) {
            cerr << "Не удалось загрузить шрифт!" << endl;
        }

        // Настройка фона
        background.setSize(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        background.setFillColor(Color(50, 50, 50)); // Тёмно-серый фон

        // Настройка заголовка
        title.setFont(font);
        title.setString("Snake Game");
        title.setCharacterSize(50);
        title.setFillColor(Color::White);
        title.setStyle(Text::Bold);
        title.setPosition(WINDOW_WIDTH / 2 - 150, 100);

        // Настройка пунктов меню
        for (size_t i = 0; i < menuOptions.size(); i++) {
            Text text;
            text.setFont(font);
            text.setString(menuOptions[i]);
            text.setCharacterSize(30);
            text.setFillColor(i == selectedIndex ? Color::Red : Color::White); // Выбранный пункт красным
            text.setPosition(WINDOW_WIDTH / 2 - 100, 250 + static_cast<int>(i) * 50);
            menuItems.push_back(text);
        }
    }

    // Отрисовка меню
    void draw(RenderWindow &window) {
        window.draw(background); // Отрисовка фона
        window.draw(title);      // Отрисовка заголовка
        for (const auto &item : menuItems) {
            window.draw(item);   // Отрисовка пунктов
        }
    }

    // Навигация вверх
    void moveUp() {
        if (selectedIndex > 0) {
            menuItems[selectedIndex].setFillColor(Color::White); // Убираем выделение
            selectedIndex--;
            menuItems[selectedIndex].setFillColor(Color::Red);   // Новый выделенный пункт
        }
    }

    // Навигация вниз
    void moveDown() {
        if (selectedIndex < static_cast<int>(menuItems.size()) - 1) {
            menuItems[selectedIndex].setFillColor(Color::White); // Убираем выделение
            selectedIndex++;
            menuItems[selectedIndex].setFillColor(Color::Red);   // Новый выделенный пункт
        }
    }

    // Получение текущего выбора
    int getSelectedIndex() const {
        return selectedIndex;
    }
};



class Snake : public Entity {
protected:
    Texture Snaketexture;
    vector<RectangleShape> snake_blocks;
    Color color;
    Direction direction;
    bool alive;
    int score;
    int start_size = 10;

public:
    Snake(Color color, int startX, int startY)
            : color(color), direction(RIGHT), alive(true), score(0) {
        for (int i = 0; i < start_size; i++) {
            RectangleShape block(Vector2f(UNIT_SIZE, UNIT_SIZE));
            block.setFillColor(color);
            block.setPosition(startX - i * UNIT_SIZE, startY);
            snake_blocks.push_back(block);
        }
    }

    // Перегрузка оператора присваивания
    Snake& operator=(const Snake &other) {
        if (this != &other) {
            this->snake_blocks = other.snake_blocks;
            this->color = other.color;
            this->direction = other.direction;
            this->alive = other.alive;
            this->score = other.score;
            this->start_size = other.start_size;
        }
        return *this;
    }

    const RectangleShape& getHead() const {
        return snake_blocks[0];
    }

    void setDirection(Direction newDir) {
        if ((direction == LEFT && newDir != RIGHT) ||
            (direction == RIGHT && newDir != LEFT) ||
            (direction == UP && newDir != DOWN) ||
            (direction == DOWN && newDir != UP)) {
            direction = newDir;
        }
    }

    void move() {
        if (!alive) return;

        for (int i = snake_blocks.size() - 1; i > 0; --i) {
            snake_blocks[i].setPosition(snake_blocks[i - 1].getPosition());
        }

        Vector2f headPos = snake_blocks[0].getPosition();
        switch (direction) {
            case UP:    snake_blocks[0].move(0, -UNIT_SIZE); break;
            case DOWN:  snake_blocks[0].move(0, UNIT_SIZE); break;
            case LEFT:  snake_blocks[0].move(-UNIT_SIZE, 0); break;
            case RIGHT: snake_blocks[0].move(UNIT_SIZE, 0); break;
        }

        if (headPos.x < 0 || headPos.x >= WINDOW_WIDTH || headPos.y < 0 || headPos.y >= WINDOW_HEIGHT) {
            alive = false;
        }

        for (size_t i = 1; i < snake_blocks.size(); ++i) {
            if (snake_blocks[0].getGlobalBounds().intersects(snake_blocks[i].getGlobalBounds())) {
                alive = false;
            }
        }
    }

    void grow() {
        Vector2f tailPos = snake_blocks.back().getPosition();
        RectangleShape newBlock(Vector2f(UNIT_SIZE, UNIT_SIZE));
        newBlock.setFillColor(color);
        newBlock.setPosition(tailPos);
        snake_blocks.push_back(newBlock);
        score += 10;
    }

    void draw(RenderWindow &window) override {
        for (auto &block : snake_blocks) {
            window.draw(block);
        }
    }

    bool isAlive() const { return alive; }

    int getScore() const { return score; }

    // Метод для "убийства" змеи
    void kill() {
        alive = false;
    }

// Метод для получения блоков змеи
    const vector<RectangleShape>& getBlocks() const {
        return snake_blocks;
    }

};

// Food inherits from Entity
class Food : public Entity {
protected:
    CircleShape foodShape;
    Texture foodTexture;
    bool isBig;
    bool isActive;

public:
    Food(bool isBigFood) : isBig(isBigFood), isActive(false) {
        foodShape.setRadius(isBig ? UNIT_SIZE : UNIT_SIZE / 2);
        foodShape.setFillColor(isBig ? Color::Red : Color::Yellow);

        if (!foodTexture.loadFromFile("../snake/texture/apple.png")) {
            cerr << "Не удалось загрузить текстуру еды!" << endl;
        }
        foodShape.setTexture(&foodTexture);
    }

    void spawn() {
        isActive = true;
        float x = rand() % (WINDOW_WIDTH / UNIT_SIZE) * UNIT_SIZE;
        float y = rand() % (WINDOW_HEIGHT / UNIT_SIZE) * UNIT_SIZE;
        foodShape.setPosition(x, y);
    }

    void setActive(bool active) {
        isActive = active;
    }

    bool getActive() const {
        return isActive;
    }

    FloatRect getBounds() const {
        return foodShape.getGlobalBounds();
    }

    void draw(RenderWindow &window) override {
        if (isActive) {
            window.draw(foodShape);
        }
    }
};

class Score {
private:
    int player1Score;
    int player2Score;
    Font font;
    Text player1Text;
    Text player2Text;

public:
    // Конструктор
    Score() : player1Score(0), player2Score(0) {
        if (!font.loadFromFile("../snake/texture/ArialRegular.ttf")) {
            cerr << "Не удалось загрузить шрифт для очков!" << endl;
        }

        // Настройка текста для первого игрока
        player1Text.setFont(font);
        player1Text.setCharacterSize(20);
        player1Text.setFillColor(sf::Color::Red);
        player1Text.setPosition(10, 10);
        updateText(1);

        // Настройка текста для второго игрока
        player2Text.setFont(font);
        player2Text.setCharacterSize(20);
        player2Text.setFillColor(sf::Color::Green);
        player2Text.setPosition(WINDOW_WIDTH - 150, 10);
        updateText(2);
    }

    // Добавление очков
    void addPoints(int points, int player) {
        if (player == 1) {
            player1Score += points;
            updateText(1);
        } else if (player == 2) {
            player2Score += points;
            updateText(2);
        }
    }

    // Сброс очков
    void reset() {
        player1Score = 0;
        player2Score = 0;
        updateText(1);
        updateText(2);
    }

    // Отрисовка очков
    void draw(sf::RenderWindow &window) {
        window.draw(player1Text);
        window.draw(player2Text);
    }

private:
    // Обновление текста
    void updateText(int player) {
        if (player == 1) {
            player1Text.setString("Player 1: " + to_string(player1Score));
        } else if (player == 2) {
            player2Text.setString("Player 2: " + to_string(player2Score));
        }
    }
};

class Game {
private:
    RenderWindow window;
    Snake *snake1, *snake2;
    Font font;
    Menu menu;
    Food regularFood;
    Food bigFood;
    int regularFoodCounter;
    bool isPlaying;
    Score score;

public:
    Game() 
        : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game"), 
          regularFood(false), bigFood(true), 
          regularFoodCounter(0), isPlaying(false) 
    {
        window.setVerticalSyncEnabled(true);
        srand(static_cast<unsigned>(time(0)));
        regularFood.spawn();
    }

    ~Game() {
        delete snake1;
        delete snake2;
    }

    void run() {
        while (window.isOpen()) {
            if (isPlaying) {
                gameLoop();
            } else {
                menuLoop();
            }
        }
    }

private:
    void gameLoop() {
        Clock clock;
        snake1 = new Snake(Color::Red, 100, WINDOW_HEIGHT / 3);
        snake2 = new Snake(Color::Green, 100, (WINDOW_HEIGHT * 2) / 3);

        while (isPlaying) {
            Time elapsed = clock.getElapsedTime();
            if (elapsed.asSeconds() >= SPEED) {
                clock.restart();
                update();
            }
            processEvents();
            render();
        }

        delete snake1;
        delete snake2;
    }

    void menuLoop() {
        Event event;
        while (!isPlaying && window.isOpen()) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                window.close();
            }

            processMenuEvents();
            renderMenu();
        }
    }

    void processMenuEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }

        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Up) menu.moveUp();
            if (event.key.code == Keyboard::Down) menu.moveDown();
            if (event.key.code == Keyboard::Enter) {
                switch (menu.getSelectedIndex()) {
                case 0: // "Start Game"
                    isPlaying = true;
                    break;
                case 1: // "Settings"
                    cout << "Открыть настройки!" << endl;
                    break;
                case 2: // "Exit"
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }
    }
    }


    void processEvents() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) snake1->setDirection(UP);
                if (event.key.code == Keyboard::Down) snake1->setDirection(DOWN);
                if (event.key.code == Keyboard::Left) snake1->setDirection(LEFT);
                if (event.key.code == Keyboard::Right) snake1->setDirection(RIGHT);

                if (event.key.code == Keyboard::W) snake2->setDirection(UP);
                if (event.key.code == Keyboard::S) snake2->setDirection(DOWN);
                if (event.key.code == Keyboard::A) snake2->setDirection(LEFT);
                if (event.key.code == Keyboard::D) snake2->setDirection(RIGHT);
            }
        }
    }

    void update() {
    snake1->move();
    snake2->move();

    checkCollisions(snake1, snake2); // Проверка столкновений для первой змеи
    checkCollisions(snake2, snake1); // Проверка столкновений для второй змеи

        if (!snake1->isAlive() && !snake2->isAlive()) {
            isPlaying = false; // Игра завершается, если обе змеи мертвы
        }
    }


    void render() {
        window.clear();
        snake1->draw(window);
        snake2->draw(window);
        regularFood.draw(window);
        bigFood.draw(window);
        score.draw(window); // Отрисовка очков
        window.display();
}

    void renderMenu() {
        window.clear();
        menu.draw(window);
        window.display();
    }

    void checkCollisions(Snake *snake, Snake *otherSnake) {
    // Проверка на столкновение с едой
    if (snake->getHead().getGlobalBounds().intersects(regularFood.getBounds())) {
        snake->grow();
        regularFood.spawn();
        if (snake == snake1) {
            score.addPoints(10, 1);
        } else {
            score.addPoints(10, 2);
        }
    }

    if (snake->getHead().getGlobalBounds().intersects(bigFood.getBounds())) {
        snake->grow();
        snake->grow();
        bigFood.setActive(false);
        if (snake == snake1) {
            score.addPoints(20, 1);
        } else {
            score.addPoints(20, 2);
        }
    }

    // Проверка на столкновение с другой змеёй
    for (const auto &block : otherSnake->getBlocks()) {
        if (snake->getHead().getGlobalBounds().intersects(block.getGlobalBounds())) {
            snake->kill(); // Убиваем змею
            break;
        }
    }
    }

};