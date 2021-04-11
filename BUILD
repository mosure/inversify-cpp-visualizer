load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")


cc_library(
    name = "inversify_visualizer",
    copts = [
        "-std=c++17",
        "-pedantic-errors",
        "-Wall",
        "-Wextra",
        "-Wshadow",
    ],
    hdrs = glob([
        "include/**/*.hpp",
    ]),
    includes = [
        "include",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@inversify//:inversify",
        "@boost//:core",
        "@boost//:graph",
    ],
)

cc_binary(
    name = "example",
    copts = [
        "-std=c++17",
        "-DINVERSIFY_BINDING_INSPECTION",
    ],
    srcs = glob([
        "example/**/*.cpp",
    ]),
    deps = [
        ":inversify_visualizer",
    ],
    visibility = ["//visibility:public"],
)
