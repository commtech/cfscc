Ignore Timeout
=============

Get
---

```c
#include <fscc.h>
...

unsigned status;

fscc_get_ignore_timeout(h, &status);
```

A complete example of how to do this can be found in the file
[`examples\ignore-timeout.c`](https://github.com/commtech/cfscc/blob/master/examples/ignore-timeout/ignore-timeout.c)


Enable
------

```c
#include <fscc.h>
...

fscc_enable_ignore_timeout(h);
```

A complete example of how to do this can be found in the file
[`examples\ignore-timeout.c`](https://github.com/commtech/cfscc/blob/master/examples/ignore-timeout/ignore-timeout.c)


Disable
-------

```c
#include <fscc.h>
...

fscc_disable_ignore_timeout(h);
```

A complete example of how to do this can be found in the file
[`examples\ignore-timeout.c`](https://github.com/commtech/cfscc/blob/master/examples/ignore-timeout/ignore-timeout.c)
