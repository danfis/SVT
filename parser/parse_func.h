#ifndef _PARSE_FUNC_H_
#define _PARSE_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Try to parse given string to float (returned by val).
 * This function returns 0 on success, -1 otherwise
 */
int parseFloat(const char *str, float *val);

/**
 * Simliar to parseFloat except it parses integers.
 */
int parseInt(const char *str, int *val);

#ifdef __cplusplus
}
#endif

#endif
