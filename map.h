#ifndef __MAP_H__
# define __MAP_H__

struct sMap {
  int	sizeX;
  int	sizeY;
  char	**tab; // doing it with double tab but going to convert it into a bitfield
};

struct sResult {
  int	x;
  int	y;
  int	size;
};

typedef sMap Map;
typedef sResult Result;

void	initMap(Map* m, char *fileName);
Result*	solveMap(Map* m);


#endif
