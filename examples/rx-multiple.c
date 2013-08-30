#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_{get, enable, disable}_rx_multiple */

int main(void)
{
	fscc_handle h;
	unsigned status;

	fscc_connect(0, 0, &h);

	fscc_get_rx_multiple(h, &status);

	fscc_enable_rx_multiple(h);
	fscc_disable_rx_multiple(h);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
