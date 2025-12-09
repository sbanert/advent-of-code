#include <stdio.h>
#include <stdlib.h>

int main(void) {
  ssize_t nchars;
  char *line = NULL;
  size_t linecapp = 0;
  nchars = getline(&line, &linecapp, stdin);
  if (nchars < 0)
    exit(1);

  // Initialisation of products and sums; since I don't know how many
  // numbers I get, I reserve enough memory by taking the number of
  // chars.
  long *products = malloc(nchars * sizeof(long));
  long *sums = malloc(nchars * sizeof(long));

  size_t i = 0;
  char *nptr = line;
  char *endptr = line;
  long num;
  while (1) {
    num = strtol(nptr, &endptr, 10);
    if (nptr == endptr)
      break;
    sums[i] = num;
    products[i] = num;
    ++i;
    nptr = endptr;
  }

  // Update of sums and products if new numbers are being read
  while(1) {
    nchars = getline(&line, &linecapp, stdin);

    char *fst_non_whitespace = line;
    while (*fst_non_whitespace == ' ') ++fst_non_whitespace;
    if (*fst_non_whitespace > '9' || *fst_non_whitespace < '0')
      break;

    nptr = line;
    endptr = line;
    size_t i = 0;
    while (1) {
      num = strtol(nptr, &endptr, 10);
      if (nptr == endptr)
        break;
      sums[i] += num;
      products[i] *= num;
      ++i;
      nptr = endptr;
    }
  }

  long grandtotal = 0;
  i = 0;
  for (nptr = line; *nptr != '\0'; ++nptr) {
    if (*nptr == '+') {
      grandtotal += sums[i];
    } else if (*nptr == '*') {
      grandtotal += products[i];
    } else
      continue;
    ++i;
  }

  printf("%ld\n", grandtotal);

  free(sums);
  free(products);
  free(line);
  return 0;
}
