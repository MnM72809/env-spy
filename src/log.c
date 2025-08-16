#ifdef DEBUG
#include "log.h"
#include <stdarg.h>
#include <time.h>

static FILE *log_file = NULL;

void log_init(const char *filename)
{
	log_file = fopen(filename, "w");
	if (!log_file)
	{
		perror("fopen");
	}
	log_msg("\n--- Init log ---");
}

void log_close(void)
{
	if (log_file)
	{
		log_msg("\n--- Close log ---\n");
		fclose(log_file);
		log_file = NULL;
	}
}

void log_msg(const char *fmt, ...)
{
	if (!log_file)
		return;

	// Optional: add timestamp
	time_t t = time(NULL);
	struct tm *tm_info = localtime(&t);
	char buffer[20];
	strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", tm_info);
	fprintf(log_file, "[%s] ", buffer);

	va_list args;
	va_start(args, fmt);
	vfprintf(log_file, fmt, args);
	va_end(args);

	fprintf(log_file, "\n");
	fflush(log_file);
}
#endif
