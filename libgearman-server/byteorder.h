/*
  Taken from libmemcached.
 */

/* LibMemcached
 * Copyright (C) 2006-2009 Brian Aker
 * All rights reserved.
 *
 * Use and distribution licensed under the BSD license.  See
 * the COPYING file in the parent directory for full text.
 *
 * Summary:
 *
 */

#ifndef GEARMAN_BYTEORDER_H
#define GEARMAN_BYTEORDER_H

#ifndef HAVE_HTONLL

uint64_t ntohll(uint64_t);

uint64_t htonll(uint64_t);

#endif

#ifdef linux
/* /usr/include/netinet/in.h defines macros from ntohs() to _bswap_nn to
 * optimize the conversion functions, but the prototypes generate warnings
 * from gcc. The conversion methods isn't the bottleneck for my app, so
 * just remove the warnings by undef'ing the optimization ..
 */
#undef ntohs
#undef ntohl
#undef htons
#undef htonl
#endif

#endif /* GEARMAN_BYTEORDER_H */
