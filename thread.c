#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef THREAD_LCL
#define THREAD_LCL
#if defined(_WIN32)
#include <windows.h>
#define sleep(x) Sleep(x)
#elif defined(__unix__)
#include <unistd.h>
#include <syscall.h>
#define thread_yield() sched_yield()
#endif

typedef struct {
    int running;
    void (*start_routine)(void*);
    void* arg;
} thread_t;

void handle_error(const char* message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void* thread_start(void* arg)
{
    thread_t* thread = (thread_t*)arg;
    thread->start_routine(thread->arg);
    thread->running = 0;
    return NULL;
}

void thread_create(thread_t** thread, void (*start_routine)(void*), void* arg)
{
    *thread = (thread_t*)malloc(sizeof(thread_t));
    if (*thread == NULL) {
        handle_error("malloc");
    }

    (*thread)->running = 1;
    (*thread)->start_routine = start_routine;
    (*thread)->arg = arg;

    // Create the thread using platform-specific code
    // ...
}

void thread_exit()
{
    exit(EXIT_SUCCESS);
}

void thread_join(thread_t* thread)
{
    while (thread->running) {
        // Do nothing
    }
    free(thread);
}

void thread_yield()
{
#if defined(_WIN32)
    Sleep(0);
#elif defined(__unix__)
    thread_yield();
#endif
}

void thread_sleep(int milliseconds)
{
#if defined(_WIN32)
    Sleep(milliseconds);
#elif defined(__unix__)
    usleep(milliseconds * 1000);
#endif
}

int thread_equal(thread_t* thread1, thread_t* thread2)
{
#if defined(_WIN32)
    return (thread1 == thread2);
#elif defined(__unix__)
    return (syscall(SYS_gettid) == syscall(SYS_gettid));
#endif
}
#endif /*THREAD_LCL*/

