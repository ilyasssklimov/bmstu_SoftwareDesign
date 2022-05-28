include(FetchContent)

FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)
FetchContent_MakeAvailable(libpqxx)

add_library(data_access_layer STATIC
        src/model_dal/post.cpp
        src/model_dal/user.cpp
        src/model_dal/comment.cpp
        src/database/pg_database.cpp
        )

target_include_directories(data_access_layer PUBLIC include)
# target_include_directories(data_access_layer PUBLIC ../business_logic)

target_link_libraries(data_access_layer "${PQXX_LIBRARIES}")

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
