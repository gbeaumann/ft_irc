#ifndef	MESSAGE_HPP
# define MESSAGE_HPP

#include	<iostream>
#include	<vector>

class	Message
{
	private:
		std::string	_nick;
		std::string	_hostName;
		std::string	_cmd;
		std::vector<std::string>	_param;
	public:
		Message(void);
		~Message(void);
		
		std::vector<std::string>	pars;
		
		void	msgParsing(std::string toParse);
		void	splitData(void);
		int		checkCmd(std::string toCheck);
		void	fillData(std::string data);

		void	clearParam(void);

		void	printTest(void);
};

# endif