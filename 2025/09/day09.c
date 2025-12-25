#include <stdio.h>
#include <stdlib.h>

struct Red_Tile {
  long x, y;
};

int main(void) {
  size_t red_count = 0;
  size_t red_cap = 1;
  struct Red_Tile *red_tiles = malloc(sizeof(struct Red_Tile));

  char *line = NULL;
  size_t line_cap = 0;

  for (;;) {
    long x, y;
    ssize_t n = getline(&line, &line_cap, stdin);
    if (n < 3) {
      break;
    }
    char *next;
    x = strtol(line, &next, 10);
    y = strtol(next + 1, NULL, 10);
    ++red_count;
    if (red_cap < red_count) {
      red_cap *= 2;
      red_tiles = realloc(red_tiles, red_cap * sizeof(struct Red_Tile));
    }
    red_tiles[red_count - 1].x = x;
    red_tiles[red_count - 1].y = y;
  }

  long max_area = 0;
  for (size_t i = 0; i < red_count; ++i) {
    for (size_t j = 0; j < i; ++j) {
      long a = (1 + labs(red_tiles[i].x - red_tiles[j].x))
               * (1 + labs(red_tiles[i].y - red_tiles[j].y));
      if (a > max_area) max_area = a;
    }
  }
  printf("%ld\n", max_area);

  free(line);
  free(red_tiles);
}
