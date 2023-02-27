/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:09 by fleblanc          #+#    #+#             */
/*   Updated: 2023/02/17 17:50:13 by amorel           ###   ########.fr       */
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
#include "parsing/Config.class.hpp"

void	socketTest(void);
void	responseTest(void);
void	parsingTest();


#endif
