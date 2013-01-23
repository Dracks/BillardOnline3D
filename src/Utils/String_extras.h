//
//  String.h
//  BillardOnline3D
//
//  Created by Dracks on 11/22/12.
//
//

#ifndef __BillardOnline3D__String__
#define __BillardOnline3D__String__

#include <iostream>
#include <sstream>
#include <string.h>

namespace utils{
	template <typename T>
	std::string NumberToString ( T Number )
	{
		std::ostringstream ss;
		ss << Number;
		return ss.str();
	}
	
	template <typename T>
	T StringToNumber ( const std::string &Text )
	{
		std::istringstream ss(Text);
		T result;
		return ss >> result ? result : 0;
	}
}

#include "String_extras.cpp"

#endif /* defined(__BillardOnline3D__String__) */
