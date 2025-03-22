#include <string.h>

typedef struct CodeFile {
  int lines;
  int filetype;
} codefile_t;

typedef struct Graphics {
  int fps;
  int height;
  int width;
} graphics_t;

void dump_graphics(graphics_t gsettings[10]);

codefile_t change_filetype(codefile_t *f, int new_filetype);

void update_file(int filedata[200], int new_filetype, int new_num_lines);

void concat_strings(char *str1, const char *str2);

typedef struct {
  size_t length;
  char buffer[64];
} TextBuffer;

int smart_append(TextBuffer* dest, const char* src);
