#include <fscc.h>

int main(void)
{
	HANDLE h;
	/*! [Setup variables] */
	/* Declare our registers variable */
	struct fscc_registers r;
	/*! [Setup variables] */
	
	fscc_connect(0, FALSE, &h);
	
	/*! [Set registers] */
	/* Initialize our registers structure */
	FSCC_REGISTERS_INIT(r);
	
	/* Change the CCR0 and BGR elements to our desired values */
	r.CCR0 = 0x0011201c;
	r.BGR = 10;
	
	/* Set the CCR0 and BGR register values */
	fscc_set_registers(h, &r);
	/*! [Set registers] */
	
	/*! [Get registers] */
	/* Initialize our registers structure */
	FSCC_REGISTERS_INIT(r);
	
	/* Mark the CCR0 and CCR1 elements to retrieve values */
	r.CCR1 = FSCC_UPDATE_VALUE;
	r.CCR2 = FSCC_UPDATE_VALUE;
	
	/* Get the CCR1 and CCR2 register values */
	fscc_get_registers(h, &r);
	
	fscc_disconnect(h);
	
	return EXIT_SUCCESS;
}