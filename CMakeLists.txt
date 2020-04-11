cmake_minimum_required(VERSION 3.11)

project(LowPolyEngine)

# SETTERS
set(CMAKE_CXX_STANDARD 17)
set(GLAD_DIR "/usr/include/glad")
set(GLFW_DIR "/usr/local/include/GLFW")
SET(PLATFORM_SPECIFIC_LIBS "-lpthread")

include_directories(include)
include_directories(lib)

# SET SOURCES
SET(GLAD_SOURCES ${GLAD_DIR}/src/glad.c)
set(LPE_SOURCES src/main.cpp
		include/encapsulation/L_OpenGL.h src/encapsulation/L_OpenGL.cpp
        include/engine/Camera.h src/engine/Camera.cpp
		include/encapsulation/Light.h src/encapsulation/Light.cpp
		include/encapsulation/Window.h src/encapsulation/Window.cpp
		include/encapsulation/Input.h src/encapsulation/Input.cpp
		include/map/Diamond.h src/map/Diamond.cpp
				include/out/WriteObj.h src/out/WriteObj.cpp
				include/encapsulation/Shader.h src/encapsulation/Shader.cpp
	 			include/map/Perlin.h src/map/Perlin.cpp
				include/map/Chunk.h src/map/Chunk.cpp
				include/map/Terrain.h src/map/Terrain.cpp
				src/out/WriteObj.cpp src/map/Land.cpp
				src/map/Mountain.cpp include/map/Land.h
				include/map/Mountain.h include/map/Biome.h src/map/QuadTree.cpp include/map/QuadTree.h include/encapsulation/Texture.h src/encapsulation/Texture.cpp src/encapsulation/stb_image.cpp include/encapsulation/Menu.h src/encapsulation/Menu.cpp include/encapsulation/VertexBuffer.h src/encapsulation/VertexBuffer.cpp include/encapsulation/VertexArray.h src/encapsulation/VertexArray.cpp src/encapsulation/Layout.cpp include/encapsulation/ErrorManager.h src/encapsulation/ErrorManager.cpp
		include/encapsulation/Matrix.h)

# add exec with sources
add_executable(LowPolyEngine ${LPE_SOURCES} ${GLAD_SOURCES})

# link GLFW
target_include_directories(LowPolyEngine PRIVATE "${GLFW_DIR}/include")
target_link_libraries(LowPolyEngine glfw3)

# link GLAD
target_include_directories(LowPolyEngine PRIVATE "${GLAD_DIR}/include/glad/")
target_link_libraries(LowPolyEngine ${GLAD_DIR}/glad)

# add external libs
target_link_libraries(LowPolyEngine ${PLATFORM_SPECIFIC_LIBS})
target_link_libraries(LowPolyEngine "${CMAKE_DL_LIBS}")
