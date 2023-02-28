/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:56:44 by amorel            #+#    #+#             */
/*   Updated: 2023/02/28 01:47:15 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>

class Config
{
	private:
		std::string													_ip;
		std::string													_port;
		std::string													_listen;
		std::string													_root;
		std::string													_index;
		std::string													_autoIndex;
		std::string													_serverName;
		std::string													_clientBodyLimit;
		std::map<std::string, std::string>							_errorPages;
		std::map<std::string, std::map<std::string, std::string> >	_locations;

	public:
		Config(void);
		// Config(const Config &copy);
		~Config(void);

		bool														empty;
		std::string													getIp(void);
		std::string													getPort(void);
		std::string													getListen(void);
		std::string													getRoot(void);
		std::string													getIndex(void);
		std::string													getAutoIndex(void);
		std::string													getServerName(void);
		std::string													getClientBodyLimit(void);
		std::map<std::string, std::string>							getErrorPages(void);
		std::map<std::string, std::map<std::string, std::string> >	getLocations(void);

		void	setIp(const std::string &ip);
		void	setPort(const std::string &port);
		void	setListen(const std::string &listen);
		void	setRoot(const std::string &root);
		void	setIndex(const std::string &index);
		void	setAutoIndex(const std::string &autoIndex);
		void	setServerName(const std::string &serverName);
		void	setClientBodyLimit(const std::string &clientBodyLimit);
		void	setErrorPages(const std::string &errorPage);
		void	setLocations(std::ifstream &file, std::string buf);

		void	checkIP();
		void	checkPort();
		void	checkRoot();
		void	checkIndex();
		void	checkAutoIndex();
		void	checkServerName();
		void	checkClientBodyLimit();
		void	checkErrorPages();
		void	checkLocations();


		void	printErrorPages(void);
		void	printLocations(void);

		class ErrorFileException : public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
    class ErrorPortOutOfBounds : public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
    class ErrorIpOutOfBounds : public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
    class ErrorBadArgument : public std::exception
    {
        public:
            virtual const char* what() const throw();
    };
};
