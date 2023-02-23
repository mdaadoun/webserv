/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:12:25 by amorel            #+#    #+#             */
/*   Updated: 2023/02/15 17:05:49 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/Config.class.hpp"

/*
*  @brief	Default constructor of the class Config.
*           Initialize the config with default file "config_default.ini".
*  @param	void
*  @return	void
*/
Config::Config()
{
    config_to_map("conf/config_default.ini");
}

/*
*  @brief	Copy constructor of the class Config.
*           Initialize the config with config received as argument.
*  @param	Config &copy
*  @return	void
*/
Config::Config(const Config &copy) : _list(copy.getList())
{
    return ;
}

/*
*  @brief	Overload constructor of the class Config.
*           Initialize the config with path file.
*  @param	string &path
*  @return	void
*/
Config::Config(const std::string &path)
{
    config_to_map(path);
}

/*
*  @brief	Default deconstructor of the class Config.
*  @param	void
*  @return	void
*/
Config::~Config()
{
}

/*
*  @brief	Method to parse and check file into map.
*  @param	string path
*  @return	void
*/
void	Config::config_to_map(const std::string& path)
{
    std::ifstream file;
    std::string line;
    std::string key;
    std::string value;
    std::map<std::string, std::string>				config;
    std::map<std::string, std::string>::iterator	it;

    file.open(path.c_str());
    if (file.fail())
    {
        throw(Config::ErrorFileException());
    }
    it = config.begin();
    while (true)
    {
        getline(file, line, '\n');
        //if (line.empty() || file.eof())
        if (file.eof())
        {
            if (!checkIndex(config))
                config.insert(std::pair<std::string, std::string>("error", "yes"));
            checkErrorPages(&config);
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            break ;
        }

        if (line == "[server]")
        {
            if (config.empty())
                continue ;
            if (!checkIndex(config))
                config.insert(std::pair<std::string, std::string>("error", "yes"));
            checkErrorPages(&config);
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            config.clear();
            continue ;
        }

        std::string::size_type pos = line.find('=');
        if (pos != std::string::npos)
        {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            Config::check_key_value(key, value);
            if (key == "listen")
            {
                std::string listenkey = "ip";
                std::string listenvalue = parse_listen_ip(value);
                Config::check_key_value(listenkey, listenvalue);
                config.insert(it, std::pair<std::string, std::string>(listenkey, listenvalue));
                it = config.end();
                listenkey = "port";
                listenvalue = parse_listen_port(value);
                Config::check_key_value(listenkey, listenvalue);
                config.insert(it, std::pair<std::string, std::string>(listenkey, listenvalue));
                it = config.end();
            }
        }
        config.insert(it, std::pair<std::string, std::string>(key, value));
        it = config.end();
    }
    file.close();
}

/*
*  @brief	Parse listen and return only the IP part.
*  @param	string listen
*  @return	string
*/
std::string Config::parse_listen_ip(const std::string& listen)
{
    std::string res;
    size_t     colon;

    res = listen;
    colon = res.find(':');
    while (res.size() != colon)
        res.erase(res.length() - 1);

    return (res);
}

/*
*  @brief	Parse listen and return only the port part.
*  @param	string listen
*  @return	string
*/
std::string Config::parse_listen_port(std::string listen)
{
    return (&listen.at(listen.find(':') + 1));
}

/*
*  @brief	Print all map content.
*  @param	std::vector<std::map<std::string, std::string> >::iterator it
*  @return	void
*/
void    Config::printMap(std::vector<std::map<std::string, std::string> >::iterator it)
{
    std::map<std::string, std::string>::iterator	itm;
    std::cout << "-------------------------------" << std::endl;
    if (it->find("error") != it->end())
        std::cout << "Error on server " << it->find("server_name")->second << std::endl;
    else
    {
        for (itm = it->begin(); itm != it->end(); itm++)
            std::cout << itm->first << ":" << itm->second << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}

/*
*  @brief	Return vector _list.
*  @param	void
*  @return	std::vector<std::map<std::string, std::string> >
*/
std::vector<std::map<std::string, std::string> > Config::getList() const
{
    return (_list);
}

/*
*  @brief	Return map at n position of vector _list.
*  @param	int n
*  @return	std::map<std::string, std::string>
*/
std::map<std::string, std::string>	*Config::getMap(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (&(*it));
}

/*
*  @brief	Return content of "listen" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string	Config::getListen(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("listen")->second);
}

/*
*  @brief	Return content of "ip" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string	Config::getIP(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("ip")->second);
}

/*
*  @brief	Return content of "port" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string Config::getPort(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("port")->second);
}

/*
*  @brief	Return content of "root" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string	Config::getRoot(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("root")->second);
}

/*
*  @brief	Return content of "index" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string	Config::getIndex(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("index")->second);
}

/*
*  @brief	Return content of "server_name" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string	Config::getServerName(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("server_name")->second);
}

/*
*  @brief	Return content of "client_body_limit" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string	Config::getClientBodyLimit(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("client_body_limit")->second);
}

/*
*  @brief	Return content of ("error_page_" + error) in map at n position of vector _list.
*  @param	int n, std::string error
*  @return	std::string
*/
std::string Config::getErrorPage(int n, const std::string& error)
{
    std::string str = "error_page_" + error;
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find(str)->second);
}

