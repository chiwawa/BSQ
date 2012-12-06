#ifndef __MAP_H__
# define __MAP_H__

struct sMap {
  int	sizeX;
  int	sizeY;
  char	**tab; // doing it with double tab but going to convert it into a bitfield
  char	*map;
};

struct sResult {
  int	x;
  int	y;
  int	size;
};

typedef struct sMap Map;
typedef struct sResult Result;

int	initMap(Map* m, char *fileName);
void	iterOnMap(Map* m, Result* res, void (*func)(Map*, Result*, int, int), void (*end_func)(Map*, Result*, int, int));
Result*	solveMap(Map* m);

int	isFree(char **map, int i, int j);
void	canMakeSquare(Map* m, Result* res, int i, int j);

#endif
