#include <stdio.h>
#include <stdlib.h>

#define TEST 0

#if TEST
#define NCONNS 10
#define NBOXES 20
#else
#define NCONNS 1000
#define NBOXES 1000
#endif

struct Box {
  long x, y, z;
};

struct Conn {
  long distsq;
  size_t box1, box2;
};

int cmp_conn(const void *pc1, const void *pc2) {
  struct Conn c1 = *(struct Conn*) pc1;
  struct Conn c2 = *(struct Conn*) pc2;
  if (c1.distsq - c2.distsq > 0) return 1;
  if (c1.distsq - c2.distsq < 0) return -1;
  return 0;
}

int cmp_cluster(const void *pc1, const void *pc2) {
  size_t c1 = *(size_t*) pc1;
  size_t c2 = *(size_t*) pc2;
  if (c2 < c1)
    return -1;
  if (c1 < c2)
    return 1;
  return 0;
}

int main(void) {
  struct Box boxes[NBOXES];

  for (size_t i = 0; i < NBOXES; ++i) {
    scanf("%ld,%ld,%ld\n", &boxes[i].x, &boxes[i].y, &boxes[i].z);
  }

  // This will segfault if allocated on the stack.
  struct Conn *distances = malloc(NBOXES * (NBOXES - 1) / 2 * sizeof(struct Conn));;
  size_t k = 0;
  for (size_t i = 0; i < NBOXES; ++i) {
    for (size_t j = 0; j < i; ++j) {
      distances[k].distsq =
	(boxes[i].x - boxes[j].x) * (boxes[i].x - boxes[j].x)
	+ (boxes[i].y - boxes[j].y) * (boxes[i].y - boxes[j].y)
	+ (boxes[i].z - boxes[j].z) * (boxes[i].z - boxes[j].z);
      distances[k].box1 = j;
      distances[k].box2 = i; // box1 < box2
      ++k;
    }
  }

  qsort(distances, NBOXES * (NBOXES - 1) / 2, sizeof(struct Conn), cmp_conn);

  size_t clusters[NBOXES];
  for (size_t i = 0; i < NBOXES; ++i) {
    clusters[i] = i;
  }

  size_t connected = 0;
  for (size_t i = 0; i < NCONNS; ++i) {
    size_t b1 = distances[i].box1;
    size_t b2 = distances[i].box2;
    size_t c1 = clusters[b1];
    size_t c2 = clusters[b2];
    if (c1 != c2) {
      ++connected;
      for (size_t j = 0; j < NBOXES; ++j) {
	if (clusters[j] == c2) clusters[j] = c1;
      }
    }
  }

  size_t cluster_sizes[NBOXES];
  for (size_t i = 0; i < NBOXES; ++i) {
    cluster_sizes[i] = 0;
  }
  for (size_t i = 0; i < NBOXES; ++i) {
    ++cluster_sizes[clusters[i]];
  }

  qsort(cluster_sizes, NBOXES, sizeof(size_t), cmp_cluster);

  printf("%zu\n", cluster_sizes[0] * cluster_sizes[1] * cluster_sizes[2]);

  for (size_t i = NCONNS; ; ++i) {
    size_t b1 = distances[i].box1;
    size_t b2 = distances[i].box2;
    size_t c1 = clusters[b1];
    size_t c2 = clusters[b2];
    if (c1 != c2) {
      ++connected;
      for (size_t j = 0; j < NBOXES; ++j) {
	if (clusters[j] == c2) clusters[j] = c1;
      }
    }
    if (connected == NBOXES - 1) {
      printf("%ld\n", boxes[distances[i].box1].x * boxes[distances[i].box2].x);
      break;
    }
  }

  free(distances);
}
