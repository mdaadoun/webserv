/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:36:19 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/06 16:14:57 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

std::string	reformHeader(headerType const &head)
{
	switch (head)
	{
		case ACCEPT_CHARSET:
			return "ACCEPT_CHARSET";
		case ACCEPT_LANGUAGE:
			return "ACCEPT_LANGUAGE";
		case ALLOW:
			return "ALLOW";
		case AUTHORIZATION:
			return "AUTHORIZATION";
		case CONNECTION:
			return "CONNECTION";
		case CONTENT_LANGUAGE:
			return "CONTENT_LANGUAGE";
		case CONTENT_LENGTH:
			return "CONTENT_LENGTH";
		case CONTENT_LOCATION:
			return "CONTENT_LOCATION";
		case CONTENT_TYPE:
			return "CONTENT_TYPE";
		case DATE:
			return "DATE";
		case HOST:
			return "HOST";
		case LAST_MODIFIED:
			return "LAST_MODIFIED";
		case LOCATION:
			return "LOCATION";
		case REFERER:
			return "REFERER";
		case REMOTE_USER:
			return "REMOTE_USER";
		case RETRY_AFTER:
			return "RETRY_AFTER";
		case SERVER:
			return "SERVER";
		case TRANSFER_ENCODING:
			return "TRANSFER_ENCODING";
		case USER_AGENT:
			return "USER_AGENT";
		case WWW_AUTHENTICATE:
			return "WWW_AUTHENTICATE";
		default:
			return "INVALID HEADER";
	}
}

std::string	generatorRequest()
{
	std::string req;
	//---- start line ----//
//	req += "GET /home.html HTTP/1.1\r\n";
	req += "GET /cgi-bin/?var1=val1&var2=val2&var3=val3 HTTP/1.0\r\n";
	//---- headers ----//
//	req += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
//	req += "Accept-Encoding: gzip, deflate, br\r\n";
//	req += "Upgrade-Insecure-Requests: 1\r\n";
//	req += "If-Modified-Since: Mon, 18 Jul 2016 02:36:04 GMT\r\n";
//	req += "If-None-Match: \"c561c68d0ba92bbeb8b0fff2a9199f722e3a621a\"";
//	req += "Cache-Control: max-age=0\r\n";
	req += "User-Agent: Mozilla/5.0 (Linux; Intel OS X 10.9; rv:50.0) Gecko/20100101 Firefox/50.0\r\n";
	req += "Host: developer.mozilla.org\r\n";
	req += "Transfer-Encoding: chunked\r\n";
	req += "Referer: https://developer.mozilla.org/testpage.html\r\n";
	req += "Accept-Language: en-US,en;q=0.5\r\n";
	req += "Connection: keep-alive\r\n\r\n";
	//---- body ----//
	req += "request send from client------>\r\n";
	req += "Content-Type: text/html; charset=utf-8\r\n";
	req += "Content-Type: multipart/form-data; boundary=something\r\n";
	return (req);
}

void	requestTest()
{
	Request	req;
	std::string	to_parse = generatorRequest();
	req.parsing(to_parse, 10000);
	std::cout << "========== result of parsing ==========" << std::endl;
	std::cout << "\n** Start Line **" << std::endl;
	std::cout	<< "status:\t" << req.getStatus() << std::endl
				<< "Method:\t" << req.getMethod() << std::endl
				<< "URI:\t" << req.getUri().first << " : " << req.getUri().second << std::endl;
	std::map<std::string, std::string>	cgi = req.getCgi();
	if (cgi.empty())
		std::cout << "not CGI params..." << std::endl;
	else
		std::cout << "CGI:" << std::endl;
	std::map<std::string, std::string>::iterator	cgit = cgi.begin();
	std::map<std::string, std::string>::iterator	cgite = cgi.end();
	for (; cgit != cgite; cgit++)
		std::cout << "var: " << cgit->first << "\n\tvalue: " << cgit->second << std::endl;
	std::cout	<< "version:\t" << req.getVersion().first << std::endl
				<< "sub-version:\t" << req.getVersion().second << std::endl
				<< "\n** Headers **" << std::endl;
	std::map<headerType, std::string>	headers = req.getHeaders();
	std::map<headerType, std::string>::iterator	it = headers.begin();
	std::map<headerType, std::string>::iterator	ite = headers.end();
	for (; it != ite; it++)
		std::cout << "header: " << reformHeader(it->first) << "\n\tvalue =  " << it->second << std::endl;
	std::cout << "\n** Body (not parsed again) **" << std::endl;
	std::cout << req.getBody() << std::endl;
}
