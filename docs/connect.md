# Connect

Opening a handle using this API will only give you access to the
synchronous functionality of the card. You will need to use the COM ports
if you would like to use the asynchronous functionality.

###### Driver Support
| Code           | Version
| -------------- | --------
| `fscc-windows` | `v2.0.0` 
| `fscc-linux`   | `v2.0.0` 


## Connect
```c
int fscc_connect(unsigned port_num, unsigned overlapped, fscc_handle *h)
```

| Parameter     | Type           | Description
| ------------ | --------------- | -----------------------
| `port_num    | `unsigned`      | The port number you would like to connect to
| `overlapped` | `unsigned int`  | Whether to open port in overlapped IO mode
| `h`          | `fscc_handle *` | The handle to your port

| Return Value | Cause
| ------------ | ------------------------------------------------------------------
| 0            | Success

###### Examples
Connect to port 0.

```c
#include <fscc.h>
...

HANDLE h;

fscc_connect(0, 0, &h);
```

###### Support
| Code           | Version
| -------------- | --------
| `cfscc`        | `v1.0.0`


### Additional Resources
- Complete example: [`examples\tutorial.c`](https://github.com/commtech/cfscc/blob/master/examples/tutorial/tutorial.c)
- Implemenation details: [`src\fscc.c`](https://github.com/commtech/cfscc/blob/master/src/fscc.c)
