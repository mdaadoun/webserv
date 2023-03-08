/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:11:36 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/08 11:18:10 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

// includes
#include <iostream>

// Sockets class
#include "sockets/ASocket.class.hpp"
#include "sockets/BindSocket.class.hpp"
#include "sockets/ComSocket.class.hpp"
#include "sockets/ListenSocket.class.hpp"

// parsing class
#include "parsing/Config.hpp"
#include "parsing/Parsing.hpp"

// Server class
#include "server/Server.class.hpp"

// manager
#include "manager/Manager.class.hpp"

#endif
