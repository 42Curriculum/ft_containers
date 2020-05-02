/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 15:14:15 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/01 02:36:36 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

#include <cstdlib>
#include <memory>
#include <list>

namespace ft
{
	
template <typename T, class Allocator = std::allocator<T> >

class list
{
	private:
	Allocator alloc;
	size_t sizes;
	struct node
	{
		node* prev;
		node* next;
		T content;
	};
	node* head;
	node* tail;

	public :

class Iterator
{

private:
    list::node* curr;
public:
	size_t i;
    Iterator(){curr = new node();}  
    Iterator(list::node* n)
	{
		curr = n;
		i = 0;
	}
	
    T*			operator->()        {return  &(curr->content);}

    Iterator&	operator++()
	{
		curr = curr->next;
		return *this;}
    Iterator&	operator--()       {curr = curr->prev; return *this;}
	bool		operator!= (Iterator &r) {return (curr->content != r.curr->content );}
    bool		operator== (Iterator &r) {return curr->content == r->curr->content;}
};
	list(const Allocator& allocator = Allocator())
	{
		head = new node();
		head->next = NULL;
		head->content = 0;
		head->prev = NULL;
		alloc= allocator;
		sizes = 0;
	}


	list(size_t n, T val)
	{
		head = new node();
		head->next = NULL;
		head->content = val;
		head->prev = NULL;
		tail = head;
		alloc = Allocator();
		for(size_t i = 0; i < n - 1;i++)
		{
			push_back(val);
		}
		sizes = n;

	}

	list (const list& x)
	{
		node* x_lst = x.front();
		node* current = new node;
		node* tmp = NULL;
		head = current;
		while(x_lst->next!= NULL)
		{
			*current = *x_lst;
			current->pev = tmp;
			x_lst = x_lst->next;
			current->next = new node();
			current = current->next;
			tmp = current;
		}
		current->prev = tmp;
		current = x_lst;
		current->next = nullptr;
		tail = current;
	}

	~list()
	{
		node* current = head;
		for (size_t i = 0;i < sizes;i++)
		{
			current->prev = NULL;
			current = current->next;
		}
		sizes = 0;
		head = NULL;
		tail = NULL;
	}

	list& operator= (const list& x)
	{
		sizes = x.size();
		node* tmp = *head;
		node* x_tmp = *x.front();		
		for(size_t i = 0; i++; i < x.size())
		{
			tmp->content = x_tmp->content;
			tmp = tmp->next;
			x_tmp = x_tmp->next;
		}
		return &this;
	}
	Iterator begin()
	{
		Iterator it(head);
		return it;
	}
	
	Iterator end()
	{
		Iterator it(tail);
		return it;
	}
	
	size_t size() const {return sizes;}

	bool empty() const 
	{
		return sizes == 0;
	}

	void resize (size_t n)
	{
		if (n > sizes)
		{
			node* current = tail;
			node* prev = tail->prev;
			for (size_t i = 0;i < n - sizes; i++)
			{
				current->next = new node();
				current->prev = prev;
				current = current->next;
				prev = prev->next;
			}
		}
		else if (n < sizes)
		{
			size_t diff = sizes - n;
			node* current = tail;
			for (size_t i = 0; i < diff; i++)
			{
				current->next = NULL;
				current = current->prev;
				delete current->next;
			}
			tail = current;
		}
		sizes = n;
	}

	void assign (size_t n, const T& content)
	{
		node* current = head;

		if (n > sizes)
			resize(n);
		for (size_t i = 0; i < n; i++)
		{
			current = current->next;
		}
		current->content = content;
	}

	Iterator insert(Iterator position, T& content)
	{
		node* tmp = head;
		for (size_t i = 0; i < position.i; i++)
			tmp = tmp->next;
		node* n = new node;
		n->content = content;
		tmp->next->prev = n;
		tmp->next = n;
	}
	
    void insert(Iterator position, size_t n, const T& content)
	{
		node* tmp = head;
		for (size_t i = 0; i < position.i; i++)
			tmp = tmp->next;
		for (size_t i = 0; i < n; i++)
		{
			node* n = new node;
			tmp->next->prev = n;
			tmp->next = n;
			tmp = tmp->next;
			n->content = content;
		}
	}

