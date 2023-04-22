#pragma once
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#ifdef _WIN32
typedef HANDLE thread_t;
#else
typedef pthread_t thread_t;
#endif

typedef struct {
  thread_t handle;
  void (*func)(void *);
  void *arg;
} Thread;

void *run_thread(void *arg);

int create_thread(Thread *thread, void (*func)(void *), void *arg);

void join_thread(Thread *thread);

#ifdef _WIN32
typedef DWORD thread_id_t;
#else
typedef pthread_t thread_id_t;
#endif

thread_id_t get_current_thread_id();

void set_thread_name(const char *name);

void sleep_ms(unsigned int ms);

void stop_thread(Thread *thread);

int is_thread_running(Thread *thread);
