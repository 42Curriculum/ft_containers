/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 15:14:15 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/27 04:25:45 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

#include <cstdlib>
#include <memory>
#include <list>

template <typename T>

class list
{
	class Iterator
{

private:
    node* node;
public:
    Iterator():        node(NULL){}   
    Iterator(node* n): node(n){}
	
    T*       operator->()        {return  &(this->node->content);}

    Iterator& operator++()       {node = this.node->next; return *this;}
    Iterator& operator--()       {node = this.node->prev; return *this;}
	Iterator operator++()       {Iterator (*this); operator++; return *it;}
	Iterator operator++()       {Iterator (*this); operator--; return *it;}
};
	private:
	Allocator<T> alloc;
	size_t size;
	node* head;
	node* end

	node() : prev(nullptr), next(nullptr), content(NULL){};
	public :
	struct node
	{F
		node* prev;
		node* next;
		T content;
	}

	list(const Allocator& alloc = T) : head(nullptr), size(0), node->prev(nullptr), node->next(nullptr), node->content(NULL) {}
	
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
	Iterator begin(return new Iterator(head));
	
	Iterator end(){return new Iterator(end)}
	
	size_t size() const {return sizes;}

	bool empty() const 
	{
		return sizes == 0;
	}

	void resize (size_t n)
	{
		if (n > sizes)
		{
			node* current = end;
			node* prev = end->prev;
			for (i = 0; i++; i < n - sizes)
			{
				current->next = new node();
				current->prev = prev;
				current = current->next;
				prev = prev->next;
			}
		}
		else if (n < sizes)
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
		sizes = n;
	}

	void assign (size_t n, const T& val)
	{
		node* current = head;
		for (i = 0;i++; i < n)
		{
			current = current->next;
		}
		current->content = val;
	}

    void insert (Iterator position, size_t n, const T& val);

	Iterator erase (Iterator position);
	
	Iterator erase (Iterator first, Iterator last);

	void push_back (const T& val)
	{
		end->next = new node();
		end->next->content = val;
		end->next->prev = end;
		end = end->next;
	}

	void pop_back()
	{
		node *curr = end;
		curr = end->prev;
		delete end;
		end = curr;
	}

	void push_front (const T& val)
	{
		node* f = new node();
		front->prev = f;
		f->next = front;
		f->content = val;
		front = f;
	}

	void pop_front()
	{
		node* tmp = front->next;
		front->next = nullptr;
		delete front;
		tmp = front;
	}

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
	{
		node* tmp;
		node* xtmp = x.front();
		tmp = head;
		T ctm;
		for (i = 0; i < x.size(); i++)
		{
			ctm = xtmp->content;
			xtmp->content = tmp->content;
			tmp->content = ctm;
			tmp = tmp->next;
			xtmp = xtmp->next;
		}
	}

	void splice (Iterator position, list& x)
	{
		node* tmp = position->next;
		position->next = x.front();
		tmp->prev = position->next;
		position->node->end = x.back();
	}

	void splice (Iterator position, list& x, Iterator i)
	{
		
	}

	void remove (const T& val)
	{
		size_t rem = 0;
		node *curr = head;
		for( i = 0; i < sizes; i++)
		{
			if (curr->content == val)
			{
				node* tmp = curr;
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				rem++;
			}
			curr = curr->next;
		}
		size -= rm;
	}

	void remove_if (Predicate pred);

	void unique()
	{
		T val;
		node* current = head;		
		for (size_t i = 0; i < sizes)
		{
			node* sw = current;
			val = current->content;
			for (size_t i = 0; i < sizes)
			{
				node *tmp = sw->next;
				if (sw->content == val)
				{
					sw->prev->next = sw->next;
					sw->next->prev =  sw->prev;
					delete sw->content;
				}
				sw = tmp;
			}
			current->content = val;
			current = current->next;
		}
	}

	void merge (list& x)
	{
		end->next = x.front();
		this.sort();
		x->front = nullptr;
		x.resize(0);
	}

	void sort()
	{
		T val;
		node* current = head;		
		for (size_t i = 0; i < sizes)
		{
			node* sw = current;
			val = current->content;
			for (size_t i = 0; i < sizes)
			{
				if (sw->content < val)
				{
					T tmp = val;
					val = sw->content;
					sw->content = tmp;
				}
				sw = sw->
			}
			current->content = val;
			current = current->next;
		}
	}

	void reverse()
	{
		node *current = end;
		node *tmp;
		while (current->previous)
		{
			tmp = current->previous;
			current->previous = current->next;
			current->next = tmp;
			current = current->next;
		}
	}
};

#endif