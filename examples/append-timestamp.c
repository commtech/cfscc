#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_{get, enable, disable}_append_timestamp */

int main(void)
{
	fscc_handle h;
	unsigned status;

	fscc_connect(0, 0, &h);

	fscc_get_append_timestamp(h, &status);

	fscc_enable_append_timestamp(h);
	fscc_disable_append_timestamp(h);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
