# Write

###### Support
| Code | Version |
| ---  | ------- |
| fscc-windows | 2.0.0 |
| fscc-linux | 2.0.0 |
| cfscc | 1.0.0 |


## Write (Overlapped)
```c
int fscc_write(fscc_handle h, char *buf, unsigned size, unsigned *bytes_written, OVERLAPPED *o)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `fscc_handle` | The handle to your port |
| `buf` | `char *` | The data buffer to transmit |
| `size` | `unsigned` | The number of bytes to transmit |
| `bytes_written` | `unsigned *` | How many bytes were written to the FIFO |
| `o` | `OVERLAPPED *` | [Overlapped IO structure](http://msdn.microsoft.com/en-us/library/windows/desktop/ms686358.aspx) |

| Return Code | Value | Cause |
| ------------ | -----:| ----- |
| | 0 | Success |
| `FSCC_TIMEOUT` | 16000 | Command timed out (missing clock) |
| `FSCC_INCORRECT_MODE` | 16001 | Using the synchronous port while in asynchronous mode |
| `FSCC_BUFFER_TOO_SMALL` | 16002 | The write size exceeds the output memory usage cap |
| `Other` | `Other` | [`See Windows System standard error codes`](http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx) |

###### Examples
```c
#include <fscc.h>
...

char odata[] = "Hello world!";
unsigned bytes_written;

fscc_write(h, odata, sizeof(odata), &bytes_written, NULL);
```


## Write (Blocking)
```c
int fscc_write_with_blocking(fscc_handle h, char *buf, unsigned size, unsigned *bytes_written)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `fscc_handle`    | The handle to your port |
| `buf` | `char *` | The data buffer to transmit |
| `size` | `unsigned` | The number of bytes to transmit |
| `bytes_written` | `unsigned *` | How many bytes were written to the FIFO |

| Return Code | Value | Cause |
| ----------- | -----:| ----- |
| | 0 | Success |
| `FSCC_TIMEOUT` | 16000 | Command timed out (missing clock) |
| `FSCC_INCORRECT_MODE` | 16001 | Using the synchronous port while in asynchronous mode |
| `FSCC_BUFFER_TOO_SMALL` | 16002 | The write size exceeds the output memory usage cap |
| `Other` | `Other` | [`See Windows System standard error codes`](http://msdn.microsoft.com/en-us/library/windows/desktop/ms681381%28v=vs.85%29.aspx) |

###### Examples
```c
#include <fscc.h>
...

char odata[] = "Hello world!";
unsigned bytes_written;

fscc_write_with_blocking(h, odata, sizeof(odata), &bytes_written);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/fscc.c`](../src/fscc.c)
