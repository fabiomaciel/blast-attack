/*
 * Copyright (c) 2021, Johnny Richard
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
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
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "hitbox.h"
#include "player.h"
#include "screen.h"

int
main(int argc, char* args[])
{

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(
      stderr, "SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  screen_t screen;

  if (screen_init(&screen) == false) {
    return EXIT_FAILURE;
  }

  SDL_Rect bg_rect = { .x = 0, .y = 0, .w = screen.width, .h = screen.height };

  bool quit = false;
  controller_t ctrl = { 0 };

  player_t player;
  player_init(&player);

  SDL_Renderer* renderer = screen.renderer;
  hitbox_t hitbox = { .x = screen.width / 2 - 50,
                      .y = screen.height / 2 - 50,
                      .width = 100,
                      .height = 100 };

  while (!quit) {

    screen_reset(&screen);
    uint64_t start = SDL_GetPerformanceCounter();

    SDL_SetRenderDrawColor(renderer, 0XCC, 0XCC, 0XCC, 1);
    SDL_RenderFillRect(renderer, &bg_rect);

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
      controller_update(&ctrl, &event);
    }

    player_update(&player, &ctrl, screen.width, screen.height);
    player_draw(&player, renderer);
    hitbox_draw(&hitbox, renderer);

    SDL_RenderPresent(renderer);

    uint64_t end = SDL_GetPerformanceCounter();

    float elapsedMS =
      (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
    SDL_Delay(floor(16.666f - elapsedMS));
  }

  screen_destroy(&screen);
  SDL_Quit();

  return EXIT_SUCCESS;
}
