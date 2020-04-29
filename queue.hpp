/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:52:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/28 19:17:33 by jjosephi         ###   ########.fr       */
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
	}

	~queue()
	{
		node* h = head;
		node* tmp;
		for (size_t i = 0; i < capacity; i++)
		{
			tmp = h;
			al.destroy(tmp);
			h = h->next;
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
	}

	void pop()
	{
		node* curr;
		
		curr = head;
		head = head->previous;
		delete curr;
	}
};
}

#endif