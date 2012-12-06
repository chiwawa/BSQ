#include <string.h>
#include <stdio.h>
#include "map.h"


void
display(Map* m, Result* res, int i, int j) {
  printf("%c", m->tab[i][j]);
}

void
displayLine(Map* m, Result* res, int i, int j) {
  printf("\n");
}

int
main(int argc, char **argv) {
  if (argc > 1) {
    Map	m;

    initMap(&m, argv[1]);
    iterOnMap(&m, 0, display, displayLine);
    Result res;

    iterOnMap(&m, &res, canMakeSquare, 0);
    printf("%d %d %d\n", res.x, res.y, res.size);
  }
}
