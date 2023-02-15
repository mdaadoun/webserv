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

class parsing
{
private:
	std::map<std::string, std::string>				config;
    std::map<std::string, std::string>::iterator	it;
	
	void	config_to_map(std::string path);
	void	printMap(void);
	void	checkIP(void);
	void	checkRoot(void);
	void	checkName(void);
	void	checkIndex(void);
	void	checkClientBodyLimit(void);
	void	checkErrorPages(void);

public:
	parsing(std::string path);
	parsing(void);
	~parsing(void);

	std::map<std::string, std::string>	*getMap(void);
	std::string							getIP(void);
	std::string							getIPP(void);
	std::string							getPort(void);
	std::string							getRoot(void);
	std::string							getIndex(void);
	std::string							getServerName(void);
	std::string							getClientBodyLimit(void);
};

#endif // PARSING_HPP
