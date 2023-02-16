/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/13 11:17:33 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/response/Response.class.hpp"

/*
*  @brief   Default constructor.
*  @param   void
*  @return  void
*/
Response::Response()
{
    this->_response = "---> response from Server...\n\nrequest send to server;\n";
}

/*
*  @brief   Assignment operator.
*           copy other response in this response
*  @param   Response &
*  @return  Response &
*/
Response	&Response::operator=(Response const &rhs)
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
Response::~Response()
{
}

/*
*  @brief   Getter.
*  @param   void
*  @return  response string
*/
std::string	Response::getResponse() const
{
    return this->_response;
}