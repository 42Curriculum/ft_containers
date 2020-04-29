/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 00:03:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/29 02:12:55 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstdlib>
#include <memory>

namespace ft
{
	
template <typename T, typename Allocator = std::allocator<T> >
class vector
{
	class vect_Iterator
{

private:
    vector<T>* v;
    int        i;
public:
    vect_Iterator():                    v(NULL), i(0) {}   
    vect_Iterator(vector<T>* v, int i): v(v),       i(i) {}

    T&       operator*()             {return (*v)[i];}
    T*         operator->()            {return &((*v)[i]);}
    T&       operator[](int m)       {return (*v)[i + m];}


    vect_Iterator& operator++()       {++i;return *this;}
    vect_Iterator& operator--()       {--i;return *this;}
    vect_Iterator  operator++(int)    {vect_Iterator r(*this);++i;return r;}
    vect_Iterator  operator--(int)    {vect_Iterator r(*this);--i;return r;}

    vect_Iterator& operator+=(int n)  {i += n;return *this;}
    vect_Iterator& operator-=(int n)  {i -= n;return *this;}

    vect_Iterator operator+(int n)   const {vect_Iterator r(*this);return r += n;}
    vect_Iterator operator-(int n)   const {vect_Iterator r(*this);return r -= n;}

    bool operator<(vect_Iterator const& r)  const {return i <  r.i;}
    bool operator<=(vect_Iterator const& r) const {return i <= r.i;}
    bool operator>(vect_Iterator const& r)  const {return i >  r.i;}
    bool operator>=(vect_Iterator const& r) const {return i >= r.i;}
    bool operator!=(const vect_Iterator &r) const {return i != r.i;}
    bool operator==(const vect_Iterator &r) const {return i == r.i;}
	size_t index(){return i;}
};
class Reverse_vect_Iterator
{

private:
    vector<T>* v;
    int        i;
public:

   Reverse_vect_Iterator():                    v(NULL), i(0) {}   
   Reverse_vect_Iterator(vector<T>* v, int i): v(v),       i(i) {}

    T&       operator*()             {return (*v)[i];}
    T*         operator->()            {return &((*v)[i]);}
    T&       operator[](int m)       {return (*v)[i + m];}


   Reverse_vect_Iterator& operator++()       {--i;return *this;}
   Reverse_vect_Iterator& operator--()       {++i;return *this;}
   Reverse_vect_Iterator  operator++(int)    {vect_Iterator r(*this);--i;return r;}
   Reverse_vect_Iterator  operator--(int)    {vect_Iterator r(*this);++i;return r;}

   Reverse_vect_Iterator& operator+=(int n)  {i -= n;return *this;}
   Reverse_vect_Iterator& operator-=(int n)  {i += n;return *this;}

   Reverse_vect_Iterator operator+(int n)   const {vect_Iterator r(*this);return r -= n;}
   Reverse_vect_Iterator operator-(int n)   const {vect_Iterator r(*this);return r += n;}

    bool operator<(vect_Iterator const& r)  const {return i <  r.i;}
    bool operator<=(vect_Iterator const& r) const {return i <= r.i;}
    bool operator>(vect_Iterator const& r)  const {return i >  r.i;}
    bool operator>=(vect_Iterator const& r) const {return i >= r.i;}
    bool operator!=(Reverse_vect_Iterator &r) const {return i != r.i;}
    bool operator==(Reverse_vect_Iterator &r) const {return i == r.i;}
	size_t index(){return i;}
};
private:
	size_t sizes;
	size_t cap;
	T *ptr;
	Allocator al;
public:
	
	vector(Allocator& al = Allocator())
	{
		sizes = 0;
		cap = 0;
		ptr = al.allocate(sizes);
	}

	~vector()
	{
	//	delete[] ptr;
		al.deallocate(ptr, sizes);
		ptr = NULL;
		sizes = 0;
		cap = 0;
	}

	vector(const vector& cpy)
	{
		ptr = new T[cpy.capacity()];
        std::copy(&cpy[0], &cpy[cpy.size()], ptr);
        sizes = cpy.size();
	}

	vector(size_t n, const T& val)
	{
		sizes = n;
		cap = n;
		ptr = al.allocate(n);
		if (n > 0)
		{
			for (size_t i = 0; i < n; i++)
				ptr[i] = val;
		}
	}
	
	vect_Iterator begin(){return new vect_Iterator(this, 0);}// Returns an vect_Iterator pointing to the first element in the this.
	
	vect_Iterator end(){return new vect_Iterator(this, sizes);}//Returns an vect_Iterator referring to the past-the-end element in the vector container.
	
	
	size_t size(){return sizes;}//Returns the number of elements in the vector.
	
	bool empty() {return sizes <= 0;}//is sizes 0?
	
	void resize(size_t n)//Resizes the container so that it contains n elements.
	{
		if (sizes > n)
			sizes = n;
		else if (n <= cap)
			sizes = n;
		else
		{
			reserve(n);
			sizes = n;
		}
	}
	
