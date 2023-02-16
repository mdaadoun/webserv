/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/13 11:17:33 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/request/Request.class.hpp"

/*
*  @brief   Default constructor.
*  @param   void
*  @return  void
*/
Request::Request() {}

/*
*  @brief   Assignment operator.
*           copy other request in this request
*  @param   Request &
*  @return  Request &
*/
Request	&Request::operator=(Request const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
Request::~Request()
{
}

/*
*  @brief   Getter.
*  @param   void
*  @return  request string
*/
std::string	Request::getRequest() const
{
    return this->_request;
}

/*
*  @brief   Setter.
*  @param   std::string request
*  @return  void
*/
void Request::setRequest(std::string const &req)
{
    this->_request = req;
}