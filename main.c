#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"


void
display(Map* m, Result* res, int i, int j) {
  int index1d = (m->sizeX * i + j);
  int indexBitField = index1d / 8;

  if ((m->map[indexBitField] >> (7 - (index1d - (indexBitField * 8)))) & 1)
    printf("x");
  else
    printf(".");
}

void
displayLine(Map* m, Result* res, int i, int j) {
  printf("\n");
}

void
insertSquare(Map *m, Result* res, int i, int j) {
  int jInterval = res->x + res->size;
  int iInterval = res->y + res->size;

  if (j >= res->x && j < jInterval &&
      i >= res->y && i < iInterval) {
    int index1d = (m->sizeX * i + j);
    int indexBitField = index1d / 8;

    printf("Insert on %d %d, %d indexBitField[%d]\n", i, j, (8 - (index1d - (indexBitField * 8))), indexBitField);
    m->map[indexBitField] |= (1 << (7 - (index1d - (indexBitField * 8))));
  }
}

int
main(int argc, char **argv) {
  if (argc > 1) {
    Map	m;

    if (initMap(&m, argv[1]) == -1) return EXIT_FAILURE;
    Result res;
    iterOnMap(&m, &res, canMakeSquare, 0);
    iterOnMap(&m, 0, display, displayLine);
    iterOnMap(&m, &res, insertSquare, 0);
    printf("%d %d %d\n", res.x, res.y, res.size);
    iterOnMap(&m, 0, display, displayLine);
  }
  return EXIT_SUCCESS;
}
