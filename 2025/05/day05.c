#include <stdio.h>
#include <stdlib.h>

struct range {
  size_t l, u;
};

int main(void) {
  struct range *ranges = malloc(sizeof(struct range));
  size_t range_count = 0;
  size_t range_cap = 1;

  char *line = NULL;
  size_t cap = 0;
  for (;;) {
    ssize_t nchars = getline(&line, &cap, stdin);
    if (nchars <= 1)
      break;
    ++range_count;
    if (range_count > range_cap) {
      range_cap *= 2;
      ranges = realloc(ranges, range_cap * sizeof(struct range));
    }
    char *next;
    ranges[range_count - 1].l = strtoul(line, &next, 10);
    ranges[range_count - 1].u = strtoul(next + 1, NULL, 10);
  }

  size_t nfresh = 0;
  for (;;) {
    ssize_t nchars = getline(&line, &cap, stdin);
    if (nchars <= 1)
      break;
    size_t ingred = strtoul(line, NULL, 10);
    for (size_t i = 0; i < range_count; ++i) {
      if (ranges[i].l <= ingred && ingred <= ranges[i].u) {
        ++nfresh;
        break;
      }
    }
  }

  printf("%zu\n", nfresh);

  free(ranges);
  free(line);
}
