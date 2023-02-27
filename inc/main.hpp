/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 10:11:36 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/24 10:20:12 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HPP
# define MAIN_HPP

// includes
#include <iostream>

// Sockets class
#include "sockets/ISocket.class.hpp"
#include "sockets/BindSocket.class.hpp"
#include "sockets/ComSocket.class.hpp"
#include "sockets/ListenSocket.class.hpp"

// parsing class
#include "parsing/Config.class.hpp"

// Server class
#include "server/Server.class.hpp"

// manager
#include "manager/Manager.class.hpp"

#endif
