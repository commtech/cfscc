#include <fscc.h>

int main(void)
{
	HANDLE h;
	/*! [Setup variables] */
	/* Declare our modifiers variable */
	unsigned modifiers;
	/*! [Setup variables] */
	
	fscc_connect(0, FALSE, &h);

	/*! [Set TXT | XREP] */
    /* Transmit repeat & transmit on timer */
	fscc_set_tx_modifiers(h, TXT | XREP);
	/*! [Set TXT | XREP] */
	
	/*! [Set XF] */
	/* Disable modifiers */
	fscc_set_tx_modifiers(h, XF);
	/*! [Set XF] */

	/*! [Get modifiers] */
    /* Get modifiers */
	fscc_get_tx_modifiers(h, &modifiers);
	/*! [Get modifiers] */
	
	fscc_disconnect(h);
	
	return EXIT_SUCCESS;
}