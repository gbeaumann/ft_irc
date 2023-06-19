#include	"Message.hpp"

int	main()
{
	//faire un vector param avec par ex: #hello :Hello ererybody
	Message	test;
	//test.msgParsing("");
	//test.msgParsing("coucou");
	test.msgParsing("PRIVMSG #hello :Hello everybody");
	test.clearParam();
	test.msgParsing(":borja!borja@polaris.cs.uchicago.edu PRIVMSG #cmsc23300 :Hello everybody");
	return (0);
}