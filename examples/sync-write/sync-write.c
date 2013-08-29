#include <fscc.h>

int main(void)
{
	HANDLE h;
    char data[] = "Hello world!";
    unsigned bytes_written = 0;
	
	fscc_connect(0, FALSE, &h);

	fscc_write(h, data, sizeof(data), &bytes_written, 0);
	
	fscc_disconnect(h);
	
	return EXIT_SUCCESS;
}