#include <threads.h>
#include <stdlib.h>
#include <stdio.h>
#include "ickutils.h"
struct ickpoint_t { 
  int px;
  int py;
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
