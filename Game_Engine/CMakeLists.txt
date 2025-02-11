project(Game_Engine)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADERS
 ${HEADER_DIR}/Base.h
)
set(SOURCES
${SOURCE_DIR}/Base.cpp
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
include_directories(${CMAKE_SOURCE_DIR}/KT_Library/KT_Library/include)
target_include_directories(Game_Engine PUBLIC ${SFML_INCLUDE_DIR}) 
link_directories(${SFML_LIB_DIR})
target_link_libraries(${PROJECT_NAME}
PUBLIC
 Game
 PRIVATE
 sfml-graphics
 sfml-window
 sfml-system
 sfml-audio
 sfml-network
)

add_custom_command(TARGET Game_Engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_BIN_DIR} $<TARGET_FILE_DIR:Game_Engine>
)


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Game_Engine")