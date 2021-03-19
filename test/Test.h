#include "VisionPlugin.h"
#include <functional>

using namespace com::anyconnect::visionplugin;

class Test {
void* handle;
VisionPlugin* instance;
VisionPlugin* (*create)();
void (*destroy)(VisionPlugin*);

public:
  Test();
  ~Test();
void loadLib(std::string name);
bool isLoaded();
void setCallback();
void analyze();
void closePlugin();
};

