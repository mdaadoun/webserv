/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:09 by fleblanc          #+#    #+#             */
/*   Updated: 2023/02/16 19:43:58 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

#include "sockets/BindSocket.class.hpp"
#include "sockets/ClientSocket.class.hpp"
#include "sockets/ISocket.class.hpp"
#include "sockets/ListenSocket.class.hpp"
#include "parsing/Config.hpp"

void	socketTest(void);
void    Parsing_Test(std::string file);

#endif
