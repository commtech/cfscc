# TX Modifiers

- XF - Normal transmit - disable modifiers
- XREP - Transmit repeat
- TXT - Transmit on timer
- TXEXT - Transmit on external signal

## Get
```c
int fscc_get_tx_modifiers(fscc_handle h, unsigned *modifiers)
```

| Parameter   | Type             | Description
| ----------- | ---------------- | -----------------------
| `h`         | `fscc_handle`    | The handle to your port
| `modifiers` | `unsigned int *` | The current `tx modifiers` value


###### Examples
```
#include <fscc.h>
...

unsigned modifiers;

fscc_get_tx_modifiers(h, &modifiers);
```


## Set
```c
int fscc_set_tx_modifiers(fscc_handle h, unsigned modifiers)
```

| Parameter   | Type           | Description
| ----------- | -------------- | -----------------------
| `h`         | `fscc_handle`  | The handle to your port
| `modifiers` | `unsigned int` | What `tx modifiers` you would like to set


###### Examples
```
#include <fscc.h>
...

fscc_set_tx_modifiers(h, XF | XREP);
```


### Additional Resources
- Complete example: [`examples\tx-modifiers.c`](https://github.com/commtech/cfscc/blob/master/examples/tx-modifiers/tx-modifiers.c)
- Implemenation details: [`src\fscc.c`](https://github.com/commtech/cfscc/blob/master/src/fscc.c)
