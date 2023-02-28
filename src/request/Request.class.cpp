/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/28 14:50:36 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/request/Request.class.hpp"

/*
*  @brief   Default constructor.
*  @param   void
*  @return  void
*/
Request::Request(): _status(0), _rec_method(), _uri()
{
	this->initiMapMethods();
	this->initMapHeaders();
}

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
    return this->_to_parse; // to modify when parsing is done
}

/*
*  @brief   Init map methods.
*			Initialisation for the map of all methods
*  @param   void
*  @return  void
*/
void	Request::initiMapMethods()
{
	this->_methods["GET"] = GET;
	this->_methods["HEAD"] = HEAD;
	this->_methods["POST"] = POST;
	this->_methods["PUT"] = PUT;
	this->_methods["DELETE"] = DELETE;
	this->_methods["CONNECT"] = CONNECT;
	this->_methods["OPTIONS"] = OPTIONS;
	this->_methods["TRACE"] = TRACE;
	this->_methods["ERROR"] = ERROR;
}

/*
*  @brief   Init map headers.
*			Initialisation for the map of all headers
*  @param   void
*  @return  void
*/
void	Request::initMapHeaders()
{
	this->_headers["ACCEPT_CHARSET"] = ACCEPT_CHARSET;
	this->_headers["ACCEPT_LANGUAGE"] = ACCEPT_LANGUAGE;
	this->_headers["ALLOW"] = ALLOW;
	this->_headers["AUTHORIZATION"] = AUTHORIZATION;
	this->_headers["CONNECTION"] = CONNECTION;
	this->_headers["CONTENT_LANGUAGE"] = CONTENT_LANGUAGE;
	this->_headers["CONTENT_LENGTH"] = CONTENT_LENGTH;
	this->_headers["CONTENT_LOCATION"] = CONTENT_LOCATION;
	this->_headers["CONTENT_TYPE"] = CONTENT_TYPE;
	this->_headers["DATE"] = DATE;
	this->_headers["HOST"] = HOST;
	this->_headers["LAST_MODIFIED"] = LAST_MODIFIED;
	this->_headers["LOCATION"] = LOCATION;
	this->_headers["REFERER"] = REFERER;
	this->_headers["REMOTE_USER"] = REMOTE_USER;
	this->_headers["RETRY_AFTER"] = RETRY_AFTER;
	this->_headers["SERVER"] = SERVER;
	this->_headers["TRANSFER_ENCODING"] = TRANSFER_ENCODING;
	this->_headers["USER_AGENT"] = USER_AGENT;
	this->_headers["WWW_AUTHENTICATE"] = WWW_AUTHENTICATE;
}

/*
*  @brief   Parsing the request.
*			check if all the request is propely established
*  @param   std::string const &
*  @return  void
*/
void	Request::parsing(std::string const &req)
{
	this->_env.clear();
	this->parseHeader(req);

}

/*
*  @brief   Parsing the header of the request.
*			check if all the header of the request is propely established
*  @param   std::string const &
*  @return  void
*/
void	Request::parseHeader(std::string const & req)
{
	this->_to_parse = req;
	this->_status = 200;
	this->_reqHeaders.clear();
	try
	{
		this->parseStartLineRequest();
		this->parseProtocolHeaders();
	}
	catch(...)
	{
		std::cerr << "request not parsed correctly..." << std::endl;
		this->_status = 400;
	}
	//end of parsing and recover headers request
}

/*
*  @brief   Parsing the first line of request.
*			check and recove the string header 1rst segment
*  @param   void
*  @return  void
*/
void	Request::parseStartLineRequest()
{
	size_t	end_of_req = this->_to_parse.find("\r\n");
	// check the begin of request
	if (this->_to_parse[0] == ' ' && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: space in start of request. $$$$$" << std::endl;
		this->_status = 400;
	}
	// check end of header request
	if (end_of_req == std::string::npos && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: no body in request. $$$$$" << std::endl;
		this->_status = 400;
	}
	// check spaces in headers segment
	int	space = 0;
	int	d_space = 0;
	for (int i = 0; this->_to_parse[i] != '\r'; i++)
	{
		if (this->_to_parse[i] == ' ')
			space++;
		if (this->_to_parse[i] == ' ' && this->_to_parse[i + 1] = ' ')
			d_space++;
	}
	if ((space != 2 || d_space > 0) && this->_status = 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: too more spaces in header. $$$$$" << std::endl;
		this->_status = 400;
	}
	// recover the method in request
	size_t	len = 0;
	this->recoveryMethods(end_of_req, len);
	// recover the conf for URI
	len++;
	this->recoveryUri(end_of_req, len);
	len++;
	// recover version of method
	this->recoveryVersion(end_of_req, len);
	//delete headers from request to parse
	this->_to_parse.erase(0, len + 5);
}

