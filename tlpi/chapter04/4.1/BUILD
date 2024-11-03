cc_binary(
    name = "tee",
    srcs = [
        "tee.c"
    ],
    deps = ["//lib:tlpi"],
    copts=["-Ilib"]
)

alias(
    name = "4.1",
    actual = ":tee"
)
