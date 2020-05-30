#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

typedef struct Controller {
  bool up;
  bool down;
  bool left;
  bool right;
} Controller;

int 
main (int   argc,
      char *args[])
{
  SDL_Window*  window        = NULL;
  SDL_Surface* screenSurface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow(
      "SDL Tutorial", 
      SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, 
      SCREEN_WIDTH, SCREEN_HEIGHT, 
      SDL_WINDOW_SHOWN
  );

  if (window == NULL) {
    fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  
  SDL_Rect rect = { .x = 0, .y = 0, .w = 20, .h = 20 };

  bool quit = false;
  Controller controller = {0};

  while (!quit) {
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) { 
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
          controller.up = true;
          break;
          case SDLK_DOWN:
          controller.down = true;
          break;
          case SDLK_LEFT:
          controller.left = true;
          break;
          case SDLK_RIGHT:
          controller.right = true;
          break;
        }
      }

      if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
          controller.up = false;
          break;

          case SDLK_DOWN:
          controller.down = false;
          break;

          case SDLK_LEFT:
          controller.left = false;
          break;

          case SDLK_RIGHT:
          controller.right = false;
          break;
        }
      }
    }

    if (controller.up)    rect.y -= 1;
    if (controller.down)  rect.y += 1;
    if (controller.left)  rect.x -= 1;
    if (controller.right) rect.x += 1;

    SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0xFF, 0x0, 0x0));
    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
