/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:52:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/01 23:16:56 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include <cstdlib>

#define MAX_SIZE 10
namespace ft
{
	
template <typename T , class Allocator = std::allocator<T> >
class stack {
    private:
        size_t capacity;
		struct node
		{
			node* next;
			T val;
		};
    	node* head;
		node* tail;
		Allocator al;

   	public:

	stack (T cont, Allocator all = Allocator())
	{
		head = new node();
		head->val = cont;
		head->next = NULL;
		tail = head;
		al = all;
		capacity = 1;
	}

	~stack()
	{
		node* h = head;
		node* tmp;
		for (size_t i = 0; i < capacity; i++)
		{
			tmp = h;
			delete tmp;
			if (h->next)
				h = h->next;
			else
				return  ;
		}
	}

	bool empty() {return capacity == 0;}
	
	size_t size() {return capacity;}
	
	T& front() {return head->val;}
	
	T& back() {return tail->val;}

	void push (const T& val)
	{
		node* n = new node();
		
		n->val = val;
		n->next = head;
		head = n;
		capacity++;
	}

	void pop()
	{
		node* curr;
		
		if (capacity >0)
		{
			
	
		curr = head;
			if (head->next)
			{
				head = head->next;
			}
		delete curr;
		capacity--;
		}
	}
};
}

#endif
