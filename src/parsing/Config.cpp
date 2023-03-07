/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:13:14 by amorel            #+#    #+#             */
/*   Updated: 2023/03/07 12:52:19 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/Config.hpp"

/*
*  @brief	Default constructor of the class Config.
*           Set attribute Empty to true.
*  @param	void
*  @return	void
*/
Config::Config()
{
	empty = true;
}

/*
*  @brief	Copy constructor of the class Config.
*           Initialize the config with config received as argument.
*  @param	const Config &copy
*  @return	void
*/
Config::Config(const Config &copy)
{
    empty = copy.empty;
    this->_ip = copy.getIp();
    this->_port = copy.getPort();
    this->_listen = copy.getListen();
    this->_root = copy.getRoot();
    this->_index = copy.getIndex();
    this->_autoIndex = copy.getAutoIndex();
    this->_serverName = copy.getServerName();
    this->_clientBodyLimit = copy.getClientBodyLimit();
    this->_errorPages = copy.getErrorPages();
    this->_locations = copy.getLocations();
    this->_cgi = copy.getCgi();
}

/*
*  @brief	Default deconstructor of the class Config.
*           Set attribute Empty to true.
*  @param	void
*  @return	void
*/
Config::~Config()
{
	empty = true;
	_errorPages.clear();
	_locations.clear();
	_cgi.clear();
}

/*
*  @brief   Assignment operator.
*           copy other config in this config
*  @param   Config &
*  @return  Config &
*/
Config &Config::operator=(const Config &copy)
{
    empty = copy.empty;
    this->_ip = copy.getIp();
    this->_port = copy.getPort();
    this->_listen = copy.getListen();
    this->_root = copy.getRoot();
    this->_index = copy.getIndex();
    this->_autoIndex = copy.getAutoIndex();
    this->_serverName = copy.getServerName();
    this->_clientBodyLimit = copy.getClientBodyLimit();
    this->_errorPages = copy.getErrorPages();
    this->_locations = copy.getLocations();
    this->_cgi = copy.getCgi();
    return *this;
}

/*
*  @brief	Return attribute _ip.
*  @param	void
*  @return	std::string
*/
std::string	Config::getIp() const
{
	return _ip;
}

/*
*  @brief	Return attribute _port.
*  @param	void
*  @return	std::string
*/
std::string	Config::getPort() const
{
	return _port;
}

/*
*  @brief	Return attribute _listen.
*  @param	void
*  @return	std::string
*/
std::string	Config::getListen() const
{
	return _listen;
}

/*
*  @brief	Return attribute _root.
*  @param	void
*  @return	std::string
*/
std::string	Config::getRoot() const
{
	return _root;
}

/*
*  @brief	Return attribute _index.
*  @param	void
*  @return	std::string
*/
std::string	Config::getIndex() const
{
	return _index;
}

/*
*  @brief	Return attribute _autoIndex.
*  @param	void
*  @return	std::string
*/
std::string	Config::getAutoIndex() const
{
	return _autoIndex;
}

/*
*  @brief	Return attribute _serverName.
*  @param	void
*  @return	std::string
*/
std::string	Config::getServerName() const
{
	return _serverName;
}

/*
*  @brief	Return attribute _clientBodyLimit.
*  @param	void
*  @return	std::string
*/
std::string	Config::getClientBodyLimit() const
{
	return _clientBodyLimit;
}

/*
*  @brief	Return attribute _errorPages.
*  @param	void
*  @return	std::map<std::string, std::string>
*/
std::map<std::string, std::string>	Config::getErrorPages() const
{
	return _errorPages;
}

/*
*  @brief	Return attribute _locations.
*  @param	void
*  @return	std::map<std::string, std::map<std::string, std::string> >
*/
std::map<std::string, std::map<std::string, std::string> >	Config::getLocations() const
{
	return _locations;
}

/*
*  @brief	Return attribute _cgi.
*  @param	void
*  @return	std::map<std::string, std::map<std::string, std::string> >
*/
std::map<std::string, std::map<std::string, std::string> >	Config::getCgi() const
{
    return _cgi;
}

/*
*  @brief	Set attribute _ip with argument received.
*  @param	const std::string &ip
*  @return	void
*/
void	Config::setIp(const std::string &ip)
{
	empty = false;
	_ip = ip;
}

/*
*  @brief	Set attribute _port with argument received.
*  @param	const std::string &port
*  @return	void
*/
void	Config::setPort(const std::string &port)
{
	empty = false;
	_port = port;
}

