INCLUDE_DIRECTORIES (${CMAKE_SOURCE_DIR} ${SDL2_INCLUDE_DIRS} ${STB_INCLUDE_DIRS})

ADD_EXECUTABLE (GX_EXAMPLE_HELLO_WORLD exm-hello-world.cpp exm-hello-world.hpp)
TARGET_LINK_LIBRARIES (GX_EXAMPLE_HELLO_WORLD GEAROENIX_ENGINE_LIB ${GX_LIBS})