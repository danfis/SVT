/**
 * SVT
 * ----------
 * Copyright (c)2007,2008,2009 Daniel Fiser <danfis (at) danfis (dot) cz>
 *
 *
 * This file is part of SVT
 *
 * SVT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SVT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SVT. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SVT_PARSE_FUNC_H_
#define _SVT_PARSE_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Try to parse given string to float (returned by val).
 * This function returns 0 on success, -1 otherwise
 */
int svtParseFloat(const char *str, float *val);

/**
 * Simliar to parseFloat except it parses integers.
 */
int svtParseInt(const char *str, int *val);


/**
 * Exactly same as svtParseInt() but returning value is long.
 */
int svtParseLong(const char *str, long *val);

#ifdef __cplusplus
}
#endif

#endif
