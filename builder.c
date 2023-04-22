#define NOBUILD_IMP
#include "string.c"
#include "third-party/_nobuild.h/nobuild.h"
i32 main(i32 argc, str *argv) {
  if (argc <= 0) {
    printf("no args given");
  }
  // GO_REBUILD_URSELF(argc, argv);
  if (argv[1] != nullptr && argv[2] == nullptr) {
    CMD("gcc", "-o", "builded", argv[1]);
  }
  if (argv[1] != nullptr && argv[2] != nullptr && argv[3] == nullptr) {
    CMD("gcc", argv[2], "-o", "builded", argv[1]);
  }
  if (argv[2] != nullptr && argv[1] != nullptr && argv[3] != nullptr) {
    CMD("gcc", add_all(argv, 2, true), "-o", "builded", argv[1]);
  }
  if (argv[2] == "-s" && argv[1] != nullptr && argv[3] != nullptr) {
    // TODO: save to a config file to don`t repeat eavery time :)
  }
}
