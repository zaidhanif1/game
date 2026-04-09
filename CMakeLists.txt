cmake_minimum_required(VERSION 3.28)
project(KnightsQuest LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(KnightsQuest
    main.cpp
    Player/Player.cpp
    GameObject/GameObject.cpp
    Animation/Animation.cpp
    Platform/Platform.cpp
    Physics/Collision.cpp
    Enemy/Enemy.cpp
)

target_include_directories(KnightsQuest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(KnightsQuest PRIVATE cxx_std_17)
target_link_libraries(KnightsQuest PRIVATE SFML::Graphics)

# Copy assets to the output directory so the executable can find them at runtime
add_custom_command(TARGET KnightsQuest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:KnightsQuest>/assets
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT KnightsQuest)
