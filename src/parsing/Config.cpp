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
        getline(file, key, '=');
        getline(file, value);
        if (key.empty() || value.empty())
        {
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            break;
        }
        if (key == "[server]")
        {
            if (config.size() == 0)
                continue;
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            config.clear();
            continue;
        }
        this->config.insert(it, std::pair<std::string, std::string>(key, value));
        this->it = this->config.end();
    }
    file.close();
}

void    Config::printMap(std::vector<std::map<std::string, std::string> >::iterator it)
{
    //std::map<std::string, std::string>  map = _list.;
    (void)it;
    std::cout << "-------------------------------" << std::endl;
    for (this->it = this->config.begin(); this->it != this->config.end(); it++)
        std::cout << this->it->first << ":" << this->it->second << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

/*
** getters
*/
std::vector<std::map<std::string, std::string> > Config::getList() const
{
    return (_list);
}

std::map<std::string, std::string>	*Config::getMap()
{
    return (&(this->config));
}

std::string	Config::getIPP()
{
    return (this->config.find("listen")->second);
}

std::string	Config::getIP()
{
    std::string ip;
    size_t     colon;

    ip = this->config.find("listen")->second;
    colon = ip.find(':');
    while (ip.size() != colon)
        ip.erase(ip.length() - 1);
    return (ip);
}

int Config::getPort()
{
    return (std::atoi(this->getStringPort().c_str()));
}

std::string	Config::getStringPort()
{
    return (&(this->config.find("listen")->second.at(this->config.find("listen")->second.find(':'))) + 1);
}

std::string	Config::getRoot()
{
    return (this->config.find("root")->second);
}

std::string	Config::getIndex()
{
    return (this->config.find("index")->second);
}

std::string	Config::getServerName()
{
    return (this->config.find("server_name")->second);
}

std::string	Config::getClientBodyLimit()
{
    return (this->config.find("client_body_limit")->second);
}

/*
** checking
*/

void	Config::checkIP()
{
    std::stringstream   ip(this->getIP());
    std::string         tmp;
    int                 ipMembers[4];
    int                 port = this->getPort();

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
    if (port < 1023 || port > 65325)
        std::cerr << "port out of bounds" << std::endl; //THROW here pls
}

void	Config::checkName()
{
    if (this->getServerName().empty())
        this->config.find("server_name")->second = "default";
}

void	Config::checkIndex()
{
    std::string index = this->getRoot() + this->getIndex();
    std::ifstream file;

    file.open(index.c_str());
    if (file.fail())
        throw(Config::ErrorFileException());
    file.close();
}

void	Config::checkClientBodyLimit()
{
    if (std::atoi(this->getClientBodyLimit().c_str()) <= 0)
        std::cerr << "invalid client body limit" << std::endl; //THROW here pls
}

void	Config::checkErrorPages()
{
    std::string index = this->config.find("error_page_400")->second;
    std::ifstream file;

    file.open(index.c_str());
    if (file.fail())
        throw(Config::ErrorFileException());
    file.close();
}

const char *Config::ErrorFileException::what() const throw()
{
    return ("Error::Failed open file");
}