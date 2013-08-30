#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_{get, enable, disable}_ignore_timeout */

int main(void)
{
	fscc_handle h;
	unsigned ignore_timeout;

	fscc_connect(0, 0, &h);

	fscc_get_ignore_timeout(h, &ignore_timeout);

	fscc_enable_ignore_timeout(h);
	fscc_disable_ignore_timeout(h);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
