cc_binary(
    name = "large_file",
    srcs = [
        "large_file.c"
    ],
    deps = ["//lib:tlpi"],
    copts=["-Ilib"]
)

alias(
    name = "5.1",
    actual = ":large_file"
)
