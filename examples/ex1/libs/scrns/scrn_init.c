#include "scrn_init.h"
#include "ickutils.h"
#include "ickclock.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
int session_start(char* argv[]) {
  ickclock_t* session_clock = ickclock();
  recycle_bin = ickbox();
  ickclock_setmode(session_clock, TC_TICK);
  if (ickclock_boot(session_clock) != ICKSUCCESS)
  { return ICKERR; }
  ickbox_load(recycle_bin, session_clock);

  return scrn_init();
}
int session_end() {
  ickclock_kill((ickclock_t* )ickbox_check(recycle_bin, 0));
  for (int i = 0; i < ickbox_getweight(recycle_bin); i ++)
  {
    if (ickbox_check(recycle_bin, i) != NULL)
    { free((ickbox_check(recycle_bin, i))); }
  }

  return ICKSUCCESS;
}
int scrn_init() {
  int prev_row, prev_col;
  int row, col, ch;
  int y, x;
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);
  getmaxyx(stdscr, row, col);
  const char* scrnTitle = "[Testing Environment]";
  int attr_scrnTitle = A_BOLD;
  const char* scrnAuthor = "Shickko Playground";
  int attr_scrnAuthor = A_DIM | A_UNDERLINE;
  const char* escapeHint = "< -- [SPACE TO ESCAPE] -- >";
  int attr_escapeHint = A_BOLD | A_BLINK;
  ickpoint_t* posTitle = ickpoint(1, 
      col / 2 - strlen(scrnTitle) / 2);
  ickpoint_t* posAuthor = ickpoint(2,
      col / 2 - strlen(scrnAuthor) / 2);
  ickpoint_t* posEscape = ickpoint(row - 2, 
      col / 2 - strlen(escapeHint) / 2);
  ickbox_load(recycle_bin, posTitle);
  ickbox_load(recycle_bin, posAuthor);
  ickbox_load(recycle_bin, posEscape);
  do {
    ch = getch();
    erase();
    getmaxyx(stdscr, row, col);
    setXY(posTitle, 1, col / 2 - strlen(scrnTitle) / 2);
    setXY(posAuthor, 2, col / 2 - strlen(scrnAuthor) / 2);
    setXY(posEscape, row - 2, col / 2 - strlen(escapeHint) / 2);
    prev_row = row;
    prev_col = col;
    attron(attr_scrnTitle);
    mvprintw(getX(posTitle), getY(posTitle), scrnTitle);
    attroff(attr_scrnTitle);
    attron(attr_scrnAuthor);
    mvprintw(getX(posAuthor), getY(posAuthor), scrnAuthor);
    attroff(attr_scrnAuthor);
    attron(attr_escapeHint);
    mvprintw(getX(posEscape), getY(posEscape), escapeHint);
    attroff(attr_escapeHint);
    mvprintw(3, 1, "\tCurrent Session Length: \t%d [sec]", 
        ickclock_getclen((ickclock_t* )ickbox_check(recycle_bin, 0)));
    mvprintw(4, 1, "\tGarbage Bin Weight: \t\t%d [kg]", 
        ickbox_getweight(recycle_bin));
    for (int i = 0; i < ickbox_getweight(recycle_bin); i++) {
      mvprintw(5 + i, 1, "\t  %d: %p", i, ickbox_check(recycle_bin, i));
    }
    getyx(stdscr, y, x);
    mvprintw(y + 1, 1, "\t//End");
    box(stdscr, 0, 0);
    timeout(100);
    getmaxyx(stdscr, row, col);
    refresh();
  } while (ch != (char)(32));
  endwin();
  return session_end();
}
