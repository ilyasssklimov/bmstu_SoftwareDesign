add_library(business_logic STATIC
        src/model/post.cpp
        src/model/user.cpp
        src/model/comment.cpp
        src/controller/guest.cpp
        src/controller/client.cpp
        src/controller/author.cpp
        src/controller/admin.cpp
        src/logger/logger.cpp)

target_include_directories(business_logic PUBLIC include)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