/*
*  @brief	Return content of "location_/_allow_methods" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string Config::getLocAllowMethod(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("location_/_allow_methods")->second);
}

/*
*  @brief	Return content of "location_/content_allow_methods" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string Config::getLocContentAllowMethod(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("location_/content_allow_methods")->second);
}

/*
*  @brief	Return content of "location_/cgi-bin_allow_methods" in map at n position of vector _list.
*  @param	int n
*  @return	std::string
*/
std::string Config::getLocCgiAllowMethod(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("location_/cgi-bin_allow_methods")->second);
}

/*
*  @brief	Identify key value for call check Method for value.
*  @param	std::string key, std::string value
*  @return	void
*/
void Config::check_key_value(std::string &key, std::string &value)
{
    std::string params[4] = {"server_name",
                             "ip",
                             "port",
                             "client_body_limit"};
    void    (*fct[4])(std::string &value) = {Config::checkName,
                                             Config::checkIP,
                                             Config::checkPort,
                                             Config::checkClientBodyLimit};
    for (int i = 0; i < 4; i++)
    {
        if (key == params[i])
            fct[i](value);
    }
    (void)value;
}

/*
*  @brief	Verify if port value is correct.
*  @param	std::string value
*  @return	void
*/
void	Config::checkPort(std::string &value)
{
    int port = std::atoi(value.c_str());

    if (port < 1023 || port > 65325)
        std::cerr << "port out of bounds" << std::endl; //THROW here pls
}

/*
*  @brief	Verify if ip value is correct.
*  @param	std::string value
*  @return	void
*/
void	Config::checkIP(std::string &value)
{
    std::stringstream   ip(value);
    std::string         tmp;
    int                 ipMembers[4];

    for (int i = 0; i < 4; i++)
    {
        getline(ip, tmp, '.');
        ipMembers[i] = std::atoi(tmp.c_str());
    }
    for (int i = 0; i < 4; i++)
    {
        if (ipMembers[i] < 0 || ipMembers[i] > 255)
            std::cerr << "ip out of bounds" << std::endl; //THROW here pls
    }
}

/*
*  @brief	Verify if server_name is not empty, if empty set it with "default" name.
*  @param	std::string value
*  @return	void
*/
void	Config::checkName(std::string &value)
{
    if (value.empty())
        value = "default";
}

/*
*  @brief	Combine index with root and verify if index can be open, if not return false.
*  @param	std::map<std::string, std::string> map
*  @return	bool
*/
bool	Config::checkIndex(std::map<std::string, std::string> map)
{
    if (map.find("root") == map.end() || map.find("index") == map.end())
        return (false);
    std::string index = map.find("root")->second + "/" + map.find("index")->second;
    if (index.find("//") < index.size())
        index.erase(index.find("//"), 1);
    std::ifstream file;

    file.open(index.c_str());
    if (file.fail())
        return (false);
    file.close();
        return (true);
}

/*
*  @brief	Verify if client_body_limit is a valid value.
*  @param	std::string value
*  @return	void
*/
void	Config::checkClientBodyLimit(std::string &value)
{
    if (std::atoi(value.c_str()) <= 0)
        std::cerr << "invalid client body limit" << std::endl; //THROW here pls
}

/*
*  @brief	Combine error_page_<value> with root and verify if it can be open, if not reset with default file <value> + ".html".
*  @param	std::string value
*  @return	void
*/
void	Config::checkErrorPages(std::map<std::string, std::string> *map)
{
    std::string errors[9] = {"400", "401", "403", "404", "405", "410", "431", "500", "503"};
    std::string filepath;
    std::ifstream file;

    for (int i = 0; i < 9; i++)
    {
        if (map->find("root") == map->end())
            std::cout << "NOPE" << std::endl;
        else if (map->find("error_page_" + errors[i]) == map->end())
            map->insert(std::pair<std::string, std::string>("error_page_" + errors[i], errors[i] + ".html"));
        else
        {
            filepath =  map->find("root")->second + "/" + map->find("error_page_" + errors[i])->second;
            if (filepath.find("//") < filepath.size())
                filepath.erase(filepath.find("//"), 1);
            file.open(filepath.c_str());
            if (file.fail())
                map->find("error_page_" + errors[i])->second = errors[i] + ".html";
            file.close();
        }
    }
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