/*
*  @brief	Set attribute _listen with argument received.
*           Parse Listen and set ip and port.
*  @param	const std::string &listen
*  @return	void
*/
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

/*
*  @brief	Set attribute _root with argument received.
*  @param	const std::string &root
*  @return	void
*/
void	Config::setRoot(const std::string &root)
{
	empty = false;
	_root = root;
}

/*
*  @brief	Set attribute _index with argument received.
*  @param	const std::string &index
*  @return	void
*/
void	Config::setIndex(const std::string &index)
{
	empty = false;
	_index = index;
}

/*
*  @brief	Set attribute _autoIndex with argument received.
*  @param	const std::string &autoIndex
*  @return	void
*/
void	Config::setAutoIndex(const std::string &autoIndex)
{
	empty = false;
	_autoIndex = autoIndex;
}

/*
*  @brief	Set attribute _serverName with argument received.
*  @param	const std::string &serverName
*  @return	void
*/
void	Config::setServerName(const std::string &serverName)
{
	empty = false;
	_serverName = serverName;
}

/*
*  @brief	Set attribute _clientBodyLimit with argument received.
*  @param	const std::string &clientBodyLimit
*  @return	void
*/
void	Config::setClientBodyLimit(const std::string &clientBodyLimit)
{
	empty = false;
	_clientBodyLimit = clientBodyLimit;
}

/*
*  @brief	Insert new member to  attribute _errorPages with argument received.
*  @param	const std::string &errorPages
*  @return	void
*/
void	Config::setErrorPages(const std::string &errorPage)
{
	empty = false;
	std::string error = errorPage.substr(11, errorPage.find('='));
	std::string file = errorPage.substr(errorPage.find('=') + 1, errorPage.size() - 1);

	_errorPages.insert(std::pair<std::string, std::string>(error, file));
}

/*
*  @brief	Parse and check argument to insert new member to attribute _locations.
*  @param	std::ifstream &file, std::string buf
*  @return	void
*/
void	Config::setLocations(std::ifstream &file, std::string buf)
{
	empty = false;
	if (buf.find(':') == std::string::npos)
		throw (Config::ErrorBadArgument());

	std::string	location = buf.substr(buf.find(':') + 1, buf.size() - 1);
	std::string	key;
	std::string	val;
	std::map<std::string, std::string>	tmp;
	while (!file.eof() && buf != "}")
	{
		getline(file, buf, '\n');
		if (!buf.empty() && !file.eof() && buf != "{" && buf != "}")
		{
			if (buf[0] == '\t')
				buf.erase(0, 1);
			else if (buf.compare(0, 4, "    ") == 0)
				buf.erase(0, 4);
			key = buf.substr(0, buf.find('='));
			val = buf.substr(buf.find('=') + 1, buf.size() - 1);
			tmp.insert(std::pair<std::string, std::string>(key, val));
		}
	}
	_locations.insert(std::pair<std::string, std::map<std::string, std::string> >(location, tmp));
	if (_locations.empty())
	{
		tmp.insert(std::pair<std::string, std::string>("allow_methods", "GET"));
		_locations.insert(std::pair<std::string, std::map<std::string, std::string> >("/", tmp));
	}
	tmp.clear();
}

/*
*  @brief	Parse and check argument to insert new member to attribute _cgi.
*  @param	std::ifstream &file, std::string buf
*  @return	void
*/
void	Config::setCgi(std::ifstream &file, std::string buf)
{
    empty = false;
    if (buf.find(':') == std::string::npos)
        throw (Config::ErrorBadArgument());

    std::string	cgi = buf.substr(buf.find(':') + 1, buf.size() - 1);
    std::string	key;
    std::string	val;
    std::map<std::string, std::string>	tmp;
    while (!file.eof() && buf != "}")
    {
        getline(file, buf, '\n');
        if (!buf.empty() && !file.eof() && buf != "{" && buf != "}")
        {
            if (buf[0] == '\t')
                buf.erase(0, 1);
			else if (buf.compare(0, 4, "    ") == 0)
				buf.erase(0, 4);
            key = buf.substr(0, buf.find('='));
            val = buf.substr(buf.find('=') + 1, buf.size() - 1);
            tmp.insert(std::pair<std::string, std::string>(key, val));
        }
    }
	if (tmp.find("directory") == tmp.end())
    	tmp.insert(std::pair<std::string, std::string>("directory", "cgi-bin"));
    _cgi.insert(std::pair<std::string, std::map<std::string, std::string> >(cgi, tmp));
    tmp.clear();
}

