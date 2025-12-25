#include <stdio.h>
#include <stdlib.h>

struct range {
  size_t l, u;
};

int rng_cmp(const void *pr1, const void *pr2) {
  struct range r1 = *(struct range *)pr1;
  struct range r2 = *(struct range *)pr2;
  if (r1.l < r2.l)
    return -1;
  if (r1.l > r2.l)
    return 1;
  return 0;
}

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

  size_t fresh_ids = 0;
  size_t pos = 0;
  qsort(ranges, range_count, sizeof(struct range), rng_cmp);
  for (size_t i = 0; i < range_count; ++i) {
    if (ranges[i].l >= pos) {
      fresh_ids += ranges[i].u - ranges[i].l + 1;
      pos = ranges[i].u + 1;
    } else if (ranges[i].l < pos && ranges[i].u >= pos) {
      fresh_ids += ranges[i].u - pos + 1;
      pos = ranges[i].u + 1;
    }
  }

  printf("%zu\n%zu\n", nfresh, fresh_ids);

  free(ranges);
  free(line);
}
