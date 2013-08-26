/*! \file */

/*
    Copyright (C) 2013 Commtech, Inc.

    This file is part of fscc-linux.

    fscc-linux is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fscc-linux is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with fscc-linux.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef FSCC_H
#define FSCC_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>

#define FSCC_REGISTERS_INIT(registers) memset(&registers, -1, sizeof(registers))
#define FSCC_MEMORY_CAP_INIT(memory_cap) memset(&memory_cap, -1, sizeof(memory_cap))
#define FSCC_UPDATE_VALUE -2

enum transmit_type { XF=0, XREP=1, TXT=2, TXEXT=4 };
typedef int64_t fscc_register;

struct fscc_registers {
    /* BAR 0 */
    fscc_register reserved1[2];

    fscc_register FIFOT;

    fscc_register reserved2[2];

    fscc_register CMDR;
    fscc_register STAR; /* Read-only */
    fscc_register CCR0;
    fscc_register CCR1;
    fscc_register CCR2;
    fscc_register BGR;
    fscc_register SSR;
    fscc_register SMR;
    fscc_register TSR;
    fscc_register TMR;
    fscc_register RAR;
    fscc_register RAMR;
    fscc_register PPR;
    fscc_register TCR;
    fscc_register VSTR; /* Read-only */

    fscc_register reserved3[1];

    fscc_register IMR;
    fscc_register DPLLR;

    /* BAR 2 */
    fscc_register FCR;
};

struct fscc_memory_cap {
    int input;
    int output;
};

#ifdef _WIN32
	#define FSCC_IOCTL_MAGIC 0x8018

	#define FSCC_GET_REGISTERS CTL_CODE(FSCC_IOCTL_MAGIC, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_SET_REGISTERS CTL_CODE(FSCC_IOCTL_MAGIC, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_PURGE_TX CTL_CODE(FSCC_IOCTL_MAGIC, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_PURGE_RX CTL_CODE(FSCC_IOCTL_MAGIC, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_ENABLE_APPEND_STATUS CTL_CODE(FSCC_IOCTL_MAGIC, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_DISABLE_APPEND_STATUS CTL_CODE(FSCC_IOCTL_MAGIC, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_GET_APPEND_STATUS CTL_CODE(FSCC_IOCTL_MAGIC, 0x80D, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_SET_MEMORY_CAP CTL_CODE(FSCC_IOCTL_MAGIC, 0x806, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_GET_MEMORY_CAP CTL_CODE(FSCC_IOCTL_MAGIC, 0x807, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_SET_CLOCK_BITS CTL_CODE(FSCC_IOCTL_MAGIC, 0x808, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_ENABLE_IGNORE_TIMEOUT CTL_CODE(FSCC_IOCTL_MAGIC, 0x80A, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_DISABLE_IGNORE_TIMEOUT CTL_CODE(FSCC_IOCTL_MAGIC, 0x80B, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_GET_IGNORE_TIMEOUT CTL_CODE(FSCC_IOCTL_MAGIC, 0x80F, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_SET_TX_MODIFIERS CTL_CODE(FSCC_IOCTL_MAGIC, 0x80C, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_GET_TX_MODIFIERS CTL_CODE(FSCC_IOCTL_MAGIC, 0x80E, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_ENABLE_RX_MULTIPLE CTL_CODE(FSCC_IOCTL_MAGIC, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_DISABLE_RX_MULTIPLE CTL_CODE(FSCC_IOCTL_MAGIC, 0x811, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_GET_RX_MULTIPLE CTL_CODE(FSCC_IOCTL_MAGIC, 0x812, METHOD_BUFFERED, FILE_ANY_ACCESS)

	#define FSCC_ENABLE_APPEND_TIMESTAMP CTL_CODE(FSCC_IOCTL_MAGIC, 0x813, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_DISABLE_APPEND_TIMESTAMP CTL_CODE(FSCC_IOCTL_MAGIC, 0x814, METHOD_BUFFERED, FILE_ANY_ACCESS)
	#define FSCC_GET_APPEND_TIMESTAMP CTL_CODE(FSCC_IOCTL_MAGIC, 0x815, METHOD_BUFFERED, FILE_ANY_ACCESS)
