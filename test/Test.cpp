#include "Test.h"
#include <assert.h>
#include <dlfcn.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <vector>

#if 0
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
#endif

Test::Test()
{

}

void Test::loadLib(std::string name) 
{
  instance = NULL;
  handle = dlopen(name.c_str(), RTLD_LAZY);
	 
  if (!handle) {
    printf("%s\n", dlerror());
    return;
  }

  create = (VisionPlugin* (*)()) dlsym(handle, "create");
  destroy = (void(*)(VisionPlugin*)) dlsym(handle, "destroy");

  char* error;
  if ((error = dlerror()) != NULL) {
    printf("%s\n", error);
    return;
  }

  instance = create();

  instance->setNetworkModelsFilePath("./anyconnect300x.xml.enc");
  instance->initPlugin();
}

bool Test::isLoaded() 
{
  return instance != NULL; 
}

void Test::setCallback()
{
#if 0	
  instance->setInferenceResultCallback([this](std::string source, time_t timestamp, unsigned char *data, int len, cv::Mat frame, std::vector<InferenceResult> results){
    printf("Inference Result array size: %d\n", results.size());		  
  });
#endif
}

void Test::analyze()
{

#if 0
  cv::VideoCapture cap;
  bool isOk = cap.open(0);
  if(isOk==0) {
    std::cout << "Failed to open device" << std::endl;
    return;
  }
  cv::Mat frame;
  cap >>frame;
  while(cap.read(frame)) {
    try {
      u_int64_t timestamp = 1594028376272;
      std::string imager = "vid_1";
      MediaInfo mi;
      std::vector<InferenceResult> result = instance->feedMediaData(MediaType::VIDEO, imager, timestamp, mi, frame, nullptr, 0); 
    }
    catch(...) {
    }
  }
#endif
}

void Test::closePlugin()
{
  instance->deInitPlugin();
}

Test::~Test() {
  destroy(instance);
  dlclose(handle);
  handle = NULL;
}

Test *pTest = new Test();

int main()
{
  pTest->loadLib("./libacvisionplugin.so");
  if(pTest->isLoaded()) {
    printf("Your AnyConnect Vision plugin loaded!\n");
    pTest->setCallback();
  }
  else {
    printf("Your AnyConnect Vision Plugin does not load.\n");
  }

  int count = 0;
  while(1) {  
    sleep(5);
  }
  return 0;
}
