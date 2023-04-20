#pragma once
#ifdef DEF
#include "defines.hpp"
#endif // END-DEF
#ifdef NORMAL
#include <algorithm>
#include <array>
#include <random>
#include <cmath>
#include <cstring>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>
#endif // END-NORMAL
#ifdef EXTRA
#include <cassert>
#include <chrono>
#include <cstdio>
#include <regex>
#include <sstream>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>
#endif // END-EXTRA
#ifdef VARIANTIC
#include <stdarg>
#endif // END-VARIANTIC
#ifdef ERRH
#include <assert.h>
#endif // END-ERRH
#ifdef C_THREAD
#include "../thread.c"
#endif // END-C_THREAD
       // CORE.HPP