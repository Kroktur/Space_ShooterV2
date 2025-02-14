project(sample)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

message(STATUS ${SOURCE_DIR})

set(SOURCES
 ${SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
${SOURCES}
)
include_directories(${CMAKE_SOURCE_DIR}/KT_Library/KT_Library/include)
target_include_directories(sample PUBLIC ${SFML_INCLUDE_DIR}) 
link_directories(${SFML_LIB_DIR})
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            sfml-graphics-d
            sfml-window-d
            sfml-system-d
            sfml-audio-d
            sfml-network-d
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            sfml-graphics
            sfml-window
            sfml-system
            sfml-audio
            sfml-network
    )
endif()
target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Game
        Game_Engine
)
add_custom_command(TARGET sample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SFML_BIN_DIR} $<TARGET_FILE_DIR:sample>
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Work")