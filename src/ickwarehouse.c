#include "ickwarehouse.h"
#include "ickutils.h"
#include <threads.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
struct ickshelf_t {
  cargo_t* shelf_cargo;
  char** cargo_label;
  size_t shelf_height;
  int weight;
};
struct ickbox_t {
  ickbox_t* boxlink;
  cargo_t cargo;
  int weight;
  int boxid;
};

ickbox_t* ickbox() {
  ickbox_t* this = malloc(sizeof(ickbox_t));
  if (this == NULL) { return NULL; }
  this -> boxlink = NULL;
  this -> cargo = NULL;
  this -> weight = 0;
  this -> boxid = 0;
  return this;
}
int ickbox_smash(ickbox_t** box) {
  if (box == NULL || *box == NULL)
  { return ICKERR; }
  int currpos = 0;
  ickbox_t* currbox = *box;
  ickbox_t* tempbox = NULL;
  while (currbox -> boxlink != NULL) {
    if (currbox -> cargo != NULL)
    { ickbox_unload(*box, currpos); }
    currpos += 1;
    currbox = currbox -> boxlink;
  }
  currbox = *box;
  ickbox_unload(*box, currpos);
  while (currbox -> boxlink != NULL) {
    tempbox = currbox;
    currbox = currbox -> boxlink;
    free(tempbox);
  }
  free(currbox);
  return ICKSUCCESS;
}
int ickbox_getweight(const ickbox_t* box)
{ return box -> boxid == 0 ? box -> weight : ICKERR; }
int ickbox_load(ickbox_t* box, cargo_t tar) {
  if (box -> boxid != 0) { return ICKERR; }
  ickbox_t* currbox = box;
  int currpos = 0;
  while (currbox -> cargo != NULL) {
    currpos += 1;
    if (currbox -> boxlink == NULL) {
      currbox -> boxlink = ickbox();
      if (currbox -> boxlink == NULL) 
      { return ICKERR; }
      currbox -> boxlink -> boxid = currpos;
    }
    currbox = currbox -> boxlink;
    if (currbox -> boxid != currpos)
    { return ICKUE; }
  }
  currbox -> cargo = tar;
  box -> weight += 1;
  return ICKSUCCESS;
}
int ickbox_loadat(ickbox_t* box, cargo_t tar, int pos) {
  if (box -> boxid != 0) { return ICKERR; }
  ickbox_t* currbox = box;
  int currpos = 0;
  while (currpos != pos) {
    currpos += 1;
    if (currbox -> boxlink == NULL) {
      currbox -> boxlink = ickbox();
       if (currbox -> boxlink == NULL)
       { return ICKERR; }
       currbox -> boxlink -> boxid = currpos;
    }
    currbox = currbox -> boxlink;
  }
  currbox -> cargo = tar;
  box -> weight += 1;
  return ICKSUCCESS;
}
cargo_t ickbox_check(ickbox_t* box, int pos) {
    if (box -> boxid != 0) { return NULL; }
    ickbox_t* currbox = box;
    int currpos = 0;
    while (currpos != pos) {
      if (currbox -> boxlink == NULL)
      { return NULL; }
      currbox = currbox -> boxlink;
      currpos += 1;
    }
    return currbox -> cargo;
}
cargo_t ickbox_unload(ickbox_t* box, int pos) {
  if (box -> boxid != 0) { return NULL; }
  ickbox_t* currbox = box;
  int currpos = 0;
  while (currpos != pos) {
    if (currbox -> boxlink == NULL) 
    { return NULL; }
    currbox = currbox -> boxlink;
    currpos += 1;
  }
  if (currbox -> cargo == NULL)
  { return NULL; }
  cargo_t tar = currbox -> cargo;
  currbox -> cargo = NULL;
  box -> weight -= 1;
  return tar;
}
ickshelf_t* ickshelf() {
  ickshelf_t* this = malloc(sizeof(ickshelf_t));
  if (this == NULL) { return NULL; }
  cargo_t* arrCargo = calloc(SHELF_STACK_HEIGHT, sizeof(cargo_t));
  char** arrChecker = calloc(SHELF_STACK_HEIGHT, sizeof(char* ));
  if (arrCargo == NULL) { free(this); return NULL; }
  this -> shelf_cargo = arrCargo;
  this -> cargo_label = arrChecker;
  this -> shelf_height = SHELF_STACK_HEIGHT;
  this -> weight = 0;
  return this;
}
int ickshelf_smash(ickshelf_t** shelf) {
  if (shelf == NULL || *shelf == NULL)
  { return ICKERR; }
  ickshelf_t* this = *shelf;
  free(this -> shelf_cargo);
  this -> shelf_cargo = NULL;
  free(this -> cargo_label);
  this -> cargo_label = NULL;
  free(this);
  this = NULL;
  shelf = NULL;
  return ICKSUCCESS;
}
int ickshelf_getweight(const ickshelf_t* shelf)
{ return shelf -> weight; }
static size_t ickshelf_findlabel(const char* label) {
  size_t label_key = 0;
  for (int i = 0; i < strlen(label); i++) {
    if ((int)label[i] - 65 < 0)
    { label_key += 1; continue; }
    label_key += (int)label[i] - 65;
  }
  return label_key;
}
static int ickshelf_expand(ickshelf_t* shelf, size_t tar_height) {
  while (shelf -> shelf_height < tar_height) 
  { shelf -> shelf_height += SHELF_STACK_HEIGHT; }
  shelf -> shelf_cargo = realloc(shelf -> shelf_cargo, 
      shelf -> shelf_height * sizeof(cargo_t));
  shelf -> cargo_label = realloc(shelf -> cargo_label, 
      shelf -> shelf_height * sizeof(char* ));
  if (shelf -> shelf_cargo == NULL || shelf -> cargo_label == NULL) {
    //Very bad issue if happen
    ickshelf_smash(&shelf);
    exit(-1);
    return ICKERR; 
  } else { return ICKSUCCESS; }
}
int ickshelf_place(ickshelf_t* shelf, char* label, cargo_t tar) { 
  if (strlen(label) > CARGO_LABEL_LIMITS)
  { return ICKERR; }
  size_t label_key = ickshelf_findlabel(label);
  if (shelf -> shelf_height <= label_key)
  { ickshelf_expand(shelf, label_key); }
  if (shelf -> cargo_label[label_key] == NULL) {
    shelf -> cargo_label[label_key] = label;
    shelf -> shelf_cargo[label_key] = tar;
    printf("Saved at %d\n", label_key);
    return ICKSUCCESS;
  }
  if (shelf -> cargo_label[label_key] != NULL &&
      strcmp(shelf -> cargo_label[label_key], label) == 0) 
  { shelf -> shelf_cargo[label_key] = tar; }
  else { while (shelf -> cargo_label[label_key] != NULL) {
    label_key += 1;
    if (shelf -> shelf_height >= label_key) 
    { ickshelf_expand(shelf, label_key); }
  } 
  shelf -> shelf_cargo[label_key] = tar;
  shelf -> cargo_label[label_key] = label; }
  printf("Saved at %d\n", label_key);
  return ICKSUCCESS;
}
cargo_t ickshelf_grab(ickshelf_t* shelf, char* label) {
  size_t label_key = ickshelf_findlabel(label);
  if (shelf -> cargo_label[label_key] != label) {
    while (shelf -> cargo_label[label_key] != label) {
      label_key += 1;
      if (label_key >= shelf -> shelf_height - 1)
      { return NULL; }
    }
  }
  cargo_t tar = shelf -> shelf_cargo[label_key];
  shelf -> shelf_cargo[label_key] = NULL;
  shelf -> cargo_label[label_key] = NULL;
  return tar;
}
cargo_t ickshelf_check(ickshelf_t* shelf, char* label) {
  size_t label_key = ickshelf_findlabel(label);
  if (shelf -> cargo_label[label_key] != label) { 
    while (shelf -> cargo_label[label_key] != label) { 
      label_key += 1;
      if (label_key >= shelf -> shelf_height  - 1)
      { return NULL; }
    }
  }
  return shelf -> shelf_cargo[label_key];
}
const char* ickshelf_search(ickshelf_t* shelf, cargo_t tar) {
  for (int i = 0; i < shelf -> shelf_height; i++) { 
    if (shelf -> shelf_cargo[i] == tar)
    { return shelf -> cargo_label[i]; }
  }
  return NULL;
}



