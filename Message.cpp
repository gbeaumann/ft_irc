#include "Message.hpp"

Message::Message(void) : _nick(""), _hostName(""), _cmd("") {}

Message::~Message(void) {}

int	Message::checkCmd(std::string toCheck)
{
	std::vector<std::string>	cmdList;// vector test
	cmdList.push_back("NICK");
	cmdList.push_back("PRIVMSG");
	cmdList.push_back("JOIN");
	std::vector<std::string>::iterator	it = cmdList.begin();
	for (; it != cmdList.end(); it++)
	{
		if (toCheck == *it)
		{
			this->_cmd = toCheck;
			std::vector<std::string>::iterator	it2 = this->pars.begin() + 1;
			it++;
			for (;it2 != this->pars.end(); it2++)
				this->_param.push_back(*it2);
			this->pars.clear();
			return(1);
		}
	}
	return (0);
}

void	Message::fillData(std::string	data)
{
	static int	i = 0;
	
	switch	(i)
	{
		case 0:
			this->_nick = data;
			i++;
			break;
		case 1:
			this->_hostName = data;
			i++;
			break;
		case 2:
			this->_cmd = data;
			i++;
			break;
		case 3:
			this->_param.push_back(data);
			break;
	}
}

void	Message::splitData(void)
{
	int			type;
	
	if (checkCmd(this->pars[0]))
		return;
	else
	{
		std::vector<std::string>::iterator	it = this->pars.begin();
		for (; it != this->pars.end(); it++)
			this->fillData(*it);
	}
	this->pars.clear();
}

void	Message::msgParsing(std::string toParse)
{
	int pos = 0;
	int	pos2 = 0;
	std::string	stock;
	if (toParse == "")
	{
		std::cout << "Error: Empty message" << std::endl;
		return;
	}
	if (toParse.find(":") == 0)
		toParse.erase(0, 1);
	while ((pos = toParse.find(" ")) < toParse.find(":"))
	{
		if ((pos2 = toParse.find("!")) < toParse.find(":"))
		{	stock = toParse.substr(0, pos2);
			this->pars.push_back(stock);
			toParse.erase(0, pos2 + 1);
		}
		else
		{
			stock = toParse.substr(0, pos);
			this->pars.push_back(stock);
			toParse.erase(0, pos + 1);
		}
	}
	toParse.erase(0, 1);
	this->pars.push_back(toParse);

	this->splitData();
	
	this->printTest();
}

void	Message::clearParam(void)
{
	if (!(this->_param.empty()))
		this->_param.clear();
}

void	Message::printTest(void)
{
	std::cout << "Nick: " << this->_nick << ", Hostname: " << this->_hostName << ", Cmd: " << this->_cmd << ", Params: ";
	std::vector<std::string>::iterator	it = this->_param.begin();
	for (; it != this->_param.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
