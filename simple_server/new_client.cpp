#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <string>
#include <iostream>
#include <unistd.h>

int	new_client(int listen_sd, int &max_sd, fd_set &master_set)
{
	int	new_sd;

	printf("  Listening socket is readable\n");
	do
	{
		new_sd = accept(listen_sd, NULL, NULL);
		if (new_sd < 0)
		{
			if (errno == EWOULDBLOCK)
				break;

			perror("  accept() failed");
			return 1;
		}

		printf("  New incoming connection - %d\n", new_sd);
		FD_SET(new_sd, &master_set);
		if (new_sd > max_sd)
			max_sd = new_sd;

	} while (new_sd != -1);
	return 0;
}
