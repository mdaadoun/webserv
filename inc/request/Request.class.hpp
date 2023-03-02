#pragma once
#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <utility>

typedef enum e_METHOD
{
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	CONNECT,
	OPTIONS,
	TRACE,
	ERROR
}m_METHOD;

enum headerType
{
	ACCEPT_CHARSET,
	ACCEPT_LANGUAGE,
	ALLOW,
	AUTHORIZATION,
	CONNECTION,
	CONTENT_LANGUAGE,
	CONTENT_LENGTH,
	CONTENT_LOCATION,
	CONTENT_TYPE,
	DATE,
	HOST,
	LAST_MODIFIED,
	LOCATION,
	REFERER,
	REMOTE_USER,
	RETRY_AFTER,
	SERVER,
	TRANSFER_ENCODING,
	USER_AGENT,
	WWW_AUTHENTICATE
};

class Request
{
	public:
		//---- canonical form ----//
			// constructor //
		Request();

			// destructor //
		~Request();
		
		//---- getters ----//
        std::string 						getRequest(void) const;
		int									getStatus() const;
		std::string							getMethod() const;
		std::string							getUri() const;
		std::pair<int, int>					getVersion() const;
		std::map<headerType, std::string>	getHeaders() const;
		
		//---- member methods ----//
			// parsing the request received
		void 		parsing(std::string const &req);

	private:
		//---- member objects ----//
			//for parse the original request
		std::string							_to_parse;
			
			//for comp the methods
		std::map<std::string, m_METHOD>	_methods;
			//for comp the headers
		std::map<std::string, headerType>	_headers;
			

			//code status of request
		int									_status;
			//for record the header in request
		std::map<headerType, std::string>	_reqHeaders;
			//for record the method in header
		m_METHOD							_rec_method;
			// for record uri configuration
		std::string							_uri;
			// for record version
		std::pair<int, int>					_version;
			

			//for record all headers when is parsed
		std::map<std::string, std::string>	_env; //rename this

		//---- assignement operator ----//
		Request	&operator=(Request const &rhs);

		//---- private methods ----//
			// init datas
		void	initMapMethods();
		void	initMapHeaders();
			// parsing helpers
		void	parseHeader(std::string const &req);
				// parsing and rec start-line
		void	parseStartLineRequest();
		void	recoveryMethods(size_t end_of_req, size_t &len);
		void	recoveryUri(size_t end_of_req, size_t len);
		void	recoveryVersion(size_t end_of_req, size_t &len);
				// parsing and rec headers protocols
		void	parseProtocolHeaders();
				// record in _env
		void	setHeadersEnv(std::string const &header, std::string const &value);
};

std::ostream	&operator<<(std::ostream &oss, Request const &req);

#endif
