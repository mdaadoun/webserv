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
parsing::parsing(void)
{
    config_to_map("config_default.ini");
}

parsing::parsing(std::string path)
{
    config_to_map(path);
}

parsing::~parsing()
{
}

/*
** private functions
*/
void	parsing::config_to_map(std::string path)
{
    std::ifstream file;
    std::string key;
    std::string value;

    file.open(path);
    if (file.fail())
    {
        std::cerr << "Error while opening file.";
        return;
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

void    parsing::printMap(void)
{
    std::cout << "-------------------------------" << std::endl;
    for (this->it = this->config.begin(); this->it != this->config.end(); it++)
        std::cout << this->it->first << ":" << this->it->second << std::endl;
    std::cout << "-------------------------------" << std::endl;
}

/*
** getters
*/
std::map<std::string, std::string>	*parsing::getMap(void)
{
    return (&(this->config));
}

std::string	parsing::getIPP(void)
{
    return (this->config.find("listen")->second);
}

std::string	parsing::getIP(void)
{
    std::string ip;
    ssize_t     colon;

    ip = this->config.find("listen")->second;
    colon = ip.find(':');
    while (ip.size() != colon)
        ip.pop_back();
    return (ip);
}

std::string	parsing::getPort(void)
{
    return (&(this->config.find("listen")->second.at(this->config.find("listen")->second.find(':'))));
}

std::string	parsing::getRoot(void)
{
    return (this->config.find("root")->second);
}

std::string	parsing::getIndex(void)
{
    return (this->config.find("index")->second);
}

std::string	parsing::getServerName(void)
{
    return (this->config.find("server_name")->second);
}

std::string	parsing::getClientBodyLimit(void)
{
    return (this->config.find("client_body_limit")->second);
}

/*
** checking
*/

void	parsing::checkIP(void)
{
    std::stringstream   ip(this->getIP());
    std::string         tmp;
    int                 ipMembers[4];
    int                 port = std::stoi(this->getPort());

    for (int i = 0; i < 4; i++)
    {
        getline(ip, tmp, '.');
        ipMembers[i] = std::stoi(tmp);
    }

    for (int i = 0; i < 4; i++)
    {
        if (ipMembers[i] < 0 || ipMembers[i] > 255)
            std::cerr << "ip out of bounds" << std::endl; //THROW here pls
    }
    if (port < 1023 || port > 65325)
        std::cerr << "port out of bounds" << std::endl; //THROW here pls
}

void	parsing::checkName(void)
{
    if (this->getServerName().empty())
        this->config.find("server_name")->second = "default";
}

void	parsing::checkIndex(void)
{
    std::string index = this->getRoot() + this->getIndex();
    std::ifstream file;

    file.open(index);
    if (file.fail())
        std::cerr << index << " not found" << std::endl; //THROW here pls
}

void	parsing::checkClientBodyLimit(void)
{
    if (std::stoi(this->getClientBodyLimit()) <= 0)
        std::cerr << "invalid client body limit" << std::endl; //THROW here pls
}

void	parsing::checkErrorPages(void)
{
}