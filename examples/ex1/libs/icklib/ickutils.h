#ifndef ICKLIB_H_UTILS
#define ICKLIB_H_UTILS
#define ICKUE     -2
#define ICKERR    -1
#define ICKSUCCESS 0
typedef struct ickpoint_t ickpoint_t;
typedef struct ickbox_t ickbox_t;
ickpoint_t* ickpoint(int x, int y);
int ickpoint_smash(ickpoint_t** tar);
ickbox_t* ickbox();
int getX(ickpoint_t* tar);
int getY(ickpoint_t* tar);
void setX(ickpoint_t* tar, int x);
void setY(ickpoint_t* tar, int y);
void setXY(ickpoint_t* tar, int x, int y);
int ickbox_smash(ickbox_t** box);
int ickbox_load(ickbox_t* box, void* tar);
int ickbox_loadto(ickbox_t* box, void* tar, int pos);
void* ickbox_check(ickbox_t* box, int pos);
void* ickbox_unload(ickbox_t* box, int pos);
int ickbox_getweight(const ickbox_t* box);
#endif
