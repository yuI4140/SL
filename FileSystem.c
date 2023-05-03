#define DEF
#define DEF_DIR
#define NORMAL
#include ".h/core.h"
#include "Err.c"
typedef struct {
  cstr fname;
  size_t sz;
  Fsp fcore;
} Fs;
#define WRITE 1
#define READ 2
#define BOTH 3
Fs InitFs(cstr _fname, i8 mode) {
  CHECK(mode != 1 || mode != 2 || mode != 3, 17,
        "fail mode -->Help: use 1(write),2(read),3(both)");
  str md;
  if (mode == 1) {
    md = "w";
  }
  if (mode == 2) {
    md = "r";
  }
  if (mode == 3) {
    md = "w+";
  }
  Fsp fnew = fopen(_fname, md);
  Fs fsnew = {.fname = _fname, .sz = ftell(fnew), .fcore = fnew};
  return fsnew;
}
Fs InitFss(cstr _fname, cstr mode) {
  Fsp fnew = fopen(_fname, mode);
  Fs fsnew = {.fname = _fname, .sz = ftell(fnew), .fcore = fnew};
  return fsnew;
}
