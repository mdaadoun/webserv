/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/24 12:02:43 by tlafont          ###   ########.fr       */
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
*  @brief   Parsing the request.
*			check if all the request is propely established
*  @param   std::string request
*  @return  void
*/
void	Request::parsing(std::string &req)
{
	if(req.size() > 0)
	{
		std::cout << "****** Parsing request done ******" << std::endl;	
		//to modify when parsing implemented
		this->_request = req;
	}
	else
	{
		std::cout << "###### Parsing request done with ERROR CODE ######" << std::endl;
		//to modify when parsing implemented
		this->_request = "ERROR";
	}
}
