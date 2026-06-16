#ifndef ICKLIB_H_UTILS
#define ICKLIB_H_UTILS
#define ICKSUCCESS 0
#define ICKERR    -1
#define ICKUE     -2
typedef struct ickbox {
  struct ickbox* link;
  void*   cargo;
  int     boxid;
  int     weight;
} ickbox_t;
ickbox_t* ickbox();
int ickbox_smash(ickbox_t** box);
int ickbox_load(ickbox_t* box, void* tar);
int ickbox_loadto(ickbox_t* box, void* tar, int pos);
void* ickbox_check(ickbox_t* box, int pos);
void* ickbox_unload(ickbox_t* box, int pos);
void* ickbox_unload_all(ickbox_t* box);
static inline int ickbox_weight(ickbox_t* box)
{ return box -> boxid == 0 ? box -> weight : 0; }
#endif
