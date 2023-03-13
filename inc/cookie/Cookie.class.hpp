/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cookie.class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fleblanc <fleblanc@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:31:35 by fleblanc          #+#    #+#             */
/*   Updated: 2023/03/13 15:52:15 by fleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOKIE_HPP
#define COOKIE_HPP

#include <map> // A voir

class	Cookie
{
	public:

		Cookie();
		Cookie(const Cookie&);

		~Cookie();

		Cookie&	operator=(const Cookie&);




	private:

		std::map<std::string, std::string>	_cookie_content;
};

#endif
