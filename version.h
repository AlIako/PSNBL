#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "28";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 3;
	static const long MINOR  = 8;
	static const long BUILD  = 3158;
	static const long REVISION  = 15972;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5895;
	#define RC_FILEVERSION 3,8,3158,15972
	#define RC_FILEVERSION_STRING "3, 8, 3158, 15972\0"
	static const char FULLVERSION_STRING [] = "3.8.3158.15972";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 69;
	

}
#endif //VERSION_H
