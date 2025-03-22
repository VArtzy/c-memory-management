#include <stdio.h>

typedef struct {
  int x;
  int y;
} coord_t;

coord_t new_coord(int x, int y) {
  coord_t c;
  c.x = x;
  c.y = y;
  return c;
}

int main() {
  /**
   * These declaration aren't safe because the variable pointer life inside the function has been deallocated
   * coord_t *c1 = new_coord(10, 20); this refers nothing since the coord struct pointer deallocated from stack
   * coord_t *c2 = new_coord(30, 40);
   * coord_t *c3 = new_coord(50, 60);
  */
  coord_t c1 = new_coord(10, 20); // thus, make a copy (return struct value) allow it safe from deallocated memory
  coord_t c2 = new_coord(30, 40);
  coord_t c3 = new_coord(50, 60);

  printf("c1: %d, %d\n", c1.x, c1.y);
  printf("c2: %d, %d\n", c2.x, c2.y);
  printf("c3: %d, %d\n", c3.x, c3.y);
}
