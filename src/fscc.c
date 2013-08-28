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

#include <stdio.h>
#include <fcntl.h> /* open, O_RDWR */

#ifndef _WIN32
#include <unistd.h> /* write, close */
#endif

#include "fscc.h"
#include "errno.h"
#include "calculate-clock-bits.h"

#define UNUSED(x) (void)(x)

#define MAX_NAME_LENGTH 25

int translate_error(int e)
{
#ifdef _WIN32
    switch (e) {
        case STATUS_IO_TIMEOUT:
            return FSCC_TIMEOUT;
        case STATUS_BUFFER_TOO_SMALL:
            return FSCC_BUFFER_TOO_SMALL;
    default:
        return e;
    }
#else
    switch (e) {
        case -EOPNOTSUPP:
            return FSCC_INCORRECT_MODE;
        case -ETIMEDOUT:
            return FSCC_TIMEOUT;
        case -ENOBUFS:
            return FSCC_BUFFER_TOO_SMALL;
    default:
        return e;
    }
#endif
}

int ioctl_action(fscc_handle h, int ioctl_name)
{
    int result;

#ifdef _WIN32
	DWORD temp;

	result = DeviceIoControl(h, (DWORD)ioctl_name,
		                     NULL, 0,
							 NULL, 0,
							 &temp, (LPOVERLAPPED)NULL);

	return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_boolean(fscc_handle h, int ioctl_enable, int ioctl_disable,
                      unsigned value)
{
    int ioctl_name = 0;

    ioctl_name = (value) ? ioctl_enable : ioctl_disable;

    return ioctl_action(h, ioctl_name);
}

int ioctl_get_boolean(fscc_handle h, int ioctl_name, unsigned *status)
{
    int result;

#ifdef _WIN32
	DWORD temp;

	result = DeviceIoControl(h, (DWORD)ioctl_name,
		                     NULL, 0,
							 status, sizeof(*status),
							 &temp, (LPOVERLAPPED)NULL);

	return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, status);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_integer(fscc_handle h, int ioctl_name, int value)
{
    int result;

#ifdef _WIN32
	DWORD temp;

	result = DeviceIoControl(h, (DWORD)ioctl_name,
		                     &value, sizeof(value),
							 NULL, 0,
							 &temp, (LPOVERLAPPED)NULL);

	return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, &value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_get_integer(fscc_handle h, int ioctl_name, int *value)
{
    int result;

#ifdef _WIN32
	DWORD temp;

	result = DeviceIoControl(h, (DWORD)ioctl_name,
		                     NULL, 0,
							 value, sizeof(*value),
							 &temp, (LPOVERLAPPED)NULL);

	return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_set_pointer(fscc_handle h, int ioctl_name, const void *value,
                      int size)
{
    int result;

    #ifdef _WIN32
	    DWORD temp;

	    result = DeviceIoControl(h, (DWORD)ioctl_name,
		                         value, size,
							     NULL, 0,
							     &temp, (LPOVERLAPPED)NULL);

	    return (result == TRUE) ? 0 : translate_error(GetLastError());
    #else
        UNUSED(size);

        result = ioctl(h, ioctl_name, value);

        return (result != -1) ? 0 : translate_error(errno);
    #endif
}

int ioctl_get_pointer(fscc_handle h, int ioctl_name, void *value,
                      int size)
{
    int result;

#ifdef _WIN32
	DWORD temp;

	result = DeviceIoControl(h, (DWORD)ioctl_name,
		                     NULL, 0,
							 value, size,
							 &temp, (LPOVERLAPPED)NULL);

	return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(size);

    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

int ioctl_getset_pointer(fscc_handle h, int ioctl_name, void *value,
                         int size)
{
    int result;

#ifdef _WIN32
	DWORD temp;

	result = DeviceIoControl(h, (DWORD)ioctl_name,
							 value, size,
							 value, size,
							 &temp, (LPOVERLAPPED)NULL);

	return (result == TRUE) ? 0 : translate_error(GetLastError());
#else
    UNUSED(size);

    result = ioctl(h, ioctl_name, value);

    return (result != -1) ? 0 : translate_error(errno);
#endif
}

/******************************************************************************/
/*!

  \brief Opens a handle to an FSCC port.

  \param[in] port_num
    the FSCC port number
  \param[in] overlapped
    whether you would like to use the port in overlapped mode
  \param[out] h
    user variable that the port's HANDLE will be assigned to

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \note
    Opening a handle using this API will only give you access to the
    synchronous functionality of the card. You will need to use the COM ports
    if you would like to use the asynchronous functionality.

*/
/******************************************************************************/
int fscc_connect(unsigned port_num, int overlapped, fscc_handle *h)
{
    char name[MAX_NAME_LENGTH];

#ifdef _WIN32
	DWORD flags_and_attributes = FILE_ATTRIBUTE_NORMAL;

	sprintf_s(name, MAX_NAME_LENGTH, "\\\\.\\FSCC%u", port_num);

	if (overlapped)
		flags_and_attributes |= FILE_FLAG_OVERLAPPED;

	*h = CreateFile(name,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			flags_and_attributes,
			NULL
	);

	return (*h != INVALID_HANDLE_VALUE) ? 0 : GetLastError();
#else
    UNUSED(overlapped);

    sprintf(name, "/dev/fscc%u", port_num);

    *h = open(name, O_RDWR);

    return (*h != -1) ? 0 : errno;
#endif
}

/******************************************************************************/
/*!

  \brief Sets the transmit modifiers for the port.

  \param[in] h
    HANDLE to the port
  \param[in] modifiers
    bit mask of the transmit modifier values

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \note
    XF - Normal transmit - disable modifiers
    XREP - Transmit repeat
    TXT - Transmit on timer
    TXEXT - Transmit on external signal

  \snippet set-tx-modifiers.c Set TXT | XREP
  \snippet set-tx-modifiers.c Set XF

*/
/******************************************************************************/
int fscc_set_tx_modifiers(fscc_handle h, unsigned modifiers)
{
    return ioctl_set_integer(h, FSCC_SET_TX_MODIFIERS, modifiers);
}

/******************************************************************************/
/*!

  \brief Gets the transmit modifiers for the port.

  \param[in] h
    HANDLE to the port
  \param[out] modifiers
    bit mask of the transmit modifier values

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \note
    XF - Normal transmit - disable modifiers
    XREP - Transmit repeat
    TXT - Transmit on timer
    TXEXT - Transmit on external signal

  \snippet get-tx-modifiers.c Setup variables
  \snippet get-tx-modifiers.c Get modifiers

*/
/******************************************************************************/
int fscc_get_tx_modifiers(fscc_handle h, unsigned *modifiers)
{
    return ioctl_get_integer(h, FSCC_GET_TX_MODIFIERS, (int *)modifiers);
}

/******************************************************************************/
/*!

  \brief Sets the FSCC driver's memory caps.

  \param[in] h
    HANDLE to the port
  \param[in] memcap
    input and output memory cap values

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-memory-cap.c Setup variables
  \snippet set-memory-cap.c Set memory cap

*/
/******************************************************************************/
int fscc_set_memory_cap(fscc_handle h, const struct fscc_memory_cap *memcap)
{
    return ioctl_set_pointer(h, FSCC_SET_MEMORY_CAP, memcap, sizeof(*memcap));
}

/******************************************************************************/
/*!

  \brief Gets the FSCC driver's memory caps.

  \param[in] h
    HANDLE to the port
  \param[in] memcap
    input and output memory cap values

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet get-memory-cap.c Setup variables
  \snippet get-memory-cap.c Get memory cap

*/
/******************************************************************************/
int fscc_get_memory_cap(fscc_handle h, struct fscc_memory_cap *memcap)
{
    return ioctl_get_pointer(h, FSCC_GET_MEMORY_CAP, memcap, sizeof(*memcap));
}

/******************************************************************************/
/*!

  \brief Sets a port's register values.

  \param[in] h
    HANDLE to the port
  \param[in] regs
    the new register values

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-registers.c Setup variables
  \snippet set-registers.c Set registers

*/
/******************************************************************************/
int fscc_set_registers(fscc_handle h, const struct fscc_registers *regs)
{
    return ioctl_set_pointer(h, FSCC_SET_REGISTERS, regs, sizeof(*regs));
}

/******************************************************************************/
/*!

  \brief Gets a port's register values.

  \param[in] h
    HANDLE to the port
  \param[out] regs
    the register values

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet get-registers.c Setup variables
  \snippet get-registers.c Get registers

*/
/******************************************************************************/
int fscc_get_registers(fscc_handle h, struct fscc_registers *regs)
{
    return ioctl_getset_pointer(h, FSCC_GET_REGISTERS, regs, sizeof(*regs));
}

/******************************************************************************/
/*!

  \brief Gets a port's append status value.

  \param[in] h
    HANDLE to the port
  \param[out] status
    the append status value

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet get-append-status.c Setup variables
  \snippet get-append-status.c Get append status

*/
/******************************************************************************/
int fscc_get_append_status(fscc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, FSCC_GET_APPEND_STATUS, status);
}

/******************************************************************************/
/*!

  \brief Enable appending the status to the received data.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-append-status.c Enable append status

*/
/******************************************************************************/
int fscc_enable_append_status(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_APPEND_STATUS,
                             FSCC_DISABLE_APPEND_STATUS, 1);
}

/******************************************************************************/
/*!

  \brief Disable appending the status to the received data.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-append-status.c Disable append status

*/
/******************************************************************************/
int fscc_disable_append_status(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_APPEND_STATUS,
                             FSCC_DISABLE_APPEND_STATUS, 0);
}

/******************************************************************************/
/*!

  \brief Gets a port's append timestamp value.

  \param[in] h
    HANDLE to the port
  \param[out] status
    the append timestamp value

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_get_append_timestamp(fscc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, FSCC_GET_APPEND_TIMESTAMP, status);
}

/******************************************************************************/
/*!

  \brief Enable appending the timestamp to the received data.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_enable_append_timestamp(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_APPEND_TIMESTAMP,
                             FSCC_DISABLE_APPEND_TIMESTAMP, 1);
}

/******************************************************************************/
/*!

  \brief Disable appending the timestamp to the received data.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_disable_append_timestamp(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_APPEND_TIMESTAMP,
                             FSCC_DISABLE_APPEND_TIMESTAMP, 0);
}

/******************************************************************************/
/*!

  \brief Gets a port's ignore timeout value.

  \param[in] h
    HANDLE to the port
  \param[out] status
    the append status value

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet get-ignore-timeout.c Setup variables
  \snippet get-ignore-timeout.c Get ignore timeout

*/
/******************************************************************************/
int fscc_get_ignore_timeout(fscc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, FSCC_GET_IGNORE_TIMEOUT, status);
}

