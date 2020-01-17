cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project(71K2ledeb)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules/)
if (WIN32)
	set(SFML_ROOT ${CMAKE_SOURCE_DIR}/lib/SFML/)
	set(GLUT_ROOT_PATH ${CMAKE_SOURCE_DIR}/lib/GL/)
	set(GLUT_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/GL/lib/)


	set(OPENGL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/GL/include/)
	set(GLUT_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/GL/include/)

endif()

find_path( GLUT_INCLUDE_DIR NAMES GL/glut.h PATHS  ${GLUT_ROOT_PATH}/include/)
FIND_LIBRARY(GLUT_glut_LIBRARY NAMES glut glut32 PATHS ${GLUT_ROOT_PATH}/lib/)

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
find_package(OpenGL REQUIRED)
find_package(GLUT  REQUIRED)
find_package(GLEW REQUIRED)
FIND_PACKAGE(FLTK REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)


include_directories(include)

set(71K2ledeb
		src/engine/main.cpp

		include/encapsulation/L_OpenGL.hpp
		src/encapsulation/L_OpenGL.cpp

		include/engine/Camera.hpp
		src/engine/Camera.cpp

		include/Light.hpp
		src/Light.cpp

		include/encapsulation/Window.hpp

		include/encapsulation/Input.hpp
		src/encapsulation/Input.cpp

		include/map/Diamond.hpp
		src/map/Diamond.cpp

		include/encapsulation/Shader.h src/encapsulation/Shader.cpp src/encapsulation/Window.cpp include/map/Perlin.h src/map/Perlin.cpp src/map/Terrain.cpp src/map/Chunk.cpp include/map/Chunk.h include/map/Terrain.h src/out/WriteObj.cpp src/map/Land.cpp src/map/Mountain.cpp include/map/Land.h include/map/Mountain.h include/map/Biome.h src/map/QuadTree.cpp include/map/QuadTree.h)


add_executable(ledeb ${71K2ledeb})

if (WIN32)
	set(LIBS 	${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
			${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
else()
	set(LIBS	dl
			${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
			${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES} ${FLTK_LIBRARIES} ${GLFW_LIBRARIES})
endif (WIN32)


target_include_directories(ledeb
		PRIVATE ${CMAKE_SOURCE_DIR}/include
		PRIVATE ${SFML_INCLUDE_DIR}
		PRIVATE ${OPENGL_INCLUDE_DIRS}
		PRIVATE ${GLUT_INCLUDE_DIRS}
		PRIVATE ${GLEW_INCLUDE_DIRS}
		PRIVATE include/
		)

set(GLAD_DIR "/usr/include/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(ledeb PRIVATE "${GLAD_DIR}/include")
target_link_libraries(ledeb "glad" "${CMAKE_DL_LIBS}")
target_link_libraries(ledeb ${LIBS})


