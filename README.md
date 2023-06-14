# LibCJ 

**LibCJ** is C utility library

## Build instructions

This project is only tested to compile with the `clang` compiler on
macOS. You will need to install it along with `meson` and `ninja`.
For faster rebuilds you may install `ccache` as well.

### Setup:

```sh

meson build

```

### Build:

```sh

ninja -C build

```

### Usage:

Add the following into a file called `subprojects/LibCJ.wrap`:

```wrap
[wrap-git]
url = https://github.com/juniorrantila/libcj.git
revision = main
depth = 1
```

After the file is created you can use the LibCJ libraries by
adding something similar to the following to your `meson.build`:

```meson
cj_proj = subproject('LibCJ')
cj_dep = cj_proj.get_variable('cj_dep')
trace_dep = cj_proj.get_variable('trace_dep')

my_program_exe = executable('my-program', [
    'my-source.c',
  ],
  dependencies: [
    cj_dep,
    trace_dep,
  ]
)
```
