#include <SDL.h>
#include "controller.h"


void 
controller_update(controller_t *self, 
                  SDL_Event    *event)
{
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_UP:
        self->up = true;
        break;
      case SDLK_DOWN:
        self->down = true;
        break;
      case SDLK_LEFT:
        self->left = true;
        break;
      case SDLK_RIGHT:
        self->right = true;
        break;
    }
  }

  if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
      case SDLK_UP:
        self->up = false;
        break;

      case SDLK_DOWN:
        self->down = false;
        break;

      case SDLK_LEFT:
        self->left = false;
        break;

      case SDLK_RIGHT:
        self->right = false;
        break;
    }
  }
}

