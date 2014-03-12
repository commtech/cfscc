# Disconnect

###### Support
| Code | Version |
| ---- | ------- |
| fscc-windows | 2.0.0 |
| fscc-linux | 2.0.0 |
| cfscc | 1.0.0 |


## Disconnect
```c
int fscc_disconnect(fscc_handle h)
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

fscc_disconnect(h);
```


### Additional Resources
- Complete example: [`examples/tutorial.c`](../examples/tutorial.c)
- Implementation details: [`src/fscc.c`](../src/fscc.c)
