// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Inspired by Chromium video capture interface
// Simplified and stripped from internal base code

#ifndef S3D_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_3D_H
#define S3D_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_3D_H

#include "video_capture_device.h"

#include <cstdint>

class VideoCaptureDevice3D : rule_of_five_interface<VideoCaptureDevice3D> {
 public:
  class Client : rule_of_five_interface<VideoCaptureDevice3D::Client> {
   public:
    virtual void OnIncomingCapturedData(const gsl::span<const uint8_t> leftImage,
                                        const gsl::span<const uint8_t> rightImage,
                                        const VideoCaptureFormat& frameFormat) = 0;

    virtual void OnError(const std::string& reason) = 0;
    virtual void OnLog(const std::string& message) = 0;
    virtual void OnStarted() = 0;
  };

  virtual void AllocateAndStart(const VideoCaptureFormat& format,
                                std::unique_ptr<Client> client) = 0;

  virtual void RequestRefreshFrame() {}

  virtual void MaybeSuspend() {}

  virtual void Resume() {}

  virtual void StopAndDeAllocate() = 0;
};

#endif  // S3D_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_3D_H
