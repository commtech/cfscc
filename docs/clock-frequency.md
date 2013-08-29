Clock Frequency
==============

The FSCC device has a programmable clock that can be set anywhere from
20 KHz to 200 MHz. However, this is not the full operational range of an
FSCC port, only the range that the onboard clock can be set to.

Using one of the synchronous modes you can only receive data consistently
up to 30 MHz (when you are using an external clock). If you are transmitting
data using an internal clock, you can safely receive data consistently up to 50 MHz.

Lower clock rates (less than 1 MHz for example) can take a long time for 
the frequency generator to finish. If you run into this situation we 
recommend using a larger frequency and then dividing it down to your 
desired baud rate using the BGR register.

_PPM (Parts Per Million) has been deprecated and will be removed in 
a future release. This value will be ignored in the mean time._

Set
---

```c
#include <fscc.h>
...

fscc_set_clock_frequency(h, 18432000, 2);
```

A complete example of how to do this can be found in the file
[`examples\clock-frequency.c`](https://github.com/commtech/cfscc/blob/master/examples/clock-frequency/clock-frequency.c).
