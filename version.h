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
	static const long MINOR  = 9;
	static const long BUILD  = 3191;
	static const long REVISION  = 16145;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5962;
	#define RC_FILEVERSION 3,9,3191,16145
	#define RC_FILEVERSION_STRING "3, 9, 3191, 16145\0"
	static const char FULLVERSION_STRING [] = "3.9.3191.16145";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 2;
	

}
#endif //VERSION_H
