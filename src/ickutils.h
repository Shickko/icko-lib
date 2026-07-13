#ifndef ICKLIB_H_UTILS
#define ICKLIB_H_UTILS
#define ICKUE      -2
#define ICKERR     -1
#define ICKSUCCESS  0
typedef enum {
  LG_SILENT     = 0,
  LG_CRITICAL   = 1,
  LG_ERRONLY    = 2,
  LG_WARNING    = 3,
  LG_OUTPUT     = 4,
} icklogstat_t;
static icklogstat_t ickloglevel;
static inline icklogstat_t ickloglevel_get()
{ return ickloglevel; }
static inline void ickloglevel_set(icklogstat_t s)
{ ickloglevel = s; }
typedef struct ickpoint_t ickpoint_t;
ickpoint_t* ickpoint(int x, int y);
int ickpoint_smash(ickpoint_t** tar);
int getX(ickpoint_t* tar);
int getY(ickpoint_t* tar);
void setX(ickpoint_t* tar, int x);
void setY(ickpoint_t* tar, int y);
void setXY(ickpoint_t* tar, int x, int y);
#endif
