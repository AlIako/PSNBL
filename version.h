#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "27";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 8;
	static const long BUILD  = 3090;
	static const long REVISION  = 15584;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5756;
	#define RC_FILEVERSION 3,8,3090,15584
	#define RC_FILEVERSION_STRING "3, 8, 3090, 15584\0"
	static const char FULLVERSION_STRING [] = "3.8.3090.15584";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 1;
	

}
#endif //VERSION_H
