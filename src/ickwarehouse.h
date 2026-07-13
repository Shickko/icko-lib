#ifndef ICKLIB_H_WAREHOUSE
#define ICKLIB_H_WAREHOUSE
#define CARGO_LABEL_LIMITS 10
#define SHELF_STACK_HEIGHT 128
typedef struct ickshelf_t ickshelf_t;
typedef struct ickbox_t ickbox_t;
typedef void* cargo_t;

ickbox_t* ickbox();
int ickbox_smash(ickbox_t** box);
int ickbox_getweight(const ickbox_t* box);
int ickbox_getlength(const ickbox_t* box);
int ickbox_load(ickbox_t* box, cargo_t tar);
int ickbox_loadat(ickbox_t* box, cargo_t tar, int pos);
cargo_t ickbox_check(ickbox_t* box, int pos);
cargo_t ickbox_unload(ickbox_t* box, int pos);

ickshelf_t* ickshelf();
int ickshelf_smash(ickshelf_t** shelf);
int ickshelf_getweight(const ickshelf_t* shelf);
int ickshelf_place(ickshelf_t* shelf, char* label, cargo_t tar);
cargo_t ickshelf_grab(ickshelf_t* shelf, char* label);
cargo_t ickshelf_check(ickshelf_t* shelf, char* label);
const char* ickshelf_search(ickshelf_t* shelf, cargo_t tar);

#endif

