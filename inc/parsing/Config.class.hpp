/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:14:07 by amorel            #+#    #+#             */
/*   Updated: 2023/02/24 13:37:55 by tlafont          ###   ########.fr       */
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


    //Constructor, Destructor
    Config(const std::string& path);
    Config(const Config &copy);
    Config();
    ~Config();

    //Getter Method
    std::vector<std::map<std::string, std::string> >    getList() const;
    std::map<std::string, std::string>	                *getMap(int n);
    std::string							                getIP(int n);
    std::string							                getListen(int n);
    std::string 						                getPort(int n);
    std::string							                getRoot(int n);
    std::string						                   	getIndex(int n);
    std::string							                getServerName(int n);
    std::string						                	getClientBodyLimit(int n);
    std::string                                         getErrorPage(int n, const std::string& error);
    std::string                                         getLocAllowMethod(int n);
    std::string                                         getLocContentAllowMethod(int n);
    std::string                                         getLocCgiAllowMethod(int n);

    //Utils Method
    static void	printMap(std::vector<std::map<std::string, std::string> >::iterator it);

    //Exception class
    class ErrorFileException : public std::exception
    {
    public:

        virtual const char* what() const throw();
    };

    class ErrorIpOutOfBoundException : public std::exception
    {
    public:

        virtual const char* what() const throw();
    };

    class ErrorPortOutOfBoundException : public std::exception
    {
    public:

        virtual const char* what() const throw();
    };

private:
    std::vector<std::map<std::string, std::string> >    _list;

	void	            config_to_map(const std::string& path);
    static std::string  parse_listen_ip(const std::string& listen);
    static std::string  parse_listen_port(std::string listen);
    static void         check_key_value(std::string &key, std::string &value);
    static void	        checkPort(std::string &value);
	static void	        checkIP(std::string &value);
	static void	        checkName(std::string &value);
	static bool		    checkIndex(std::map<std::string, std::string> map);
	static void	        checkClientBodyLimit(std::string &value);
	static void	        checkErrorPages(std::map<std::string, std::string> *config);
};

#endif
