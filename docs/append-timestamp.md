# Append Timestamp

###### Driver Support
| Code           | Version
| -------------- | --------
| `fscc-windows` | `v2.4.0` 
| `fscc-linux`   | `v2.4.0` 


## Get
```c
int fscc_get_append_timestamp(fscc_handle h, unsigned *status)
```

| Parameter | Type             | Description
| --------- | ---------------- | -----------------------
| `h`       | `fscc_handle`    | The handle to your port
| `status`  | `unsigned int *` | The current `append timestamp` value

| Return Value | Cause
| ------------ | ------------------------------------------------------------------
| 0            | Success

###### Examples
```c
#include <fscc.h>
...

unsigned status;

fscc_get_append_timestamp(h, &status);
```

###### Support
| Code           | Version
| -------------- | --------
| `cfscc`        | `v1.0.0`


## Enable
```c
int fscc_enable_append_timestamp(fscc_handle h)
```

| Parameter | Type             | Description
| --------- | ---------------- | -----------------------
| `h`       | `fscc_handle`    | The handle to your port

| Return Value | Cause
| ------------ | ------------------------------------------------------------------
| 0            | Success

###### Examples
```c
#include <fscc.h>
...

fscc_enable_append_timestamp(h);
```

###### Support
| Code           | Version
| -------------- | --------
| `cfscc`        | `v1.0.0`


## Disable
```c
int fscc_disable_append_timestamp(fscc_handle h)
```

| Parameter | Type             | Description
| --------- | ---------------- | -----------------------
| `h`       | `fscc_handle`    | The handle to your port

| Return Value | Cause
| ------------ | ------------------------------------------------------------------
| 0            | Success

###### Examples
```c
#include <fscc.h>
...

fscc_disable_append_timestamp(h);
```

###### Support
| Code           | Version
| -------------- | --------
| `cfscc`        | `v1.0.0`


### Additional Resources
- Complete example: [`examples\append-timestamp.c`](https://github.com/commtech/cfscc/blob/master/examples/append-timestamp/append-timestamp.c)
- Implemenation details: [`src\fscc.c`](https://github.com/commtech/cfscc/blob/master/src/fscc.c)
