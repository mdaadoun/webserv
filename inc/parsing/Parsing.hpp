/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:23:24 by amorel            #+#    #+#             */
/*   Updated: 2023/02/28 16:24:03 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "../inc/parsing/Config.hpp"

class Parsing
{
	private:
		std::vector<class Config>	_servers;

	public:
		Parsing(void);
		Parsing(const std::string &path);
		~Parsing(void);

		std::vector<class Config>	getServers(void);
		class Config				*getNServer(int n);
		void						parseConfig(const std::string &path);
		void						checkConfig();
};