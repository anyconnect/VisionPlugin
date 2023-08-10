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
  
  // Vision box result
  type::VisionBox visionBox;
  
  // Frame result
  type::FrameResult fr;
  fr.inputSource = source;
  fr.timestamp = timestamp;
  
#if 0
  // Line co-ordinate storing
  std::vector<std::shared_ptr<cv::Point2f>> line;
  
  type::Line ln;
  ln.label = "left_line";
  ln.confidence = 100;
  ln.unit = "%";
  std::copy(line.begin(), line.end(),
		  std::back_inserter(ln.line));
  
  fr.lines.emplace_back(std::move(ln));
  
  // Object detection with bounding box
  type::Object obj;
  obj.label = "STOP_SIGN";
  obj.confidence = 90;
  obj.unit = "%"; 
  obj.bbox = std::make_shared<cv::Rect>(cv::Rect(100.0, 125.0, 200.0, 225.0));
  fr.objects.emplace_back(std::move(obj));
  
  // Object details for driver face keypoint
  type::KeyPoint kepo;
  kepo.point = std::make_shared<cv::Point>(10, 20);
  kepo.label = "driver-key";
  fr.objectDetails.data["hand_position"] = std::make_shared<type::UnivObject<type::KeyPoint>>(kepo);
  
   
  // get the data from object details by name mapping
  kepo = dynamic_cast<type::UnivObject<type::KeyPoint>*>(fr.objectDetails.data["hand_position"].get())->get();
  
  // Store a list of data to the object detail map
  
  std::vector<double> v{ 3.1, 0.042, 0.02 };
  fr.objectDetails.data["accelerometer"] = std::make_shared<type::UnivObject<std::vector<double>>>(v);
  
  // get the list of data from the object details map
  auto accel = dynamic_cast<type::UnivObject<std::vector<double>>*>(fr.objectDetails.data["accelerometer"].get())->get();
  
  // Detection results with points
  type::KeyPoint kp;
  kp.point = std::make_shared<cv::Point>(55,65);
  kp.label = "driver-key";
  kp.confidence = 90;
  kp.unit = "%"; 
  fr.points.emplace_back(std::move(kp));
 
  
  if(fr.lines.size() > 0 || fr.objects.size() > 0)
  {
    visionBox.results.push_back(std::move(fr));

    InferenceResult irs;
    irs.visionBoxAvailable = true;
    irs.visionBox = std::move(visionBox);
    irList.push_back(irs);
  }
  
 #endif
  
  // Get the output from your AI model or SDK and store on this variable
  // and return.
   
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
