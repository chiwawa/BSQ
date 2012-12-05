#include "get_next_line.h"
#include "map.h"

void
initMap(Map *m, char *fileName) {
  int fd = open(fileName, O_RDONLY);
  if (fd == -1) {
    return ;
  }

  char *s = get_next_line(fd);
  if (s == 0) return ;

  int sizeY = atoi(s);
  m->sizeY = sizeY;
  if ((m->tab = malloc(sizeof(*m->tab) * (m->sizeY + 1))) == 0) return ;

  int i = 0;
  while (i != m->sizeY) {
    m->tab[i] = get_next_line(fd);
    if (m->tab[i] == 0) return ;
    ++i;
  }
  m->tab[i] = 0;
}

Result*
solveMap(Map *m) {
  return 0;
}
