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

void
displayBinary(Map* m, char *tab) {
  int stop = ceil(m->sizeY * m->sizeX / 8.0f);
  int i = 0;

  while (i < stop) {
    printf("--%d--\n", tab[i]);
    ++i;
  }
  /*  int stop = m->sizeY * m->sizeX;

  int nbBits = 0;
  int i = 0;
  while (nbBits < stop) {
    int j = sizeof(char) * 8 - 1;
    int j2 = 0;
    while (j >= 0) {
      if (((i * 8) + j2) % m->sizeX == 0)
	printf("\n");
      printf("-%d-", (tab[i] >> j) & 1);
      ++j2;
      --j;
      ++nbBits;
    }
    ++nbBits;
    ++i;
  }
  */
}

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
	m->map[indexBitField] |= (1 << (8 - (index1d - (indexBitField * 8))));
      }
      ++i;
    }
    ++j;
  } while ((s = get_next_line(fd)));

  displayBinary(m, m->map);
  exit(1);
  return 0;
}
/*
  if ((m->tab = malloc(sizeof(*m->tab) * (m->sizeY + 1))) == 0) return -1;
  int i = 0;
  while (i != m->sizeY) {
    m->tab[i] = get_next_line(fd);
    if (m->tab[i] == 0) return -1;
    m->sizeX = strlen(m->tab[i]);
    ++i;
  }
  m->tab[i] = 0;
  */

int
isFree(char **map, int i, int j) {
  return map[i][j] == '.' && map[i][j] != '\0';
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
	if (isFree(m->tab, i, j) == 0) {
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
