#include "level.h"
#include <string>


#ifdef LEVELLOADER_EXPORTS
#define LEVELLOADER_API __declspec(dllexport)
#else
#define LEVELLOADER_API __declspec(dllimport)
#endif

// This class is exported from the LevelLoader.dll
class LEVELLOADER_API LevelLoader {
public:
	LevelLoader(void);
	void openFile(std::string file);
	
private:
	
};


