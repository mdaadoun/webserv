#pragma once
#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>
#include <string>
#include <map>

class Request
{
	public:
		//---- canonical form ----//
			// constructor //
		Request();

			// destructor //
		~Request();
		
		//---- getters ----//
        std::string getRequest(void) const;
		
		//---- member methods ----//
			// parsing the request received
		void parsing(std::string const &req);

	private:
		std::string							_to_parse;
		int									_status;


		std::map<std::string, std::string>	_request;

		//---- assignement operator ----//
		Request	&operator=(Request const &rhs);
};

#endif
