#ifndef _SHARED_BUFFER
#define _SHARED_BUFFER

#include <mutex>
#include <list>
#include <any>
#include <memory>
#include <deque>
#include <vector>
#include <chrono>
#include <algorithm>

namespace com {
namespace anyconnect {
namespace visionplugin {

enum class DataType;

class SharedData {
  using data_t = std::list<std::any>;
public:
  using timePoint = std::chrono::time_point<std::chrono::steady_clock>;

  SharedData(DataType type, timePoint ts, std::string sensorData, std::any data)
    : _data({std::move(data)}), _type(type), _ts(ts), _sensorData(std::move(sensorData)) {}

  void push_back(std::any data) {
    std::lock_guard lock(_dataMtx);
    _data.push_back(std::move(data));
  }

  std::pair<data_t::const_iterator, data_t::const_iterator> getData() const {
    std::lock_guard lock(_dataMtx);
    return {_data.begin(), --_data.end()};
  }

  const DataType _type;
  const timePoint _ts;
  const std::string _sensorData;

  friend bool operator<(const SharedData& l, const SharedData& r) {
    return l._ts < r._ts;
  }

private:
  std::list<std::any> _data;
  mutable std::mutex _dataMtx;
};

class SharedBuffer {
public:
  SharedBuffer(std::chrono::milliseconds period = std::chrono::milliseconds(10000)) : _period(period) {}

  void emplace(DataType type, SharedData::timePoint ts, std::string sensorData, std::any data) {
    auto dataPtr = std::make_shared<SharedData>(type, ts, std::move(sensorData), std::move(data));
    std::lock_guard lock(_mtx);
    // find correct position
    auto pos = std::upper_bound(_buf.begin(), _buf.end(), ts,
      [](const auto& ts, const auto& ptr) {
        return ts < ptr->_ts;
      });
    _buf.insert(pos, std::move(dataPtr));
    while (_buf.size() && (ts - _buf.front()->_ts) > _period) {
      _buf.pop_front();
    }
  }

  std::vector<std::shared_ptr<SharedData>> get(SharedData::timePoint from, SharedData::timePoint to) {
    std::lock_guard lock(_mtx);
    auto [fromPos, toPos] = getTimeRange(from, to);
    return {fromPos, toPos};
  }

  std::vector<std::shared_ptr<SharedData>> get(DataType type, SharedData::timePoint from, SharedData::timePoint to) {
    std::lock_guard lock(_mtx);
    auto [fromPos, toPos] = getTimeRange(from, to);
    std::vector<std::shared_ptr<SharedData>> res;
    for (; fromPos != toPos; ++fromPos) {
        if (type == (*fromPos)->_type) {
          res.push_back(*fromPos);
        }
    }
    return res;
  }

  std::vector<std::shared_ptr<SharedData>> getLastN(DataType type, size_t n) {
    std::lock_guard lock(_mtx);
    std::vector<std::shared_ptr<SharedData>> res;
    for (auto it = _buf.rbegin(); (it != _buf.rend()) && n != 0; ++it) {
      if (type == (*it)->_type) {
        res.push_back(*it);
        --n;
      }
    }
    return res;
  }

private:
  using buf_t = std::deque<std::shared_ptr<SharedData>>;
  std::pair<buf_t::iterator, buf_t::iterator> getTimeRange(SharedData::timePoint from, SharedData::timePoint to) noexcept {
    auto fromPos = std::upper_bound(_buf.begin(), _buf.end(), from,
      [](const auto& ts, const auto& ptr) {
        return ts <= ptr->_ts;
      });
    auto toPos = std::upper_bound(_buf.begin(), _buf.end(), to,
      [](const auto& ts, const auto& ptr) {
        return ts <= ptr->_ts;
      });
    return {fromPos, toPos};
  }

private:
  const std::chrono::milliseconds _period;
  buf_t _buf;
  mutable std::mutex _mtx;

};

} // visionplugin
} // anyconnect
} // com

#endif // _SHARED_BUFFER