# Disconnect


###### Driver Support
| Code           | Version
| -------------- | --------
| `fscc-windows` | `v2.0.0` 
| `fscc-linux`   | `v2.0.0` 


## Disconnect
```c
int fscc_disconnect(fscc_handle h)
```

| Parameter     | Type         | Description
| ------------ | ------------- | -----------------------
| `h`          | `fscc_handle` | The handle to your port

| Return Value | Cause
| ------------ | ------------------------------------------------------------------
| 0            | Success

###### Examples
```c
#include <fscc.h>
...

fscc_disconnect(h);
```

###### Support
| Code           | Version
| -------------- | --------
| `cfscc`        | `v1.0.0`


### Additional Resources
- Complete example: [`examples\tutorial.c`](https://github.com/commtech/cfscc/blob/master/examples/tutorial/tutorial.c)
- Implemenation details: [`src\fscc.c`](https://github.com/commtech/cfscc/blob/master/src/fscc.c)
