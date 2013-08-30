Registers
=========

The FSCC driver is a swiss army knife of sorts with communication. It can
handle many different situations, if configured correctly. Typically to
configure it to handle your specific situation you need to modify the card's
register values.

_For a complete listing of all of the configuration options please see the 
manual._

In HDLC mode some settings are fixed at certain values. If you are in
HDLC mode and after setting/getting your registers some bits don't look correct,
then they are likely fixed. A complete list of the fixed values can be found in 
the CCR0 section of the manual.

All of the registers, except FCR, are tied to a single port. FCR on the other hand 
is shared between two ports on a card. You can differentiate between which FCR 
settings affects what port by the A/B labels. A for port 0 and B for port 1.

You should purge the data stream after changing the registers.
Settings like CCR0 will require being purged for the changes to take 
effect.

Set
---

```
#include <fscc.h>
...

struct fscc_registers registers;

FSCC_REGISTERS_INIT(registers);

registers.CCR0 = 0x0011201c;
registers.BGR = 10;

fscc_set_registers(h, &registers);
```

A complete example of how to do this can be found in the file
[`examples\registers.c`](https://github.com/commtech/cfscc/blob/master/examples/registers/registers.c).


Get
------

```
#include <fscc.h>
...

struct fscc_registers registers;

FSCC_REGISTERS_INIT(registers);

registers.CCR0 = FSCC_UPDATE_VALUE;
registers.BGR = FSCC_UPDATE_VALUE;

fscc_get_registers(h, &registers);
```

At this point `regs.CCR0` and `regs.BGR` would be set to their respective
values.

A complete example of how to do this can be found in the file
[`examples\registers.c`](https://github.com/commtech/cfscc/blob/master/examples/registers/registers.c).
