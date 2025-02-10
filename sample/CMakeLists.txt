project(sample)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

message(STATUS ${SOURCE_DIR})

set(SOURCES
 ${SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
)

target_include_directories(sample PUBLIC ${SFML_INCLUDE_DIR}) 
link_directories(${SFML_LIB_DIR})
target_link_libraries(${PROJECT_NAME}
PUBLIC
 Game_Engine
 Game
 PRIVATE
 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
 sfml-network
)

add_custom_command(TARGET sample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_BIN_DIR} $<TARGET_FILE_DIR:sample>
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Work")