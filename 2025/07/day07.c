#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
  ssize_t nchars, line_len;
  char *line = NULL;
  size_t linecapp = 0;
  nchars = getline(&line, &linecapp, stdin);
  if (nchars < 0) {
    exit(1);
  } else {
    line_len = nchars - 1; // substract '\n' character
  }

  bool *tachyons = malloc(line_len * sizeof(bool));
  for (size_t i = 0; *(line + i) != '\n'; ++i) {
    if (*(line + i) == 'S') {
      tachyons[i] = true;
    } else {
      tachyons[i] = false;
    }
  }

  size_t nsplits = 0;

  while (1) {
    nchars = getline(&line, &linecapp, stdin);
    if (nchars < 1)
      break;
    for (size_t i = 0; *(line + i) != '\n'; ++i) {
      if (*(line + i) == '^' && tachyons[i]) {
        tachyons[i] = false;
        if (i > 0)
          tachyons[i - 1] = true;
        if (i < line_len - 1)
          tachyons[i + 1] = true;
	++nsplits;
      }
    }
  }

  printf("%lu\n", nsplits);

  free(tachyons);
  free(line);
  return 0;
}
