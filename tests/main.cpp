#include <stdio.h>
#include <unistd.h>

#include <bluec/bluec.h>

int main()
{
	printf("Before init\n");
	if(bluez_Init())
	{
		printf("Failed to init\n");
		return -1;
	}
	printf("init done\n");
	sleep(2);

	printf("Before deinit\n");
	bluez_DeInit();
	printf("deinit done\n");

	return 0;
}