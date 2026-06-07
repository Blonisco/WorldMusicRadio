cmake_minimum_required(VERSION 3.15)
project(WorldMusicRadio LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -------------------------------------------------------------------
# 1. 查找系统工具与 OpenGL
# -------------------------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# 使用 pkg-config 查找 GLFW3 和 libvlc (彻底避开 CMake 找不到 .cmake 的包名问题)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)
pkg_check_modules(libvlc REQUIRED IMPORTED_TARGET libvlc)

# -------------------------------------------------------------------
# 2. 通过 FetchContent 引入 CPR
# -------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG        1.10.x  
)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")
set(CPR_BUILD_TESTS OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(cpr)

# -------------------------------------------------------------------
# 3. 源码路径定义
# -------------------------------------------------------------------
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
set(Src_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(SOURCES
    ${Src_DIR}/main.cpp
    ${Src_DIR}/UI.cpp
    ${Src_DIR}/RadioPlayer.cpp
    ${Src_DIR}/apiProvider.cpp
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# -------------------------------------------------------------------
# 4. 创建可执行文件
# -------------------------------------------------------------------
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES})
endif()

# -------------------------------------------------------------------
# 5. 头文件包含路径
# -------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PRIVATE
    ${Src_DIR}
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# -------------------------------------------------------------------
# 6. 链接库
# -------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::GLFW       # 链接来自 pkg-config 的 GLFW
    OpenGL::GL
    cpr::cpr
    PkgConfig::libvlc     # 链接来自 pkg-config 的 libvlc
)
