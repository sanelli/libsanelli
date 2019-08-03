target_sources(testme
    PRIVATE
        test.cpp
)

add_subdirectory(tree)
add_subdirectory(automa)
add_subdirectory(tokenizer)
add_subdirectory(parser)
add_subdirectory(string)
