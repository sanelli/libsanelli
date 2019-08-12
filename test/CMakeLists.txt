target_sources(sanelli-test
    PRIVATE
        test.cpp
)

add_subdirectory(tree)
add_subdirectory(automa)
add_subdirectory(tokenizer)
add_subdirectory(parser)
add_subdirectory(string)
add_subdirectory(memory)
add_subdirectory(algorithm)
add_subdirectory(fuzzy)
