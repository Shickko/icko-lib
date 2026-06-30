#include "scrn_init.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
  int exit_status = 0;
  printf("\033[2J\033[H[ICKO] Initializing session...");

  exit_status = session_start(argv);

  printf("[ICKO] Escaped with status[%d]\n", exit_status);
  //Exit
  return exit_status;
}
