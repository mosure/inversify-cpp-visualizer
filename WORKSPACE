load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")


git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "1e3a69bf2d5cd10c34b74f066054cd335d033d71",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1591047380 -0700",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()


git_repository(
    name = "inversify",
    remote = "https://github.com/mosure/inversify-cpp",
    commit = "19725d56443bab6844be07fa86d5e71df0350a29",
)
