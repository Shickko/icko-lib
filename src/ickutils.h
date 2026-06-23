#ifndef ICKLIB_H_UTILS
#define ICKLIB_H_UTILS
#define ICKUE     -2
#define ICKERR    -1
#define ICKSUCCESS 0
typedef struct ickbox_t ickbox_t;
ickbox_t* ickbox();
int ickbox_smash(ickbox_t** box);
int ickbox_load(ickbox_t* box, void* tar);
int ickbox_loadto(ickbox_t* box, void* tar, int pos);
void* ickbox_check(ickbox_t* box, int pos);
void* ickbox_unload(ickbox_t* box, int pos);
int ickbox_getweight(const ickbox_t* box);
#endif
