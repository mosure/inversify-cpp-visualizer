load("@rules_cc//cc:defs.bzl", "cc_library")


cc_library(
    name = "catch2",
    copts = [
        "-std=c++11",
    ],
    hdrs = [
        "third_party/catch2/catch.hpp",
    ],
    includes = [
        "third_party",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cpp_template",
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
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "test",
    srcs = glob([
        "test/**/*.cpp",
    ]),
    deps = [
        ":catch2",
        ":cpp_template"
    ],
    visibility = ["//visibility:public"]
)
