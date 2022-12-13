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

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "controller.h"
#include <munit.h>

static SDL_Event
an_event(SDL_EventType type, SDL_KeyCode keycode) {
    SDL_Event event;
    event.type = type;
    event.key.keysym.sym = keycode;
    return event;
}

static MunitResult
press_and_release_up(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_UP);
    controller_update(&ctrl, &event);
    assert_true(controller_is_up_pressed(&ctrl));

    event = an_event(SDL_KEYUP, SDLK_UP);
    controller_update(&ctrl, &event);
    assert_false(controller_is_up_pressed(&ctrl));
    return MUNIT_OK;
}

static MunitResult
press_and_release_down(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_DOWN);
    controller_update(&ctrl, &event);
    assert_true(controller_is_down_pressed(&ctrl));

    event = an_event(SDL_KEYUP, SDLK_DOWN);
    controller_update(&ctrl, &event);
    assert_false(controller_is_down_pressed(&ctrl));
    return MUNIT_OK;
}

static MunitResult
press_and_release_right(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_RIGHT);
    controller_update(&ctrl, &event);
    assert_true(controller_is_right_pressed(&ctrl));

    event = an_event(SDL_KEYUP, SDLK_RIGHT);
    controller_update(&ctrl, &event);
    assert_false(controller_is_right_pressed(&ctrl));
    return MUNIT_OK;
}

static MunitResult
press_and_release_left(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_LEFT);
    controller_update(&ctrl, &event);
    assert_true(controller_is_left_pressed(&ctrl));

    event = an_event(SDL_KEYUP, SDLK_LEFT);
    controller_update(&ctrl, &event);
    assert_false(controller_is_left_pressed(&ctrl));
    return MUNIT_OK;
}

MunitTest tests[] = {
    { "/press_and_release_up",    press_and_release_up,    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/press_and_release_down",  press_and_release_down,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/press_and_release_right", press_and_release_right, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { "/press_and_release_left",  press_and_release_left,  NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL,                       NULL,                    NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
    "/controller", tests, NULL, 1, MUNIT_TEST_OPTION_NONE
};

int
main(int argc, char *argv[])
{
    return munit_suite_main(&suite, NULL, argc, argv);
}
