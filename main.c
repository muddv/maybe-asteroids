#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#define SCREEN_W 640
#define SCREEN_H 480

SDL_Window *window = NULL;
SDL_Renderer *renderer;
SDL_Texture *screen;
uint32_t *pixels = NULL;

int init(void);
int draw_bg(void);

int main(void) {
  init();
  draw_bg();
  // game loop
  int quit = 0;
  while (quit == 0) {
    SDL_PumpEvents();
	SDL_UpdateTexture(screen, NULL, pixels, SCREEN_W * sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, screen, NULL, NULL);
		SDL_RenderPresent(renderer);
  }
}

int init(void) {
  SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN, &window,
                              &renderer);
  screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
  pixels = (Uint32 *)malloc((SCREEN_W * SCREEN_H) * sizeof(Uint32));
  // TODO handle errors
  return 0;
}

int draw_bg(void) {
  for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
    pixels[i] = 0xFF000000;
  }
  return 0;
}
