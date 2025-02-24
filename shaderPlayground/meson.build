project('pong', ['cpp', 'c'], default_options : ['warning_level=3', 'cpp_std=c++20'])

#compiler = meson.get_compiler('cpp')



inc = include_directories('include')
executable('game', sources: ['main.cpp', 'glad.c', 'shader.cpp'],
  include_directories: inc,
  dependencies: [
    dependency('glfw3'),
    dependency('gl'),
    dependency('x11'),
    dependency('xi'),
    dependency('dl'),
    dependency('threads'),
    dependency('xrandr')
    ]
  )