/******************************************************************************/
/*!

  \brief Ignore card timeouts.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-ignore-timeout.c Enable ignore timeout

*/
/******************************************************************************/
int fscc_enable_ignore_timeout(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_IGNORE_TIMEOUT,
                             FSCC_DISABLE_IGNORE_TIMEOUT, 1);
}

/******************************************************************************/
/*!

  \brief Disable ignore timeout.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-ignore-timeout.c Disable ignore timeout

*/
/******************************************************************************/
int fscc_disable_ignore_timeout(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_IGNORE_TIMEOUT,
                             FSCC_DISABLE_IGNORE_TIMEOUT, 0);
}
/******************************************************************************/
/*!

  \brief Gets a port's receive multiple value.

  \param[in] h
    HANDLE to the port
  \param[out] status
    the rx multiple value

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_get_rx_multiple(fscc_handle h, unsigned *status)
{
    return ioctl_get_boolean(h, FSCC_GET_RX_MULTIPLE, status);
}

/******************************************************************************/
/*!

  \brief Receive frames in groups.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_enable_rx_multiple(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_RX_MULTIPLE,
                             FSCC_DISABLE_RX_MULTIPLE, 1);
}

/******************************************************************************/
/*!

  \brief Disable receive multiple.

  \param[in] h
    HANDLE to the port

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_disable_rx_multiple(fscc_handle h)
{
    return ioctl_set_boolean(h, FSCC_ENABLE_RX_MULTIPLE,
                             FSCC_DISABLE_RX_MULTIPLE, 0);
}

/******************************************************************************/
/*!

  \brief Clears the transmit and/or receive data out of the card.

  \param[in] h
    HANDLE to the port
  \param[in] tx
    whether to clear the transmit data out
  \param[in] rx
    whether to clear the receive data out

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \note
    Any pending transmit data will not be transmited upon a purge.

  \note
    If you receive a ERROR_TIMEOUT you are likely at a speed too slow (~35 Hz)
        for this driver. You will need to contact Commtech to get a custom driver.

  \snippet purge.c Purge TX
  \snippet purge.c Purge RX
  \snippet purge.c Purge both TX & RX

*/
/******************************************************************************/
int fscc_purge(fscc_handle h, unsigned tx, unsigned rx)
{
    int error;

    if (tx) {
        error = ioctl_action(h, FSCC_PURGE_TX);

        if (error)
            return error;
    }

    if (rx) {
        error = ioctl_action(h, FSCC_PURGE_RX);

        if (error)
            return error;
    }

    return 0;
}

