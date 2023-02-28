/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:13:14 by amorel            #+#    #+#             */
/*   Updated: 2023/02/28 19:34:09 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/Config.hpp"

Config::Config()
{
	empty = true;
}

Config::~Config()
{
	empty = true;
	_errorPages.clear();
	_locations.clear();
}



std::string	Config::getIp(void)
{
	return _ip;
}

std::string	Config::getPort(void)
{
	return _port;
}

std::string	Config::getListen(void)
{
	return _listen;
}

std::string	Config::getRoot(void)
{
	return _root;
}

std::string	Config::getIndex(void)
{
	return _index;
}

std::string	Config::getAutoIndex(void)
{
	return _autoIndex;
}

std::string	Config::getServerName(void)
{
	return _serverName;
}

std::string	Config::getClientBodyLimit(void)
{
	return _clientBodyLimit;
}

std::map<std::string, std::string>	Config::getErrorPages(void)
{
	return _errorPages;
}

std::map<std::string, std::map<std::string, std::string> >	Config::getLocations(void)
{
	return _locations;
}



void	Config::setIp(const std::string &ip)
{
	empty = false;
	_ip = ip;
}

void	Config::setPort(const std::string &port)
{
	empty = false;
	_port = port;
}

void	Config::setListen(const std::string &listen)
{
	empty = false;
	if (listen.find(':') == std::string::npos)
		throw (Config::ErrorBadArgument());
	std::string	ip = listen.substr(0, listen.find(':'));
	std::string	port = listen.substr(listen.find(':') + 1, listen.size() - 1);
	_listen = listen;
	setIp(ip);
	setPort(port);
}

void	Config::setRoot(const std::string &root)
{
	empty = false;
	_root = root;
}

void	Config::setIndex(const std::string &index)
{
	empty = false;
	_index = index;
}

void	Config::setAutoIndex(const std::string &autoIndex)
{
	empty = false;
	_autoIndex = autoIndex;
}

void	Config::setServerName(const std::string &serverName)
{
	empty = false;
	_serverName = serverName;
}

void	Config::setClientBodyLimit(const std::string &clientBodyLimit)
{
	empty = false;
	_clientBodyLimit = clientBodyLimit;
}

void	Config::setErrorPages(const std::string &errorPage)
{
	empty = false;
	std::string error = errorPage.substr(11, errorPage.find('='));
	std::string file = errorPage.substr(errorPage.find('=') + 1, errorPage.size() - 1);

	_errorPages.insert(std::pair<std::string, std::string>(error, file));
}

void	Config::setLocations(std::ifstream &file, std::string buf)
{
	empty = false;
	if (buf.find(':') == std::string::npos)
		throw (Config::ErrorBadArgument());

	std::string	location = buf.substr(buf.find(':') + 1, buf.size() - 1);
	std::string	key;
	std::string	val;
	std::map<std::string, std::string>	tmp;
	while (!file.eof() && !buf.empty() && buf != "}")
	{
		getline(file, buf, '\n');
		if (!buf.empty() && !file.eof() && buf != "{" && buf != "}")
		{
			if (buf[0] == '\t')
				buf.erase(0, 1);
			key = buf.substr(0, buf.find('='));
			val = buf.substr(buf.find('=') + 1, buf.size() - 1);
			tmp.insert(std::pair<std::string, std::string>(key, val));
		}
	}
	_locations.insert(std::pair<std::string, std::map<std::string, std::string> >(location, tmp));
	tmp.clear();
}




void	Config::checkIP()
{
	std::stringstream	ip(_ip);
	std::string			tmp;
	std::string			ipMembers[4];

	for (int i = 0; i < 4; i++)
	{
		getline(ip, tmp, '.');
		ipMembers[i] = tmp.c_str();
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; ipMembers[i][j]; j++)
		{
			if (ipMembers[i].size() > 3 || ipMembers[i][j] < '0' || ipMembers[i][j] > '9')
				throw(Config::ErrorIpOutOfBounds());
		}
		if (std::atoi(ipMembers[i].c_str()) < 0 || std::atoi(ipMembers[i].c_str()) > 255)
			throw(Config::ErrorIpOutOfBounds());
	}
}

void	Config::checkPort()
{
	int		plus = (_port[0] == '+');
	bool	error = false;

	if (_port.size() - plus > 5)
		error = true;
	else
	{
		for (std::string::size_type i = 0; i < _port.size() - plus; i++)
			if (_port[i + plus] < '0' || _port[i + plus] > '9')
				error = true;
		if (!error)
			if (std::atoi(_port.c_str()) < 1023 || std::atoi(_port.c_str()) > 65325)
				error = true;
	}

	if (error)
		throw(Config::ErrorPortOutOfBounds());
}

void	Config::checkRoot()
{
	if (_root.empty())
		_root = "./www/html";
}

void	Config::checkIndex()
{
	if (_index.empty())
		_index = "index.html";

	std::string		path = _root + '/' + _index;
	std::ifstream	file;

	if (path.find("//") != std::string::npos)
		path.erase(path.find("//"), 1);
	file.open(path.c_str());
	if (file.fail())
		throw(Config::ErrorFileException());
	file.close();
}

void	Config::checkAutoIndex()
{
	if (_autoIndex.empty())
		_autoIndex = "on";
	if (_autoIndex != "off" && _autoIndex != "on")
		throw(Config::ErrorBadArgument());
}

void	Config::checkServerName()
{
	if (_serverName.empty())
		_serverName = "default";
}

void	Config::checkClientBodyLimit()
{
	if (_clientBodyLimit.empty())
		_clientBodyLimit = "4096";
	else if (std::atoi(_clientBodyLimit.c_str()) <= 0)
		throw(Config::ErrorBadArgument());
}

void	Config::checkErrorPages()
{
	std::string		errors[9] = {"400", "401", "403", "404", "405", "410", "431", "500", "503"};
	std::string		filepath;
	std::ifstream	file;

	if (_root.empty())
		throw(Config::ErrorFileException());

	for (int i = 0; i < 9; i++)
	{
		if (_errorPages.find("error_page_" + errors[i]) == _errorPages.end())
			_errorPages.insert(std::pair<std::string, std::string>("error_page_" + errors[i], errors[i] + ".html"));
		else
		{
			filepath = _errorPages.find("root")->second + "/" + _errorPages.find("error_page_" + errors[i])->second;
			if (filepath.find("//") < filepath.size())
				filepath.erase(filepath.find("//"), 1);
			file.open(filepath.c_str());
			if (file.fail())
				_errorPages.find("error_page_" + errors[i])->second = errors[i] + ".html";
			file.close();
		}
	}
}

void	Config::checkLocations()
{

}





void	Config::printErrorPages()
{
	std::map<std::string, std::string>::iterator	it;

	std::cout << "-------------------------------" << std::endl;
	for (it = _errorPages.begin(); it != _errorPages.end(); it++)
			std::cout << it->first << ":" << it->second << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void	Config::printLocations()
{
	std::map <std::string, std::map<std::string, std::string> >::iterator	it;
	std::map<std::string, std::string>::iterator							itm;

	
	for (it = _locations.begin(); it != _locations.end(); it++)
	{
		for (itm = it->second.begin(); itm != it->second.end(); itm++)
			std::cout << it->first << " - " << itm->first << ":" << itm->second << std::endl;
		std::cout << "-------------------------------" << std::endl;
	}
	std::cout << std::endl;
}

const char *Config::ErrorFileException::what() const throw()
{
    return ("Error::Failed open file");
}

const char *Config::ErrorPortOutOfBounds::what() const throw()
{
    return ("Error::Port out of bounds");
}

const char *Config::ErrorIpOutOfBounds::what() const throw()
{
    return ("Error::IP out of bounds");
}

const char *Config::ErrorBadArgument::what() const throw()
{
    return ("Error:: bad argument");
}