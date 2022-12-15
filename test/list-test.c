/*
 * Copyright (c) 2022, Johnny Richard
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

#define MUNIT_ENABLE_ASSERT_ALIASES

#include "list.h"

#include <munit/munit.h>
#include <stdbool.h>

static MunitResult
test_is_empty(const MunitParameter params[], void* fixture)
{
  assert_true(list_is_empty(NULL));
  return MUNIT_OK;
}

static MunitResult
test_push(const MunitParameter params[], void* fixture)
{
  list_t* list = NULL;

  int number = 1;
  list_push(&list, &number);

  assert_false(list_is_empty(list));

  assert_int(*((int*)list->value), ==, 1);
  assert_true(list->next == NULL);

  return MUNIT_OK;
}

static MunitResult
test_pop(const MunitParameter params[], void* fixture)
{
  list_t* list = NULL;

  int n1 = 1;
  int n2 = 2;

  list_push(&list, &n1);
  list_push(&list, &n2);

  assert_int(*((int*)list->value), ==, 2);
  assert_int(*((int*)list->next->value), ==, 1);
  assert_true(list->next->next == NULL);

  list_t* head = list_pop(&list);
  assert_int(*((int*)head->value), ==, 2);
  assert_int(*((int*)list->value), ==, 1);
  assert_true(list->next == NULL);

  return MUNIT_OK;
}

MunitTest tests[] = {
  { "/test_is_empty", test_is_empty, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_push", test_push, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { "/test_pop", test_pop, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
  { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = { "/list",
                                  tests,
                                  NULL,
                                  1,
                                  MUNIT_TEST_OPTION_NONE };

int
main(int argc, char* argv[])
{
  return munit_suite_main(&suite, NULL, argc, argv);
}
