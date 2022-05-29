add_library(business_logic STATIC
        src/model_bl/post.cpp
        src/model_bl/user.cpp
        src/model_bl/comment.cpp
        src/controller/guest.cpp
        src/controller/client.cpp
        src/controller/author.cpp
        src/controller/admin.cpp)

target_include_directories(business_logic PUBLIC include)
target_link_libraries(business_logic logger)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
