#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

// Delimiters is optional and will default to newline and whitespace
const char** split_string(const char* s, int* len, char* delimiters);

#endif // STRING_UTILS_H_
