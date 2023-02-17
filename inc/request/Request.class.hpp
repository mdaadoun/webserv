#pragma once
#ifndef REQUEST_HPP
# define REQUEST_HPP

#include <iostream>

class Request
{
	public:
		//---- canonical form ----//
			// constructors //
		Request();
		// Request with a constructor, then parsing
//		Request(string/char*);

			// destructor //
		~Request();

        void setRequest(std::string const &req);
		// void parseRequest();
        std::string getRequest(void) const;

	private:
		std::string		_request;
		// probably need a structure to put all the request key/values

		Request	&operator=(Request const &rhs);
};

#endif
