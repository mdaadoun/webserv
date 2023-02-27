/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/27 16:29:06 by tlafont          ###   ########.fr       */
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
*  @brief   Getter.
*  @param   void
*  @return  request string
*/
std::string	Request::getRequest() const
{
    return this->_request;
}

/*
*  @brief   Parsing the request.
*			check if all the request is propely established
*  @param   std::string const &
*  @return  void
*/
void	Request::parsing(std::string const &req)
{
	this->_to_parse = req;
	this->_status = 200;

}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
Request::~Request()
{
	this->_request.clear();
}
