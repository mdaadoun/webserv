/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorel <amorel@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/06 12:51:01 by tlafont          ###   ########.fr       */
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
*			Use the requestHandler class with the parsed request to get the responses element
*			Compose the response with the requestHandler getters (status code, content type, etc..)
*  @param   std::string & (to modify when Request class established)
*  @return  void
*/
void	Response::buildResponse(Request const &req, Parsing const &config)
{
	(void)config; // pour link la config ...
    RequestHandler rh(req);
    rh.run();

    std::string header_sep = "\r\n";
    std::string body_sep = "\r\n\r\n";

    // HEADER
    this->_response = "";
    this->_response += rh.getProtocolVersion() + " ";
    this->_response += rh.getStatusCodeString();
    this->_response += header_sep;
    this->_response += "Content-Type: " + rh.getContentType() + "; charset=UTF-8";
    this->_response += header_sep;
    this->_response += "Date: " + rh.getDate();
    this->_response += header_sep;
    this->_response += "Server: Webserv/0.1 (Ubuntu) OpenSSL 1.1.1f PHP/7.4";
//    this->_response += header_sep;
//	this->_response += "Content-Length: " + rh.getContentLength();
//    this->_response += header_sep;
//	_response += "Last-Modified: " + rh.getLastModified();
//    this->_response += header_sep;
//	_response += "ETag: \"xxxxxxxxx\"";

    // BODY
    this->_response += body_sep;
    this->_response += rh.getBody();
}

/*
*  @brief   Overloaded stream insertion operator
*  @param   std::ostream &out   the output stream (out)
*           Response &rh  a reference to a Response object
*  @return  std::ostream &
*/
std::ostream &operator<<(std::ostream &out, Response &rh) {
    out << "response:\n";
    out << rh.getResponse();
    return out;
}
