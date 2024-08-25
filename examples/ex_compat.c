/* -*-  mode:c; tab-width:8; c-basic-offset:8; indent-tabs-mode:nil;  -*- */
/*
   Copyright (C) 2024 by André Guilherme <andregui17@outlook.com>

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program; if not, see <http://www.gnu.org/licenses/>.
*/

#include "ex_compat.h"

#if defined(__amigaos4__) || defined(__AMIGA__) || defined(__AROS__)
#ifndef __amigaos4__
#define NEED_READV
#define NEED_WRITEV
#include <proto/bsdsocket.h>
#define read(fd, buf, count) recv(fd, buf, count, 0)
#define write(fd, buf, count) send(fd, buf, count, 0)
#ifndef __AROS__
#define select(nfds, readfds, writefds, exceptfds, timeout) WaitSelect(nfds, readfds, writefds, exceptfds, timeout, NULL)
#endif
#ifdef libnix
StdFileDes *_lx_fhfromfd(int d) { return NULL; }
struct MinList __filelist = { (struct MinNode *) &__filelist.mlh_Tail, NULL, (struct MinNode *) &__filelist.mlh_Head };
#endif
#endif

#define login_num ENXIO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#ifdef __PS2__

#ifdef _EE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#else
#include <sysclib.h>
#include <thbase.h>
#include <stdio.h>
#include <stdarg.h>
#endif
#include <errno.h>

#ifdef _IOP

int errno;

int iop_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen)
{
        int rc;
        int err = 0;
        socklen_t err_size = sizeof(err);

        if ((rc = lwip_connect(sockfd, addr, addrlen)) < 0) {
                if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR,
			       (char *)&err, &err_size) != 0 || err != 0) {
                        errno = err;
                }
        }

        return rc;
}

#endif

#endif /* __PS2__ */

#ifdef __vita__

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define login_num ENXIO

#endif

#if defined(__SWITCH__) || defined(__3DS__) || defined(__WII__) || defined(__GC__) || defined(__WIIU__) || defined(__NDS__)

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <alloca.h>
#include <stdio.h>
#if !defined(__WII__) && !defined(__GC__)
#include <sys/socket.h>
#endif
#if defined(__NDS__)
#include <netinet/in.h>
#endif
#if defined(__SWITCH__)
#include <switch/types.h>
#elif defined(__3DS__)
#include <3ds/types.h>	
#elif defined(__WII__) || defined(__GC__)
#include <gctypes.h>
#elif defined(__WIIU__)
#include <wut_types.h>
#elif defined(__NDS__)
#include <mm_types.h>
#endif

#define login_num ENXIO

#endif /* __SWITCH__ */
