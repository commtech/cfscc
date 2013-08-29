#include <fscc.h>

int main(void)
{
	HANDLE h;
	
	fscc_connect(0, FALSE, &h);

	/*! [Purge TX] */
	/* Purge TX */
	fscc_purge(h, 1, 0);
	/*! [Purge TX] */

	/*! [Purge RX] */
	/* Purge RX */
	fscc_purge(h, 0, 1);
	/*! [Purge RX] */

	/*! [Purge both TX & RX] */
	/* Purge both TX & RX */
	fscc_purge(h, 1, 1);
	/*! [Purge both TX & RX] */
	
	fscc_disconnect(h);
	
	return EXIT_SUCCESS;
}