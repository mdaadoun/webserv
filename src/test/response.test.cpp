/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.test.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:33:14 by fleblanc          #+#    #+#             */
/*   Updated: 2023/02/17 10:37:46 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	responseTest()
{
	std::cout << "\033[0;34m # Response test # \033[0;0m" << std::endl;
//    Response rs;
//    std::string rq;
//    rs.buildResponse(rq);

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
//    std::cout << rs;
}
