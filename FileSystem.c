#pragma once
#include "core.h"
typedef struct {
  FILE *file;
  long sz;
} Fs;

Fs createFs(const char *filename) {
  Fs fs;
  fs.file = fopen(filename, "r+");
  fseek(fs.file, 0, SEEK_END);
  fs.sz = ftell(fs.file);
  fseek(fs.file, 0, SEEK_SET);
  return fs;
}
Fs FromFs(FILE *fs) {
  long sz = ftell(fs);
  Fs fs2 = {fs, sz};
  return fs2;
}
void freeFs(Fs *fs) { fclose(fs->file); }

long fileSize(Fs fs) {
  size_t size = ftell(fs.file);
  fs.sz = size;
  return fs.sz;
}

void readFromFile(Fs fs, long offset, void *data, long size) {
  fseek(fs.file, offset, SEEK_SET);
  fread(data, size, 1, fs.file);
}

void writeToFile(Fs fs, const char *data) { fputs(data, fs.file); }
void appendToFile(Fs fs, void *data, long size) {
  fseek(fs.file, 0, SEEK_END);
  fwrite(data, size, 1, fs.file);
  fs.sz += size;
}

void deleteFromFl(Fs fs, long offset, long size) {
  char *buffer = malloc(fs.sz - size);
  fseek(fs.file, 0, SEEK_SET);
  fread(buffer, offset, 1, fs.file);
  fseek(fs.file, offset + size, SEEK_SET);
  fread(buffer + offset, fs.sz - offset - size, 1, fs.file);
  fseek(fs.file, 0, SEEK_SET);
  fwrite(buffer, fs.sz - size, 1, fs.file);
  fs.sz -= size;
  free(buffer);
}

void truncateFile(Fs fs, long size) {
  if (size < fs.sz) {
    fseek(fs.file, size, SEEK_SET);
    ftruncate(fileno(fs.file), size);
    fs.sz = size;
  }
}

void copyFile(const char *src, const char *dest) {
  FILE *srcFile = fopen(src, "rb");
  fseek(srcFile, 0, SEEK_END);
  long sz = ftell(srcFile);
  fseek(srcFile, 0, SEEK_SET);
  char *buffer = malloc(sz);
  fread(buffer, sz, 1, srcFile);
  fclose(srcFile);
  FILE *destFile = fopen(dest, "wb");
  fwrite(buffer, sz, 1, destFile);
  fclose(destFile);
  free(buffer);
}
void readStringFromFile(Fs fs, long offset, char *str, long size) {
  fseek(fs.file, offset, SEEK_SET);
  fread(str, size, 1, fs.file);
  str[size] = '\0';
}

void writeStringToFile(Fs fs, long offset, const char *str) {
  long size = strlen(str);
  fseek(fs.file, offset, SEEK_SET);
  fwrite(str, size, 1, fs.file);
  fs.sz += size - (fs.sz - offset);
}

void copyStringToFile(Fs fs, const char *str) {
  long size = strlen(str);
  fwrite(str, size, 1, fs.file);
  fs.sz += size;
}
void resizeFile(Fs fs, long newSize) {
  if (newSize == fs.sz) {
    return;
  }
  if (newSize < fs.sz) {
    ftruncate(fileno(fs.file), newSize);
  } else {
    fseek(fs.file, newSize - 1, SEEK_SET);
    fputc(0, fs.file);
  }
  fs.sz = newSize;
}