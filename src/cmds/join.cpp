//Command: JOIN
//Parameters: <channelname> ?
void	join(Msg msg)
{
	std::string	channel_name;

	channel_name = msg.params[0]; //need error check ?

	channel = channels.insert(channel_name); //Create if need, returns channel

	channel.addClient(&client);

	send(); //Send success or error
}

