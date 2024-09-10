///
/// \file VisionPlugin.h
///
/// Vision plugin header file
///
/// Copyright © 2021
/// Smarter AI International Private Limited. All rights reserved.
///

#ifndef _VISION_PLUGIN_
#define _VISION_PLUGIN_

#include <string>
#include <functional>
#include <vector>
#include "SharedBuffer.h"


namespace com {
namespace anyconnect {
namespace visionplugin {
///
/// \brief media types.
///
/// Supported media types: audio, video, sensor.
///
enum class MediaType {
  AUDIO,
  VIDEO,
  SENSOR
};


///
/// \brief media information.
///
struct MediaInfo {
  ///
  /// Width of the video
  ///
  int videoWidth;
  ///
  /// Height of the video.
  ///
  int videoHeight;
  ///
  /// Maximum video frame per second.
  ///
  int videoFps;
  ///
  /// Maximum bitrate.
  ///
  long bitRate;
  ///
  /// Audio sampling rate
  ///
  long sampleRate;
  ///
  /// Audio fps
  ///
  int audioFps;
};

///
/// \brief inference results.
///
struct InferenceResult {
  /// Type of the media
  MediaType mediaType;
  /// Name of the source e.g., front-door camera, patio camera, gyroscope, accelerometer etc.
  std::string name;
  /// Source name for mapping usage, vid_1, gyro_1, aud_1, etc.
  std::string source;
  /// Label of the detection
  std::string label;
  /// Bounding box coordinate
  int xmin;
  int ymin;
  int xmax;
  int ymax;
  /// Accuracy between 1 and 100
  /// Also can contain durations, distance, angles etc value
  double confidence;
  /// Unit of confidence or other value sent over the field confidence
  std::string unit;
  /// Inference result summary
  std::string summary;
  /// Detail result in JSON format if any.
  /// e.x., resultJson = [{"mediatype": "video", "source": "vid_1", "label": "person", "precision": 90.2, "xmin": 100, "ymin": 120, "xmax": 300, "ymax": 400, "summary": "not in safe distance"},
  ///                    {"mediatype": "video", "source": "vid_1", "label": "person", "precision": 98, "xmin": 400, "ymin": 520, "xmax": 700, "ymax": 600, "summary": "in safe distance"},
  ///                    {"mediatype": "gyroscope", "source": "gyro_1", "summary": "changing lane"}]
  std::string resultJson;

};

class VisionPlugin {
public:
    VisionPlugin() {}

    /// \brief Initialize the plugin
    ///
    /// \return true on successful initialization,
    ///  otherwise false.
    ///
    virtual bool initPlugin() = 0;

    ///
    /// \brief De-initialize the plugin.
    ///
    virtual void deInitPlugin() = 0;

    ///
    /// \brief Set networks model filepath
    ///
    /// \param[in] filePath - model file path.
    /// \param[in] modelConfigParams - model config parameters from dashboard in json format
    ///
    virtual void setNetworkModelsFilePath(std::string filePath, std::string modelConfigParams = "") = 0;
    ///
    /// \brief Provides decoded media data (frame) to the plugin for analysis.
    ///
    /// \param[in] mediaType - the type of the provided media
    /// \param[in] source - source for which the data is provided
    /// \param[in] timestamp - the timestamp of the frame in milliseconds.
    /// \param[in] mediaInfo - media related information.
    /// \param[in] data -  audio/video frame data.
    /// \param[in] len - length of the provided data.
    /// \return - a list of Inference result.
    ///
    virtual std::vector<InferenceResult> feedMediaData(MediaType mediaType, std::string source, u_int64_t timestamp, MediaInfo mediaInfo,  unsigned char* data, int len) = 0;

    ///
    /// \brief Provides sensor data to the plugin for analysis.
    ///
    /// \param[in] timestamp - the timestamp of the provided data.
    /// \param[in] dataJson -  sensor data in JSON format.
    /// e.x., dataJson = [{"mediaType": "gyroscope", "source": "gyro_1", "x":20, "y":35, "z":10}]
    ///
    virtual void feedSensoryApparatusData(u_int64_t timestamp, std::string dataJson) = 0;
};

class VisionPluginV1 : public VisionPlugin {
public:
    virtual void setSharedBuffer(SharedBuffer& buf) {
      _sharedBuf = &buf;
    }

protected:
    SharedBuffer* _sharedBuf = nullptr;
};

} //< visionplugin
} //< anyconnect
} //< com

#endif

