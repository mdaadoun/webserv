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
            std::map<std::string, std::string>  tmp = config;
            _list.push_back(tmp);
            break;
        }

        if (line == "[server]")
        {
            if (config.size() == 0)
                continue;
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
        }
        this->config.insert(it, std::pair<std::string, std::string>(key, value));
        this->it = this->config.end();
    }
    file.close();
}

void Config::check_key_value(std::string &key, std::string &value)
{
    std::string params[18] = {"server_name",
                            "listen",
                            "root=",
                            "index",
                            "autoindex",
                            "client_body_limit",
                            "error_page_400",
                            "error_page_401",
                            "error_page_403",
                            "error_page_404",
                            "error_page_405",
                            "error_page_410",
                            "error_page_413",
                            "error_page_500",
                            "error_page_503",
                            "location_/",
                            "location_/content",
                            "location_/cgi"};
    void    (*fct[18])(std::string &value) = {checkName,
                                              checkListen,
                                              checkRoot,
                                              checkIndex,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL,
                                              NULL};
    for (int i = 0; i < 18; i++)
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

void Config::checkListen(std::string &value)
{
    std:std::string port = &(this->config.find("listen")->second.at(this->config.find("listen")->second.find(':'))) + 1;
    this->config.insert(it, std::pair<std::string, std::string>("port", port));
    this->it = this->config.end();

    size_t     colon;
    std::string ip = value;
    colon = ip.find(':');
    while (ip.size() != colon)
        ip.erase(ip.length() - 1);
    this->config.insert(it, std::pair<std::string, std::string>("ip", ip));
    this->it = this->config.end();
}

void	Config::checkName(std::string &value)
{
    if (value.empty())
        value = "default";
}

void	Config::checkIndex(std::string &value)
{
    std::string index = this->getRoot() + value;
    std::ifstream file;

    file.open(index.c_str());
    if (file.fail())
        throw(Config::ErrorFileException());
    file.close();
}

void	Config::checkClientBodyLimit(std::string &value)
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