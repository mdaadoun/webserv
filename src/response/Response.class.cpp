/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/27 10:03:50 by tlafont          ###   ########.fr       */
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
	this->_response = "";
   // this->_response = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n<pre>---> response from Server...\n\nrequest sent to server:\n";
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

/*
*  @brief   Build response to send.
*			set the respons in function of request parsed
*  @param   std::string & (to modify when Request class established)
*  @return  void
*/
void	Response::buildResponse(std::string &req)
{
	// just for test
	if (req == "ERROR")
		this->_response = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n<pre>---> response from Server...\n\n#----- ERROR REQUEST NOT PROPERLY ESTABLISHED\n";
	else
		this->_response += req;
}
