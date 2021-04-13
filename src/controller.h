#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct controller_t {
  bool up;
  bool down;
  bool left;
  bool right;
} controller_t;

#ifdef __cplusplus
}
#endif

#endif /* CONTROLLER_H */
