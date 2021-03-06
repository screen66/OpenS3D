// Copyright 2013 The Chromium Authors. All rights reserved.
// Inspired by Chromium video capture interface
// Simplified and stripped from internal base code

#ifndef S3D_VIDEO_CAPTURE_FILE_VIDEO_CAPTURE_DEVICE_H
#define S3D_VIDEO_CAPTURE_FILE_VIDEO_CAPTURE_DEVICE_H

#include "video_capture_device.h"

#include "s3d/concurrency/timed_loop_sleep.h"

#include <atomic>
#include <thread>

namespace s3d {

class VideoFileParser;

class FileVideoCaptureDeviceRawUYVY : public VideoCaptureDevice {
 public:
  class CaptureLoopClient : public s3d::TimedLoop::Client {
   public:
    explicit CaptureLoopClient(FileVideoCaptureDeviceRawUYVY* captureDevice);
    gsl::owner<s3d::TimedLoop::Client*> clone() const override;
    void callback() override;

   private:
    gsl::not_null<FileVideoCaptureDeviceRawUYVY*> captureDevice_;
  };

  explicit FileVideoCaptureDeviceRawUYVY(std::string filePath);

  gsl::owner<VideoCaptureDevice*> clone() const override;

  ~FileVideoCaptureDeviceRawUYVY() override;

  void AllocateAndStart(const VideoCaptureFormat& format,
                        VideoCaptureDevice::Client* client) override;

  void Start(const VideoCaptureFormat& format,
             VideoCaptureDevice::Client* client,
             std::unique_ptr<s3d::TimedLoop::Client> captureLoopClient,
             std::unique_ptr<VideoFileParser> fileParser,
             std::unique_ptr<s3d::TimedLoop> timedLoop);

  void MaybeSuspend() override;
  void Resume() override;
  void WaitUntilDone();
  void StopAndDeAllocate() override;
  VideoCaptureFormat DefaultFormat() override;
  void MaybeSeekTo(std::chrono::microseconds timestamp) override;
  void RequestRefreshFrame() override;

 protected:
  void OnAllocateAndStart();

 private:
  virtual void StartCaptureThread();
  virtual void OnCaptureTask();

  virtual std::unique_ptr<VideoFileParser> GetVideoFileParser(const std::string& filePath);

  virtual bool InitializeFileParser(std::unique_ptr<VideoFileParser>& fileParser,
                                    VideoCaptureFormat* format);

  virtual std::unique_ptr<TimedLoop> GetTimedLoop();

  virtual std::unique_ptr<TimedLoop::Client> GetTimedLoopClient();

  // seeking
  std::atomic<bool> shouldSeek_{false};
  std::chrono::microseconds seekingTimestamp_;
  std::mutex seekingMutex_;

  // belongs to capture thread
  std::string filePath_;
  std::unique_ptr<TimedLoop::Client> captureLoopClient_;
  std::unique_ptr<TimedLoop> captureLoop_;
  std::unique_ptr<std::thread> captureThread_;
  std::unique_ptr<VideoFileParser> fileParser_;
  VideoCaptureDevice::Client* client_;
  std::vector<uint8_t> videoFrame_;
  VideoCaptureFormat captureFormat_;
};

}  // namespace s3d

#endif  // S3D_VIDEO_CAPTURE_FILE_VIDEO_CAPTURE_DEVICE_H
