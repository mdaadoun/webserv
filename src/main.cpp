/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/21 08:44:02 by tlafont          ###   ########.fr       */
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
				Config config("conf/config_default.ini");
				// construction du Manager
				Manager	manager(config);
				// init du manager
				manager.initConnetions();
				// lancement du manager
				manager.managementProcess();
			}
			catch (std::execption &e)
				std::cout << e.what() << std::endl;
		}
		else
		{
			try
			{
				Config config(av[1]);
				Server serv(config, 1);
				serv.launch();
			}
			catch (std::exeption &e)
				std::cout << e.what() << std::endl;
		}
	}
	else
		std::cout << "Usage: ./webserv [configuration file]" << std::endl;
    return 0;
}
