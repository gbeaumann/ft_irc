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

#define SERVER_PORT 6667

void	handle_client(int i, int &max_sd, fd_set &master_set);
int		new_client(int listen_sd, int &max_sd, fd_set &master_set);

int	close_fd_exit(int fd, std::string msg, int ret)
{
	perror(msg.c_str());
	if (fd > 0)
		close(fd);
	return ret;
}

int	init(void)
{
	struct sockaddr_in6	addr;
	int					on = 1;
	int					listen_sd = socket(AF_INET6, SOCK_STREAM, 0);

	if (listen_sd < 0)
		close_fd_exit(-1, "socket() failed", -1);

	if (setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) < 0)
		close_fd_exit(listen_sd, "setsockopt() failed", -1);

	if (ioctl(listen_sd, FIONBIO, (char *)&on) < 0)
		close_fd_exit(listen_sd, "ioctl() failed", -1);

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	addr.sin6_port = htons(SERVER_PORT);

	if (bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		close_fd_exit(listen_sd, "bind() failed", -1);

	if (listen(listen_sd, 32) < 0)
		close_fd_exit(listen_sd, "listen() failed", -1);

	return listen_sd;
}

int	handle_select_error(int fd_ready)
{
	if (fd_ready > 0)
		return 0;
	else if (fd_ready == 0)
		fprintf(stderr, "  select() timed out.  End program.\n");
	else
		perror("  select() failed");
	return 1;
}

int	main(int argc, char *argv[])
{
	int			fd_ready;
	int			listen_sd, max_sd;
	int			end_server = 0;
	fd_set		master_set, working_set;

	listen_sd = init();

	FD_ZERO(&master_set);
	max_sd = listen_sd;
	FD_SET(listen_sd, &master_set);

	while (end_server == 0)
	{
		memcpy(&working_set, &master_set, sizeof(master_set));

		printf("Waiting on select()...\n");
		fd_ready = select(max_sd + 1, &working_set, NULL, NULL, NULL);
		if (handle_select_error(fd_ready))
			break;

		for (int i = 0; i <= max_sd && fd_ready > 0; ++i)
		{
			if (FD_ISSET(i, &working_set))
			{
				fd_ready--;

				if (i == listen_sd)
					end_server = new_client(listen_sd, max_sd, master_set);
				else
					handle_client(i, max_sd, master_set);
			}
		}
	}

	for (int i = 0; i <= max_sd; ++i)
	{
		if (FD_ISSET(i, &master_set))
			close(i);
	}
}
