#ifndef _VISION_H_
#define _VISION_H_

// Vision library header file.  
// This derived class overrides VisionPlugin base class member functions.
// The AnyConnect Smarter Camera Platform libraries calls these APIs
// to request/push data from/to a inference engine for inferencing.


#include "VisionPlugin.h"


using namespace com::anyconnect::visionplugin;

class Vision: public VisionPlugin {
public:
  Vision();
  virtual ~Vision();

  bool initPlugin();

  void deInitPlugin();
  
  void setNetworkModelsFilePath(std::string filePath, std::string modelConfigParams = "");

  std::vector<com::anyconnect::visionplugin::InferenceResult> feedMediaData(com::anyconnect::visionplugin::MediaType mediaType, 
															std::string source, 
															u_int64_t timestamp,
															MediaInfo mediaInfo,
															unsigned char* data,
															int len);

  void feedSensoryApparatusData(u_int64_t timestamp, std::string dataJson);

};
#endif

