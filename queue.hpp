/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:52:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/01 23:16:05 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

#include <iostream>
#include <cstdlib>

#define MAX_SIZE 10
namespace ft
{
	
template <typename T , class Allocator = std::allocator<T> >
class queue {
    private:
        size_t capacity;
		struct node
		{
			node* previous;
			T val;
		};
    	node* head;
		node* tail;
		Allocator al;

   	public:

	queue (T cont, Allocator all = Allocator())
	{
		head = new node();
		head->val = cont;
		head->previous = NULL;
		tail = head;
		al = all;
		capacity = 1;
	}

	~queue()
	{
		node* h = head;
		node* tmp;
		for (size_t i = 0; i < capacity; i++)
		{
			tmp = h;
			delete tmp;
			if (h->previous)
				h = h->previous;
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
		tail->previous = n;
		n->previous = NULL;
		tail = n;
		capacity++;
	}

	void pop()
	{
		node* curr;
		
		if (capacity >0)
		{
			
		curr = head;
		head = head->previous;
		delete curr;
		capacity--;
		}
	}
};
}

#endif
