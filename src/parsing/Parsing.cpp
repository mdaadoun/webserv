/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:28:36 by amorel            #+#    #+#             */
/*   Updated: 2023/02/28 15:44:25 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/Parsing.hpp"

/*
*  @brief	Default constructor of the class Parsing.
*           Launch Parser and checker with "config_default.ini".
*  @param	void
*  @return	void
*/
Parsing::Parsing()
{
	Parsing::parseConfig("conf/config_default.ini");
	Parsing::checkConfig();
}

/*
*  @brief	Overload constructor of the class Parsing.
*           Launch Parser and checker with argument path.
*  @param	const std::string &path
*  @return	void
*/
Parsing::Parsing(const std::string &path)
{
	Parsing::parseConfig(path);
	Parsing::checkConfig();
}

/*
*  @brief	Copy constructor of the class Parsing.
*           Initialize the Parsing with Parsing received as argument.
*  @param	const Parsing &copy
*  @return	void
*/
Parsing::Parsing(const Parsing &copy)
{
    this->_servers = copy.getServers();
}

/*
*  @brief	Default deconstructor of the class Parsing.
*  @param	void
*  @return	void
*/
Parsing::~Parsing() {}

/*
*  @brief   Assignment operator.
*           copy other Parsing in this Parsing
*  @param   Parsing &
*  @return  Parsing &
*/
Parsing &Parsing::operator=(const Parsing &copy)
{
    this->_servers = copy.getServers();
    return *this;
}

/*
*  @brief	Default constructor of the class Parsing.
*           Initialize the config with default file "config_default.ini".
*  @param	const std::string &path
*  @return	void
*/
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
				this->_servers.push_back(tmp);
			break ;
		}
		else if (buf == "[server]")
		{
			if (tmp.empty)
				continue;
			this->_servers.push_back(tmp);
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

/*
*  @brief	Return attribute _servers;
*  @param	void
*  @return	std::vector<class Config>
*/
std::vector<class Config>	Parsing::getServers() const
{
	return _servers;
}

/*
*  @brief	Return number n Config member of attribute _servers.
*  @param	void
*  @return	class Config *
*/
class Config				*Parsing::getNServer(int n)
{
	return &(_servers.at(n));
}

/*
*  @brief	Launch all check function of Config Class member of attribute _servers.
*  @param	void
*  @return	void
*/
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
