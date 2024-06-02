# 디렉토리에 있는 *.cpp 파일을 SRC_SERVER_LIST 변수에 추가한다
file(
    GLOB_RECURSE SRC_SERVER_LIST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
# 변수를 상위 스코프로 올린다
set(SRC_SERVER_LIST ${SRC_SERVER_LIST} PARENT_SCOPE)

# my_program
add_executable(server ${INCLUDE_LIST} ${SRC_SERVER_LIST})

# my_program 의 의존성 라이브러리
target_link_libraries(
    server PRIVATE
    my_library
    PkgConfig::gtkmm4
)