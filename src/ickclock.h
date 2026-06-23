#ifndef ICKLIB_H_ICKCLOCK
#define ICKLIB_H_ICKCLOCK
typedef enum {
  TC_ERR        = -1,
  TC_IDLE       = 0,
  TC_JOB        = 1,
  TC_TERMINATE  = 2,
} ickclock_stat;
typedef enum {
  TC_THRD       = 0,
  TC_SEQ        = 1,
  TC_TICK       = 2,
} ickclock_mode;
typedef struct ickclock_t ickclock_t;
ickclock_t* ickclock();
int ickclock_smash(ickclock_t** tar);
int ickclock_kill(ickclock_t* tar);
int ickclock_boot(ickclock_t* tar);
void ickclock_reset(ickclock_t* tar);
time_t ickclock_getcurr(const ickclock_t* tar);
time_t ickclock_getcend(const ickclock_t* tar);
time_t ickclock_getclen(const ickclock_t* tar);
void ickclock_setlen(ickclock_t* tar, int len);
void ickclock_setmode(ickclock_t* tar, ickclock_mode md);
ickclock_stat ickclock_getstat(const ickclock_t* tar);
ickclock_mode ickclock_getmode(const ickclock_t* tar);
#endif