	size_t capacity() {return cap;} //Returns the sizes of the storage space currently allocated for the vector, expressed in terms of elements.
	
	void reserve (size_t n)//Requests that the vector cap be at least enough to contain n elements.
	{
		if (n > cap)
		{
			T* tmp = al.allocate(n);
			std::copy(ptr, ptr + cap, tmp);
			delete[] ptr;
			ptr = tmp;
			cap = n;
		}
	}
	
	T& front() {return ptr[0];}//Returns a T& to the first element in the vector.
	
	T& back() {return ptr[sizes - 1];}//back
	
	T& operator[] (size_t n)
	{
		if (n > sizes)
			std::__throw_out_of_range("Index is out of range");
		return ptr[n];
	}//Returns a T& to the element at position n in the vector container.
	
	vector& operator= (vector& x) //Assigns new contents to the container, replacing its current contents, and modifying its sizes accordingly
	{
		if (x.size() > sizes)
			resize(x.size());
		for(size_t i = 0;i < x.size();i++)
		{
			ptr[i] = x[i];
		}
		sizes = x.size();
		return *this;
	}
	
	T& at (size_t n)//Position of an element in the container. OOR exceptions
	{
		if (n >= sizes)
			std::out_of_range("");
		return ptr[n];
	}
	
	
	//The vector is extended by inserting new elements before the element at the specified position
	void insert (size_t pos, size_t n, T val)
	{
		if (pos + n > cap)
			reserve((sizes = pos + n));
		else if(pos + n> sizes)
            sizes = pos + n;
		else if (cap == sizes)
		{
			reserve(sizes += n);
		}
		printf("End\n");
        for (size_t i = 0; i < n; i--)
        {
            ptr[pos + i + n] = ptr[pos + i] ;
        }
        for(size_t i = pos; i < pos + n; i++)
        {
            ptr[i] = val;
        }
	}
	
    void insert (size_t pos, const T& val)
	{
		if (pos > cap)
			reserve((sizes = pos));
		else if(pos > sizes)
            sizes = pos;
		else if (cap == sizes)
		{
			reserve(++sizes);
		}
        for(size_t i = sizes - 1; i > pos; i--)
        {
            ptr[i] = ptr[i-1];
        }
        ptr[pos] = val;
	}

	//Removes from the vector either a single element (position) or a range of elements ([first,last)).
	vect_Iterator erase (size_t n)
	{
		size_t i = n;
		vect_Iterator it;
		if (n > cap)
			return (it = vect_Iterator());
        for(i = n; i < sizes - 1; i++)
        {
            ptr[i] = ptr[i + 1];   //  Shift all the elements one step left, beginning from "pos+1"
        }
        sizes--;
		return (it = vect_Iterator(this, i));
	}
	
	Reverse_vect_Iterator rbegin()//Returns a reverse vect_Iterator pointing to the last element in the this (i.e., its reverse beginning).
	{
		return new Reverse_vect_Iterator(this, sizes);
	}
	
	Reverse_vect_Iterator rend()//Returns a reverse vect_Iterator pointing to the theoretical element preceding the first element in the this
	{
		return new Reverse_vect_Iterator(&this, -1);
	}
	
	void assign (vect_Iterator first, vect_Iterator last)//Assigns new contents to the vector, replacing its current contents, and modifying its sizes accordingly.
	{
		size_t n = first.index() - last.index();
		if (cap < n)
			reserve(n);
		else if (sizes < n)
			sizes = n;
		int i = 0;
		for (first; first != last; first++)
		{
			ptr[i] = first[i];
			i++;
		}
		return first;
	}
	
	void assign (size_t n, T val)
	{
		if (n > cap)
			reserve(n);
		for(size_t i = 0; i < n; i++)
		{
			ptr[i] = val;
		}
		if (sizes < n)
			sizes = n;
	}
	
	void push_back (T val) //Adds a new element at the end of the vector, after its current last element
	{
		if (sizes == cap)
			reserve(sizes + 1);
		ptr[++sizes - 1] = val;

	}
	
	void pop_back()//Removes the last element in the vector, effectively reducing the container sizes by one4
	{
		sizes--;
	}
	
	void clear()//Removes all elements from the vector (which are destroyed), leaving the container with a sizes of 0.4
	{
		for (size_t i = sizes; i > 0; i--)
			ptr[i] = 0;
		this->sizes = 0;
	}
	
	void swap (vector& x) //Exchanges the content of the container by the content of x, which is another vector object of the same type
	{
		T* tmp1 = ptr;
		size_t tmp_size = sizes;
		size_t tmp_cap = cap;
		
		ptr = x.ptr;
		x.ptr = tmp1;
		sizes = x.sizes;
		x.sizes = tmp_size;
		cap = x.cap;
		x.cap = tmp_cap;
	}
	
};
}

#endif