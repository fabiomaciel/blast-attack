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

#include "player.h"

#include <SDL.h>
#include <assert.h>

void
player_init(player_t* player)
{
  assert(player && "player is required");
  player->x = 0;
  player->y = 0;
  player->width = 20;
  player->height = 20;
  player->speed = 8;
}

void
player_update(player_t* player,
              controller_t* ctrl,
              int screen_width,
              int screen_height)
{
  if (controller_is_up_pressed(ctrl) && player->y > 0) {
    player->y -= player->speed;
    player->y = player->y < 0 ? 0 : player->y;
  }

  if (controller_is_down_pressed(ctrl) && player->y < screen_height) {
    player->y += player->speed;
    player->y = player->y + player->height > screen_height
                  ? screen_height - player->height
                  : player->y;
  }

  if (controller_is_left_pressed(ctrl) && player->x > 0) {
    player->x -= player->speed;
    player->x = player->x < 0 ? 0 : player->x;
  }

  if (controller_is_right_pressed(ctrl) && player->x < screen_width) {
    player->x += player->speed;
    player->x = player->x + player->width > screen_width
                  ? screen_width - player->width
                  : player->x;
  }
}

void
player_draw(player_t* player, SDL_Renderer* renderer)
{
  SDL_Rect rect = {
    .x = player->x, .y = player->y, .w = player->width, .h = player->height
  };

  SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 1);
  SDL_RenderFillRect(renderer, &rect);
}
