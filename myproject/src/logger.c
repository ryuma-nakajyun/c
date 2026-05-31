#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>

static FILE *log_fp = NULL;

static void now(char *buf, size_t size) {
  struct timeval tv;
  gettimeofday(&tv, NULL);

  struct tm tm;
  localtime_r(&tv.tv_sec, &tm);

  int msec = tv.tv_usec / 1000;

  // RFC3339 + ミリ秒
  snprintf(buf, size, "%04d-%02d-%02dT%02d:%02d:%02d.%03d%z", tm.tm_year + 1900,
           tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, msec,
           0); // %z を正しく扱いたいなら別処理が必要
}

void log_init(void) {
  mkdir("log", 0755);

  struct timeval tv;
  gettimeofday(&tv, NULL);

  struct tm tm;
  localtime_r(&tv.tv_sec, &tm);

  int msec = tv.tv_usec / 1000;

  // yyyymmddhhmmsszzz
  char ts[32] = {0};
  snprintf(ts, sizeof(ts), "%04d%02d%02d%02d%02d%02d%03d", tm.tm_year + 1900,
           tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, msec);

  char filename[256] = {0};
  snprintf(filename, sizeof(filename), "log/%s.log", ts);

  log_fp = fopen(filename, "w");
  if (!log_fp) {
    perror("log open failed");
  }
}

void log_close(void) {
  if (log_fp) {
    fclose(log_fp);
    log_fp = NULL;
  }
}

static void write_log(const char *level, const char *fmt, va_list ap) {
  if (!log_fp)
    return;

  char ts[64] = {0};
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
