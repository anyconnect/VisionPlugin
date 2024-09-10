#include "Vision.h"
#include "iostream"
#include <vector>


Vision::Vision() {
  //Write your initialization code
}

Vision::~Vision() {
  // De-Initialize the vision.
}

void Vision::setNetworkModelsFilePath(std::string filePath, std::string modelConfigParam)
{
  // Set the model directory file path 
}

bool Vision::initPlugin() {
   // Initialize the plugin linked libs
   return true;
}

void Vision::deInitPlugin() {
  
  //
  // DeInitialize the plugin linked libs.
  //
}

std::vector<InferenceResult> Vision::feedMediaData(MediaType mediaType, std::string source, u_int64_t timestamp, MediaInfo mediaInfo, unsigned char* data, int len) {

  // If person/object detected, then store data.
  std::vector<InferenceResult> irList;
 
  
    
  // Get the output from your AI model or SDK and store on this variable
  // and return.

  InferenceResult res;
  res.label = "banana";
  res.xmin = 222;
  res.ymin = 250;
  res.xmax = 444;
  res.ymax = 450;
  res.confidence = 99;

  irList.push_back(res);

  return irList;
}

void Vision::feedSensoryApparatusData(u_int64_t timestamp, std::string dataJson) {

}


// Create and destroy the vision instance.
extern "C" {
Vision* create() {
	return new Vision();
}
void destroy(Vision* vision) {
	delete vision;
}
}
