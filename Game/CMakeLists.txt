
project(Game)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADERS
 ${HEADER_DIR}/Game.h
)
set(SOURCES
${SOURCE_DIR}/Game.cpp
)

add_library(${PROJECT_NAME}

${SOURCES}
${HEADERS}
)


target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

target_include_directories(Game PUBLIC ${SFML_INCLUDE_DIR}) 

link_directories(${SFML_LIB_DIR})

target_link_libraries(${PROJECT_NAME}
PUBLIC
 Game_Engine
 PRIVATE
 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
 sfml-network
)
add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_BIN_DIR} $<TARGET_FILE_DIR:Game>
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Game")