/**
 * SVT
 * ----------
 * Copyright (c)2007,2008 Daniel Fiser <danfis (at) danfis (dot) cz>
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

#ifndef _MSG_HPP_
#define _MSG_HPP_

#include <iostream>

#ifndef NDEBUG
# define DBG(str) \
    std::cerr << __func__ << ": " << str << std::endl; \
    std::cerr.flush()
#else
# define DBG(str)
#endif

#define ERR(str) \
    std::cerr << "Error: " << str << std::endl; \
    std::cerr.flush()

#endif
