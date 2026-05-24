#ifndef LOGGER_H
#define LOGGER_H

void log_init(void);
void log_close(void);

void log_debug(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_warn(const char *fmt, ...);
void log_error(const char *fmt, ...);

#endif
