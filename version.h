#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "15";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 7;
	static const long BUILD  = 1904;
	static const long REVISION  = 8903;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3242;
	#define RC_FILEVERSION 2,7,1904,8903
	#define RC_FILEVERSION_STRING "2, 7, 1904, 8903\0"
	static const char FULLVERSION_STRING [] = "2.7.1904.8903";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 15;
	

}
#endif //VERSION_H
