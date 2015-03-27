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
	static const long MINOR  = 7;
	static const long BUILD  = 3042;
	static const long REVISION  = 15323;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 5673;
	#define RC_FILEVERSION 3,7,3042,15323
	#define RC_FILEVERSION_STRING "3, 7, 3042, 15323\0"
	static const char FULLVERSION_STRING [] = "3.7.3042.15323";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 53;
	

}
#endif //VERSION_H
