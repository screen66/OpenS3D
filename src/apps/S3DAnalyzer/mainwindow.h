#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "rendering/entity/entitymanager.h"
#include "utilities/usersettings.h"

#include <s3d/multiview/stan_fundamental_matrix_solver.h>
#include <s3d/cv/image_operation/camera_alignment.h>
#include <s3d/video/video_types.h>

#include <chrono>

namespace Ui {
class MainWindow;
}  // namespace Ui

class OpenGLWindow;
class DepthAnalyzer;
struct RenderingContext;
class VideoSynchronizer;
class DisparitySettingsDialog;
class FeaturesSettingsDialog;
class FilterSettingsDialog;
class StereoDemuxerQImage;
class StereoDemuxerFactoryQImage;

namespace s3d {
class DisparityAnalyzerSTAN;
struct VideoCaptureFormat;
}  // namespace s3d

#include <QAction>

class ImageOperationActionController;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

  void computeAndUpdate();
  void updateConvergenceHint(float minDisparity, float maxDisparity);

 protected:
  void mouseDoubleClickEvent(QMouseEvent* e) override;
  void closeEvent(QCloseEvent* event) override;

 private:
  EntityManager::DisplayMode getCurrentDisplayMode();

  void handleNewImagePair(const QImage& imgLeft,
                          const QImage& imgRight,
                          std::chrono::microseconds timestamp);

  template <class Functor>
  void requestImageFilename(Functor f);

  template <class Functor>
  void requestVideoFilename(Functor f);

  void updateInputMode();
  void updateStereo3DFormat();

  void demuxImage(const QImage& image);
  bool stereoFormatChanged();
  void updateStereoDemuxer();
  bool stereoDemuxerRequired();

  // todo: does this belong here
  std::unique_ptr<VideoSynchronizer> m_videoSynchronizer;
  std::unique_ptr<StereoDemuxerQImage> m_stereoDemuxer;
  std::unique_ptr<StereoDemuxerFactoryQImage> m_stereoDemuxerFactory;
  s3d::Stereo3DFormat m_stereoFormat;

  QImage m_imageLeft{};
  QImage m_imageRight{};
  bool m_imageLeftReady{false};
  bool m_imageRightReady{false};

  std::unique_ptr<RenderingContext> m_widgetRenderingContext;
  std::unique_ptr<RenderingContext> m_windowRenderingContext;
  RenderingContext* m_currentContext;
  std::unique_ptr<OpenGLWindow> m_openGLWindow;

  int m_analyzerMinNbInliers{s3d::robust::estimation_algorithm_traits<s3d::StanFundamentalMatrixSolver>::MIN_NB_SAMPLES*2};
  std::unique_ptr<s3d::DisparityAnalyzerSTAN> m_analyzer;
  std::unique_ptr<s3d::image_operation::CameraAlignment> m_imageOperations;
  std::vector<std::unique_ptr<ImageOperationActionController>> m_imageOperationsActionControllers;

  UserSettings m_userSettings{};
  std::unique_ptr<DisparitySettingsDialog> m_disparitySettingsDialog;
  std::unique_ptr<FeaturesSettingsDialog> m_featuresSettingsDialog;
  std::unique_ptr<FilterSettingsDialog> m_filterSettingsDialog;

  Ui::MainWindow* ui;
};

#endif  // MAINWINDOW_H
