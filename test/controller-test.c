#define MUNIT_ENABLE_ASSERT_ALIASES
#include "controller.h"
#include <munit/munit.h>

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
    assert_true(ctrl.up);

    event = an_event(SDL_KEYUP, SDLK_UP);
    controller_update(&ctrl, &event);
    assert_false(ctrl.up);
    return MUNIT_OK;
}

static MunitResult
press_and_release_down(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_DOWN);
    controller_update(&ctrl, &event);
    assert_true(ctrl.down);

    event = an_event(SDL_KEYUP, SDLK_DOWN);
    controller_update(&ctrl, &event);
    assert_false(ctrl.down);
    return MUNIT_OK;
}

static MunitResult
press_and_release_right(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_RIGHT);
    controller_update(&ctrl, &event);
    assert_true(ctrl.right);

    event = an_event(SDL_KEYUP, SDLK_RIGHT);
    controller_update(&ctrl, &event);
    assert_false(ctrl.right);
    return MUNIT_OK;
}

static MunitResult
press_and_release_left(const MunitParameter params[], void* fixture)
{
    controller_t ctrl = {0};

    SDL_Event event = an_event(SDL_KEYDOWN, SDLK_LEFT);
    controller_update(&ctrl, &event);
    assert_true(ctrl.left);

    event = an_event(SDL_KEYUP, SDLK_LEFT);
    controller_update(&ctrl, &event);
    assert_false(ctrl.left);
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
