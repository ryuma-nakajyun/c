#include "logger.h"

int main(void) {
  log_init();

  log_info("system start");
  log_debug("debug message");
  log_warn("warning");
  log_error("error occurred");

  log_close();
  return 0;
}