/*
*  @brief   Recover Methods.
*			Extracts the Methods in the header of request
*  @param   size_t, size_t &
*  @return  void
*/
void	Request::recoveryMethods(size_t end_of_req, size_t &len)
{
	// check if no empty header
	len = this->_to_parse.find(' ');
	if (len > end_of_req && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: empty header... $$$$$" << std::endl;
		this->_status = 400;
	}
	// check if method exist
	std::string	extract = this->_to_parse.substr(0, len);
	std::map<std::string, methodType>::iterator	it = this->_methods.find(extract);
	if (it != this->_methods.end())
		this->_rec_method = it->second;
	else if (this->_status == 200)
	{
		// for debug mode
		std::cerr << "$$$$$ Error: method not existing. $$$$$" << std::endl;
		this->_status = 400;
	}
}

/*
*  @brief   Recover URI configuration.
*			Extracts the conf for URI in the header
*  @param   size_t, size_t
*  @return  void
*/
void	Request::recoveryUri(size_t end_of_req, size_t len)
{
	// check if conf uri not empty
	size_t	len2 = this->_to_parse.find(' ');
	if (len2 > end_of_req && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: Uri conf empty. $$$$$" << std::endl;
		this->_status = 400;
	}
	// extract the config uri
	this->_uri = this->_to_parse.substr(len, len2 - len);
	// check if config uri is properly established
	if (this->_uri[0] == ':' && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: URI conf not properly established $$$$$" << std::endl;
		this->_status = 400;
	}
	// check tyhe size of uri conf
	if (this->_uri.length() > 10000000 && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: Uri conf too long $$$$$" << std::endl;
	}
}

/*
*  @brief   Recover version of method.
*			Extracts the version for method in the header
*  @param   size_t, size_t
*  @return  void
*/
void	Request::recoveryVersion(size_t end_of_req, size_t &len)
{
	// check if version is set
	len = this->_to_parse.find("HTTPS/");
	if (len > end_of_req && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: version not set. $$$$$" << std::endl;
		this->_status = 400;
	}
	len += 5;
	// check if not after end of header request
	size_t	len2 = this->_to_parse.find("\r\n", pos);
	if (len2 > end_of_req && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: version set too small $$$$$" << std::endl;
		this->_status = 400;
	}
	// extract version string
	std::string	extract = this->_to_parse.substr(len, len2 - len);
	// conversion to a pair of data
	int	ver, sub_ver;
	std::istringstream(extract) >> ver;
	std::istringstream(extract + 2) >> sub_ver;
	this->_version = std::make_pair(ver, sud_ver);
}

/*
*  @brief   Parse the headers protocols.
*			check and recover headers protocols
*  @param   void
*  @return  void
*/
void	Request::parseProtocolHeaders()
{
	std::string	tmp;
	size_t		end_of_head = 0;
	int			offset = 0;
	while (!this->_to_parse.empty())
	{
		tmp.clear();
		end_of_head = this->_to_parse.find("\r\n");
		// check headers not empty
		if (end_of_head && end_of_head != std::string::npos)
		{
			// check the begin of line
			if (this->_to_parse[0] == ' ' && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: header starting with space. $$$$$" << std::endl;
				this->_status = 400;
			}
			// check if structur of header
			size_t	len = this->_to_parse.find(':');
			if (len > end_of_head && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: not struct of header protocol. $$$$$\n";
				this->_status = 400;
			}
			// recover of the header
			std::string	head = this->_to_parse.substr(0, len);
			if (head.empty() && this->_status = 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: empty name of header. $$$$$" << std::endl;
				this->_status = 400;
			}
			// check if the space is in the end of header name
			size_t	len_space = head.find(' ');
			if (len_space != std::string::npos && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: space not at the end. $$$$$" << std::endl;
				this->_status = 400;
			}
			// for skip the name of header
			len++;
			len = this->_to_parse.find_first_not_of(' ', len);
			offset = 0;
			//to be continued......
		}
		else
		{
			// check not the end of request
			if (end_of_head == std::string::npos && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: headers and/or body empty. $$$$$" << std::endl;
				this->_status = 400;
			}
			//delete headers segment
			this->_to_parse.erase(0, end_of_head + 2);
			//stop parsing
			return ;
		}
		//delete segment parsed
		this->_to_parse.erase(0, end_of_head + 2);
	}
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
Request::~Request()
{
	this->_to_parse.clear();
	this->_request.clear();
	this->_methods.clear();
	this->_headers.clear();
	this->_reqHeaders.clear();
	this->_uri.clear();
}
