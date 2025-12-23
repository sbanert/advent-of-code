#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Specialised function for part 1
long get_joltage2(char *l) {
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

long get_joltage(size_t b, const char *l) {
  // Containing the positions of the result digits in the string
  // Initialize with 0, ..., b-1
  size_t digits[b];
  for (size_t i = 0; i < b; ++i)
    digits[i] = i;
  // Effective length of the digit sequence;
  // results from getline contain newline.
  // Might not be portable to Windows (where long is 4 bytes anyway).
  size_t len = strlen(l) - 1;

  for (size_t i = 1; i < len; ++i) {
    for (size_t j = 0; j < b; ++j) {
      if (i > digits[j] && l[i] > l[digits[j]] && b + i <= len + j) {
	for (size_t k = 0; j + k < b; ++k) {
	  digits[j + k] = i + k;
	}
	break;
      }
    }
  }

  long result = 0;
  for (size_t i = 0; i < b; ++i) {
    result *= 10;
    result += l[digits[i]] - '0';
  }
  return result;
}

int main(void) {
  char *line = NULL;
  size_t linecapp = 0;
  ssize_t nchars;

  long sum_joltages = 0;
  long sum_big_joltages = 0;
  while(1) {
    nchars = getline(&line, &linecapp, stdin);
    if (nchars < 2) break;
    sum_joltages += get_joltage(2, line);
    sum_big_joltages += get_joltage(12, line);
  }

  printf("%ld\n%ld\n", sum_joltages, sum_big_joltages);

  free(line);
}
