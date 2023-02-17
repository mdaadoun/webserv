/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 15:41:09 by fleblanc          #+#    #+#             */
/*   Updated: 2023/02/17 10:39:48 by fleblanc         ###   ########.fr       */
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

void	socketTest(void);
void	responseTest(void);
void	parsingTest(void);


#endif
