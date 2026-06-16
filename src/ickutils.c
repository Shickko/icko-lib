#include "ickutils.h"
#include <stdlib.h>
#include <stdio.h>
ickbox_t* ickbox() {
  ickbox_t* this = malloc(sizeof(ickbox_t));
  if (!this) { return NULL; }
  this -> boxid = 0;
  this -> weight = 0;
  this -> link = NULL;
  return this;
}
int ickbox_smash(ickbox_t** box) {
  ickbox_t* currbox = *box;
  if (!box || !currbox) 
  { return ICKERR; }
  while (currbox -> link != NULL) {
    currbox = currbox -> link;
  }
  return ICKSUCCESS;
}
int ickbox_load(ickbox_t* box, void* tar) {
  if (!tar) { return ICKERR; }
  int currpos = 0;
  ickbox_t* currbox = box;
  while (currbox -> cargo != NULL /* I BELIEVE IT'S HERE!!! */) {
    currpos += 1;
    if (currbox -> link == NULL) {
      ickbox_t* nbox = malloc(sizeof(ickbox_t));
      if (!nbox) { return ICKERR; }
      nbox -> boxid = currpos;
      nbox -> cargo = NULL;
      nbox -> link = NULL;
      currbox -> link = nbox;
    }
    currbox = currbox -> link;
    if (currbox -> boxid != currpos)
    { return ICKUE; }
  }
  box -> weight += 1;
  currbox -> cargo = tar;
  return ICKSUCCESS;
}
int ickbox_loadto(ickbox_t* box, void* tar, int pos) {
  if (!tar) { return ICKERR; }
  int currpos = 0;
  ickbox_t* currbox = box;
  while (currpos != pos) {
    currpos += 1;
    if (currbox -> link == NULL) {
      ickbox_t* nbox = malloc(sizeof(ickbox_t));
      if (!nbox) { return ICKERR; }
      nbox -> boxid = currpos;
      nbox -> cargo = NULL;
      nbox -> link = NULL;
      currbox -> link = nbox;
    }
    else {
      if (currbox -> boxid != currpos)
      { return ICKUE; }
    }
    currbox = currbox -> link;
  }
  if (!&(currbox -> cargo))
  { box -> weight += 1; }
  currbox -> cargo = tar;
  return ICKSUCCESS;
}
void* ickbox_check(ickbox_t* box, int pos) {
  ickbox_t* currbox = box;
  while (currbox -> boxid != pos) {
    if (!(currbox -> link))
    { return NULL; }
    currbox = currbox -> link;
  }
  return currbox -> cargo;
}
void* ickbox_unload_all(ickbox_t* box) {}
void* ickbox_unload(ickbox_t* box, int pos) {
  ickbox_t* currbox = box;
  while (currbox -> boxid != pos) {
    if (!(currbox -> link))
    { return NULL; }
    currbox = currbox -> link;
  }
  if (!(currbox -> cargo))
  { return NULL; }
  void* tar = currbox -> cargo;
  currbox -> cargo = NULL;
  return tar;
};
