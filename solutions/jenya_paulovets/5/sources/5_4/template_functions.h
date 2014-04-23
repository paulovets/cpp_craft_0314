#ifndef _TASK5_4_TEMPLATE_FUNCTIONS_H_
#define _TASK5_4_TEMPLATE_FUNCTIONS_H_

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>

namespace task5_4
{

	template< bool delete_first, typename Container>
	typename boost::enable_if_c< !boost::is_pointer < typename Container::value_type>::value, void >::type clear_container( Container& C)
	{
		C.clear();
	}

	template< bool delete_first, typename Container>
	typename boost::enable_if_c< boost::is_pointer < typename Container::value_type>::value, void >::type clear_container( Container& C)
	{
		if( delete_first)
		{
			for(typename Container::iterator it = C.begin(); it != C.end(); it++)
			{
				delete *it;
			}
		}
		C.clear();
	}

	template<bool delete_first, bool delete_second, typename Container>
	typename boost::enable_if_c<!boost::is_pointer<typename Container::key_type>::value &&
	!boost::is_pointer<typename Container::mapped_type>::value, void>::type clear_container(Container &C)
	{
		C.clear();
	}


	template<bool delete_first, bool delete_second, typename Container>
	typename boost::enable_if_c<boost::is_pointer<typename Container::key_type>::value &&
	!boost::is_pointer<typename Container::mapped_type>::value>::type clear_container(Container &C)
	{
		if (delete_first)
		{
			for(typename Container::iterator it = C.begin(); it != C.end(); it++)
			{
				delete it->first;
			}
		}
		C.clear();
	}


	template<bool delete_first, bool delete_second, typename Container>
	typename boost::enable_if_c<!boost::is_pointer<typename Container::key_type>::value &&
	boost::is_pointer<typename Container::mapped_type>::value>::type clear_container(Container &C)
	{
		if (delete_second)
			for(typename Container::iterator it = C.begin(); it != C.end(); it++)
			{
				delete it->second;
			}
		C.clear();
	}

	template<bool delete_first, bool delete_second, typename Container>
	typename boost::enable_if_c<boost::is_pointer<typename Container::key_type>::value &&
	boost::is_pointer<typename Container::mapped_type>::value, void>::type clear_container(Container &C)
	{
		if (delete_first)
			for(typename Container::iterator it = C.begin(); it != C.end(); it++)
			{
				delete it->first;
			}
		if (delete_second)
			for(typename Container::iterator it = C.begin(); it != C.end(); it++)
			{
				delete it->second;
			}
		C.clear();
	}
}


#endif // _TASK5_4_TEMPLATE_FUNCTIONS_H_

