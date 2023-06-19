#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

struct	Client
{
	std::string	nickname;
	std::string	username;
	std::string	realname;
	int			socket;
};

#endif
