#include <threads.h>
#include <stdlib.h>
#include <stdio.h>
#include "ickclock.h"
#include "ickutils.h"
static int ickwait(void* tar);
struct ickclock_t {
  ickclock_stat clock_stat;
  ickclock_mode clock_mode;
  thrd_t clock_thrd;
  time_t curr;
  time_t cend;
  time_t clen;
  mtx_t mlock;
};
ickclock_t* ickclock() {
  ickclock_t* this = malloc(sizeof(ickclock_t));
  if (!this) { return NULL; }
  if (mtx_init(&(this -> mlock), mtx_plain) == thrd_error)
  { return NULL; }
  this -> curr = 0;
  this -> clen = 0;
  this -> cend = 0;
  this -> clock_stat = TC_IDLE;
  this -> clock_mode   = TC_THRD;
  return this;
}
int ickclock_smash(ickclock_t** tar) {
  if (!tar || !(*tar)) { return ICKERR; }
  ickclock_t* this = *tar;
  if (this -> clock_stat == TC_JOB) { 
    return (ickclock_kill(this) == ICKSUCCESS) ?
            ickclock_smash(tar) : ICKERR;
  }
  mtx_destroy(&(this -> mlock));
  free(this); 
  return ICKSUCCESS;
}
int ickclock_kill(ickclock_t* tar) {
  tar -> clock_stat = TC_TERMINATE;
  if (thrd_detach(tar -> clock_thrd) == thrd_success)
  { tar -> clock_stat = TC_IDLE; return ICKSUCCESS; }
  return ICKERR;
}
int ickclock_boot(ickclock_t* tar) {
  if (tar -> clock_mode != TC_TICK &&
      tar -> clen == 0) {
    return ICKERR;
  }
  if (tar -> clock_stat == TC_JOB)
  { return ICKERR; }
  mtx_lock(&(tar -> mlock));
  if (thrd_create(&(tar -> clock_thrd), ickwait, tar) != thrd_success)
  { return ICKERR; }
  int exit_status = 0;
  tar -> clock_stat = TC_JOB;
  if (tar -> curr == 0) 
  { tar -> curr = time(0); }
  mtx_unlock(&(tar -> mlock));
  if (tar -> clock_mode != TC_SEQ)
  { return ICKSUCCESS; }
  if (thrd_join(tar -> clock_thrd, &exit_status) == thrd_success)
  { return ICKSUCCESS; }
  thrd_detach(tar -> clock_thrd);
  return ICKERR;
}
static int ickwait(void* tar) {
  ickclock_t* clock = tar;
  time_t clock_len = clock -> clen;
  if (clock -> clock_mode == TC_TICK) {
    while (clock -> clock_stat != TC_TERMINATE)
    {
      thrd_yield();
      mtx_lock(&(clock -> mlock));
      thrd_sleep(&(struct timespec)
          { .tv_sec = 0, .tv_nsec = 50 * 1000000 }, 
          NULL);
      clock -> cend = time(0);
      clock_len = clock -> cend - clock -> curr;
      clock -> clen = clock_len;
      mtx_unlock(&(clock -> mlock));
    }
    return ICKSUCCESS;
  }
  if (thrd_sleep(&(struct timespec) 
     { .tv_sec = clock_len }, NULL
  ) != thrd_success )
  { return ICKERR; }
  mtx_lock(&(clock -> mlock));
  clock -> cend = time(0);
  clock -> clen = clock_len;
  clock -> clock_stat = TC_TERMINATE;
  mtx_unlock(&(clock -> mlock));
  return ICKSUCCESS;
}
void ickclock_reset(ickclock_t* tar) {
  if (tar -> clock_stat == TC_JOB)
  { return; }
  tar -> clock_stat = TC_IDLE;
  tar -> curr = time(0);
  tar -> cend = 0;
  tar -> clen = 0;
}
time_t ickclock_getcurr(const ickclock_t* tar) 
{ return (tar -> curr); }
time_t ickclock_getcend(const ickclock_t* tar) 
{ return (tar -> cend); }
time_t ickclock_getclen(const ickclock_t* tar)
{ return (tar -> clen); }
void ickclock_setlen(ickclock_t* tar, int len)
{ if (ickclock_getstat(tar) == TC_JOB) { return; } tar -> clen = len; }
void ickclock_setmode(ickclock_t* tar, ickclock_mode md)
{ if (ickclock_getstat(tar) == TC_JOB) { return; } tar -> clock_mode = md; }
ickclock_stat ickclock_getstat(const ickclock_t* tar)
{ return tar -> clock_stat; }
ickclock_mode ickclock_getmode(const ickclock_t* tar)
{ return tar -> clock_mode; }


