/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:31:27 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/17 11:19:26 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.hpp"


int main()
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
				Config config(av[1]);
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
