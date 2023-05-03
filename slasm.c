#define NOBUILD_IMP
#include "Err.c"
#include "Color.c"
//#include "string.c"
#include ".h/defines.h"
#include "third-party/_nobuild.h/nobuild.h"

i32 main(i32 argc, str *argv) {
  CHECK(argc <= 0, 97, "no args given");

  // GO_REBUILD_URSELF(argc, argv);
  if (argv[1] != nullptr && argv[2] == nullptr) {
    CMD("nasm", "-f elf64", argv[1], "-o", "builded.o");
    CMD("ld", "builded.o", "-o", "builded");
#ifdef __WIN32__
    CMD("del","./builded.o");
#endif
    CMD("rm","./builded.o");
  }
  // if (argv[1] != nullptr && argv[2] != nullptr && argv[3] == nullptr) {
  //   CMD("nasm");
  // }
  // if (argv[2] != nullptr && argv[1] != nullptr && argv[3] != nullptr) {
  //   CMD("gcc", add_all(argv, 2, true), "-o", "builded", argv[1]);
  // }
}