/******************************************************************************/
/*!

  \brief Sets a port's clock frequency.

  \param[in] h
    HANDLE to the port
  \param[in] frequency
    the new clock frequency
  \param[in] ppm
    TODO

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

  \snippet set-clock-frequency.c Set clock frequency

  \todo
    What should I do about PPM?

*/
/******************************************************************************/
int fscc_set_clock_frequency(fscc_handle h, unsigned frequency, unsigned ppm)
{
    unsigned char clock_bits[20];

    calculate_clock_bits(frequency, ppm, clock_bits);

    return ioctl_set_pointer(h, FSCC_SET_CLOCK_BITS, clock_bits, sizeof(clock_bits));
}

/******************************************************************************/
/*!

  \brief Transmits data out of a port.

  \param[in] h
    HANDLE to the port
  \param[in] buf
    the buffer containing the data to transmit
  \param[in] size
    the number of bytes to transmit from 'buf'
  \param[out] bytes_written
    the input variable to store how many bytes were actually written
  \param[in,out] o
    OVERLAPPED structure for asynchronous operation

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_write(fscc_handle h, char *buf, unsigned size,
               unsigned *bytes_written, OVERLAPPED *o)
{
    int result;

#ifdef _WIN32
    BOOL result;

	result = WriteFile(h, buf, size, (DWORD*)bytes_written, o);

	return (result == TRUE) ? 0 : GetLastError();
#else
    UNUSED(o);

    result = write(h, buf, size);

    if (result == -1)
        return errno;

    *bytes_written = result;

    return 0;
#endif
}

/******************************************************************************/
/*!

  \brief Reads data out of a port.

  \param[in] h
    HANDLE to the port
  \param[in] buf
    the input buffer used to store the receive data
  \param[in] size
    the maximum number of bytes to read in (typically sizeof(buf))
  \param[out] bytes_read
    the user variable to store how many bytes were actually read
  \param[in,out] o
    OVERLAPPED structure for asynchronous operation

  \return 0
    if the operation completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_read(fscc_handle h, char *buf, unsigned size, unsigned *bytes_read,
              OVERLAPPED *o)
{
    int result;
#ifdef _WIN32

	result = ReadFile(h, buf, size, (DWORD*)bytes_read, o);

	return (result == TRUE) ? 0 : GetLastError();
#else
    UNUSED(o);

    result = read(h, buf, size);

    if (result == -1)
        return errno;

    *bytes_read = result;

    return 0;
#endif
}

/******************************************************************************/
/*!

  \brief Closes the handle to an FSCC port.

  \param[in] h
    HANDLE to the port

  \return 0
    if closing the port completed successfully
  \return >= 1
    if the operation failed (see MSDN 'System Error Codes')

*/
/******************************************************************************/
int fscc_disconnect(fscc_handle h)
{
    int result;

#ifdef _WIN32
	result = CloseHandle(h);

	return (result == TRUE) ? 0 : GetLastError();
#else

    result = close(h);

    return (result != -1) ? 0 : errno;
#endif
}
