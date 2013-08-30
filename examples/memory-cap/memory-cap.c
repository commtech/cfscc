#include <stdlib.h> /* EXIT_SUCCESS */
#include <fscc.h> /* fscc_connect, fscc_disconnect, fscc_handle
                     fscc_{get, set}_memory_cap, struct fscc_memory_cap */

int main(void)
{
	fscc_handle h;
	struct fscc_memory_cap m;

	fscc_connect(0, 0, &h);

	m.input = 1000000; /* 1 MB */
	m.output = 2000000; /* 2 MB */

	fscc_set_memory_cap(h, &m);

	fscc_get_memory_cap(h, &m);

	fscc_disconnect(h);

	return EXIT_SUCCESS;
}
