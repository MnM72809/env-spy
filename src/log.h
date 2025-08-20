#ifndef LOG_H
#define LOG_H

#ifdef DEBUG
void log_init(const char *filename);
void log_close(void);
void log_msg(const char *fmt, ...);
#else
// No-op versions for production
#define log_init(filename) ((void)0)
#define log_close() ((void)0)
#define log_msg(fmt, ...) ((void)0)
#endif

#endif
