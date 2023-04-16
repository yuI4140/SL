#pragma once
#define DEF
#define NORMAL
#include "core.h"
str fsName;
typedef struct {
  FILE *file;
  long sz;
} Fs;
Fs newFs(cstr filename) {
  FILE *file = fopen(filename, "r+");
  fsName = filename;
  long sz = ftell(file);
  Fs fs2 = {file, sz};
  return fs2;
}
str getName() { return fsName; }
void freeFs(Fs *fs) { fclose(fs->file); }

long fileSize(Fs fs) {
  size_t size = ftell(fs.file);
  fs.sz = size;
  return fs.sz;
}
void writeFs(Fs fs, int index, const char *line) {
  if (fs.file == NULL) {
    printf("Failed to open file \n");
    return;
  }

  // Move file pointer to the beginning of the line to be replaced
  int line_num = 0;
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), fs.file) != NULL) {
    if (line_num == index) {
      break;
    }
    line_num++;
  }

  // Write the new line to the file at the specified index
  fseek(fs.file, -strlen(buffer),
        SEEK_CUR); // Move file pointer back to the start of the line
  fprintf(fs.file, "%s", line); // Write the new line
  freeFs(&fs);
}
const char *readFs(Fs fs, int index) {
  if (fs.file == NULL) {
    printf("Failed to open file\n");
    return NULL;
  }

  char buffer[256]; // Buffer to store each line
  int line_num = 0; // Line number counter
  while (fgets(buffer, sizeof(buffer), fs.file) != NULL) {
    if (line_num == index) { // Match line number
      fclose(fs.file);       // Close file
      // Remove newline character at the end of the line
      char *newline = strchr(buffer, '\n');
      if (newline != NULL) {
        *newline = '\0';
      }
      return strdup(
          buffer); // Return the line as a dynamically allocated string
    }
    line_num++; // Increment line number
  }

  freeFs(&fs);

  // If line number is out of range, return NULL
  printf("Line index out of range: %d\n", index);
  return nullptr;
}