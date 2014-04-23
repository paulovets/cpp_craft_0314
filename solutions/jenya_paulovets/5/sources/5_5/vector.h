#ifndef _TASK5_5_VECTOR_H_
#define _TASK5_5_VECTOR_H_

#include <cstdlib>
#include <stdexcept>

namespace task5_5
{
	template< typename T >
	class vector
	{
		static const unsigned long defCap = 4;
		static const unsigned long defSize = 0;
		static const double k = 2;
		size_t size_;
		size_t capacity_;
		T *data_;

	public:
		typedef T* iterator ; // you could change this
		typedef const T* const_iterator; // you could change this

	public:
		explicit vector();
		vector( const vector& copy );
		vector& operator=( const vector& copy_from );

		void push_back( const T& value );
		void insert( const size_t index, const T& value );

		T& operator[]( const size_t index );
		const T& operator[]( const size_t index ) const;

		void resize( const size_t amount );
		void reserve( const size_t amount );

		size_t size() const;
		size_t capacity() const;
		bool empty() const;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;
		~vector();
	};

	// TODO, please realise the rest methods according to the tests

	template< typename T >
	vector< T >::vector():size_(defSize), capacity_(defCap)
	{
		data_ = new T[defCap];
	}

	template< typename T >
	vector< T >::vector( const vector< T >&  v): size_(v.size()), capacity_(v.capacity())
	{
		data_ = new T[capacity_];

		size_t i = 0;

		for(const_iterator it = v.begin(); it != v.end(); ++it, ++i)
		{
			data_[i] = *it;
		}
	}

	template< typename T >
	vector< T >::~vector()
	{
	delete []data_;
	}

	template< typename T >
	vector< T >& vector< T >::operator=( const vector< T >&  v)
	{
		if(capacity_ >= v.size())
		{
			size_ = v.size();

			size_t i = 0;

			for(const_iterator it = v.begin(); it != v.end(); ++it, ++i)
			{
				data_[i] = *it;
			}

		}
		else
		{
			delete []data_;
			size_ = v.size();
			capacity_ = v.capacity();
			data_ = new T[capacity_];

			size_t i = 0;

			for(const_iterator it = v.begin(); it != v.end(); ++it, ++i)
			{
				data_[i] = *it;
			}
		}

		return *this;
	}

	template< typename T >
	void vector< T >::push_back( const T& el)
	{
		if(size_ < capacity_)
		{
			data_[size_++] = el;
		}
		else
		{
			capacity_ = size_ * k;
			size_++;
			T* buf = new T[capacity_];

			for(size_t i = 0; i < size_ - 1; ++i)
			{
				buf[i] = data_[i];
			}
			buf[size_ - 1] = el;

			delete []data_;
			data_ = buf;
		}
	}

	template< typename T >
	void vector< T >::insert( const size_t pos, const T&  el)
	{
		if(pos <= size_ && pos >= 0)
		{
		if(size_ < capacity_)
		{
			size_t i = size_;
			while( i != pos)
			{
				data_[i] = data_[i - 1];
				i--;
			}
			size_++;
			data_[i] = el;
		}
		else
		{
			capacity_ = size_ * k;
			size_++;
			T* buf = new T[capacity_];
			size_t i = 0;

			while( i != pos)
			{
				buf[i] = data_[i];
				i++;
			}
			buf[i++] = el;
			while( i < size_)
			{
				buf[i] = data_[i - 1];
				i++;
			}

			delete []data_;
			data_ = buf;
		}
		}
		else
			throw std::out_of_range("Incorrect posistion");
	}

	template< typename T >
	T& vector< T >::operator[]( const size_t  pos)
	{
		return const_cast<T&>(static_cast<const vector< T >&>(*this).operator[](pos));
	}

	template< typename T >
	const T& vector< T >::operator[]( const size_t pos ) const
	{
		if(pos >= size_|| pos < 0 || size_ == 0 )
			throw std::out_of_range("Incorrect posistion");

		return data_[pos];
	}

	template< typename T >
	void vector< T >::resize( const size_t  ns)
	{
		if(ns <= size_) size_ = ns;
		else if( ns > size_ && ns <= capacity_)
		{
			size_t i = size_;
			while(i < ns)
			{
				T el = T();
				data_[i++] = el;
			}
			size_ = ns;
		}
		else
		{
			if(size_ <= 4) capacity_ = ns;
			else capacity_ = ns * k;

			T* buf = new T[capacity_];
			size_t i;

			for(i = 0; i < size_; ++i)
			{
				buf[i] = data_[i];
			}

			while(i < ns)
			{
				T el = T();
				buf[i++] = el;
			}
			size_ = ns;

			delete []data_;
			data_ = buf;
		}
	}
	template< typename T >
	void vector< T >::reserve( const size_t  s)
	{
		if( s > capacity_)
		{
			T* buf = new T[s];

			for(size_t i = 0; i < size_ ; ++i)
			{
				buf[i] = data_[i];
			}
			capacity_ = s;

			delete []data_;
			data_ = buf;
		}
	}

	template< typename T >
	size_t vector< T >::size() const
	{
		return size_;
	}
	template< typename T >
	size_t vector< T >::capacity() const
	{
		return capacity_;
	}
	template< typename T >
	bool vector< T >::empty() const
	{
		if(size_ == 0) return true;
		return false;
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::begin()
	{
		return const_cast<T*>(static_cast<const vector< T >&>(*this).begin());
	}
	template< typename T >
	typename vector< T >::iterator vector< T >::end()
	{
		return const_cast<T*>(static_cast<const vector< T >&>(*this).end());
	}
	
	template< typename T >
	typename vector< T >::const_iterator vector< T >::begin() const
	{
		return data_;
	}
	template< typename T >
	typename vector< T >::const_iterator vector< T >::end() const
	{
		return data_ + size_;
	}
}

#endif // _TASK5_5_VECTOR_H_

