Purge
=====

Between the hardware FIFO and the driver's software buffers there are multiple places data could 
be stored, excluding your application code. If you ever need to clear this data and start fresh, 
there are a couple of methods you can use.

Execute
-------

```c
#include <fscc.h>
...

fscc_purge(h, TRUE, TRUE);
```

At this point both the transmit and receive data would be purged.

A complete example of how to do this can be found in the file
[`examples\purge.c`](https://github.com/commtech/cfscc/blob/master/examples/purge/purge.c)