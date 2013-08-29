This README file is best viewed on the [GitHub page](http://github.com/commtech/cfscc/).

### Installing Library

##### Downloading Library
You can download a pre-built driver package that includes the C library directly from our
[website](http://www.commtech-fastcom.com/CommtechSoftware.html).

Or, you can download the latest library from 
[Github](https://github.com/commtech/cfscc/releases).


### Using the API

##### Quick Start Guide
There is documentation for each specific function listed below, but lets get started
with a quick programming example for fun.

_This tutorial has already been set up for you at_ 
[`examples/tutorial/`](https://github.com/commtech/cfscc/tree/master/examples/tutorial).

First, drop `cfscc.dll` and `cfscc.lib` into a test directory. Now that those files are 
copied over, create a new C file (named tutorial.c) with the following code.

```
#include <stdio.h>
#include <stdlib.h>
#include <fscc.h>

int main(void)
{
	fscc_handle h;
	int e = 0;
	char odata[] = "Hello world!";
	char idata[20] = {0};
	unsigned tmp;

	/* Open port 0 in a blocking IO mode */
	e = fscc_connect(0, 0, &h);
	if (e != 0) {
		fprintf(stderr, "fscc_connect failed with %d\n", e);
		return EXIT_FAILURE;
	}

	/* Send our "Hello world!" text */
	fscc_write(h, odata, sizeof(odata), &tmp, NULL);

	/* Read the data back in (with our loopback connector) */
	fscc_read(h, idata, sizeof(idata), &tmp, NULL);

	fprintf(stdout, "%s\n", idata);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
```

For this example I will use the Visual Studio command line compiler, but
you can use your compiler of choice.

```
# cl /W4 /MT tutorial.c cfscc.lib /I ../../src/
```

Now attach the included loopback connector.

```
# tutorial.exe
Hello world!
```

You have now transmitted and received an HDLC frame! 

There are likely other configuration options you will need to set up for your 
own program. All of these options are described below.


##### fscc_set_registers
```
#include <fscc.h>
...

struct fscc_registers registers;

FSCC_REGISTERS_INIT(registers);

registers.CCR0 = 0x0011201c;
registers.BGR = 10;

fscc_set_registers(h, &registers);
```

A complete example of how to do this can be found in the file
[`examples\registers.c`](https://github.com/commtech/cfscc/blob/master/examples/registers/registers.c).


##### fscc_get_registers
```
#include <fscc.h>
...

struct fscc_registers registers;

FSCC_REGISTERS_INIT(registers);

registers.CCR0 = FSCC_UPDATE_VALUE;
registers.BGR = FSCC_UPDATE_VALUE;

fscc_get_registers(h, &registers);
```

A complete example of how to do this can be found in the file
[`examples\registers.c`](https://github.com/commtech/cfscc/blob/master/examples/registers/registers.c).


##### fscc_set_clock_frequency
_PPM (Parts Per Million) has been deprecated and will be removed in 
a future release. This value will be ignored in the mean time._

```c
#include <fscc.h>
...

fscc_set_clock_frequency(h, 18432000, 2);
```

A complete example of how to do this can be found in the file
[`examples\clock-frequency.c`](https://github.com/commtech/cfscc/blob/master/examples/clock-frequency/clock-frequency.c).


##### fscc_get_append_status
```c
#include <fscc.h>
...

BOOL status;

fscc_enable_append_status(h);
fscc_disable_append_status(h);

fscc_get_append_status(h, &status);
```

A complete example of how to do this can be found in the file
[`examples\append-status.c`](https://github.com/commtech/cfscc/blob/master/examples/append-status.c)


##### fscc_set_memory_cap
##### fscc_get_memory_cap
```
#include <fscc.h>
...

struct fscc_memory_cap memcap;

memcap.input = 1000000; /* 1 MB */
memcap.output = 2000000; /* 2 MB */

fscc_set_memory_cap(h, &memcap);
fscc_get_memory_cap(h, &memcap);
```

A complete example of how to do this can be found in the file
[`examples\memory-cap.c`](https://github.com/commtech/cfscc/blob/master/examples/memory-cap.c)


##### fscc_set_tx_modifiers
```
#include <fscc.h>
...

unsigned modifiers;

fscc_set_tx_modifiers(h, XF | XREP);
fscc_get_tx_modifiers(h, &modifiers);
```

A complete example of how to do this can be found in the file
[`examples\tx-modifiers.c`](https://github.com/commtech/cfscc/blob/master/examples/tx-modifiers.c)


##### Ignore Timeout
```c
#include <fscc.h>
...

BOOL status;

fscc_enable_ignore_timeout(h);
fscc_disable_ignore_timeout(h);

fscc_get_ignore_timeout(h, &status);
```

A complete example of how to do this can be found in the file
[`examples\ignore-timeout.c`](https://github.com/commtech/cfscc/blob/master/examples/ignore-timeout.c)


##### Retrieving Multiple Frames At Once
```c
#include <fscc.h>
...

BOOL status;

fscc_enable_rx_multiple(h);
fscc_disable_rx_multiple(h);

fscc_get_rx_multiple(h, &status);
```

A complete example of how to do this can be found in the file
[`examples\rx-multiple.c`](https://github.com/commtech/cfscc/blob/master/examples/rx-multiple.c)


##### Purging Data
```c
#include <fscc.h>
...

fscc_purge(h, TRUE, TRUE);
```

A complete example of how to do this can be found in the file
[`examples\purge.c`](https://github.com/commtech/cfscc/blob/master/examples/purge.c)


##### Sending/Receiving Data
The FSCC driver typically (but not always) works in "frames". This means
data is typically packaged together in permanent chunks. If the card received
two frames of data prior to you retrieving the data, you will only get one chunk
of data back at a time when you interface with the driver to get the data.

There are multiple methods of reading/writing data to/from the card. Following
are the most common methods.

Writing data will typically be done within C code using the 
[`WriteFile()`](http://msdn.microsoft.com/en-us/library/windows/desktop/aa365747.aspx)
function found in 
[`<windows.h>`](http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745.aspx). 

```
result = WriteFile(handle, buf, count, (DWORD*)bytes_written, NULL);
```

In in addition to the standard errors that the `WriteFile()` function returns, there are 
a couple of errors specific to the FSCC you might encounter.

| Error                     | Cause
| ------------------------- | ----------------------------
| `STATUS_IO_TIMEOUT`       | You are executing a command that requires a transmit clock present
| `STATUS_BUFFER_TOO_SMALL` | The write size exceeds the output memory usage cap


Reading data will typically be done within C code using the 
[`ReadFile()`](http://msdn.microsoft.com/en-us/library/windows/desktop/aa365467.aspx)
function found in
[`<windows.h>`](http://msdn.microsoft.com/en-us/library/windows/desktop/aa383745.aspx). 

```c
result = ReadFile(handle, buf, length, (DWORD*)bytes_read, NULL);
```

The length argument of the `ReadFile()` function means different things depending
on the mode you are using.

In a frame based mode the length argument specifies the maximum frame size
to return. If the next queued frame is larger than the size you specified
the error `STATUS_BUFFER_TOO_SMALL` is returned and the data will remain 
waiting for a `ReadFile()` of a larger value. If a `ReadFile()` length is specified 
that is larger than the length of multiple frames in queue, you will still only receive 
one frame per `ReadFile()` call.

In streaming mode (no frame termination) the length argument specifies the
maximum amount of data to return. If there are 100 bytes of streaming data
in the card and you `ReadFile()` with a length of 50, you will receive 50 bytes.
If you do a `ReadFile()` of 200 bytes, you will receive the 100 bytes available.

Frame based data and streaming data are kept separate within the driver.
To understand what this means, first imagine the following scenario. You are in a
frame based mode and receive a couple of frames. You then switch to
streaming mode and receive a stream of data. When calling `ReadFile()`
you will receive the the streaming data until you switch back into a frame based
mode and do a `ReadFile()`.

In in addition to the standard errors that the `ReadFile()`function returns, there 
are a couple of errors specific to the FSCC you might encounter.

| Error                     | Cause
| ------------------------- | ----------------------------
| `STATUS_BUFFER_TOO_SMALL` | The read size is smaller than the next frame (in a frame based mode)

Most users will want the advanced I/O capabilities included by using the Windows
[OVERLAPPED I/O API](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx). 
We won't duplicate the documentation here, but for your reference, here is an [article]
(http://blogs.msdn.com/b/oldnewthing/archive/2011/02/02/10123392.aspx) on a common
bug developers introduce while trying to cancel I/O operations when using OVERLAPPED I/O.


##### Asynchronous Communication
The FSCC driver includes a slightly modified version of the Windows serial 
driver for handling the asynchronous communication for our UARTs. The Windows
serial driver is highly tested and likely more stable than anything we could 
produce in any reasonable amount of time.

The FSCC and SerialFC drivers work together to automatically switch between 
synchronous and asynchronous modes by modifying the FCR register for you. 
All you need to do is open the FSCC handle to be in synchronous mode and the 
COM handle to be in asychronous mode.

More information about using the UART's is available in the 
[SerialFC driver README](https://github.com/commtech/serialfc-windows/blob/master/README.md) file.


### FAQ

##### Why does executing a purge without a clock put the card in a broken state?
When executing a purge on either the transmitter or receiver there is
a TRES or RRES (command from the CMDR register) happening behind the
scenes. If there isn't a clock available, the command will stall until
a clock is available. This should work in theory but doesn't in
practice. So whenever you need to execute a purge without a clock: first
put it into clock mode 7, execute your purge, and then return to your other
clock mode.

   
##### How long after CTS until the data is transmitted?
Transmission happens within a fixed time frame after CTS of around 1 - 1.5 clock cycles.


##### What are the project's dependencies?
For 99% of our customers you will be able to install the driver without any additional
dependencies. The full dependency list is below.

- Driver Package: Windows (32 and 64) staring with XP
- Driver Source Code: Windows Driver Kit 7.1.0 (Only required when building from source)
- Python Library: Python, pySerial


##### What was changed in 2.X?
You can view an up-to-date list of driver changes in our 
[ChangeLog](https://github.com/commtech/fscc-windows/blob/master/ChangeLog.txt).


##### How do I build a custom version of the driver source code?
The source code for the Fastcom FSCC driver is hosted on Github code hosting.
To check out the latest code you will need Git and to run the following command in a
terminal:

```
git clone git://github.com/commtech/fscc-windows.git fscc
```

We prefer you use the above method for downloading the driver source code
(because it is the easiest way to stay up to date), but you can also get 
the driver source code from the
[download page](https://github.com/commtech/fscc-windows/tags/).

Now that you have the latest code checked out, you will probably want
to switch to a stable version within the code directory. You can do this by browsing
the various tags for one you would like to switch to. Version v2.2.8 is only
listed here as an example.

```
git tag
git checkout v2.2.8
```

Provided you have Windows Driver Kit 7.1.0 installed you can build the driver by
running the BLD command from within the source code directory.

```
cd fscc/src/
BLD
```

### License

Copyright (C) 2013 [Commtech, Inc.](http://commtech-fastcom.com)

Licensed under the [GNU General Public License v3](http://www.gnu.org/licenses/gpl.txt).
