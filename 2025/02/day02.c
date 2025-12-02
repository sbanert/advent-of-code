#include <stdio.h>
#include <stdlib.h>

// Fast integer exponentiation
long int_pow(long b, long e) {
  long result = 1;
  while (e) {
    if (e % 2) result *= b;
    e /= 2;
    b = b * b;
  }
  return result;
}

// Number of decimal digits
long num_digits(long n) {
  long result = 0;
  while (n) {
    ++result;
    n /= 10;
  }
  return result;
}

// Smallest invalid number that is >= n
long next_invalid(long n) {
  long d = num_digits(n);
  if (d % 2) return int_pow(10, d/2) + int_pow(10, d);
  long first_half = n / int_pow(10, d/2);
  long second_half = n % int_pow(10, d/2);
  if (second_half <= first_half)
    return first_half + first_half *int_pow(10, d / 2);
  if (first_half + 1 < int_pow(10, d / 2))
    return first_half + 1 + (first_half + 1) * int_pow(10, d / 2);
  // unreachable
  exit(1);
}

int main(void) {
  char *line = NULL;
  size_t linecapp = 0;
  ssize_t nchars;
  nchars = getline(&line, &linecapp, stdin);
  if (nchars < 0) {
    return 1;
  }

  char *next_char = line;
  long lower, upper;
  long sum_invalid = 0;
  do {
    lower = strtol(next_char, &next_char, 10);
    upper = strtol(next_char + 1, &next_char, 10);
    while (lower <= upper) {
      long n = next_invalid(lower);
      if (n <= upper)
        sum_invalid += n;
      lower = n + 1;
    }
    next_char++;
  } while (*next_char);

  printf("%ld\n", sum_invalid);

  free(line);
}
