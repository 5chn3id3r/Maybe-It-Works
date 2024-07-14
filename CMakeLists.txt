cmake_minimum_required(VERSION 3.5)

project(ItWorks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE CXX_HEADERS "./src/*.hpp")
file(GLOB_RECURSE CXX_SOURCES "./src/*.cpp")
file(GLOB_RECURSE C_HEADERS "./src/*.h")
file(GLOB_RECURSE C_SOURCES "./src/*.c")


add_executable(
ItWorks
    ${CXX_HEADERS}
	${CXX_SOURCES}
	${C_HEADERS}
	${C_SOURCES}
)


file(GLOB_RECURSE CXX_HEADERS "./calcgen/*.hpp")
file(GLOB_RECURSE CXX_SOURCES "./calcgen/*.cpp")
file(GLOB_RECURSE C_HEADERS "./calcgen/*.h")
file(GLOB_RECURSE C_SOURCES "./calcgen/*.c")


add_executable(
calcgen
    ${CXX_HEADERS}
	${CXX_SOURCES}
	${C_HEADERS}
	${C_SOURCES}
)


include(GNUInstallDirs)
install(TARGETS ItWorks
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(GNUInstallDirs)
install(TARGETS calcgen
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
