/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:33:14 by fleblanc          #+#    #+#             */
/*   Updated: 2023/02/17 10:37:46 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

void	cgiTest(void)
{
    CgiHandler ch;
	std::string body;
    std::cout << "\033[0;34m # CGI test # \033[0;0m" << std::endl;

    std::cout << ch << std::endl;

    body = ch.executeCgi();

    std::cout << body << std::endl;
}
