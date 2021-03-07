cmake_minimum_required(VERSION 3.11)

project(LowPolyEngine)

# SETTERS
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(GLFW_DIR "/usr/include/GLFW")

add_subdirectory(lib/glad/)
SET(PLATFORM_SPECIFIC_LIBS "-lpthread")

include_directories(include)
include_directories(lib)
include_directories(lib/glad/include/glad)

# SET SOURCES
set(LPE_SOURCES src/main.cpp
        include/encapsulation/Renderer.h src/encapsulation/Renderer.cpp
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
		include/encapsulation/Matrix.h include/encapsulation/FrameBuffer.h src/encapsulation/FrameBuffer.cpp include/encapsulation/GUI.h src/encapsulation/GUI.cpp include/encapsulation/ShadowMap.h src/encapsulation/ShadowMap.cpp src/tool/ModelCreator.cpp include/tool/ModelCreator.h)

# add exec with sources
add_executable(LowPolyEngine ${LPE_SOURCES})

set(LIBS glfw glad ${PLATFORM_SPECIFIC_LIBS} ${CMAKE_DL_LIBS})
# add external libs
target_link_libraries(LowPolyEngine ${LIBS})
