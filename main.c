#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <SDL3/SDL.h> 
#include <SDL3/SDL_main.h> 

// Global variables

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 320
#define CYCLES 644

int program_counter;
uint8_t memory[4096];

// Window Renderer

typedef struct {

	SDL_Window *window;
	SDL_Renderer *renderer;
	bool running;
} App;

static bool init(App *app, const char *title, int w, int h) {

	if(!SDL_Init(SDL_INIT_VIDEO)){

		SDL_Log("SDL_Init failed: %s", SDL_GetError());
		return false;
	}

	app->window = SDL_CreateWindow(title, w, h, 0);
	if (!app->window) {
	    SDL_Log("Window creation failed: %s", SDL_GetError());
	    SDL_Quit();
	    return false;
	}

	app->renderer = SDL_CreateRenderer(app->window, NULL);
	if (!app->renderer) {
	    SDL_Log("Renderer creation failed: %s", SDL_GetError());
	    SDL_DestroyWindow(app->window);
	    SDL_Quit();
	    return false;
	}
	app->running = true;
	return true;
}

static void handle_events(App *app) {

	SDL_Event event;
	while(SDL_PollEvent(&event)){

		if(event.type == SDL_EVENT_QUIT){

			app->running = false;
		}
	}
}

static void update( App *app) {

	(void)app;
}

static void render(App *app) {

	SDL_SetRenderDrawColor(app->renderer, 0, 255, 0, 255);
	SDL_RenderClear(app->renderer);


	SDL_RenderPresent(app->renderer);
}
static void cleanup(App *app) {

	SDL_DestroyRenderer(app->renderer);
	SDL_DestroyWindow(app->window);
	SDL_Quit();
}

// Load ROM into RAM

int fsize(const char *filename){

	struct stat sb;
	if(stat(filename, &sb) == -1){

		perror("dog");
		exit(EXIT_FAILURE);
	}

	return sb.st_size;
}

int load_rom(uint8_t RAM[], const char *filename){

	FILE *file =  fopen(filename, "r"); 
	for(int i = 0; i < (fsize(filename)*2); i++){
		fread(&RAM[i + 0x200], 1, fsize(filename), file); 
	}
}

// FDE Cycle
int fetch(int *PC, uint8_t RAM[]) {
	
	int MAR = *PC;
	int MDR = RAM[MAR];

	(*PC)++;
	return MDR;
}
int decode(int instruction){
	
		
}
int execute(int opcode, int operand){

	//(void)instruction;
}

int main(int argc, const char *argv[]) {
	
	App app = {0};
	load_rom(memory, argv[1]);	

	int i = 0;

	if(!init(&app, "CHIP-8", SCREEN_WIDTH, SCREEN_HEIGHT)) {

		return 1;		
	}
	while(app.running && i < CYCLES) {

		handle_events(&app);
		update(&app);
		render(&app);

		fetch(&program_counter, memory);
		i++;
	}
	
	cleanup(&app);
	return 0;
}
