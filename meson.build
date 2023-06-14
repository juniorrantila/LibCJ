project('playground', 'c',
  default_options: [
    'c_std=c11',
    'warning_level=3',
    'default_library=static',
    'buildtype=release',
  ])

add_project_arguments([
  '-Wno-gnu-statement-expression',
], language: 'c')

subdir('src')
