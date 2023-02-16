#pragma once
#ifndef RESPONSE_HPP
# define RESPONSE_HPP

//#include "../request/Request.class.hpp"
#include <iostream>

class Response
{
	public:
		//---- canonical form ----//
			// constructors //
		Response();

			// destructor //
		~Response();

//        void buildResponse(Request & req) const;
        std::string getResponse(void) const;
	private:
		std::string		_response;

		Response	&operator=(Response const &rhs);
};

#endif
