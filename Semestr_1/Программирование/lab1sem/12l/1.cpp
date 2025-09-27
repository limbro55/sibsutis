#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH 800
#define HEIGHT 600
#define NUM_SNOWFLAKES 100

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} Snowflake;

int main() {
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Создание окна
    SDL_Window *window = SDL_CreateWindow("Снежная карусель", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    if (window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    // Создание рендера
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // цвета
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // массив со снежинками
    Snowflake snowflakes[NUM_SNOWFLAKES];
    srand(time(NULL));
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        snowflakes[i].x = rand() % WIDTH;
        snowflakes[i].y = rand() % HEIGHT;
        snowflakes[i].dx = rand() % 7 - 3;
        snowflakes[i].dy = rand() % 5 + 1;
    }

    // Основной цикл программы
    int running = 1;
    while (running) {
        // Обработка событий
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Заполнение фона цветом
        SDL_RenderClear(renderer);

        // Отрисовка снежинок
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int i = 0; i < NUM_SNOWFLAKES; i++) {
            SDL_RenderDrawPoint(renderer, snowflakes[i].x, snowflakes[i].y);

            // Изменение координат снежинок
            snowflakes[i].x += snowflakes[i].dx;
            snowflakes[i].y += snowflakes[i].dy;

            // Проверка выхода за границы окна
            if (snowflakes[i].x < 0 || snowflakes[i].x > WIDTH) {
                snowflakes[i].x = rand() % WIDTH;
                snowflakes[i].y = rand() % HEIGHT;
            }

            if (snowflakes[i].y > HEIGHT) {
                snowflakes[i].y = rand() % HEIGHT;
            }
        }

        // Обновление экрана
        SDL_RenderPresent(renderer);

        // Задержка
        SDL_Delay(50);
    }

    // Освобождение ресурсов
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}