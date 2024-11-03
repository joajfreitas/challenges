cc_binary(
    name = "atomic_append",
    srcs = [
        "atomic_append.c"
    ],
    deps = ["//lib:tlpi"],
    copts = ["-Ilib"]
)

alias(
    name = "5.3",
    actual = ":atomic_append"
)
