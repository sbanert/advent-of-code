#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *line = NULL;
  size_t line_cap = 0;
  ssize_t nchars = getline(&line, &line_cap, stdin);
  if (nchars <= 0) return 1;
  size_t width = nchars - 1;

  // Dynamic array to hold the input
  size_t d_cap = width;
  size_t height = 1;
  char *diagram = malloc(d_cap * sizeof(char));
  for (size_t i = 0; i < width; ++i)
    diagram[i] = line[i];

  for (;;) {
    nchars = getline(&line, &line_cap, stdin);
    if (nchars < 2) break;
    ++height;
    if (height * width > d_cap) {
      d_cap *= 2;
      diagram = realloc(diagram, d_cap * sizeof(char));
    }
    for (size_t i = 0; i < width; ++i)
      diagram[(height - 1) * width + i] = line[i];
  }

  size_t accessible_rolls = 0;
  for (size_t i = 0; i < height * width; ++i) {
    if (diagram[i] == '@') {
      size_t neighbours = 0;
      if (i / width && i % width && diagram[i - width - 1] == '@') ++neighbours;
      if (i / width && diagram[i - width] == '@') ++neighbours;
      if (i / width && i % width + 1 < width && diagram[i - width + 1] == '@') ++neighbours;
      if (i % width && diagram[i - 1] == '@') ++neighbours;
      if (i % width + 1 < width && diagram[i + 1] == '@') ++neighbours;
      if (i / width + 1 < height && i % width && diagram[i + width - 1] == '@') ++neighbours;
      if (i / width + 1 < height && diagram[i + width] == '@') ++neighbours;
      if (i / width + 1 < height && i % width + 1 < width && diagram[i + width + 1] == '@') ++neighbours;
      if (neighbours < 4) ++accessible_rolls;
    }
  }

  printf("%zu\n", accessible_rolls);

  free(line);
  free(diagram);
}
