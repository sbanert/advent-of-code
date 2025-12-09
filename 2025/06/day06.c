#include <stdio.h>
#include <stdlib.h>

enum op { op_plus, op_times };

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

  // Column-based number for part 2
  long *revnums = malloc(nchars * sizeof(long));
  for (size_t i = 0; i < (size_t)nchars; ++i) {
    revnums[i] = 0;
  }

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

  for (size_t i = 0; line[i] != '\0'; ++i) {
    if (line[i] >= '0' && line[i] <= '9') {
      revnums[i] *= 10;
      revnums[i] += line[i] - '0';
    }
  }

  // Update of sums and products if new numbers are being read
  while(1) {
    nchars = getline(&line, &linecapp, stdin);

    char *fst_nonspace = line;
    while (*fst_nonspace == ' ') ++fst_nonspace;
    if (*fst_nonspace > '9' || *fst_nonspace < '0')
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

    for (size_t i = 0; line[i] != '\0'; ++i) {
      if (line[i] >= '0' && line[i] <= '9') {
	revnums[i] *= 10;
	revnums[i] += line[i] - '0';
      }
    }
  }

  long grandtotal = 0;
  long alt_grandtotal = 0;
  long curr;
  size_t inumber = 0;
  enum op curr_op;
  for (size_t i = 0; line[i] != '\0'; ++i) {
    if (line[i] == '+') {
      grandtotal += sums[inumber];
      curr_op = op_plus;
      curr = 0;
      ++inumber;
    } else if (line[i] == '*') {
      grandtotal += products[inumber];
      curr_op = op_times;
      curr = 1;
      ++inumber;
    }
    if (revnums[i] == 0) {
      alt_grandtotal += curr;
    } else if (curr_op == op_plus) {
      curr += revnums[i];
    } else {
      curr *= revnums[i];
    }
  }

  printf("%ld\n%ld\n", grandtotal, alt_grandtotal);

  free(revnums);
  free(sums);
  free(products);
  free(line);
  return 0;
}
