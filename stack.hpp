/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjosephi <jjosephi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/26 21:52:05 by jjosephi          #+#    #+#             */
/*   Updated: 2020/04/28 19:17:26 by jjosephi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
#include <cstdlib>

#define MAX_SIZE 10
namespace ft
{
	
template <typename T>
class Stack {
    private:
        T *arr;
        size_t top_index;
        size_t capacity;

    public:

        Stack(size_t max_size = 10);

        ~Stack();

        Stack(const Stack &old_T);

        Stack<T>& operator=(Stack<T> const &old_T);
        
        void push(T);
        void pop();
        bool empty();
        T top();
        size_t size();
};

template <typename T>
Stack<T>::Stack(size_t max_size) {
    arr = new T[max_size];
    top_index = -1;
    capacity = max_size;
}
template <typename T>
Stack<T>::~Stack() {
    delete arr;
}

template <typename T>
Stack<T>::Stack(const Stack<T> &old_T) {
    top_index = old_T.top_index;
    capacity = old_T.capacity;
}
template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> const &old_T) {
    if (this != &old_T) {
        if (capacity != old_T.capacity) {
            delete arr;
            capacity = old_T.capacity;
            arr = new T[old_T.capacity];
            top_index = old_T.top_index;
        }
        for(size_t i = 0; i < capacity; i++) {
			arr[i] = old_T[i];
		}
    }
    return *this;
}

template <typename T>
void Stack<T>::push(T elem) {
    top_index++;
    arr[top_index] = elem;
}

template <typename T>
void Stack<T>::pop() {
	if(capacity > 0)
	{
    	destroy(arr[top_index]);
    	top_index--;
	}
}

template <typename T>
bool Stack<T>::empty() {return capacity == 0;}

template <typename T>
T Stack<T>::top() {
    if (capacity > 0)
        return arr[top_index];  
} 

template <typename T>
size_t Stack<T>::size() {
    return (size);
}
}

#endif