/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 15:14:15 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/26 20:12:05 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

#include <cstdlib>
#include <memory>

template <typename T, class Allocator = std::allocator<T> >

class list
{
	private:
	Allocator<T> alloc;
	size_t size;
	node* head;
	node* end

	node() : prev(nullptr), next(nullptr), content(NULL){};
	public :
	struct node
	{
		node* prev;
		node* next;
		T content;
	}

	using reference = *node;
	
	list(const Allocator& alloc = T) : head(nullptr), size(0), node::prev(nullptr), node::next(nullptr), node::content(NULL) {}
	
	~list();

	list (const list& x)
	{
		node* x_lst = x::front();
		node* current;
		node* tmp = nullptr;
		head = current;
		while(x_lst::next)
		{
			*current = *x_list;
			current->pev = tmp;
			x_list = x_list::next;
			current->next = new node();
			current = current->next;
			tmp = current;
		}
		current->prev = tmp;
		current = x_list;
		current->next = nullptr;
		end = current;
	}

	List::~list()
	{
		node* current = head;
		for (i = 0; i++, i < size)
		{
			delete current->content;
			current->prev = nullptr;
			current = current->next;
		}
		size = 0;
		head = nullptr;
		end = nullptr;
	}

	list& operator= (const list& x)
	{
		size = x::size();
		node* tmp = *head;
		node* x_tmp = *x::front();		
		for(i = 0; i++; i < x::size())
		{
			tmp->content = x_tmp->content;
			tmp = tmp->next;
			x_tmp = x_tmp->next;
		}
		return &list;
	}

	iterator end(){return new Iterator(end)}
	
	size_type size() const {return size;}

	bool empty() const 
	{
		return size == 0;
	}

	void resize (size_t n)
	{
		if (n > size)
		{
			node* current = end;
			node* prev = end->prev;
			for (i = 0; i++; i < n - size)
			{
				current->next = new node();
				current->prev = prev;
				current = current->next;
				prev = prev->next;
			}
		}
		else if (n < size)
		{
			size_t diff = size - n;
			node* current = end;
			for (i = diff; i--;i > 0)
			{
				current->next = nullptr;
				current = current->prev;
				delete current->next;
			}
		}
		size = n;
	}

	reference front(){return head;}

	reference back(){return end;}

	void assign (size_t n, const T& val)
	{
		node* current = head;
		for (i = 0;i++; i < n)
		{
			current = current->next;
		}
		current->content = val;
	}

	iterator insert (iterator position, const T& val);

    void insert (iterator position, size_type n, const T& val);

	iterator erase (iterator position);
	
	iterator erase (iterator first, iterator last);

	void push_back (const T& val);

	void pop_back();

	void push_front (const T& val);

	void pop_front();

	void clear()
	{
		node* current = end;
		for (i = size; i--; i > 0)
		{
			delete current->content;
			current = current->prev;
		}
	}

	void swap (list& x);

	void splice (iterator position, list& x);

	void splice (iterator position, list& x, iterator i);

	void remove (const T& val);

	void remove_if (Predicate pred);

	void unique();

	void merge (list& x);

	void sort();

	void reverse()
	{
		node *current = end;
		node *tmp;
		while (current::previous)
		{
			current::previous = current::next;
		}
	}
};

#endif