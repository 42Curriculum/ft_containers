/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 04:17:50 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/28 19:17:01 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <memory>
#include <iostream>

namespace ft
{
	
template <typename Key, typename T,class Compare = std::less<Key>, class Alloc = std::allocator<T> >
	class map
	{
		class Iterator
		{
			private:
    		struct elem
			{
				Key key;
				T val;
				elem* next;
				elem* prev;
			};
			elem *current;
		public:
			size_t i;
		Iterator(){current = new elem(); i = 0;}
		Iterator(elem* n): current(n){}
		
		T*       operator->()        {return  &(this->elem->key);}

		Iterator& operator++()       {this->current = this->current->next; return *this;}
		Iterator& operator--()       {this->current = this->current->prev; return *this;}
		bool operator!=(Iterator &r) const {return this->current->key != r->elem->key;}
		bool operator==(Iterator &r) const {return this->current->key == r->elem->key;}
		};
		
		class reverse_Iterator
		{
			private:
    		struct elem
			{
				Key key;
				T val;
				elem* next;
				elem* prev;
			};
			elem* current;
		public:
			size_t i;
		reverse_Iterator(){current= new elem();}
		reverse_Iterator(elem* n){current = new elem(n); i = 0;}
		
		T*       operator->()        {return  &(this->current->key);}

		reverse_Iterator& operator++()       {current = current->prev; return *this;}
		reverse_Iterator& operator--()       {current = current->next; return *this;}
		bool operator!=(reverse_Iterator &r) const {return current->key != r->current->key;}
		bool operator==(reverse_Iterator &r) const {return current->key == r->current->key;}
		};
		
		private:
		struct elem
		{
			Key key;
			T value;
			elem* next;
			elem* prev;
		};
		elem* head;
		elem* tail;
		Compare cmp;
		Alloc al;
		size_t len;
		
		public:
		map (const Compare& comp = Compare(), const Alloc& all = Alloc()) 
		{
			head = NULL;
			tail = NULL;
			cmp = comp;
			al = all;
			len = 0;
		}
		
		map (const map& x)
		{
			len = x->size();
			Iterator h = x->begin();
			Iterator end = x->end();
			this->al = x->al;
			this->cmp = x->cmp;
			elem* el = new elem();
			head = el;
			for (; h != tail; h++)
			{
				el->key = h->key;
				el->value = h->val;
				el->next = new elem();
				el = el->next;
			}
			el->next = NULL;
			tail = el;
		}

		~map()
		{
			Iterator first = this->begin();
			Iterator last = this->end();
			elem* tmp;
			for(; first != last; first++)
			{
				tmp = head->next;
				al.destroy(head);
				head = tmp;
			}
		}

		map& operator= (const map& x)
		{
			Iterator h = x->begin();
			Iterator end = x->end();
			elem* el = new elem();
			head = el;
			for (size_t i = 0; i < x->len; i++)
			{
				el->key = h->key;
				el->value = h->val;
				if (!el->next)
					el->next = new elem();
				el = el->next;
			}
			if (x->len < len)
			{
				for (size_t i = x.size; i < len; i++)
				{
					elem* tmp;
					tmp = el;
					el = el->next;
					al.destroy(tmp);
				}
			}
			len = x->len();
			el->next = NULL;
			tail = el;
		}

		T& operator[] (const Key& k)
		{
			elem* el = head;
			while(el->next != NULL && el->key != k)
			{
				el = el->next;
			}
			return el->val;
		}
		
		size_t count (const Key& k) 
		{
			elem* el = head;
			while(el->next != NULL)
			{
				if (el->key == k)
					return 1;
			}
			return 0;
		}
		
		Iterator  insert (Key key, T& val)
		{
			elem* el = head;
			for (size_t i = 0; i < len; i++)
			{
				if (el->key == key)
					return Iterator(el);
				el = el->next;
			}
			while (!cmp(el->val, val))
			{
				el = el->next;
			}
			elem* n = new elem();
			n->key = key;
			n->val = val;
			el->next->prev = n;
			el->next = n;
			len++;
		}
		
		Iterator insert (Iterator position, const T& val)
		{
			elem* el = head;
			for (size_t i = 0; i < len; i++)
			{
				if (el->key == position)
					return Iterator(el);
				el = el->next;
			}
			while (!cmp(el->val, val))
			{
				el = el->next;
			}
			elem* n = new elem();
			n->key = position->elem->key;
			n->val = val;
			el->next->prev = n;
			el->next = n;
			len++;
		}
		
		size_t size() const {return len;}

		bool empty() const {return len == 0;}
		
		Iterator begin() {return Iterator(head);}

		Iterator end(){return Iterator(tail);}

		reverse_Iterator rbegin(){return reverse_Iterator(tail);}

		reverse_Iterator rend(){return reverse_Iterator(head);}

	    void erase (Iterator position)
		{
			elem* el = head;
			
			for (size_t i = 0; i < position->i; i++)
			{
				el = el->next;
			}
			el->next->prev = el->prev;
			el->prev->next = el->next;
			al.destroy(el);
		}

		size_t erase (const Key& k)
		{
			elem* el = head;
			for(size_t i = 0; i < len; i++)
			{
				if (el->key == k)
				{
					el->next->prev = el->prev;
					el->prev->next = el->next;
					al.destroy(el);
					len--;
					return 1;
				}
			}
		}

		void erase (Iterator first, Iterator last)
		{
			elem* el = head;
			elem* tmp;
			for(size_t i = 0; i < first->i; i++)
			{
				el = el->next;
			}
			for(;first != last; first++)
			{
				tmp = el->next;
				el->next->prev = el->prev;
				el->prev->next = el->next;
				al.destroy(el);
				el = tmp;
				len--;
			}
		}

		void clear()
		{
			elem* el = head;
			elem* tmp;
			for(size_t i = 0;i < len; i++)
			{
				tmp = el->next;
				el->next->prev = el->prev;
				if (el->prev)
					el->prev->next = el->next;
				al.destroy(el);
				el = tmp;
			}
			head = NULL;
			tail = head;
			len = 0;
		}
		
		void swap (map& xmap)
		{
			elem* el = head;
			elem* x = xmap->begin();
			elem* tmp = el;
			size_t less = (len < x->size()) ? len : x->size();
			for(size_t i = 0; i < less; i++)
			{
				tmp = el;
				el->val = x->val;
				el->key = x->key;
				x->val == tmp->val;
				x->key = tmp->key;
				x = x->next;
				el = el->next;
			}
		}
		
		Iterator find (const Key& k)
		{
			elem* el = head;
			while (el->key != k && el->next)
			{
				el = el->next;
			}
			if (el->key == k)
				return Iterator(el);
			return NULL;
		}
		
		Iterator lower_bound (const Key& k)
		{
			elem* el = head;
			while (el->next != NULL && !cmp(el->key, k))
				el = el->next;
			return Iterator(el);
		}
		
		Iterator upper_bound (const Key& k)
		{
			elem* el = head;
			while (el->next != NULL && !cmp(el->key, k))
				el = el->next;
			return Iterator(el);
		}
		
		Compare key_comp() const {return cmp;}

	};
}