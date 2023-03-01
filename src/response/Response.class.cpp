/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/01 16:40:32 by amorel           ###   ########.fr       */
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
    this->_response = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n<pre>---> response from Server...\n\nrequest sent to server:\n";
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
	// if (req == "ERROR")
	// 	this->_response = "HTTP/1.1 200 OK\r\nContent-Type:text/html\r\n\r\n<pre>---> response from Server...\n\n#----- ERROR REQUEST NOT PROPERLY ESTABLISHED\n";
	// else
	// 	this->_response += req;
	struct tm	now;
	char		*weekday[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
	char		*month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
	_response += "HTTP/1.1 200 OK\r\n";

	_response += "Date: ";
	_response += weekday[now.tm_wday];
	_response += ", ";
	_response += now.tm_mday;
	_response += " ";
	_response += month[now.tm_mon];
	_response += " ";
	_response += now.tm_year;
	_response += " ";
	_response += now.tm_hour;
	_response += ":";
	_response += now.tm_min;
	_response += ":";
	_response += now.tm_sec;
	_response += " ";
	_response += now.tm_zone;
	_response += "\r\n";

	_response += "Server: Webserv/0.1 (Ubuntu) OpenSSL 1.1.1f PHP/7.4\r\n";

	_response += "Last-Modified: ";
	_response += "ETag: \"xxxxxxxxx\"";
	_response += "Content-Length: xxxx";
	_response += "Content-Type: text/html; charset=UTF-8";
}


/*
*	@brief	Add body to response
*
*	@param	std::string& (path to the file get by the request)
*	@return	void
*/
void	Response::addBodyResponse(std::string& path)
{
	std::ifstream	file;
	std::string		buff;

	file.open(path.c_str());
	if (file.is_open())
	{
		getline(file, buff, '\0'); // A voir le delimiteur
		_response += buff;
		file.close();
	}
	// else
	// 	throw (FileNotOpenException());
}
