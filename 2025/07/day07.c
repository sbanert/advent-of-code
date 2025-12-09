#include <stdio.h>
#include <stdlib.h>

int main(void) {
  ssize_t nchars, line_len;
  char *line = NULL;
  size_t linecapp = 0;
  nchars = getline(&line, &linecapp, stdin);
  if (nchars < 0) {
    exit(1);
  } else {
    line_len = nchars - 1; // subtract '\n' character
  }

  size_t *tachyons = malloc(line_len * sizeof(size_t));
  for (size_t i = 0; *(line + i) != '\n'; ++i) {
    if (*(line + i) == 'S') {
      tachyons[i] = 1;
    } else {
      tachyons[i] = 0;
    }
  }

  size_t nsplits = 0;

  while (1) {
    nchars = getline(&line, &linecapp, stdin);
    if (nchars < 1)
      break;
    for (size_t i = 0; *(line + i) != '\n'; ++i) {
      if (*(line + i) == '^' && tachyons[i]) {
        if (i > 0)
          tachyons[i - 1] += tachyons[i];
        if (i < line_len - 1)
          tachyons[i + 1] += tachyons[i];
        tachyons[i] = 0;
	++nsplits;
      }
    }
  }

  size_t ntimelines = 0;
  for (size_t i = 0; i < line_len; ++i)
    ntimelines += tachyons[i];

  printf("%lu\n%lu\n", nsplits, ntimelines);

  free(tachyons);
  free(line);
  return 0;
}
