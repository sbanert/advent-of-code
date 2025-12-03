#include <stdio.h>
#include <stdlib.h>

long get_joltage(char *l) {
  char first = *l;
  char second = *(l + 1);
  for (++l; '0' <= *l && *l <= '9'; ++l) {
    if (*l > first && '0' <= *(l + 1) && *(l+1) <= '9') {
      first = *l;
      second = *(l + 1);
    } else if (*l > second) {
      second = *l;
    }
  }
  return 10 * (first - '0') + (second - '0');
}

int main(void) {
  char *line = NULL;
  size_t linecapp = 0;
  ssize_t nchars;

  long sum_joltages = 0;
  while(1) {
    nchars = getline(&line, &linecapp, stdin);
    if (nchars < 2) break;
    sum_joltages += get_joltage(line);
  }

  printf("%ld\n", sum_joltages);

  free(line);
}
