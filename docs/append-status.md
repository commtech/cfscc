Append Status
======

It is a good idea to pay attention to the status of each frame. For example, you
may want to see if the frame's CRC check succeeded or failed.

The FSCC reports this data to you by appending two additional bytes
to each frame you read from the card, if you opt-in to see this data. There are
a few methods of enabling this additional data.

Get
---

```c
#include <fscc.h>
...

unsigned status;

fscc_get_append_status(h, &status);
```

A complete example of how to do this can be found in the file
[`examples\append-status.c`](https://github.com/commtech/cfscc/blob/master/examples/append-status/append-status.c)


Enable
------

```c
#include <fscc.h>
...

fscc_enable_append_status(h);
```

A complete example of how to do this can be found in the file
[`examples\append-status.c`](https://github.com/commtech/cfscc/blob/master/examples/append-status/append-status.c)


Disable
-------

```c
#include <fscc.h>
...

fscc_disable_append_status(h);
```

A complete example of how to do this can be found in the file
[`examples\append-status.c`](https://github.com/commtech/cfscc/blob/master/examples/append-status/append-status.c)
