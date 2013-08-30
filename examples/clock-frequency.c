#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_set_clock_frequency */

int main(void)
{
	fscc_handle h;

	fscc_connect(0, 0, &h);

	/* Set the clock frequency to 1 Mhz */
	fscc_set_clock_frequency(h, 1000000, 2);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
