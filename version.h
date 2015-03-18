#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 10;
	static const long BUILD  = 2233;
	static const long REVISION  = 10724;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3975;
	#define RC_FILEVERSION 2,10,2233,10724
	#define RC_FILEVERSION_STRING "2, 10, 2233, 10724\0"
	static const char FULLVERSION_STRING [] = "2.10.2233.10724";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 44;
	

}
#endif //VERSION_H
