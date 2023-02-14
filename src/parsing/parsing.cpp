/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:12:25 by amorel            #+#    #+#             */
/*   Updated: 2023/02/14 15:38:48 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.hpp"

std::map	*parse_config_file(std::string  file)
{
	std::map	*config;
    std::ifstream   infile;
    std::string key;
    std::string value;

    infile.open(file.c_str());
    if (infile.fail())
    {
        std::cerr << "Error while opening file.";
        return (0);
    }
    do
    {
        getline(infile, key, '=');
        getline(infile, value);
        std::cout << key << "=" << value << std::endl;
    }while (!key.empty());
    return (0);
}