/*
*  @brief	Check attribute _ip and throw exception if error detected.
*  @param	void
*  @return	void
*/
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

/*
*  @brief	Check attribute _port and throw exception if error detected.
*  @param	void
*  @return	void
*/
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

/*
*  @brief	Check attribute _root and set it with "./www/html" if empty.
*  @param	void
*  @return	void
*/
void	Config::checkRoot()
{
	if (_root.empty())
		_root = "./www/html";
}

/*
*  @brief	Check attribute _index and throw exception if error detected.
*           If attribute is empty, set it with "index.html".
*  @param	void
*  @return	void
*/
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

/*
*  @brief	Check attribute _autoIndex and throw exception if error detected.
*           If attribute is empty, set it with "on".
*  @param	void
*  @return	void
*/
void	Config::checkAutoIndex()
{
	if (_autoIndex.empty())
		_autoIndex = "on";
	if (_autoIndex != "off" && _autoIndex != "on")
		throw(Config::ErrorBadArgument());
}

/*
*  @brief	Check attribute _serverName.
*           If attribute is empty, set it with "default".
*  @param	void
*  @return	void
*/
void	Config::checkServerName()
{
	if (_serverName.empty())
		_serverName = "default";
}

/*
*  @brief	Check attribute _clientBodyLimit and throw exception if error detected.
*           If attribute is empty, set it with "4096".
*  @param	void
*  @return	void
*/
void	Config::checkClientBodyLimit()
{
	if (_clientBodyLimit.empty())
		_clientBodyLimit = "4096";
    for (std::string::size_type i = 0; i < _clientBodyLimit.length(); i++)
    {
        if (!isdigit(_clientBodyLimit[i]))
            throw(Config::ErrorBadArgument());
    }
	if (std::atoi(_clientBodyLimit.c_str()) <= 0)
		throw(Config::ErrorBadArgument());
}

/*
*  @brief	Check attribute _errorPages and throw exception if error detected.
*  @param	void
*  @return	void
*/
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

void	Config::checkCgi()
{

}

/*
*  @brief	Print all member of attribute _errorPages.
*  @param	void
*  @return	void
*/
void	Config::printErrorPages()
{
	std::map<std::string, std::string>::iterator	it;

	std::cout << "-------------------------------" << std::endl;
	for (it = _errorPages.begin(); it != _errorPages.end(); it++)
			std::cout << it->first << ":" << it->second << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

/*
*  @brief	Print all member of attribute _locations.
*  @param	void
*  @return	void
*/
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
}

/*
*  @brief	Print all member of attribute _errorPages.
*  @param	void
*  @return	void
*/
void	Config::printCgi()
{
    std::map <std::string, std::map<std::string, std::string> >::iterator	it;
    std::map<std::string, std::string>::iterator							itm;


    for (it = _cgi.begin(); it != _cgi.end(); it++)
    {
        for (itm = it->second.begin(); itm != it->second.end(); itm++)
            std::cout << it->first << " - " << itm->first << ":" << itm->second << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
    std::cout << std::endl;
}


/*
*  @brief	Clear
*  @param	void
*  @return	void
*/
void	Config::clear()
{
	this->_locations.clear();
	this->_cgi.clear();
	this->_errorPages.clear();

}

/*
*  @brief	Inserts a location in _locations
*  @param	void
*  @return	void
*/
void	Config::insertLocation(std::string location, std::map<std::string, std::string> tmp)
{
	this->_locations.insert(std::pair<std::string, std::map<std::string, std::string> >(location, tmp));
}

/*
*  @brief	Return "Error::Failed open file".
*  @param	void
*  @return	char *
*/
const char *Config::ErrorFileException::what() const throw()
{
    return ("Error::Failed open file");
}

/*
*  @brief	Return "Error::Port out of bounds".
*  @param	void
*  @return	char *
*/
const char *Config::ErrorPortOutOfBounds::what() const throw()
{
    return ("Error::Port out of bounds");
}

/*
*  @brief	Return "Error::IP out of bounds".
*  @param	void
*  @return	char *
*/
const char *Config::ErrorIpOutOfBounds::what() const throw()
{
    return ("Error::IP out of bounds");
}

/*
*  @brief	Return "Error:: bad argument".
*  @param	void
*  @return	char *
*/
const char *Config::ErrorBadArgument::what() const throw()
{
    return ("Error:: bad argument");
}