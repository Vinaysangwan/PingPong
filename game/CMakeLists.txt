project(ping_pong)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  src/**.cpp
  include/**.hpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  engine
)
