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

			// destructor //
		~Request();
		
		//---- getters ----//
        std::string getRequest(void) const;
		
		//---- member methods ----//
			// parsing the request received
		void parsing(std::string &req);

	private:
		std::string		_request;
		// probably need a structure/map to put all the request key/values

		Request	&operator=(Request const &rhs);
};

#endif
