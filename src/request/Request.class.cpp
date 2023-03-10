/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/03/07 09:04:15 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/request/Request.class.hpp"

/*
*  @brief   Default constructor.
*  @param   void
*  @return  void
*/
Request::Request(): _status(0), _rec_method(), _cgi()
{
	this->initMapMethods();
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
*  @brief   Getter for the request parsed.
*  @param   void
*  @return  std::string
*/
std::string	Request::getRequest() const
{
    return this->_to_parse; // to modify when parsing is done
}

/*
*  @brief   Getter for the status after parsing.
*			Access to the status
*  @param   void
*  @return  int
*/
int	Request::getStatus() const
{
	return (this->_status);
}

/*
*  @brief   Getter for the method.
*			Access to the method after parsing
*  @param   void
*  @return  std::string
*/
std::string	Request::getMethod() const
{
	switch (this->_rec_method)
	{
		case GET:
			return "GET";
		case HEAD:
			return "HEAD";
		case POST:
			return "POST";
		case PUT:
			return "PUT";
		case DELETE:
			return "DELETE";
		case CONNECT:
			return "CONNECT";
		case OPTIONS:
			return "OPTIONS";
		case TRACE:
			return "TRACE";
		case ERROR:
			return "ERROR";
		default:
			return "NOMETHOD";
	}
}

/*
*  @brief   Getter for the uri.
*			Access to the uri after parsing
*  @param   void
*  @return  std::string
*/
std::pair<std::string, std::string>	Request::getUri() const
{
	return (this->_uri);
}

/*
*  @brief   Getter for the version.
*			Access to the version after parsing
*  @param   void
*  @return  std::pair<int, int>
*/
std::pair<int, int>	Request::getVersion() const
{
	return (this->_version);
}

/*
*  @brief   Getter for the headers.
*			Access to the headers after parsing
*  @param   void
*  @return  std::map<headerType, std::string>
*/
std::map<headerType, std::string>	Request::getHeaders() const
{
	return (this->_reqHeaders);
}

/*
*  @brief   Getter for the cgi params.
*			Access to the parameters of CGI after parsing
*  @param   void
*  @return  std::map<std::string, std::string>
*/
std::map<std::string, std::string>	Request::getCgi() const
{
	return (this->_cgi);
}

/*
*  @brief   Getter for Body request parsed.
*			Access to the parameters of body 
*  @param   void
*  @return  std::string
*/
std::string	Request::getBody() const
{
	return (this->_body);
}

/*
*  @brief   Init map methods.
*			Initialisation for the map of all methods
*  @param   void
*  @return  void
*/
void	Request::initMapMethods()
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
void	Request::parsing(std::string const &req, int const body_limit)
{
	this->_env.clear();
	this->parseHeader(req);
	this->parseBody(body_limit);
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
	// for split Uri and CGI params
	this->parseUri();
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
		if (this->_to_parse[i] == ' ' && this->_to_parse[i + 1] == ' ')
			d_space++;
	}
	if ((space != 2 || d_space > 0) && this->_status == 200)
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
	std::map<std::string, e_METHOD>::iterator	it = this->_methods.find(extract);
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
	size_t	len2 = this->_to_parse.find(' ', len);
	if (len2 > end_of_req && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: Uri conf empty. $$$$$" << std::endl;
		this->_status = 400;
	}
	// extract the config uri
	this->_all_uri = this->_to_parse.substr(len, len2 - len);
	// check if config uri is properly established
	if (this->_all_uri[0] == ':' && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: URI conf not properly established $$$$$" << std::endl;
		this->_status = 400;
	}
	// check tyhe size of uri conf
	if (this->_all_uri.length() > 10000000 && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: Uri conf too long $$$$$" << std::endl;
		this->_status = 400;
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
	len = this->_to_parse.find("HTTP/");
	if (len > end_of_req && this->_status == 200)
	{
		//for debug mode
		std::cerr << "$$$$$ Error: version not set. $$$$$" << std::endl;
		this->_status = 400;
	}
	len += 5;
	// check if not after end of header request
	size_t	len2 = this->_to_parse.find("\r\n", len);
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
	std::istringstream(extract.c_str() + 2) >> sub_ver;
	this->_version = std::make_pair(ver, sub_ver);
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
			if (head.empty() && this->_status == 200)
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
			for (size_t	i = end_of_head - 1; i != std::string::npos && this->_to_parse[i] == ' '; --i)
				offset++;
			// extract the value of header
			std::string	val = this->_to_parse.substr(len, end_of_head - len - offset);
			// check if val not empty and the begin is properly established
			if ((val.empty() || this->_to_parse[len] == '\r') && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: value of header empty. $$$$$" << std::endl;
				this->_status = 400;
			}
			//go to uppercase the header for comp
			for (size_t i = 0; head[i]; i++)
				tmp += std::toupper(head[i]);
			std::replace(tmp.begin(), tmp.end(), '-', '_');
			// check if the header exist
			std::map<std::string, headerType>::iterator	it = this->_headers.find(tmp);
			if (it  != this->_headers.end())
			{
				// check if already set
				std::map<headerType, std::string>::iterator	it_find = this->_reqHeaders.find(it->second);
				if (it_find != this->_reqHeaders.end() && this->_status == 200)
				{
					//for debug
					std::cerr << "$$$$$ Error: double header detected. $$$$$" << std::endl;
					this->_status = 400;
				}
				// record the header/value
				this->_reqHeaders.insert(std::make_pair(it->second, val));
			}
			this->setHeadersEnv(tmp, val);
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
*  @brief   Set the new header in _env.
*			record a new header in env of headers
*  @param   std::string &, std::string &
*  @return  void
*/
void	Request::setHeadersEnv(std::string const &header, std::string const &value)
{
	std::string	headTmp("HTTP_");
	headTmp += header;
	std::replace(headTmp.begin(), headTmp.end(), '-', '_');
	// check if not already recorded
	if (this->_env.count(headTmp) == 0)
		this->_env[headTmp] = value;
}

/*
*  @brief   Parse the URI.
*			check and recover CGI parameters
*  @param   void
*  @return  void
*/
void	Request::parseUri()
{
	std::string	cgi_param;
	std::string	uri_tmp;
	std::string	to_parse = this->_all_uri;
	size_t	len = to_parse.find_first_of('?');
	// recover CGI params
	if (len != std::string::npos)
		cgi_param = to_parse.substr(to_parse.find('?') + 1);
	uri_tmp = to_parse.substr(0, len);
	if (uri_tmp.find("..") != std::string::npos && this->_status == 200)
	{
		//for debug
		std::cerr << "$$$$$ Error: URI not correctly established $$$$$" << std::endl;
		this->_status = 400;
	}
	if (uri_tmp.size() > 1000 && this->_status == 200)
	{
		//for debug
		std::cerr << "$$$$$ Error: Uri too long. $$$$$" << std::endl;
		this->_status = 414;
	}
	// extract path and file of URI
	size_t	pos = uri_tmp.rfind('/');
	// check if path and uri is empty
	if (pos == std::string::npos && uri_tmp.empty() && this->_status == 200)
	{
		//for debug
		std::cerr << "$$$$$ Error: uri not set correctly. $$$$$" << std::endl;
		this->_status = 400;
	}
	std::string	path = uri_tmp.substr(0, pos + 1);
	// set/extract the path
	if (pos == std::string::npos && !uri_tmp.empty())
	{
		path = "/";
	}
	else
		path = uri_tmp.substr(0, pos + 1);
	// extract uri file name
	std::string	file = uri_tmp.substr(pos + 1, std::string::npos);
	this->_uri = std::make_pair(path, file);
	if (!cgi_param.empty())
	{
		// extract all cgi params
		while (!cgi_param.empty())
		{
			size_t		len_params = cgi_param.find('&');
			size_t		equal = cgi_param.find('=');
			// extract the name of parameter
			std::string	key = cgi_param.substr(0, equal);
			// check if not empty and the begin
			if ((key.empty() || key[0] == ' ') && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: param name not properly establish. $$$$$" << std::endl;
				this->_status = 400;
			}
			equal++;
			// extract value of parameter
			std::string	value = cgi_param.substr(equal, len_params - equal);
			// check if value not empty and the begin
			if ((value.empty() || key[0] == ' ') && this->_status == 200)
			{
				//for debug
				std::cerr << "$$$$$ Error: param vale not properly establish. $$$$$" << std::endl;
				this->_status = 400;
			}
			// record data
			this->_cgi.insert(std::make_pair(key, value));
			//delete segment recorded
			if (len_params && len_params != std::string::npos)
				cgi_param.erase(0, len_params + 1);
			else
				cgi_param.clear();
		}
	}
}

/*
*  @brief   Parsing the body.
*           Check and record body datas 
*  @param   void
*  @return  void
*/
void	Request::parseBody(size_t body_limit)
{
	// check if body is a Chunked transfer encoding
	if (this->_reqHeaders.find(TRANSFER_ENCODING) != this->_reqHeaders.end())
	{
		std::string	tmp;
		// record all body in a string without \r\n
		while (!this->_to_parse.empty())
		{
			size_t	end_of_body = this->_to_parse.rfind("\r\n");
			size_t	len = this->_to_parse.find("\r\n");
			if (len && len != end_of_body)
			{
				tmp += this->_to_parse.substr(0, len);
				if (tmp.size() >= body_limit && this->_status == 200)
				{
					//for debug
					std::cerr << "$$$$$ Error: body limits overflow. $$$$$" << std::endl;
					this->_status = 400;
				}
				this->_to_parse.erase(0, len + 2);	
			}
			else
				this->_to_parse.erase(0, len + 2);
		}
		this->_body = tmp;
	}
	else
	{
		// record body in a string 
		this->_body = this->_to_parse.substr(0, this->_to_parse.size() - 2);
		if (this->_body.size() >= body_limit && this->_status == 200)
		{
			//for debug
			std::cerr << "$$$$$ Error: body limits overflow. $$$$$" << std::endl;
			this->_status = 400;
		}
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
	this->_methods.clear();
	this->_headers.clear();
	this->_reqHeaders.clear();
	this->_all_uri.clear();
}
