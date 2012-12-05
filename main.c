#include "map.h"

int
main(int argc, char **argv) {
  if (argc > 1) {
    Map	m;

    initMap(&m, argv[1]);
    solveMap(&m);
  }
}
