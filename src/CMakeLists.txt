add_library(
        controller.cpp
        display.cpp
        mesh.cpp
        random.cpp
        shader.cpp
        shadow_map.cpp
        texture.cpp
        Ext/obj_loader.cpp
        Ext/stb_image.cpp
        )
target_link_directories(ls_tree PUBLIC ${Boost_LIBRARY_DIRS})
target_include_directories(ls_tree PUBLIC ${PROJECT_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
target_link_libraries(ls_tree PUBLIC glm::glm OpenGL::GL range-v3::range-v3
        ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${Boost_LIBRARIES})
target_compile_features(ls_tree PUBLIC cxx_std_20)