/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:14:07 by amorel            #+#    #+#             */
/*   Updated: 2023/02/15 16:35:09 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HPP
#define PARSING_HPP

#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <filesystem>

class Parsing
{
public:
    Parsing(const std::string& path);
    Parsing();
    ~Parsing();

    std::map<std::string, std::string>	*getMap();
    std::string							getIP();
    std::string							getIPP();
    std::string							getPort();
    std::string							getRoot();
    std::string							getIndex();
    std::string							getServerName();
    std::string							getClientBodyLimit();

    void	printMap(void);

    class ErrorFileException : public std::exception
    {
    public:

        virtual const char* what() const throw();
    };

private:
	std::map<std::string, std::string>				config;
    std::map<std::string, std::string>::iterator	it;
	
	void	config_to_map(std::string path);
	void	checkIP(void);
	void	checkRoot(void);
	void	checkName(void);
	void	checkIndex(void);
	void	checkClientBodyLimit(void);
	void	checkErrorPages(void);
};

#endif
