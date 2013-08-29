#include <fscc.h>

int main(void)
{
	HANDLE h;
	/*! [Setup variables] */
	/* Declare our append status variable */
	unsigned append_status;
	/*! [Setup variables] */
	
	fscc_connect(0, FALSE, &h);

	/*! [Get append status] */
    /* Get append status value */
	fscc_get_append_status(h, &append_status);
	/*! [Get append status] */

	/*! [Enable append status] */
	fscc_enable_append_status(h);
	/*! [Enable append status] */

	/*! [Disable append status] */
	fscc_disable_append_status(h);
	/*! [Disable append status] */
	
	fscc_disconnect(h);
	
	return EXIT_SUCCESS;
}