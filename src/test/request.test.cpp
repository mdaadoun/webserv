/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.test.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:36:19 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/01 13:34:41 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

std::string	generatorRequest()
{
	std::string req;
	// first line
	req += "GET /home.html HTTP/1.1\r\n";
	// headers
	req += "Host: developer.mozilla.org\r\n";
	req += "User-Agent: Mozilla/5.0 (Linux; Intel OS X 10.9; rv:50.0) Gecko/20100101 Firefox/50.0\r\n";
	req += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n";
	req += "Accept-Language: en-US,en;q=0.5\r\n";
	req += "Accept-Encoding: gzip, deflate, br\r\n";
	req += "Referer: https://developer.mozilla.org/testpage.html\r\n";
	req += "Connection: keep-alive\r\n";
	req += "Upgrade-Insecure-Requests: 1\r\n";
	req += "If-Modified-Since: Mon, 18 Jul 2016 02:36:04 GMT\r\n";
	req += "If-None-Match: \"c561c68d0ba92bbeb8b0fff2a9199f722e3a621a\"";
	req += "Cache-Control: max-age=0\r\n\r\n";
	//body
	req += "request send from client------>\r\n";
	req += "Content-Type: text/html; charset=utf-8\r\n";
	req += "Content-Type: multipart/form-data; boundary=something\r\n";
	return (req);
}

void	requestTest()
{
	Request	req;
	std::string	to_parse = generatorRequest();
	req.parsing(to_parse);
	std::cout << "========== result of parsing ==========" << std::endl
			<< req << std::endl;
}
