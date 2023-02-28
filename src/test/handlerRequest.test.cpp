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

void	handlerRequestTest(void)
{
//    Config conf("conf/config_default.ini");
    RequestHandler rh;
    std::cout << "\033[0;34m # Handler Request test # \033[0;0m" << std::endl;
    rh.run();
    std::cout << rh << std::endl;
}
