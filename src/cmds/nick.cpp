#include "../../inc/Msg.hpp"
#include <iostream>

Client	clients[5];

#define INVALID_CHARS "*$%" //Need to check this list
bool	isNickValid(const std::string &nick)
{
	if (nick.find_first_of(INVALID_CHARS) == std::string::npos)
		return 0;
	return 1;
}

bool	isNickInUse(const std::string &nick)
{
	for (size_t	i = 0; i < 5; i++)
		if (clients[i].nickname == nick)
			return 1;
	return 0;
}

/*
 * for testing
void	send(std::string msg)
{
	std::cout << msg << std::endl;
}
*/

//Command: NICK
//Parameters: <nickname>
#define ERR_ERRONEUSNICKNAME(NICK) "NICK :Erroneus nickname"
#define ERR_NONICKNAMEGIVEN " :No nickname given"
#define ERR_NICKNAMEINUSE(NICK) "NICK :Nickname is already in use"
#define ERR_NICKCOLLISION(NICK) "NICK :Nickname collision KILL from <user>@<host>"
void	nick(Msg &msg)
{
	const std::string	&nick = msg.params.front();

	if (nick.empty())
		return send(ERR_NONICKNAMEGIVEN);
	if (isNickValid(nick))
		return send(ERR_ERRONEUSNICKNAME(nick));
	if (isNickInUse(nick))
		return send(ERR_NICKNAMEINUSE(nick));

	msg.client.nickname = nick;

	//send(msg.client.nickname); //for testing
}

/*
 * for testing
int	main(void)
{
	Msg	msg;

	msg.params.push_back("jleroux");
	nick(msg);
}
*/
