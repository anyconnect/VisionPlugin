#ifndef _VISION_PLUGIN_TYPES_
#define _VISION_PLUGIN_TYPES_

#include <unordered_map>
#include <memory>
#include <any>
#include <string>
#include <vector>
#include <mutex>
#include <utility>

#pragma once

namespace cv {
  template<typename _Tp> class Rect_;
  typedef Rect_<int> Rect;
  typedef Rect_<float> Rect2f;

  template<typename _Tp> class Point_;
  typedef Point_<float> Point2f;
  typedef Point_<int> Point2i;
  typedef Point2i Point;

  class Mat;
}

namespace com {

namespace anyconnect {

namespace visionplugin {

namespace type {

template<class T, class... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

struct IObject
{
    virtual ~IObject() = default;
};

template<class T>
class UnivObject final : public IObject
{
public:
    UnivObject(T t_content) : m_context(t_content){}
    ~UnivObject() = default;

    const T& get() const
    {
        return m_context;
    }

private:
    T m_context;
};

struct DrawingStyle {
  std::string type;   // Dashed, solid, point etc. 
  std::string color;  // Hex-Color code e.g., #f2e607
  bool fill;          // Box or object is filled
  int size;           // Size of the object lines, points.
};

struct Object {
  std::shared_ptr<cv::Rect> bbox;   // Bounding box minx, miny, maxx, maxy
  std::string label;                // Label of the classified object.
  float confidence;                 // Confidence of the classification.
  std::string unit;                 // Unit string e.g., %, s, meter etc.
  DrawingStyle style;               // Style of the line, rect, and point
};

struct Line {
  std::vector<std::shared_ptr<cv::Point2f>> line;  // Vector of line point.
  std::string label;                               // label of the classified line
  float confidence;                                // Confidence of the classification
  std::string unit;                                // Unit string e.g., %, s, meter etc.
  DrawingStyle style;                              // Style of the line, rect, and point
};

struct KeyPoint {
  std::shared_ptr<cv::Point2f> point; // Point co-ordinate x, y
  std::string label;                  // Classification
  float confidence;                   // Confidence of the object
  std::string unit;                   // Unit string 
  DrawingStyle style;                 // Style of the line, rect, and point
};

struct Mask {
  std::shared_ptr<cv::Mat> mask;      // OpenCV mask object
  std::string label;                  // classification of the object 
  float confidence;                   // Confidence value
  std::string unit;                   // Unit string
};


struct ObjectDetails {
  /// Details of the classified or detected object
  std::unordered_map<std::string, std::shared_ptr<IObject>> data;
};

struct SensorData {
  /// Details of the sensor related data
  std::unordered_map<std::string, std::shared_ptr<IObject>> data;
};

struct FrameData {
  /// Details inference data mapping for a frame
  std::unordered_map<std::string, std::shared_ptr<IObject>> data;
};

struct FrameResult {
  std::string inputSource;           // Id of the model input source.
  std::vector<Object> objects;       // Object's info with bbox, conf, label
  ObjectDetails objectDetails;       // Object specific information (e.g., driver)
  std::vector<Line> lines;           // Line points
  std::vector<KeyPoint> points;      // Points list for an object.
  std::vector<Mask> masks;           // Masks for segmentation models
  FrameData frameData;               // Inference data related to the frame
  uint64_t timestamp;                // Frame timestamp
  FrameResult() {
  }
};

struct VisionBox {
  std::vector<FrameResult>results;    // Inference results for frames
  std::vector<SensorData>sensorDatas; // Sensor data
};

}
}
}
}

#endif
