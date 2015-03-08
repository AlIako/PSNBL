#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "08";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 2;
	static const long MINOR  = 1;
	static const long BUILD  = 1305;
	static const long REVISION  = 5540;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 2084;
	#define RC_FILEVERSION 2,1,1305,5540
	#define RC_FILEVERSION_STRING "2, 1, 1305, 5540\0"
	static const char FULLVERSION_STRING [] = "2.1.1305.5540";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 16;
	

}
#endif //VERSION_H
