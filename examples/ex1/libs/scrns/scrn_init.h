#ifndef SCRN_H_INIT
#define SCRN_H_INIT
#include "ickutils.h"
static ickbox_t* recycle_bin;
int session_start(char* argv[]);
int session_end();
int scrn_init();
#endif
