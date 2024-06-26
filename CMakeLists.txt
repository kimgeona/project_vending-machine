# ==== cmake 설정 ====
cmake_minimum_required(VERSION 3.28)
project(
    Vending-Machine
    VERSION 1.0.0
    DESCRIPTION "Vending Machine for some drinks."
    LANGUAGES CXX
)

# ==== 프로젝트 버전 정보를 컴파일러 옵션으로 전달합니다. ====
add_compile_definitions(VM_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_compile_definitions(VM_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_compile_definitions(VM_VERSION_PATCH=${PROJECT_VERSION_PATCH})

# ==== 패키지 ====
find_package(PkgConfig REQUIRED)                                # 외부 시스템에서 패키지 검색
pkg_check_modules(gtkmm4 REQUIRED IMPORTED_TARGET gtkmm-4.0)    # 패키지를 타겟 형태로 불러오기

# ==== C++ 표준 설정 ====
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==== include 디렉토리 설정 ====
include_directories(
    ./include
    PkgConfig::GTK4_INCLUDE_DIRS
)

# ==== 파일 조사, 타겟 생성 ====
add_subdirectory(./include)
add_subdirectory(./lib)
add_subdirectory(./src_client)
add_subdirectory(./src_server)

# ==== 운영체제 관련 설정 ====
if(APPLE)
    # Xcode : Apple Framework 만들기
    #set_target_properties(
    #    my_library PROPERTIES
    #    FRAMEWORK TRUE
    #    FRAMEWORK_VERSION ${CMAKE_PROJECT_VERSION} # 프로젝트 버전과 동일하게 가려고 함.
    #    MACOSX_FRAMEWORK_IDENTIFIER org.cmake.my_library
    #)
    # Xcode : Working Directory 설정
    set_target_properties(
        client PROPERTIES
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src_client_io/
    )
    set_target_properties(
        server PROPERTIES
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src_server_io/
    )
elseif(WIN32)
    # MSVC : Working Directory 설정
    set_target_properties(
        client PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src_client_io/
    )
    set_target_properties(
        server PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src_server_io/
    )
    target_compile_options(my_library PRIVATE "/utf-8")
    target_compile_options(client PRIVATE "/utf-8")
    target_compile_options(server PRIVATE "/utf-8")
endif()

# ==== 프로젝트 설치 ====
# ...나중에 작성 예정

# ==== 변수 출력 ====
# include(CMakePrintHelpers)
# cmake_print_variables(CMAKE_PROJECT_VERSION)
# cmake_print_variables(INCLUDE_LIST)
# cmake_print_variables(LIB_LIST)
# cmake_print_variables(SRC_LIST)