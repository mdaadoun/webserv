/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:28:36 by amorel            #+#    #+#             */
/*   Updated: 2023/02/28 19:33:22 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/Parsing.hpp"

Parsing::Parsing(void)
{
	Parsing::parseConfig("conf/config_default.ini");
	Parsing::checkConfig();
}

Parsing::Parsing(const std::string &path)
{
	Parsing::parseConfig(path);
	Parsing::checkConfig();
}

Parsing::~Parsing(void)
{
		_servers.clear();
}

void	Parsing::parseConfig(const std::string &path)
{
	std::ifstream			file;
	std::string				buf;
	Config					tmp;
	std::string::size_type	pos;
    std::string				key;
    std::string				value;

	file.open(path.c_str());
	if (file.fail())
	{
		throw(Config::ErrorFileException());
	}
	while (true)
	{
		getline(file, buf, '\n');
		pos = buf.find('=');
		if (buf.empty() || file.eof())
		{
			if (!tmp.empty)
				this->_servers.insert(_servers.end(), tmp);
			break ;
		}
		else if (buf == "[server]")
		{
			if (tmp.empty)
				continue;
			this->_servers.insert(_servers.end(), tmp);
		}
		else if (buf.find('=') != std::string::npos)
		{
			key = buf.substr(0, pos);
			value = buf.substr(pos + 1);

			if (key == "server_name")
				tmp.setServerName(value);
			else if (key == "listen")
				tmp.setListen(value);
			else if (key == "root")
				tmp.setRoot(value);
			else if (key == "index")
				tmp.setIndex(value);
			else if (key == "autoindex")
				tmp.setAutoIndex(value);
			else if (key == "client_body_limit")
				tmp.setClientBodyLimit(value);
			else if (key.substr(0, 9) == "error_page")
				tmp.setErrorPages(buf);
		}
		else if (buf.find("location:") != std::string::npos)
			tmp.setLocations(file, buf);
	}
	file.close();
}

std::vector<class Config>	Parsing::getServers(void)
{
	return _servers;
}

class Config				*Parsing::getNServer(int n)
{
	return &(_servers.at(n));
}

void	Parsing::checkConfig()
{
	std::vector<Config>::iterator	it;

	for (it = _servers.begin(); it != _servers.end(); it++)
	{
		it->checkIP();
		it->checkPort();
		it->checkRoot();
		it->checkIndex();
		it->checkAutoIndex();
		it->checkServerName();
		it->checkClientBodyLimit();
		it->checkErrorPages();
		it->checkLocations();
	}
}
