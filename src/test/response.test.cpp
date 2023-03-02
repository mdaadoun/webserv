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

void	responseTest(void)
{
	std::cout << "\033[0;34m # Response test # \033[0;0m" << std::endl;
    Response rs;
    std::string rq;
    rs.buildResponse(rq);
    std::cout << rs;
}