#else
	#define FSCC_IOCTL_MAGIC 0x18
	#define FSCC_GET_REGISTERS _IOR(FSCC_IOCTL_MAGIC, 0, struct fscc_registers *)
	#define FSCC_SET_REGISTERS _IOW(FSCC_IOCTL_MAGIC, 1, const struct fscc_registers *)

	#define FSCC_PURGE_TX _IO(FSCC_IOCTL_MAGIC, 2)
	#define FSCC_PURGE_RX _IO(FSCC_IOCTL_MAGIC, 3)

	#define FSCC_ENABLE_APPEND_STATUS _IO(FSCC_IOCTL_MAGIC, 4)
	#define FSCC_DISABLE_APPEND_STATUS _IO(FSCC_IOCTL_MAGIC, 5)
	#define FSCC_GET_APPEND_STATUS _IOR(FSCC_IOCTL_MAGIC, 13, unsigned *)

	#define FSCC_SET_MEMORY_CAP _IOW(FSCC_IOCTL_MAGIC, 6, struct fscc_memory_cap *)
	#define FSCC_GET_MEMORY_CAP _IOR(FSCC_IOCTL_MAGIC, 7, struct fscc_memory_cap *)

	#define FSCC_SET_CLOCK_BITS _IOW(FSCC_IOCTL_MAGIC, 8, const unsigned char[20])

	#define FSCC_ENABLE_IGNORE_TIMEOUT _IO(FSCC_IOCTL_MAGIC, 10)
	#define FSCC_DISABLE_IGNORE_TIMEOUT _IO(FSCC_IOCTL_MAGIC, 11)
	#define FSCC_GET_IGNORE_TIMEOUT _IOR(FSCC_IOCTL_MAGIC, 15, unsigned *)

	#define FSCC_SET_TX_MODIFIERS _IOW(FSCC_IOCTL_MAGIC, 12, const int)
	#define FSCC_GET_TX_MODIFIERS _IOR(FSCC_IOCTL_MAGIC, 14, unsigned *)

	#define FSCC_ENABLE_RX_MULTIPLE _IO(FSCC_IOCTL_MAGIC, 16)
	#define FSCC_DISABLE_RX_MULTIPLE _IO(FSCC_IOCTL_MAGIC, 17)
	#define FSCC_GET_RX_MULTIPLE _IOR(FSCC_IOCTL_MAGIC, 18, unsigned *)

	#define FSCC_ENABLE_APPEND_TIMESTAMP _IO(FSCC_IOCTL_MAGIC, 19)
	#define FSCC_DISABLE_APPEND_TIMESTAMP _IO(FSCC_IOCTL_MAGIC, 20)
	#define FSCC_GET_APPEND_TIMESTAMP _IOR(FSCC_IOCTL_MAGIC, 21, unsigned *)
#endif

/******************************************************************************/
/*!

  Initializes an fscc_registers structure for use in other functions.

  \def FSCC_REGISTERS_INIT(registers)

*/
/******************************************************************************/
#define FSCC_REGISTERS_INIT(registers) memset(&registers, -1, sizeof(registers))

#define FSCC_UPDATE_VALUE -2


#ifdef _WIN32
typedef HANDLE fscc_handle;
#else
typedef int fscc_handle;
#endif

int fscc_connect(unsigned port_num, int *fd);
int fscc_set_tx_modifiers(int fd, unsigned modifiers);
int fscc_get_tx_modifiers(int fd, unsigned *modifiers);
int fscc_set_memory_cap(int fd, const struct fscc_memory_cap *memcap);
int fscc_get_memory_cap(int fd, struct fscc_memory_cap *memcap);
int fscc_set_registers(int fd, const struct fscc_registers *regs);
int fscc_get_registers(int fd, struct fscc_registers *regs);
int fscc_get_append_status(int fd, unsigned *status);
int fscc_enable_append_status(fscc_handle fd);
int fscc_disable_append_status(int fd);
int fscc_get_append_timestamp(int fd, unsigned *status);
int fscc_enable_append_timestamp(int fd);
int fscc_disable_append_timestamp(int fd);
int fscc_get_ignore_timeout(int fd, unsigned *status);
int fscc_enable_ignore_timeout(int fd);
int fscc_disable_ignore_timeout(int fd);
int fscc_get_rx_multiple(int fd, unsigned *status);
int fscc_enable_rx_multiple(int fd);
int fscc_disable_rx_multiple(int fd);
int fscc_purge(int fd, unsigned tx, unsigned rx);
int fscc_write(int fd, char *buf, unsigned size, unsigned *bytes_written);
int fscc_read(int fd, char *buf, unsigned size, unsigned *bytes_read);
int fscc_disconnect(int fd);
int fscc_set_clock_frequency(int fd, unsigned frequency, unsigned ppm);

#ifdef __cplusplus
}
#endif

#endif
