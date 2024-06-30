#ifndef THREAD_VS_PROCESS_UTILS_H
#define THREAD_VS_PROCESS_UTILS_H

void* thread_timer(void*);
void* process_timer(void*);
void measure_thread();
void measure_process();

#define ITERATIONS 1000

#endif // !THREAD_VS_PROCESS_UTILS_H
