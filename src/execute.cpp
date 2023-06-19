
//Reimplement with pointer on functions array
void	execute(Msg &msg)
{
	if (msg.command == "NICK")
		nick(msg);
	else if (msg.command == "USER")
		user(msg);
	else if (msg.command == "JOIN")
		join(msg);
	else if (msg.command == "PRIVMSG")
		privmsg(msg);
	else
		cmd_does_not_exist(msg);
}