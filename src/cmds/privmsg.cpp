//Command: PRIVMSG
//Parameters: ?
void	privMsg(std::string target, std::string msg)
{
	if (channels.contains(target))
		broadcast(msg);
	if (users.contains(target))
		send(msg);
	else
		send(targetDoesNotExistsError(?));
}

