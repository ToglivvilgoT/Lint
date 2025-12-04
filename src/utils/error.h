#ifndef ERROR_H_
#define ERROR_H_

#include <stdbool.h>

// Enable or disable error logging globally
void error_set_enabled(bool enabled);
bool error_is_enabled(void);

// Log an error to stderr if enabled (printf-style)
void error_log(const char *fmt, ...);

#endif // ERROR_H_