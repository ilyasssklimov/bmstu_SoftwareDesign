add_library(data_access_layer STATIC
        src/model/post.cpp
        src/model/user.cpp
        src/model/comment.cpp
        )

target_include_directories(data_access_layer PUBLIC include)
target_include_directories(data_access_layer PUBLIC ../business_logic)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
