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

include_directories(include)

set(71K2ledeb
		src/engine/main.cpp

		include/engine/ObjParser.hpp
		src/engine/ObjParser.cpp

		include/encapsulation/L_OpenGL.hpp
		src/encapsulation/L_OpenGL.cpp

		include/engine/Camera.hpp
		src/engine/Camera.cpp

		include/Triangle.hpp

		include/TypeDef.hpp

		include/Vector.hpp

		include/Light.hpp
		src/Light.cpp

		include/encapsulation/Window.hpp

		include/encapsulation/Input.hpp
		src/encapsulation/Input.cpp

		include/map/Diamond.hpp
		src/map/Diamond.cpp

		include/map/Cross.hpp
		src/map/Cross.cpp

		)


add_executable(ledeb ${71K2ledeb})

if (WIN32)
	set(LIBS 	${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
			${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
else()
	set(LIBS	dl
			${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
			${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARIES})
endif (WIN32)


target_include_directories(ledeb
		PRIVATE ${CMAKE_SOURCE_DIR}/include
		PRIVATE ${SFML_INCLUDE_DIR}
		PRIVATE ${OPENGL_INCLUDE_DIRS}
		PRIVATE ${GLUT_INCLUDE_DIRS}
		PRIVATE ${GLEW_INCLUDE_DIRS}
		PRIVATE include/
		)

target_link_libraries(ledeb ${LIBS}  )
