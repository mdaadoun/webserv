/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:12:25 by amorel            #+#    #+#             */
/*   Updated: 2023/02/15 17:05:49 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/parsing.hpp"
/*
** [de/con]structors
*/
Parsing::Parsing()
{
    config_to_map("config_default.ini");
}

Parsing::Parsing(const std::string &path)
{
    config_to_map(path);
}

Parsing::~Parsing()
{
}

/*
** private functions
*/
void	Parsing::config_to_map(std::string path)
{
    std::ifstream file;
    std::string key;
    std::string value;

    file.open(path.c_str());
    if (file.fail())
    {
        throw(Parsing::ErrorFileException());
    }
    this->it = this->config.begin();
    while (true)
    {
        getline(file, key, '=');
        getline(file, value);
        if (key.empty() || value.empty())
            break;
        this->config.insert(it, std::pair<std::string, std::string>(key, value));
        this->it = this->config.end();
    }
    file.close();
}

void    Parsing::printMap()
{
    std::cout << "-------------------------------" << std::endl;
    for (this->it = this->config.begin(); this->it != this->config.end(); it++)
        std::cout << this->it->first << ":" << this->it->second << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

/*
** getters
*/
std::map<std::string, std::string>	*Parsing::getMap()
{
    return (&(this->config));
}

std::string	Parsing::getIPP()
{
    return (this->config.find("listen")->second);
}

std::string	Parsing::getIP()
{
    std::string ip;
    ssize_t     colon;

    ip = this->config.find("listen")->second;
    colon = ip.find(':');
    while (ip.size() != colon)
        ip.erase(ip.length() - 1);
    return (ip);
}

std::string	Parsing::getPort()
{
    return (&(this->config.find("listen")->second.at(this->config.find("listen")->second.find(':'))));
}

std::string	Parsing::getRoot()
{
    return (this->config.find("root")->second);
}

std::string	Parsing::getIndex()
{
    return (this->config.find("index")->second);
}

std::string	Parsing::getServerName()
{
    return (this->config.find("server_name")->second);
}

std::string	Parsing::getClientBodyLimit()
{
    return (this->config.find("client_body_limit")->second);
}

/*
** checking
*/

void	Parsing::checkIP()
{
    std::stringstream   ip(this->getIP());
    std::string         tmp;
    int                 ipMembers[4];
    int                 port = std::atoi(this->getPort().c_str());

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

void	Parsing::checkName()
{
    if (this->getServerName().empty())
        this->config.find("server_name")->second = "default";
}

void	Parsing::checkIndex()
{
    std::string index = this->getRoot() + this->getIndex();
    std::ifstream file;

    file.open(index.c_str());
    if (file.fail())
        throw(Parsing::ErrorFileException());
    file.close();
}

void	Parsing::checkClientBodyLimit()
{
    if (std::atoi(this->getClientBodyLimit().c_str()) <= 0)
        std::cerr << "invalid client body limit" << std::endl; //THROW here pls
}

void	Parsing::checkErrorPages()
{
}

const char *Parsing::ErrorFileException::what() const throw()
{
    return ("Error::Failed open file");
}