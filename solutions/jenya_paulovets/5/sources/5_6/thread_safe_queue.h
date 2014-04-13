#ifndef _TASK5_6_THREAD_SAFE_QUEUE_H_
#define _TASK5_6_THREAD_SAFE_QUEUE_H_

#include <cstdlib>
#include <boost/thread.hpp>

namespace task5_6
{
	template< typename T >
	class thread_safe_queue
	{
		struct element
		{
			T key;
			element *next;
			element *prev;

			element():key(T()), next(NULL), prev(NULL)
		{}
		}*first_, *last_;

		boost::mutex lock_;
		size_t size_;

	public:
		explicit thread_safe_queue();
		~thread_safe_queue();

		void push( const T& new_element );
		bool pop( T& result );

		bool empty() const;
		size_t size() const;
	};

	template< typename T >
	thread_safe_queue< T >::thread_safe_queue():first_(NULL), last_(NULL), size_(0)
	{}

	template< typename T >
	thread_safe_queue< T >::~thread_safe_queue()
	{
		element *temp = NULL;
		while(last_ != NULL)
		{
			temp = last_;
			last_ = last_->next;
			delete temp;
		}
	}

	template< typename T >
	void thread_safe_queue< T >::push( const T&  el)
	{
		boost::mutex::scoped_lock lock(lock_);
		if(last_ == NULL)
		{
			element *temp = new element();
			temp->key = el;
			last_ = first_ = temp;
			size_++;
		}
		else
		{
			element *temp = new element();
			temp->key = el;
			temp->next = last_;
			last_->prev = temp;
			last_ = temp;
			size_++;
		}
	}

	template< typename T >
	bool thread_safe_queue< T >::pop( T& el)
	{
		boost::mutex::scoped_lock lock(lock_);

		if(first_ != NULL)
		{
			el = first_->key;
			element *temp = first_;

			if(size_ == 1)
			{
				first_ = NULL;
				last_ = NULL;
			}
			else
				first_ = first_->prev;

			delete temp;

			size_--;
			return true;
		}

		return false;
	}

	template< typename T >
	bool thread_safe_queue< T >::empty() const
	{
		if(last_ == NULL ) return true;
		return false;
	}

	template< typename T >
	size_t thread_safe_queue< T >::size() const
	{
		return size_;
	}

}

#endif // _TASK5_6_THREAD_SAFE_QUEUE_H_
