# 디렉토리에 있는 *.cpp 파일을 LIB_LIST 변수에 추가한다
file(
    GLOB_RECURSE LIB_LIST CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)
# 변수를 상위 스코프로 올린다
set(LIB_LIST ${LIB_LIST} PARENT_SCOPE)

# my_library
add_library(my_library ${INCLUDE_LIST} ${LIB_LIST})
