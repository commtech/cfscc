#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     TXT, XREP, XF, fscc_{get, set}_tx_modifiers */

int main(void)
{
	fscc_handle h;
	unsigned modifiers;

	fscc_connect(0, 0, &h);

	/* Enable transmit repeat & transmit on timer */
	fscc_set_tx_modifiers(h, TXT | XREP);

	/* Revert to normal transmission */
	fscc_set_tx_modifiers(h, XF);

	/* Get current modifiers */
	fscc_get_tx_modifiers(h, &modifiers);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
