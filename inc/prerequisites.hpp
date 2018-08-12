#pragma once

#include <assert.h>
#include <memory>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <exception>
#include <thread>
#include <mutex>
#include <condition_variable>

#ifdef WIN32
#	ifdef API_DEV_MOD
#		define	LIGHT_API	__declspec(dllexport)
#	else
#		define	LIGHT_API	__declspec(dllimport)
#	endif
#else
#	define LIGHT_API
#endif


#define BEGIN_TRY()					try{
#define CTA()		}catch(...){throw;}

namespace Light
{
	typedef unsigned char		byte;
	typedef int					int32;
	typedef long long			int64;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;
	typedef void				*pvoid;
	typedef size_t				index;
	typedef size_t				uintx;

	template<typename _Type>
	inline void safe_delete(_Type*& p_target)
	{
		if (p_target != nullptr)
		{
			delete p_target;
			p_target = nullptr;
		}
	}

	template<typename _Type>
	inline void safe_delete_arr(_Type*& p_target)
	{
		if (p_target != nullptr)
		{
			delete[] p_target;
			p_target = nullptr;
		}
	}

	template<typename _Type>
	inline void safe_release(_Type*& p_target)
	{
		if (p_target != nullptr)
		{
			p_target->release();
			p_target = nullptr;
		}
	}

	template<typename _Type>
	inline void safe_delete(std::unique_ptr<_Type>& p_target)
	{
		if (nullptr != p_target)
		{
			delete p_target.release();
		}
	}

	template<typename _Type>
	inline void safe_delete_arr(std::unique_ptr<_Type>& p_target)
	{
		if (nullptr != p_target)
		{
			delete[] p_target.release();
		}
	}

	template<typename _Type>
	inline void safe_release(std::unique_ptr<_Type>& p_target)
	{
		if (nullptr != p_target)
		{
			p_target->release();
			p_target.release();
		}
	}
}
