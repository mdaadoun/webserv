/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ComSocket.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlafont <tlafont@student.42angouleme.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:23 by tlafont           #+#    #+#             */
/*   Updated: 2023/02/22 09:12:17 by tlafont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sockets/ComSocket.class.hpp"

/*
*  @brief   Overload constructor.
*           Initialize the socket with parameters
*  @param   int
*  @return  void
*/
ComSocket::ComSocket(int fd, std::string serverName): _addr(), _fd_com()
{
	// Accept a connection on a socket
	this->fd = accept(fd, (struct sockaddr*)&addr, &size);
	testConnection(this->_fd_com);
	// set non_bolcking the socket
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error: set non-blocking ComSocket: " << serverName << std::endl;
		throw std::runtime_error(strerror(errno));
	}
	// set options in socket for reuse address
	int x = 1;
	int opt = setsockopt(this->_fd_com, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(x));
	testConnection(opt, std::string("Error: set option Comsocket."));
}

/*
*  @brief   Copy constructor.
*           copy other socket in this socket
*  @param   ComSocket &
*  @return  void
*/
ComSocket::ComSocket(ComSocket const &rhs)
{
	*this = rhs;
}

/*
*  @brief   Assignment operator.
*           copy other socket in this socket
*  @param   ComSocket &
*  @return  ComSocket &
*/
ComSocket	&ComSocket::operator=(ComSocket const &rhs)
{
	(void)rhs;
	return (*this);
}

/*
*  @brief	Get string IPP address .
*           return a string with address and port 
*  @param	void
*  @return	std::string
*/
std::string	ComSocket::getIPP() const
{
	std::string	host = inet_ntoa(addr.sin_addr);
	int			port = htons(addr.sin_port);
	std::ostringstream oss;
    oss << port;
	return (host + ':' + oss.str());
}

/*
*  @brief	Get fd.
*           return the file descrioptor of ComSocket
*  @param	void
*  @return	int
*/
int	ComSocket::getFdSocket() const
{
	return (this->_fd_com);
}

/*
*  @brief	Test _fd_com .
*           Confirm  data properly established
*  @param	int, std::string
*  @return	void
*/
void	ComSocket::testConnection(int data, std::string const &err)
{
	if (data < 0)
	{
		std::cout << err << std::endl;
		throw std::runtime_error(strerror(errno));
	}
}

/*
*  @brief   Destructor.
*           Destroy all member objects
*  @param   void
*  @return  void
*/
ComSocket::~ComSocket()
{
	close(this->_fd_com);
	this->_fd_com = -1;
}
