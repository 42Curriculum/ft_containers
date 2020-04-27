/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 04:17:50 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/27 04:23:37 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <memory>
#include <iostream>

template < typename Key, typename T,class Compare = std::less<Key>, class Alloc = std::allocator<T> >
	class map
	{
		private:
		struct elem
		{
			Key key;
			T value;	
			elem* next;
			elem* prev;
		};
	};