	Iterator erase(Iterator position)
	{
		Iterator it = this->begin();
		node* tmp = head;
		for (; it.operator!=(position); it.operator++())
		{
			tmp = tmp->next;
		}
		if (tmp->prev)
			tmp->prev->next = tmp->next;
		else
			head = tmp->next;
		delete tmp;
		Iterator ret(tmp->next);
		sizes--;
		return ret;
	}
	
	Iterator erase(Iterator first, Iterator last)
	{
		node* tmp = head;
		node* hold;
		for (size_t i = 0; i < first.i; i++)
			tmp = tmp->next;
		for (; first != last; first++)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
			hold = tmp;
			tmp = tmp->next;
			new Iterator(hold);
		}
	}

	void push_back (const T& content)
	{
		
		node* n = new node();
		tail->next = n;
		n->content = content;
		n->prev = tail;
		n->next = NULL;
		tail = n;
		sizes++;
	}

	void pop_back()
	{
		if (sizes > 0)
		{
		node *curr = tail;
		curr = tail->prev;
		delete tail;
		tail = curr;
		sizes--;
		}
	}

	void push_front (const T& content)
	{
		node* f = new node();
		head->prev = f;
		f->next = head;
		f->content = content;
		head = f;
		sizes++;
	}

	void pop_front()
	{
		if (sizes > 0)
		{
		node* tmp = head->next;
		head->next = NULL;
		delete head;
		head = tmp;
		sizes--;
		}
	}

	void clear()
	{
		node* current = tail;
		for (size_t i = sizes; i > 0;i++)
		{
			delete current->content;
			current = current->prev;
		}
	}

	void swap (list& x)
	{
		node* tmp = new node();
		node* tmps = new node();
		tmp->content = head->content;
		tmp->next = head->next;
		tmps->prev = tail->prev;
		tmps->content = tail->content;

		head = x.head;
		x.head = tmp;
		tail = x.tail;
		x.tail = tmps;
		
	
		size_t s = sizes;
		sizes = x.sizes;
		x.sizes = s;
	}

	void splice (Iterator position, list& x)
	{
		node* tmp = head;
		for (size_t i = 0; i < position.i; i++)
		{
			tmp = tmp->next;
		}
		if (tmp->next)
			tmp->next->prev = x.end();
		else
			tail = x.end();
		tmp->prev->next = x.begin();
	}
	
	void remove (const T& content)
	{
		size_t rem = 0;
		node *curr = head;
		for(size_t i = 0; i < sizes; i++)
		{
			if (curr->content == content)
			{
				node* tmp = curr;
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				rem++;
			}
			curr = curr->next;
		}
		sizes -= rem;
	}

	void unique()
	{
		T val;
		node* current = head;
		node* tmp;
		node* hold;
		val = current->content;
		for (size_t i = 0; i < sizes; i++)
		{
			if (!current->next)
			{
				tail = current;
				return ;
			}
			current = current->next;
			tmp = current;
			for(size_t n = 0; n < sizes - (i + 1); n++)
			{
				if (tmp->next)
					hold = tmp->next;
				if (tmp->content == val)
				{
					if (tmp->prev)
					{
						tmp->prev->next = tmp->next;
					}
					else
						head = tmp->next;
					if (tmp->next)
						tmp->next->prev = tmp->prev;
					else
						tail = tmp->prev;
					delete tmp;
					sizes--;
				}
				tmp = hold;
				if (tmp->next)
					tmp = tmp->next;
			}
			val = current->content;
		}
	}

	void merge (list& x)
	{
		node* curr = x.head;
	
		tail->next = curr;
		tail = x.tail;
		sizes += x.sizes;
 	}

	void sort()
	{
		T content;
		T tmp;
		node* current = head;
		node* sw;	
		for (size_t i = 0; i < sizes; i++)
		{
			sw = current;
			content = current->content;
			for (size_t n = 0; n <= sizes - i;n++)
			{
				if (sw->content < content)
				{
					tmp = content;
					content = sw->content;
					sw->content = tmp;
					current->content = content;
				}
				if (sw->next)
					sw = sw->next;
				else
					break ;
			}
			current = current->next;
		}
	}

	void reverse()
	{
		node *current = tail;
		node *tmp;
		tail = head;
		head = current;
		while (current->prev)
		{
			tmp = current->prev;
			current->prev = current->next;
			current->next = tmp;
			current = current->next;
		}
	}
};
}

#endif