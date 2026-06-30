#include <threads.h>
#include <stdlib.h>
#include <stdio.h>
#include "ickutils.h"
struct ickpoint_t { 
  int px;
  int py;
};
struct ickbox_t {
  ickbox_t* boxlink;
  void* cargo;
  int weight;
  int boxid;
};
ickpoint_t* ickpoint(int x, int y) {
  ickpoint_t* this = malloc(sizeof(ickpoint_t));
  if (this == NULL) { return NULL; }
  this -> px = x;
  this -> py = y;
  return this;
}
int ickpoint_smash(ickpoint_t** tar) {
  if (tar == NULL || *tar == NULL)
  { return ICKERR; }
  ickpoint_t* target_point = *tar;
  free(target_point);
  *tar = NULL;
  return ICKSUCCESS;
}
int getX(ickpoint_t* tar)
{ return tar -> px; }
int getY(ickpoint_t* tar)
{ return tar -> py; }
void setX(ickpoint_t* tar, int x)
{ tar -> px = x; }
void setY(ickpoint_t* tar, int y)
{ tar -> py = y; }
void setXY(ickpoint_t* tar, int x, int y)
{ tar -> px = x; tar -> py = y; }
ickbox_t* ickbox() {
  ickbox_t* this = malloc(sizeof(ickbox_t));
  if (!this) { return NULL; }
  this -> boxlink = NULL;
  this -> cargo = NULL;
  this -> weight = 0;
  this -> boxid = 0;
  return this;
}
int ickbox_smash(ickbox_t** box) {
  if (box == NULL || *box == NULL)
  { return ICKERR; }
  ickbox_t* currbox = *box;
  ickbox_t* tempbox = NULL;
  int currpos = 0;
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

int ickbox_load(ickbox_t* box, void* tar) {
  if (box -> boxid != 0) { return ICKERR;} //illegal box
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
int ickbox_loadto(ickbox_t* box, void* tar, int pos) {
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
void* ickbox_check(ickbox_t* box, int pos) {
  if (box -> boxid != 0) { return NULL; }
  ickbox_t* currbox = box;
  int currpos = 0;
  while (currpos != pos) {
    if (!(currbox -> boxlink))
    { return NULL; }
    currbox = currbox -> boxlink;
    currpos += 1;
  }
  return currbox -> cargo;
}
void* ickbox_unload(ickbox_t* box, int pos) {
  if (box -> boxid != 0) { return NULL; }
  ickbox_t* currbox = box;
  int currpos = 0;
  while (currpos != pos) {
    if (!(currbox -> boxlink))
    { return NULL; }
    currbox = currbox -> boxlink;
    currpos += 1;
  }
  if (currbox -> cargo == NULL) 
  { return NULL; } 
  void* tar = currbox -> cargo;
  currbox -> cargo = NULL;
  box -> weight -= 1;
  return tar;
}
int ickbox_getweight(const ickbox_t* box)
{ return box -> boxid == 0 ? box -> weight : 0; }
