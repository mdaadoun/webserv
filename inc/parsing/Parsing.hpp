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
		Parsing();
		Parsing(const std::string &file);
        Parsing(const Parsing &copy);
		~Parsing();

        Parsing &operator=(const Parsing &copy);

		std::vector<class Config>	getServers() const;
		class Config				*getNServer(int n);
		void						parseConfig(const std::string &file);
		void						checkConfig();
};
