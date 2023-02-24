#pragma once
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

//#include "../request/Request.class.hpp"
#include <iostream>
#include <string>

class Response
{
	public:
		//---- canonical form ----//
			// constructors //
		Response();

			// destructor //
		~Response();

		//---- getter ----//
        std::string getResponse(void) const;

		//---- member methods ----//
		void buildResponse(std::string &req);
	
	private:
		std::string		_response;

		Response	&operator=(Response const &rhs);
};

#endif
