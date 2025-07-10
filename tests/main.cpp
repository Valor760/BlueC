#include <stdio.h>
#include <unistd.h>

#include <bluec/bluec.h>

int main()
{
	printf("Before init\n");
	if(bluec_Init(true) != BLUEC_ERROR_NONE)
	{
		printf("Failed to init\n");
		return -1;
	}
	printf("init done\n");
	sleep(2);

	while(true) { sleep(60); }

	printf("Before deinit\n");
	bluec_DeInit();
	printf("deinit done\n");

	return 0;
}