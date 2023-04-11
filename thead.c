#include "core.h"
#ifdef _WIN32
#include <windows.h>
typedef struct {
    HANDLE handle;
    int id;
    CRITICAL_SECTION cs;
    CONDITION_VARIABLE cv;
    int exitCode;
} Thread;

// Function to create a thread
void thread_create(Thread *thread, void (*function)(void*), void* arg)
{
    InitializeCriticalSection(&(thread->cs));
    InitializeConditionVariable(&(thread->cv));
    thread->handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)function, arg, 0, &(thread->id));
    thread->exitCode = 0;
}

// Function to join a thread
void thread_join(Thread *thread)
{
    WaitForSingleObject(thread->handle, INFINITE);
    GetExitCodeThread(thread->handle, &(thread->exitCode));
    CloseHandle(thread->handle);
    DeleteCriticalSection(&(thread->cs));
    DeleteConditionVariable(&(thread->cv));
}

// Function to detach a thread
void thread_detach(Thread *thread)
{
    CloseHandle(thread->handle);
    DeleteCriticalSection(&(thread->cs));
    DeleteConditionVariable(&(thread->cv));
}

// Function to exit a thread
void thread_exit(int exitCode)
{
    ExitThread(exitCode);
}

// Function to get the current thread ID
int thread_get_current_thread_id()
{
    return GetCurrentThreadId();
}

// Function to get the exit code of a thread
int thread_get_thread_exit_code(Thread *thread)
{
    return thread->exitCode;
}

// Function to set the exit code of a thread
void thread_set_thread_exit_code(Thread *thread, int exitCode)
{
    thread->exitCode = exitCode;
}

// Function to get the handle of a thread
HANDLE thread_get_thread_handle(Thread *thread)
{
    return thread->handle;
}

// Function to get the ID of a thread
int thread_get_thread_id(Thread *thread)
{
    return thread->id;
}

// Function to try to lock a mutex without blocking
int thread_mutex_try_lock(CRITICAL_SECTION *mutex)
{
    return TryEnterCriticalSection(mutex);
}

// Function to wait on a condition variable with a timeout
void thread_cond_timed_wait(CONDITION_VARIABLE *cv, CRITICAL_SECTION *mutex, DWORD milliseconds)
{
    SleepConditionVariableCS(cv, mutex, milliseconds);
}

// Function to signal a condition variable to wake up all waiting threads
void thread_cond_signal_all(CONDITION_VARIABLE *cv)
{
    WakeAllConditionVariable(cv);
}
void thread_suspend(Thread *thread)
{
    SuspendThread(thread->handle);
}
#endif /*_WIN32*/