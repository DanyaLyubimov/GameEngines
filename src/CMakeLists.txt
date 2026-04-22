set(TARGET_NAME GameDev)
set(SOURCES main.cpp
    config.cpp)

add_executable(${TARGET_NAME} 
    ${SOURCES})

target_include_directories(${TARGET_NAME}  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TARGET_NAME}  PRIVATE sfml-window sfml-graphics sfml-system)
target_link_libraries(${TARGET_NAME}  PRIVATE ImGui-SFML::ImGui-SFML)