/*
* Copyright (c) 2021, Johnny Richard
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>

#include "controller.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

int
main (int   argc,
      char *args[])
{
  SDL_Window* window = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(
        stderr,
        "SDL could not be initialized! SDL_Error: %s\n",
        SDL_GetError()
    );
    return EXIT_FAILURE;
  }

  window = SDL_CreateWindow(
      "Blast Attack",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
  );

  if (window == NULL) {
    fprintf(
        stderr,
        "Window could not be created! SDL_Error: %s\n",
        SDL_GetError()
    );
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Rect rect = { .x = 0, .y = 0, .w = 20, .h = 20 };

  bool quit = false;
  controller_t ctrl = {0};

  while (!quit) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);

    uint64_t start = SDL_GetPerformanceCounter();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      controller_update(&ctrl, &event);
    }

    if (controller_is_up_pressed(&ctrl))    rect.y -= 8;
    if (controller_is_down_pressed(&ctrl))  rect.y += 8;
    if (controller_is_left_pressed(&ctrl))  rect.x -= 8;
    if (controller_is_right_pressed(&ctrl)) rect.x += 8;

    SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 1);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    uint64_t end = SDL_GetPerformanceCounter();

    float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
