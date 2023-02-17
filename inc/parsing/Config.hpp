/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:14:07 by amorel            #+#    #+#             */
/*   Updated: 2023/02/15 16:35:09 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

class Config
{
public:
    Config(const std::string& path);
    Config();
    ~Config();

    std::vector<std::map<std::string, std::string> >    getList() const;
    std::map<std::string, std::string>	*getMap(int n);
    std::string							getIP(int n);
    std::string							getListen(int n);
    std::string 						getPort(int n);
    std::string							getRoot(int n);
    std::string							getIndex(int n);
    std::string							getServerName(int n);
    std::string							getClientBodyLimit(int n);

    void	printMap(std::vector<std::map<std::string, std::string> >::iterator it);

    class ErrorFileException : public std::exception
    {
    public:

        virtual const char* what() const throw();
    };

private:
    std::vector<std::map<std::string, std::string> >    _list;
	std::map<std::string, std::string>				config;
    std::map<std::string, std::string>::iterator	it;

    void    check_key_value(std::string &key, std::string &value);
	void	config_to_map(std::string path);
    std::string getStringPort();
    std::string parse_listen_ip(std::string listen);
    std::string parse_listen_port(std::string listen);
    static void	checkPort(std::string &value);
	static void	checkIP(std::string &value);
    static void checkListen(std::string &value);
	static void	checkName(std::string &value);
	static void	checkIndex(std::map<std::string, std::string> map);
	static void	checkClientBodyLimit(std::string &value);
	static void	checkErrorPages(std::map<std::string, std::string> *config);
};

#endif
