#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
  return first_half + 1 + (first_half + 1) * int_pow(10, d / 2);
}

long next_alt_invalid(long n) {
  long d = num_digits(n);
  long result = 0;

  // Initialize result with smallest invalid number with one more digit
  long p = (d+1)/2;
  while ((d + 1) % p) --p;
  for (long e = p-1; e < d + 1; e += p) {
    result += int_pow(10, e);
  }

  for (p = d/2; p > 0; --p) {
    if (d % p) continue;
    long last_chunk = 0;
    long remainder = n;
    bool carry_one = false;
    while (remainder) {
      long new_chunk = remainder % int_pow(10, p);
      if (new_chunk > last_chunk) {
	carry_one = false;
      } else if (new_chunk < last_chunk) {
        carry_one = true;
      }
      last_chunk = new_chunk;
      remainder /= int_pow(10, p);
    }
    if (carry_one) ++last_chunk;
    long attempt = 0;
    for (long e = 0; e < d; e += p) {
      attempt += last_chunk * int_pow(10, e);
    }
    if (attempt < result) result = attempt;
  }
  return result;
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
  long sum_alt_invalid = 0;
  do {
    lower = strtol(next_char, &next_char, 10);
    upper = strtol(next_char + 1, &next_char, 10);
    while (lower <= upper) {
      long n = next_alt_invalid(lower);
      if (n <= upper) {
        sum_alt_invalid += n;
	if (next_invalid(n) == n) sum_invalid += n;
      }
      lower = n + 1;
    }
    next_char++;
  } while (*next_char);

  printf("%ld\n%ld\n", sum_invalid, sum_alt_invalid);

  free(line);
}
