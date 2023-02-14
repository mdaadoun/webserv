/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:12:25 by amorel            #+#    #+#             */
/*   Updated: 2023/02/14 17:44:54 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parsing/parsing.hpp"

void    parse_config_file(std::map<std::string, std::string> *config, std::string  file)
{
    std::map<std::string, std::string>::iterator    it = config->begin();
    std::ifstream   infile;
    std::string key;
    std::string value;

    infile.open(file.c_str());
    if (infile.fail())
    {
        std::cerr << "Error while opening file.";
        return ;
    }
    while (true)
    {
        getline(infile, key, '=');
        getline(infile, value);
        if (key.empty() || value.empty())
            break;
        config->insert(it, std::pair<std::string, std::string>(key, value));
        it = config->end();
    }
    if (config->size() != 18)
        std::cerr << "Bad number of arguments in " << file << "." << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (it = config->begin(); it != config->end(); it++)
        std::cout << it->first << ":" << it->second << std::endl;
    std::cout << "-------------------------------" << std::endl;
}
