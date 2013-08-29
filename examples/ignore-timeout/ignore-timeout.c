#include <fscc.h>

int main(void)
{
	HANDLE h;
	/*! [Setup variables] */
	/* Declare our ignore timeout variable */
	unsigned ignore_timeout;
	/*! [Setup variables] */
	
	fscc_connect(0, FALSE, &h);

	/*! [Get ignore timeout] */
    /* Get ignore timeout value */
	fscc_get_ignore_timeout(h, &ignore_timeout);
	/*! [Get ignore timeout] */

	/*! [Enable ignore timeout] */
	fscc_enable_ignore_timeout(h);
	/*! [Enable ignore timeout] */

	/*! [Disable ignore timeout] */
	fscc_disable_ignore_timeout(h);
	/*! [Disable ignore timeout] */
	
	fscc_disconnect(h);
	
	return EXIT_SUCCESS;
}