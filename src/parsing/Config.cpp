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

#include "../inc/parsing/Config.hpp"

/*
** [de/con]structors
*/
Config::Config()
{
    config_to_map("config_default.ini");
}

Config::Config(const std::string &path)
{
    config_to_map(path);
}

Config::~Config()
{
}

/*
** private functions
*/
void	Config::config_to_map(std::string path)
{
    std::ifstream file;
    std::string line;
    std::string key;
    std::string value;

    file.open(path.c_str());
    if (file.fail())
    {
        throw(Config::ErrorFileException());
    }
    this->it = this->config.begin();
    while (true)
    {
        getline(file, line, '\n');
        if (line.empty())
        {
            checkIndex(config);
            checkErrorPages(&config);
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            break;
        }

        if (line == "[server]")
        {
            if (config.size() == 0)
                continue;
            checkIndex(config);
            checkErrorPages(&config);
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            config.clear();
            continue;
        }

        std::string::size_type pos = line.find('=');
        if (pos != std::string::npos)
        {
            key = line.substr(0, pos);
            value = line.substr(pos + 1);
            this->check_key_value(key, value);
            if (key == "listen")
            {
                std::string listenkey = "ip";
                std::string listenvalue = parse_listen_ip(value);
                this->check_key_value(listenkey, listenvalue);
                this->config.insert(it, std::pair<std::string, std::string>(listenkey, listenvalue));
                this->it = this->config.end();
                listenkey = "port";
                listenvalue = parse_listen_port(value);
                this->check_key_value(listenkey, listenvalue);
                this->config.insert(it, std::pair<std::string, std::string>(listenkey, listenvalue));
                this->it = this->config.end();
            }
        }
        this->config.insert(it, std::pair<std::string, std::string>(key, value));
        this->it = this->config.end();
    }
    file.close();
}

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

void    Config::printMap(std::vector<std::map<std::string, std::string> >::iterator it)
{
    std::cout << "-------------------------------" << std::endl;
    for (this->it = it->begin(); this->it != it->end(); this->it++)
        std::cout << this->it->first << ":" << this->it->second << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

std::string Config::parse_listen_ip(std::string listen)
{
    std::string res;
    size_t     colon;

    res = listen;
    colon = res.find(':');
    while (res.size() != colon)
        res.erase(res.length() - 1);

    return (res);
}

std::string Config::parse_listen_port(std::string listen)
{
    return (&listen.at(listen.find(':') + 1));
}

/*
** getters
*/
std::vector<std::map<std::string, std::string> > Config::getList() const
{
    return (_list);
}

std::map<std::string, std::string>	*Config::getMap(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (&(*it));
}

std::string	Config::getListen(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("listen")->second);
}

std::string	Config::getIP(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("ip")->second);
}

std::string Config::getPort(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("port")->second);
}


std::string	Config::getRoot(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("root")->second);
}

std::string	Config::getIndex(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("index")->second);
}

std::string	Config::getServerName(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("server_name")->second);
}

std::string	Config::getClientBodyLimit(int n)
{
    std::vector<std::map<std::string, std::string> >::iterator  it = this->_list.begin();
    while (n-- > 1)
        it++;
    return (it->find("client_body_limit")->second);
}

/*
** checking
*/

void	Config::checkPort(std::string &value)
{
    int port = std::atoi(value.c_str());

    if (port < 1023 || port > 65325)
        std::cerr << "port out of bounds" << std::endl; //THROW here pls
}

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

void	Config::checkName(std::string &value)
{
    if (value.empty())
        value = "default";
}

void	Config::checkIndex(std::map<std::string, std::string> map)
{
    if (map.find("root") == map.end() || map.find("index") == map.end())
        throw(Config::ErrorFileException());
    std::string index = map.find("root")->second + "/" + map.find("index")->second;
    if (index.find("//") < index.size())
        index.erase(index.find("//"), 1);
    std::ifstream file;

    file.open(index.c_str());
    if (file.fail())
        throw(Config::ErrorFileException());
    file.close();
}

void	Config::checkClientBodyLimit(std::string &value)
{
    if (std::atoi(value.c_str()) <= 0)
        std::cerr << "invalid client body limit" << std::endl; //THROW here pls
}

void	Config::checkErrorPages(std::map<std::string, std::string> *map)
{
    std::string errors[9] = {"400", "401", "403", "404", "405", "410", "431", "500", "503"};
    std::string filepath;
    std::ifstream file;

    for (int i = 0; i < 9; i++)
    {
        if (map->find("root") == map->end() || map->find("error_page_" + errors[i]) == map->end())
            std::cout << "NOPE" << std::endl;
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

const char *Config::ErrorFileException::what() const throw()
{
    return ("Error::Failed open file");
}