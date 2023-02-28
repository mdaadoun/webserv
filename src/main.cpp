/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/28 15:28:11 by amorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main(int ac, char **av)
{
	if (ac < 3)
	{
		if (ac == 1)
		{	
			try
			{
				// parsing config file 
				Parsing config("conf/config_default.ini");
				// construction du Manager
				Manager	manager(config);
				// init du manager
				manager.initConnections();
				// lancement du manager
				manager.managementProcess();
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		else
		{
			try
			{
				// parsing config file 
				Parsing config(av[1]);
				// construction du Manager
				Manager	manager(config);
				// init du manager
				manager.initConnections();
				// lancement du manager
				manager.managementProcess();
			}
			catch (std::exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}
	else
		std::cout << "Usage: ./webserv [configuration file]" << std::endl;
    return 0;
}
