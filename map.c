#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "get_next_line.h"
#include "map.h"

/*
  [.....]
  [.....]
  [....x]
  [.....]
  [.....]


  x:4, y:2 => 14
  sizeline = 5
  sizeline * y + x = 14

  recuperation de l'index du tableau
  14 / 8 == 1

  recuperation du 6ieme bit
  14 - (index * 8) = 6


  [00000000][00000100][00000000][00000000]

*/

int
initMap(Map *m, char *fileName) {
  int fd = open(fileName, O_RDONLY);
  if (fd == -1) {
    return -1;
  }

  set_get_next_line_full_or_truncated(FULL_LINE);
  char *s = get_next_line(fd);
  if (s == 0) return -1;

  m->sizeY = atoi(s);

  s = get_next_line(fd);
  if (s == 0) return -1;
  m->sizeX = strlen(s);

  m->map = malloc(sizeof(*m->map) * ceil(((m->sizeY + m->sizeX) / 8.0f)));
  if (m->map == 0) return -1;
  memset(m->map, 0, (m->sizeY + m->sizeX) / 8);

  int j = 0;
  do {
    int i = 0;
    while (i != m->sizeX) {
      if (s[i] == 'o') {
	int index1d = (j * m->sizeX + i);
	int indexBitField = index1d / 8;
	m->map[indexBitField] |= (1 << (7 - (index1d - (indexBitField * 8))));
      }
      ++i;
    }
    ++j;
  } while ((s = get_next_line(fd)));
  return 0;
}
int
isFree(Map* m, int i, int j) {
  int index1d = (m->sizeX * i + j);
  int indexBitField = index1d / 8;

  return (((m->map[indexBitField] >> (7 - (index1d - (indexBitField * 8)))) & 1) == 0);
}

void
canMakeSquare(Map* m, Result* res, int startX, int startY) {
  int trySize = res->size;
  while (1) {
    int i = startY;
    int endI = startY + trySize;
    int endJ = startX + trySize;
    if (endI > m->sizeY || endJ > m->sizeX) {
      return ;
    }
    while (i != endI) {
      int j = startX;
      while (j != endJ) {
	if (isFree(m, i, j) == 0) {
	  return ;
	}
	++j;
      }
      ++i;
    }
    res->x = startX;
    res->y = startY;
    res->size = trySize;
    ++trySize;
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
