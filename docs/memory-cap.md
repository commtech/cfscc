Memory Cap
=============

If your system has limited memory available, there are safety checks in place to prevent spurious incoming data from overrunning your system. Each port has an option for setting it's input and output memory cap.

There are multiple methods of setting this value.

Get
---

```
#include <fscc.h>
...

struct fscc_memory_cap memcap;

fscc_get_memory_cap(h, &memcap);
```

At this point `memcap.input` and `memcap.output` would be set to their respective
values.

A complete example of how to do this can be found in the file
[`examples\memory-cap.c`](https://github.com/commtech/cfscc/blob/master/examples/memory-cap.c)


Set
------

```
#include <fscc.h>
...

struct fscc_memory_cap memcap;

memcap.input = 1000000; /* 1 MB */
memcap.output = 2000000; /* 2 MB */

fscc_set_memory_cap(h, &memcap);
```

A complete example of how to do this can be found in the file
[`examples\memory-cap.c`](https://github.com/commtech/cfscc/blob/master/examples/memory-cap.c)
