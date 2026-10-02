project(engine)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  src/**.cpp
  include/**.hpp
)

add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

add_subdirectory(vendor)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  NX_ENGINE
)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
  include/nexus
)

target_link_libraries(${PROJECT_NAME} 
PRIVATE
  glfw

PUBLIC
  glad
  OpenGL::GL
)
