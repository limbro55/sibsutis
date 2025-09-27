#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>

const int WIDTH = 800;
const int HEIGHT = 600;

void drawGraph(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    double x, f1, f2;
    for (x = -5; x <= 5; x += 0.1) {
        f1 = sqrt(25 - pow(x, 2));
        f2 = 2;

        if (f1 >= f2) {
            int px = (x + 5) * (WIDTH / 10);
            int py = HEIGHT - (f1 * (HEIGHT / 10));
            SDL_RenderDrawPoint(renderer, px, py);
        }
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Graph");

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        drawGraph(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
