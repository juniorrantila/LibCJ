fs_lib = library('FS', [
  'MappedFile.c'
], dependencies: [
  cj_dep,
])

fs_dep = declare_dependency(
  link_with: fs_lib,
  include_directories: '..'
)
