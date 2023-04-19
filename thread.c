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

void *run_thread(void *arg) {
  Thread *thread = (Thread *)arg;
  thread->func(thread->arg);
  return NULL;
}

int create_thread(Thread *thread, void (*func)(void *), void *arg) {
  thread->func = func;
  thread->arg = arg;

#ifdef _WIN32
  thread->handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run_thread,
                                thread, 0, NULL);
  return (thread->handle != NULL) ? 0 : -1;
#else
  return pthread_create(&thread->handle, NULL, run_thread, thread);
#endif
}

void join_thread(Thread *thread) {
#ifdef _WIN32
  WaitForSingleObject(thread->handle, INFINITE);
  CloseHandle(thread->handle);
#else
  pthread_join(thread->handle, NULL);
#endif
}
#ifdef _WIN32
typedef DWORD thread_id_t;
#else
typedef pthread_t thread_id_t;
#endif

thread_id_t get_current_thread_id() {
#ifdef _WIN32
  return GetCurrentThreadId();
#else
  return pthread_self();
#endif
}
#ifdef _WIN32
typedef struct {
  DWORD type;
  LPCSTR name;
  DWORD thread_id;
  DWORD flags;
} THREADNAME_INFO;
void set_thread_name(const char *name) {
  DWORD thread_id = GetCurrentThreadId();
  const DWORD MS_VC_EXCEPTION = 0x406D1388;

  THREADNAME_INFO info;
  info.type = 0x1000;
  info.name = name;
  info.thread_id = thread_id;
  info.flags = 0;
}
#else
void set_thread_name(const char *name) {
  pthread_setname_np(pthread_self(), name);
}
#endif
void sleep_ms(unsigned int ms) {
#ifdef _WIN32
  Sleep(ms);
#else
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, NULL);
#endif
}
void stop_thread(Thread *thread) {
#ifdef _WIN32
  TerminateThread(thread, (DWORD)0);
#else
  pthread_cancel(*thread);
#endif
}
int is_thread_running(Thread *thread) {
#ifdef _WIN32
  DWORD exit_code;
  return GetExitCodeThread(thread->handle, &exit_code) &&
         exit_code == STILL_ACTIVE;
#else
  return pthread_kill(thread->handle, 0) == 0;
#endif
}
