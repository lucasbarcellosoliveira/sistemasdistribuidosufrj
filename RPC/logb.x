struct arguments{
	float *a;
	float b;
	int size;
};

program LOGB_PROG{
	version LOGB_VERS{
		int logb(arguments)=1;
	}=1;
}=0x23451111;
