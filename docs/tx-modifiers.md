TX Modifiers
============

- XF - Normal transmit - disable modifiers
- XREP - Transmit repeat
- TXT - Transmit on timer
- TXEXT - Transmit on external signal

Get
---

```
#include <fscc.h>
...

unsigned modifiers;

fscc_get_tx_modifiers(h, &modifiers);
```

A complete example of how to do this can be found in the file
[`examples\tx-modifiers.c`](https://github.com/commtech/cfscc/blob/master/examples/tx-modifiers.c)


Set
---

```
#include <fscc.h>
...

fscc_set_tx_modifiers(h, XF | XREP);
```

A complete example of how to do this can be found in the file
[`examples\tx-modifiers.c`](https://github.com/commtech/cfscc/blob/master/examples/tx-modifiers.c)
