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

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_XBOX) || defined(_WINDOWS) || defined(__MINGW32__)

#include <stddef.h>
#include <errno.h>

#ifdef __USE_WINSOCK__
#include <io.h>
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif /* !WIN32_LEAN_AND_MEAN */

#if defined(_XBOX) || defined(__MINGW32__)
#define snprintf _snprintf
#endif

#if defined(_XBOX) || defined(__USE_WINSOCK__)

/* XBOX Defs end */
struct pollfd {
        t_socket fd;
        short events;
        short revents;
};

#ifdef _XBOX
#define inline __inline 
#endif

#endif

#ifndef POLLIN
#define POLLIN      0x0001    /* There is data to read */
#endif

#ifndef POLLPRI
#define POLLPRI     0x0002    /* There is urgent data to read */
#endif

#ifndef POLLOUT
#define POLLOUT     0x0004    /* Writing now will not block */
#endif

#ifndef POLLERR
#define POLLERR     0x0008    /* Error condition */
#endif

#ifndef POLLHUP
#define POLLHUP     0x0010    /* Hung up */
#endif

typedef SSIZE_T ssize_t;

#if defined(_XBOX) || defined(__USE_WINSOCK__)
int poll(struct pollfd *fds, unsigned int nfds, int timo);

#ifdef __USE_WINSOCK__
#define write(fd, buf, maxcount) _write(fd, buf, (unsigned int)maxcount)
#define read(fd, buf, maxcount) _read(fd, buf, (unsigned int)maxcount)
#endif

#else

#undef poll
#define poll WSAPoll

#endif

#ifdef __USE_WINSOCK__
#define close(x) _close((int)x)
#else
#define close closesocket
#endif

#pragma warning( disable : 4090 ) 

#define strdup _strdup

#endif /* _XBOX */

#ifdef PICO_PLATFORM

#include "lwip/netdb.h"
#include "lwip/sockets.h"

#ifndef SOL_TCP
#define SOL_TCP 6
#endif

#ifndef POLLIN
#define POLLIN      0x0001    /* There is data to read */
#endif

#ifndef POLLPRI
#define POLLPRI     0x0002    /* There is urgent data to read */
#endif

#ifndef POLLOUT
#define POLLOUT     0x0004    /* Writing now will not block */
#endif

#ifndef POLLERR
#define POLLERR     0x0008    /* Error condition */
#endif

#ifndef POLLHUP
#define POLLHUP     0x0010    /* Hung up */
#endif

#define EAI_AGAIN EAGAIN
long long int be64toh(long long int x);
int getlogin_r(char *buf, size_t size);

#endif /* PICO_PLATFORM */

#if defined(__amigaos4__) || defined(__AMIGA__) || defined(__AROS__)

#include <errno.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#if defined(__amigaos4__) || defined(__AROS__)
#include <sys/uio.h>
#endif
#if !defined(__amigaos4__) && (defined(__AMIGA__) || defined(__AROS__))
#include <proto/bsdsocket.h>
#undef HAVE_UNISTD_H
#define close CloseSocket
#endif
#define strncpy(a,b,c) strcpy(a,b)

struct pollfd {
        int fd;
        short events;
        short revents;
};

int poll(struct pollfd *fds, unsigned int nfds, int timo);

#ifndef POLLIN
#define POLLIN      0x0001    /* There is data to read */
#endif

#ifndef POLLPRI
#define POLLPRI     0x0002    /* There is urgent data to read */
#endif

#ifndef POLLOUT
#define POLLOUT     0x0004    /* Writing now will not block */
#endif

#ifndef POLLERR
#define POLLERR     0x0008    /* Error condition */
#endif

#ifndef POLLHUP
#define POLLHUP     0x0010    /* Hung up */
#endif

#endif

#ifdef __PS2__

#ifdef _EE
#include <unistd.h>
#else
#ifndef __ps2sdk_iop__
#include <alloc.h>
#endif
#include <stdint.h>
#include <ps2ip.h>
#include <loadcore.h>
#endif

#ifdef PS2RPC
#include <ps2ips.h>
#else
#include <ps2ip.h>
#endif

#ifdef _IOP
#define close(x) lwip_close(x)
#define snprintf(format, n, ...) sprintf(format, __VA_ARGS__)
#define fcntl(a,b,c) lwip_fcntl(a,b,c)
#endif

struct pollfd {
        int fd;
        short events;
        short revents;
};

int poll(struct pollfd *fds, unsigned int nfds, int timo);

struct iovec {
  void  *iov_base;
  size_t iov_len;
};

#ifdef _IOP
#undef connect
#define connect(a,b,c) iop_connect(a,b,c)
int iop_connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);

#define write(a,b,c) lwip_send(a,b,c,MSG_DONTWAIT)
#define read(a,b,c) lwip_recv(a,b,c,MSG_DONTWAIT)
#endif

#ifndef POLLIN
#define POLLIN      0x0001    /* There is data to read */
#endif

#ifndef POLLPRI
#define POLLPRI     0x0002    /* There is urgent data to read */
#endif

#ifndef POLLOUT
#define POLLOUT     0x0004    /* Writing now will not block */
#endif

#ifndef POLLERR
#define POLLERR     0x0008    /* Error condition */
#endif

#ifndef POLLHUP
#define POLLHUP     0x0010    /* Hung up */
#endif

#endif /* __PS2__ */

#ifdef PS3_PPU_PLATFORM

#include <sys/time.h>
#include <netdb.h>
#include <net/poll.h>

#ifndef POLLIN
#define POLLIN      0x0001    /* There is data to read */
#endif

#ifndef POLLPRI
#define POLLPRI     0x0002    /* There is urgent data to read */
#endif

#ifndef POLLOUT
#define POLLOUT     0x0004    /* Writing now will not block */
#endif

#ifndef POLLERR
#define POLLERR     0x0008    /* Error condition */
#endif

#ifndef POLLHUP
#define POLLHUP     0x0010    /* Hung up */
#endif

#endif

#if defined(__SWITCH__) || defined(__3DS__) || defined(__WII__) || defined(__GC__) || defined(__WIIU__) || defined(__NDS__)

#include <sys/types.h>

struct pollfd {
        int fd;
        short events;
        short revents;
};

int poll(struct pollfd *fds, unsigned int nfds, int timo);

#ifndef POLLIN
#define POLLIN      0x0001    /* There is data to read */
#endif

#ifndef POLLPRI
#define POLLPRI     0x0002    /* There is urgent data to read */
#endif

#ifndef POLLOUT
#define POLLOUT     0x0004    /* Writing now will not block */
#endif

#ifndef POLLERR
#define POLLERR     0x0008    /* Error condition */
#endif

#ifndef POLLHUP
#define POLLHUP     0x0010    /* Hung up */
#endif

#endif

#ifdef __cplusplus
}
#endif