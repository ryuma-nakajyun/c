#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

static FILE *log_fp = NULL;

static void now(char *buf, size_t size) {
  time_t t = time(NULL);
  struct tm tm;
  localtime_r(&t, &tm);
  strftime(buf, size, "%Y-%m-%dT%H:%M:%S%z", &tm);
}

void log_init(void) {
  mkdir("log", 0755);

  char filename[256];
  char ts[32];
  now(ts, sizeof(ts));

  // ファイル名は yyyymmdd-hhmmss.log
  snprintf(filename, sizeof(filename), "log/%.*s.log", 15, ts);

  log_fp = fopen(filename, "w");
  if (!log_fp) {
    perror("log open failed");
  }
}

void log_close(void) {
  if (log_fp)
    fclose(log_fp);
}

static void write_log(const char *level, const char *fmt, va_list ap) {
  if (!log_fp)
    return;

  char ts[32];
  now(ts, sizeof(ts));

  fprintf(log_fp, "%s %s ", ts, level);
  vfprintf(log_fp, fmt, ap);
  fprintf(log_fp, "\n");
  fflush(log_fp);
}

void log_info(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  write_log("INFO", fmt, ap);
  va_end(ap);
}

void log_debug(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  write_log("DEBUG", fmt, ap);
  va_end(ap);
}

void log_warn(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  write_log("WARN", fmt, ap);
  va_end(ap);
}

void log_error(const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  write_log("ERROR", fmt, ap);
  va_end(ap);
}
