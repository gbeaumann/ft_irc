#include "Msg.hpp"
#include "Client.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <sys/select.h>
#include <sys/socket.h>

int	error(std::string msg, int ret)
{
	std::cerr << msg << std::endl;
	return (ret);
}

//Init socket and bind it properly
int	init_connection(void)
{
	int socket = socket(AF_INET, SOCK_STREAM, 0);
	bind(socket, (const struct sockaddr *)&addr, sizeof(addr));
	listen(socket, 3);
	return socket;
}

void	reset_fds(fd_set &readfds, std::vector<int> sockets)
{
	FD_ZERO(&readfds);
	for (int socket : sockets)
		FD_SET(socket, &readfds);
}

int	main(void)
{
	int								listener;
	fd_set							readfds;
	std::vector<int>				sockets;
	struct timeval					timeout;
	//std::map<std::string, Channel>	channels;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	listener = init_connection();
	while (1)
	{
		reset_fds(readfds, sockets);

		if (select((sockets.size() + 1), &readfds, NULL, NULL, &timeout) < 0)
			return error("Error: select", -1);

		for (int socket : sockets)
		{
			if (FD_ISSET(socket, &readfds))
			{
				if (socket == listener)
					sockets.push_back(init_connection());
				else
					process(socket, getMsg());
			}
		}
	}
	return (0);
}

do
{
	new_sd = accept(listen_sd, NULL, NULL);
	printf("  New incoming connection - %d\n", new_sd);
	FD_SET(new_sd, &master_set);
	if (new_sd > max_sd)
		max_sd = new_sd;

} while (new_sd != -1);