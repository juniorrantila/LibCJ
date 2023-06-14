trace_lib = library('Trace', [
  'Trace.c'
], dependencies: [
  cj_dep,
])

trace_dep = declare_dependency(
  link_with: trace_lib,
  include_directories: '..'
)
