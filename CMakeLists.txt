cmake_minimum_required(VERSION 3.16)

project(KVAK LANGUAGES CXX)

find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

add_executable(KVAK
    main.cpp
    constants.cpp
    colours.cpp
    # characterStats.cpp
    # stat.cpp
    tabs/mainTab.cpp
    calcs/NBody/NBodySolver.cpp
    calcs/SIMPLE/Simple.cpp
    calcs/ODR/odr.cpp
    calcs/FDM/FDM.cpp
    tabs/simpleTab.cpp
    tabs/ODRTab.cpp
    tabs/FDMTab.cpp
    dataStructs/vecs.cpp
    dataStructs/scalarField.cpp
    dataStructs/vectorField2.cpp
    imguiBackends/imgui_impl_win32.cpp
    imguiBackends/imgui_impl_dx12.cpp
    utilityFuncs.cpp

)

target_include_directories(KVAK PRIVATE
    ${VCPKG_INSTALLED_DIR}/x64-windows/include
)

target_link_libraries(KVAK PRIVATE
    imgui::imgui
    implot::implot
    d3d12
    dxgi
    d3dcompiler
)
