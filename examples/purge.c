#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_purge */

int main(void)
{
	fscc_handle h;

	fscc_connect(0, 0, &h);

	/* Purge TX */
	fscc_purge(h, 1, 0);

	/* Purge RX */
	fscc_purge(h, 0, 1);

	/* Purge both TX & RX */
	fscc_purge(h, 1, 1);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
