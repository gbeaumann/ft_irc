//Full IrcMsg structure
//:nick!username@host CMD param1 param2
//CMD param1 param2

#include "parser.hpp"
#include <iostream>

//Need to verify signature, could get c-string
Msg	parse(const std::string	&raw)
{
	Msg	msg;
    size_t	start = 0;
    size_t	end = 0;

	//This while loop doesn't work for 'trailing' param!!!!!!
    while ((end = raw.find(' ', start)) != std::string::npos)
	{
        msg.params.push_back(raw.substr(start, end - start));
        start = end + 1;
    }
	msg.params.push_back(raw.substr(start));

	if (msg.params.begin()->at(0) == ':')
	{
		msg.prefix = *msg.params.begin();
		msg.params.pop_front();
	}

	msg.command = *msg.params.begin();
	if (msg.params.size())
		msg.params.pop_front();

	return msg;
}
