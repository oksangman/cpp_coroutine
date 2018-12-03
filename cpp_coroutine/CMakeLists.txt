# CMakeList.txt: cpp_coroutine에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

FILE(GLOB_RECURSE MY_HEADERS "include/*.h")
FILE(GLOB MY_SOURCES "src/*.cpp")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (${PROJECTNAME} cpp_corutine ${MY_SOURCES} ${MY_HEADERS})


# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
