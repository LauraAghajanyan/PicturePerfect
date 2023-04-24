#include "iris_tracking.hpp"
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"
//#include "iris_tracking.hpp"
using namespace std::chrono_literals;

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";
constexpr char kWindowName[] = "MediaPipe";

ABSL_FLAG(std::string, calculator_graph_config_file, "",
          "Name of file containing text format CalculatorGraphConfig proto.");
ABSL_FLAG(std::string, input_video_path, "",
          "Full path of video to load. "
          "If not provided, attempt to use a webcam.");

Iris::Iris(std::string graphFileLocation) : _graphFileLocation(graphFileLocation)
{
  std::thread processingThread(&Iris::RunMPPGraph, this);
  processingThread.detach();
}

void Iris::SetCurrentImage(cv::Mat imgData)
{
  _isDirty = true;
  _currentImage = imgData;
 }

 std::vector<std::pair<double, double>> Iris::Get()
{
  return landmark_list_vec;
}

absl::Status Iris::RunMPPGraph()
{
  std::string calculator_graph_config_contents;
  MP_RETURN_IF_ERROR(mediapipe::file::GetContents(
      _graphFileLocation,
      &calculator_graph_config_contents));
  mediapipe::CalculatorGraphConfig config =
      mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
          calculator_graph_config_contents);
          mediapipe::CalculatorGraph graph;
          MP_RETURN_IF_ERROR(graph.Initialize(config));

  ASSIGN_OR_RETURN(mediapipe::OutputStreamPoller poller2,
                   graph.AddOutputStreamPoller("face_landmarks_with_iris"));
  MP_RETURN_IF_ERROR(graph.StartRun({}));

  LOG(INFO) << "Start grabbing and processing frames.";
  bool grab_frames = true;
  while (grab_frames)
  {
    cv::Mat camera_frame_raw;
    while (!_isDirty)
    {
      sleep(5);
    }
    _isDirty = false;
    _isProcessed = false;

    cv::Mat camera_frame;
    cv::cvtColor(_currentImage, camera_frame, cv::COLOR_BGR2RGB);
    auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
        mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
        mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
    camera_frame.copyTo(input_frame_mat);
    size_t frame_timestamp_us =
        (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
    MP_RETURN_IF_ERROR(graph.AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us))));
    mediapipe::Packet packet2;
    if (!poller2.Next(&packet2))
      break;
    auto &output_landmarks = packet2.Get<mediapipe::NormalizedLandmarkList>();

std::regex pattern(R"(x: (\d+\.\d+)\n\s+y: (\d+\.\d+))");
    std::smatch matches;
  auto landmarks = output_landmarks.DebugString();
    std::string::const_iterator searchStart(landmarks.cbegin());
    while (std::regex_search(searchStart, landmarks.cend(), matches, pattern)) {
        double x = std::stod(matches[1]);
        double y = std::stod(matches[2]);
        landmark_list_vec.push_back({x, y});
        searchStart = matches.suffix().first;
    }
    _isProcessed = true;
  }
  MP_RETURN_IF_ERROR(graph.CloseInputStream(kInputStream));
  return graph.WaitUntilDone();
}