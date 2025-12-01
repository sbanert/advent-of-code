#include <stdio.h>
#include <stdlib.h>

int main(void) {
  long pos = 50;
  size_t zeros = 0;
  size_t clicks = 0;

  ssize_t nchars;
  char *ins = NULL;
  size_t l = 0;

  while (1) {
    nchars = getline(&ins, &l, stdin);
    // Check for end of input.
    if (nchars < 2) break;
    long dir = ins[0] == 'L' ? -1 : 1;
    long inc = strtol(ins + 1, NULL, 10);
    // Do not get a click when starting at zero and going left.
    if (pos == 0 && dir == -1) pos = 100;
    clicks += labs((pos + dir * inc) / 100);
    // Integer division rounds towards zero, so when going to zero or
    // below, we get an extra click.
    if (pos + dir * inc <= 0) ++clicks;
    pos = (pos + dir * inc) % 100;
    if (pos < 0) pos += 100;
    if (pos == 0) ++zeros;
  }

  free(ins);
  printf("%lu\n%lu\n", zeros, clicks);
}
