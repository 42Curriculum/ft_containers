/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 00:03:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/25 19:43:40 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <cstdlib>
#include <vector>
#include <memory>

template <typename T, class Allocator = std::allocator<T> >
class vector
{
	class Iterator
{

private:
    vector<T>* v;
    int        i;
public:
    using value_type = T;
    using pointer    = T*;
    using reference  = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    Iterator():                    v(nullptr), i(0) {}   
    Iterator(Vector<T>* v, int i): v(v),       i(i) {}

    reference       operator*()             {return (*v)[i];}
    const reference operator*()       const {return (*v)[i];}
    pointer         operator->()            {return &((*v)[i]);}
    const pointer   operator->()      const {return &((*v)[i]);}
    reference       operator[](int m)       {return (*v)[i + m];}
    const reference operator[](int m) const {return (*v)[i + m];}


    Iterator& operator++()       {++i;return *this;}
    Iterator& operator--()       {--i;return *this;}
    Iterator  operator++(int)    {Iterator r(*this);++i;return r;}
    Iterator  operator--(int)    {Iterator r(*this);--i;return r;}

    Iterator& operator+=(int n)  {i += n;return *this;}
    Iterator& operator-=(int n)  {i -= n;return *this;}

    Iterator operator+(int n)   const {Iterator r(*this);return r += n;}
    Iterator operator-(int n)   const {Iterator r(*this);return r -= n;}

    difference_type operator-(Iterator const& r) const {return i - r.i;}

    bool operator<(Iterator const& r)  const {return i <  r.i;}
    bool operator<=(Iterator const& r) const {return i <= r.i;}
    bool operator>(Iterator const& r)  const {return i >  r.i;}
    bool operator>=(Iterator const& r) const {return i >= r.i;}
    bool operator!=(const Iterator &r) const {return i != r.i;}
    bool operator==(const Iterator &r) const {return i == r.i;}
};
private:
	size_t length;
	size_t capcity;
	T *ptr;
	Allocator<T> alloc;
public:
	using reference  = T&;
	
	vector(const Allocator& alloc = T) : ptr(NULL), length(0),capacity(0)){} //Constructor
	
	~vector();							//Destructor
	
	vector(const vector& cpy);			//Copy Constructor
	
	vector (size_type n, const T& val); //Fill Constructor


	
	vector::vector()
	{
		length = 0;
		capacity = 0;
		ptr = Allocator.allocate(len);
		it = Iterator();
	}

	vector::~vector()
	{
	//	delete[] ptr;
		ptr = Allocator.deallocate(ptr, length);
		ptr = nullptr;
		length = 0;
		capacity = 0;
	}

	vector::vector(const vector& cpy)
	{
		ptr = new T[cpy.capacity()];
        std::copy(&other[0], &other[other.size()], ptr);
        length = cpy.size();
	}

	vector::vector(size_type n, const T& val)
	{
		length = n;
		capacity = n;
		ptr = Allocator.allocate(n);
		if (n > 0)
			for (i = 0; i++; i <n)
				ptr[n] = val;
	}
	
	iterator begin(){return new Iterator(vector, 0);}// Returns an iterator pointing to the first element in the vector.
	
	iterator end(){return new Iterator(vector, length);}//Returns an iterator referring to the past-the-end element in the vector container.
	
	reverse_iterator rbegin();//Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
	
	reverse_iterator rend();//Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
	
	size_type size(){return length;}//Returns the number of elements in the vector.
	
	size_type max_size() {return ??;}//Returns the maximum number of elements that the vector can hold.
	
	bool empty() {return length == 0;}//is size 0?
	
	void resize (size_type n, value_type val = value_type());//Resizes the container so that it contains n elements.
	
	size_type capacity() {return capacity;} //Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
	
	void reserve (size_type n);//Requests that the vector capacity be at least enough to contain n elements.
	
	reference front() {return ptr[0]&;}//Returns a reference to the first element in the vector.
	
	reference back() {return ptr[length]&;}//back
	
	reference operator[] (size_type n){return ptr[n]&;}//Returns a reference to the element at position n in the vector container.
	
	vector& operator= (const vector& x); //Assigns new contents to the container, replacing its current contents, and modifying its size accordingly
	
	reference at (size_type n)//Position of an element in the container. OOR exceptions
	{
		if (n >= length)
			std::out_of_range("");
		else
			return ptr[n];
	}
	
	void assign (Iterator first, Iterator last);//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
	
	void assign (size_type n, const value_type& val);
	
	//The vector is extended by inserting new elements before the element at the specified position
	Iterator insert (Iterator position, const value_type& val);	
	
    void insert (Iterator position, size_type n, const value_type& val);

	//Removes from the vector either a single element (position) or a range of elements ([first,last)).
	Iterator erase (Iterator position);
	
	Iterator erase (Iterator first, Iterator last);
	
	void push_back (const value_type& val);//Adds a new element at the end of the vector, after its current last element
	
	void pop_back();//Removes the last element in the vector, effectively reducing the container size by one4
	
	void clear();//Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
	
	void swap (vector& x); //Exchanges the content of the container by the content of x, which is another vector object of the same type
	
};



#endif