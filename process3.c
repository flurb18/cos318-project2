/* process3.c
 * COS 318, Fall 2019: Project 2 Non-Preemptive Kernel
 * Measures the time taken to context switch between processes
 */

#include "common.h"
#include "syslib.h"
#include "util.h"

static bool_t FIRST_RUN = TRUE;
static uint64_t start = 0;

void _start(void) {
  uint64_t finish = get_timer();
  if (FIRST_RUN) {
    start = get_timer();
    FIRST_RUN = FALSE;
    yield();
  } else {
    print_str(0,20,"yield(): ");
    print_int(0,29,(finish - start));
    exit();
  }
  exit();
}
