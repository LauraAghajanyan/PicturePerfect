licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])


cc_binary(
    name = "libexample.so",
    deps = [
        ":bg_remover"
    ],
    linkopts = ["-Wl,-soname,libexample.so"],
    linkshared = 1 ## Very important
)

cc_library(
    name = "bg_remover",
    srcs = ["iris_tracking.cpp"],
    hdrs = ["iris_tracking.hpp"],
    visibility = ["//visibility:public"],
    deps = [
    "//mediapipe/framework:calculator_framework",
    "//mediapipe/framework/formats:image_frame",
    "//mediapipe/framework/formats:image_frame_opencv",
    "//mediapipe/framework/formats:landmark_cc_proto",
    "//mediapipe/framework/port:file_helpers",
    "//mediapipe/framework/port:opencv_highgui",
    "//mediapipe/framework/port:opencv_imgproc",
    "//mediapipe/framework/port:opencv_video",
    "//mediapipe/framework/port:parse_text_proto",
    "//mediapipe/framework/port:status",
    "@com_google_absl//absl/flags:flag",
    "@com_google_absl//absl/flags:parse",
        # Deps for example_impl.cpp
        # "//mediapipe/framework/port:parse_text_proto",
        # "@com_google_absl//absl/flags:parse",
        # Iris tracking
        "//mediapipe/graphs/iris_tracking:iris_tracking_cpu_deps",
	],
    alwayslink = 1,
)
