target_sources(libsanelli
    PUBLIC
        sanelli.hpp
)

add_subdirectory(debug)
add_subdirectory(tree)
add_subdirectory(automa)
add_subdirectory(string)
add_subdirectory(parser)
add_subdirectory(tokenizer)
add_subdirectory(memory)
add_subdirectory(fuzzy)
add_subdirectory(math)