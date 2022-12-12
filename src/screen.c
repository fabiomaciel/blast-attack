/*
* Copyright (c) 2021, Fabio Maciel
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its
*    contributors may be used to endorse or promote products derived from
*    this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "screen.h"

#include <stdint.h>
#include <assert.h>
#include <SDL.h>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

bool
screen_init(screen_t* screen)
{
  assert(screen && "screen is required");

  screen->width = SCREEN_WIDTH;
  screen->height = SCREEN_HEIGHT;

  screen->window = SDL_CreateWindow(
      "Blast Attack",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      screen->width, screen->height,
      SDL_WINDOW_RESIZABLE
  );

  if (screen->window == NULL) {
    fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }

  screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_ACCELERATED);
  if (screen->renderer == NULL) {
    fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
    return false;
  }

  if (SDL_RenderSetLogicalSize(screen->renderer, screen->width, screen->height) < 0) {
    fprintf(stderr, "Could not set logical size: %s\n", SDL_GetError());
    return false;
  }

  return true;
}

void
screen_reset(screen_t *screen)
{
  SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, 1);
  SDL_RenderClear(screen->renderer);
}

void
screen_destroy(screen_t *screen)
{
  SDL_DestroyRenderer(screen->renderer);
  SDL_DestroyWindow(screen->window);
}
