#include "../inc/Message.hpp"

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
	switch	(this->fillIdx)
	{
		case 0:
			this->_nick = data;
			this->fillIdx++;
			break;
		case 1:
			this->_user = data;
			this->fillIdx++;
			break;
		case 2:
			this->_hostName = data;
			this->fillIdx++;
			break;
		case 3:
			this->_cmd = data;
			this->fillIdx++;
			break;
		case 4:
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
	this->fillIdx = 0;
	int	endlPos;

	if (toParse.find('\n'))
	{
		endlPos = toParse.find('\n');
		toParse.erase(endlPos, toParse.npos);
	}

	if (toParse[0] == '\n')
	{
		std::cout << "Error: Empty message" << std::endl;
		return;
	}
	if (toParse.find(":") == 0)
		toParse.erase(0, 1);
	while ((pos = toParse.find(" ")) < toParse.find(":"))
	{
		if ((pos2 = toParse.find("!")) < toParse.find(":"))
		{	
			stock = toParse.substr(0, pos2);
			this->pars.push_back(stock);
			toParse.erase(0, pos2 + 1);
		}
		else if ((pos2 = toParse.find("@")) < toParse.find(":"))
		{	
			stock = toParse.substr(0, pos2);
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
	if (toParse.find(":") == 0)
		toParse.erase(0, 1);
	this->pars.push_back(toParse);

	this->splitData();
	this->printTest();
	this->clearParam();
}

void	Message::clearParam(void)
{
	this->_nick = "";
	this->_hostName = "";
	this->_cmd = "";
	this->_param.clear();
}

void	Message::printTest(void)
{
	std::cout << "Nick: " << this->_nick << std::endl;
	std::cout << "User: " << this->_user << std::endl;
	std::cout << "Hostname: " << this->_hostName << std::endl;
	std::cout << "Cmd: " << this->_cmd << std::endl;
	std::cout << "Params: ";
	std::vector<std::string>::iterator	it = this->_param.begin();
	for (; it != this->_param.end(); it++)
	{
		std::cout << *it << " | ";
	}
	std::cout << std::endl;
}
