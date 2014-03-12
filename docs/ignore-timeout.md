# Ignore Timeout

###### Support
| Code | Version |
| ---- | ------- |
| fscc-windows | 2.0.0 |
| fscc-linux | 2.0.0 |
| cfscc | 1.0.0 |


## Get
```c
int fscc_get_ignore_timeout(fscc_handle h, unsigned *status)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `fscc_handle` | The handle to your port |
| `status` | `unsigned int *` | The current ignore timeout value |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |


###### Examples
```c
#include <fscc.h>
...

unsigned status;

fscc_get_ignore_timeout(h, &status);
```


## Enable
```c
int fscc_enable_ignore_timeout(fscc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `fscc_handle` | The handle to your port |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <fscc.h>
...

fscc_enable_ignore_timeout(h);
```


## Disable
```c
int fscc_disable_ignore_timeout(fscc_handle h)
```

| Parameter | Type | Description |
| --------- | ---- | ----------- |
| `h` | `fscc_handle` | The handle to your port |

| Return Value | Cause |
| ------------:| ----- |
| 0 | Success |

###### Examples
```c
#include <fscc.h>
...

fscc_disable_ignore_timeout(h);
```


### Additional Resources
- Complete example: [`examples/ignore-timeout.c`](../examples/ignore-timeout.c)
- Implementation details: [`src/fscc.c`](../src/fscc.c)
