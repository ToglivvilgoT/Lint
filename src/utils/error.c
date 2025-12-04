#include "utils/error.h"

#include <stdarg.h>
#include <stdio.h>

static bool g_error_enabled = true;

void error_set_enabled(bool enabled) { g_error_enabled = enabled; }
bool error_is_enabled(void) { return g_error_enabled; }

void error_log(const char *fmt, ...) {
  if (!g_error_enabled) return;
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}
