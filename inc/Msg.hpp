#ifndef MSG_HPP
# define MSG_HPP

# include "Client.hpp"
# include <deque>

struct	Msg
{
	public:
		Client					client;
		std::string				prefix;
		std::string				command;
		std::deque<std::string>	params;
};

#endif
