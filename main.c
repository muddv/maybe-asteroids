#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdint.h>

#define SCREEN_W 640
#define SCREEN_H 480

SDL_Window *window = NULL;
SDL_Renderer *renderer;
SDL_Texture *screen;
uint32_t *pixels = NULL;

int init(void);
int draw_bg(void);
void render_loop(void);
void draw_player(uint32_t position);

int main(void) {
  init();
  draw_bg();
  render_loop();
}

void render_loop(void) 
{
  int quit = 0;
	int i = 0;
  while (quit == 0) {
		i++;
		draw_player(i);
		
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
      quit = 1;
    }
    SDL_PumpEvents();
    SDL_UpdateTexture(screen, NULL, pixels, SCREEN_W * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screen, NULL, NULL);
    SDL_RenderPresent(renderer);
  }
}

int init(void) 
{
  SDL_CreateWindowAndRenderer(SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN, &window,
                              &renderer);
  screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                             SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
  pixels = (Uint32 *)malloc((SCREEN_W * SCREEN_H) * sizeof(Uint32));
  // TODO handle errors
  return 0;
}

int draw_bg(void) 
{
  for (int i = 0; i < SCREEN_W * SCREEN_H; i++) {
    pixels[i] = 0x00000000;
  }
  return 0;
}

void draw_player(uint32_t position) 
{
	pixels[position] = 0xFF000000;	
}
