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

#include "../inc/Message.hpp"


void	handle_client(int sd, int &max_sd, fd_set &master_set)
{
	Message	msgP;
	char	buffer[80];
	int		close_conn;
	int		rc;

	printf("  Descriptor %d is readable\n", sd);
	close_conn = 0;
	while (1)
	{
		rc = recv(sd, buffer, sizeof(buffer), 0);
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("  recv() failed");
				close_conn = 1;
			}
			break;
		}

		if (rc == 0)
		{
			printf("  Connection closed\n");
			close_conn = 1;
			break;
		}

		msgP.msgParsing(buffer);

		printf("  %d bytes received\n", rc);
		printf("  %s\n", buffer);

		msgP.clearParam();
	}

	if (close_conn)
	{
		close(sd);
		FD_CLR(sd, &master_set);
		if (sd == max_sd)
		{
			while (FD_ISSET(max_sd, &master_set) == 0)
				max_sd -= 1;
		}
	}
}
