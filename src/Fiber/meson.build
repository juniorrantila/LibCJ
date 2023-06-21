os = target_machine.system()
arch = target_machine.cpu_family()
context_src = arch / os / 'Context.S'

fiber_lib = library('Fiber', [
  context_src
], dependencies: [
  cj_dep,
])

fiber_dep = declare_dependency(
  link_with: fiber_lib,
  include_directories: '..'
)
