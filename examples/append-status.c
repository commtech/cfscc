#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_{get, enable, disable}_append_status */

int main(void)
{
	fscc_handle h;
	unsigned status;

	fscc_connect(0, 0, &h);

	fscc_get_append_status(h, &status);

	fscc_enable_append_status(h);
	fscc_disable_append_status(h);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
