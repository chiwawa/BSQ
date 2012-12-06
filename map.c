#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "get_next_line.h"
#include "map.h"

int
initMap(Map *m, char *fileName) {
  int fd = open(fileName, O_RDONLY);
  if (fd == -1) {
    return -1;
  }

  set_get_next_line_full_or_truncated(FULL_LINE);
  char *s = get_next_line(fd);
  if (s == 0) return -1;

  int sizeY = atoi(s);
  m->sizeY = sizeY;
  if ((m->tab = malloc(sizeof(*m->tab) * (m->sizeY + 1))) == 0) return -1;

  int i = 0;
  while (i != m->sizeY) {
    m->tab[i] = get_next_line(fd);
    if (m->tab[i] == 0) return -1;
    m->sizeX = strlen(m->tab[i]);
    ++i;
  }
  m->tab[i] = 0;
  return 0;
}

int
isFree(char **map, int i, int j) {
  return map[i][j] == '.' && map[i][j] != '\0';
}

void
canMakeSquare(Map* m, Result* res, int startX, int startY) {
  while (1) {
    int i = startX;
    int endI = startY + res->size;
    if (endI > m->sizeY) return ;
    while (i != endI) {
      int j = startX;
      int endJ = startX + res->size;
      if (endJ > m->sizeX) return ;
      while (j != endJ) {
	if (isFree(m->tab, i, j) == 0)
	  return ;
	++j;
      }
      ++i;
    }
    res->x = startX;
    res->y = startY;
    ++res->size;
  }
}

Result*
solveMap(Map *m) {
  Result* res = malloc(sizeof(*res));
  if (res == 0) return 0;
  res->x = 0;
  res->y = 0;

  int y = 0;
  while (y < m->sizeY) {
    int x = 0;
    while (x < m->sizeX) {
      canMakeSquare(m, res, x, y);
      ++x;
    }
    ++y;
  }
  return res;
}

void
displayMap(Map *m) {
  int i = 0;
  printf("size : %d %d\n", m->sizeX, m->sizeY);
  while (i < m->sizeY) {
    int j = 0;
    while (j < m->sizeX) {
      printf("%c", m->tab[i][j]);
      ++j;
    }
    printf("\n");
    ++i;
  }
}

void
iterOnMap(Map *m, Result* res,
	  void (*func)(Map*, Result*, int, int),
	  void (*end_func)(Map*, Result*, int, int)) {
  int i = 0;

  while (i < m->sizeY) {
    int j = 0;
    while (j < m->sizeX) {
      if (func != 0)
	func(m, res, i, j);
      ++j;
    }
    if (end_func != 0)
      end_func(m, res, i, j);
    ++i;
  }
}
