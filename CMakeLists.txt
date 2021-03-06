cmake_minimum_required(VERSION 3.0.0)
project(GAVO VERSION 0.1.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "../bin")
add_compile_definitions(
    _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
find_package( Threads REQUIRED )
find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME}
  "source_files/ec.edu.ups/view/main.cpp"
  "source_files/ec.edu.ups/view/main_gui.cpp"
  
  "source_files/ec.edu.ups/controller/qt_screenshot.cpp"
  "source_files/ec.edu.ups/controller/av_process_thread.cpp"
  "source_files/ec.edu.ups/controller/input_simulation.cpp"
  "source_files/ec.edu.ups/controller/iter_process.cpp"

  "source_files/ec.edu.ups/model/hu_enemy.cpp"
  "source_files/ec.edu.ups/model/template_match_enemy.cpp"

  "source_files/ec.edu.ups/utils/hsv_threshold.cpp"
)

if (WIN32)
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} )
endif()

if (UNIX)
  target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} X11 Xtst)
endif()

if (WIN32)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}>
    
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsIntegrationPlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>/platforms/
    
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::QWindowsVistaStylePlugin> $<TARGET_FILE_DIR:${PROJECT_NAME}>/styles/
  )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
