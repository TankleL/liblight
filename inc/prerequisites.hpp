#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#ifdef WIN32
#	ifdef API_DEV_MOD
#		define	LIGHT_API	__declspec(dllexport)
#	else
#		define	LIGHT_API	__declspec(dllimport)
#	endif
#else
#	define LIGHT_API
#endif