#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

typedef struct {
    SDL_Window   *window;
    SDL_Renderer *renderer;
    bool          running;
} App;

static bool init(App *app, const char *title, int w, int h) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    if (!SDL_CreateWindowAndRenderer(title, w, h, 0, &app->window, &app->renderer)) {
        SDL_Log("Window/renderer creation failed: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    app->running = true;
    return true;
}

static void handle_events(App *app) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            app->running = false;
        }
    }
}

static void update(App *app) {
    (void)app;
    // game logic here
}

static void render(App *app) {
    SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
    SDL_RenderClear(app->renderer);

    // draw stuff here

    SDL_RenderPresent(app->renderer);
}

static void cleanup(App *app) {
    SDL_DestroyRenderer(app->renderer);
    SDL_DestroyWindow(app->window);
    SDL_Quit();
}

int main(void) {
    App app = {0};

    if (!init(&app, "SDL3 Boilerplate", 800, 600)) {
        return 1;
    }

    while (app.running) {
        handle_events(&app);
        update(&app);
        render(&app);
    }

    cleanup(&app);
    return 0;
}
