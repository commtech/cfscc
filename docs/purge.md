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

/* Purge both TX and RX data */
fscc_purge(h, TRUE, TRUE);
```

A complete example of how to do this can be found in the file
[`examples\purge.c`](https://github.com/commtech/cfscc/blob/master/examples/purge.c)
