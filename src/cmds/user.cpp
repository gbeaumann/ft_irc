//Command: USER
//Parameters: <username> <hostname> <servername> <realname>
//ERR_ALREADYREGISTRED
//ERR_NEEDMOREPARAMS
void	user(Msg msg)
{
	if (msg.getClient().isConnected())
		return send(ERR_ALREADYREGISTRED);
	users.push_back(client);
}
