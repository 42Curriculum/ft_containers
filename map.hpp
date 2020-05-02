/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 04:17:50 by jjosephi          #+#    #+#             */
/*   Updated: 2020/05/01 23:17:27 by jjosephi         ###   ########.fr       */
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
		class Iterator
		{
		private:
			map::elem *current;
		public:
			size_t i;
			Iterator(){current = new elem(); i = 0;}
			Iterator(map::elem* n){current = n;}
			
			T*       operator->()        {return  &(this->current->key);}

			Iterator& operator++()       {this->current = this->current->next; return *this;}
			Iterator& operator--()       {this->current = this->current->prev; return *this;}
			bool operator!=(Iterator &r) const {return this->current->key != r.current->key;}
			bool operator==(Iterator &r) const {return this->current->key == r.current->key;}
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
		map (const Compare& comp = Compare(), const Alloc& all = Alloc()) 
		{
			head = NULL;
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
			for (; h.operator!=(tail); h.operator++())
			{
				el->key = h->key;
				el->value = h->val;
				el->next = new elem();
				el = el->next;
			}
			el->next = NULL;
			len = x.len;
			tail = el;
		}

		~map()
		{
			elem* tmp;
			
			for (size_t i = 0; i < len;i++)
			{
				tmp = head;
				head = head->next;
				delete tmp;
			}
		}

		map& operator= (map& x)
		{
			len = x.size();
			elem* tmp = head;
			elem* x_tmp = x.head;	
			for(size_t i = 0;i < x.size(); i++)
			{
				tmp->key = x_tmp->key;
				tmp->value = x_tmp->value;
				tmp = tmp->next;
				x_tmp = x_tmp->next;
			}
			return *this;
		}

		T operator[] (Key k)
		{
			elem* el = head;
			for (size_t i = 0; i < len; i++)
			{
				if(el->key == k)
					return el->value;
				if(el->next)
					el = el->next;
			}
			insert(k, 0);
			return el->value;
		}
		
		size_t count (const Key& k) 
		{
			size_t i = 0;
			elem* el = head;
			while(i < len)
			{
				if (el->key == k)
					return 1;
				el = el->next;
				i++;
			}
			return 0;
		}
		
		Iterator  insert (Key key, T val)
		{
			if (!head)
			{
				elem* h = new elem();
				head = h;
				head->key = key;
				head->value = val;
				tail = head;
				Iterator it(head);
				len++;
				return it;
			}
			elem* tmp = head;
			for (size_t i = 0; i < len; i++)
				if(tmp->next)
					tmp = tmp->next;
			elem* n = new elem;
			n->key = key;
			n->value = val;
			tmp->next = n;
			n->prev = tmp;
			tail = n;
			Iterator it(tail);
			len++;
			return it;
		}
		
		Iterator insert (Iterator position, const T val)
		{
			elem* el = head;
			for (size_t i = 0; i < len; i++)
			{
				if (el->key == position)
					return Iterator(el);
				el = el->next;
			}
			while (!cmp(el->value, val))
			{
				el = el->next;
			}
			elem* n = new elem();
			n->key = position->elem->key;
			n->value = val;
			el->next->prev = n;
			el->next = n;
			Iterator it(el);
			len++;
			return it;
		}
		
		size_t size() const {return len;}

		bool empty() const {return len == 0;}
		
		Iterator begin() {Iterator it(head);  return it;}

		Iterator end(){Iterator it(tail); return it;}

		reverse_Iterator rbegin(){reverse_Iterator rit(tail);return rit;}

		reverse_Iterator rend(){reverse_Iterator rit(head); return rit;}

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
			len--;
		}

		size_t erase (const Key& k)
		{
			elem* el = head;
			for(size_t i = 0; i < len; i++)
			{
				if (el->key == k)
				{
					if(el->next)
						el->next->prev = el->prev;
					if (el->prev)
						el->prev->next = el->next;
					delete el;
					len--;
					return 1;
				}
				el = el->next;
			}
			return 0;
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
				if (el->next)
				{
					tmp = el->next;
					el->next->prev = el->prev;
				}
				if (el->prev)
					el->prev->next = el->next;
				delete el;
				el = tmp;
			}
			head = NULL;
			tail = head;
			len = 0;
		}
		
		void swap (map& x)
		{
			
			elem* tmp = new elem();
			elem* tmps = new elem();
			
			tmp->value = head->value;
			tmp->key = head->key;
			tmp->next = head->next;
			
			tmps->prev = tail->prev;
			tmps->value = tail->value;
			tmps->key = tail->key;

			head = x.head;
			x.head = tmp;
			tail = x.tail;
			x.tail = tmps;
			
		
			size_t s = len;
			len = x.len;
			x.len = s;
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
