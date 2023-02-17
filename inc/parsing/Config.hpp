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
    std::map<std::string, std::string>	*getMap();
    std::string							getIP();
    std::string							getIPP();
    int     							getPort();
    std::string							getRoot();
    std::string							getIndex();
    std::string							getServerName();
    std::string							getClientBodyLimit();

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
	
	void	config_to_map(std::string path);
    std::string     getStringPort();
	void	checkIP(void);
	void	checkRoot(void);
	void	checkName(void);
	void	checkIndex(void);
	void	checkClientBodyLimit(void);
	void	checkErrorPages(void);
};

#endif
