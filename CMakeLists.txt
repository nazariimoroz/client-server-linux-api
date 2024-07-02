project(app)
cmake_minimum_required (VERSION 3.8)

add_executable (app 
    main.cpp 
    server.h 
    client.h
    defines.h)

set_property(TARGET app PROPERTY CXX_STANDARD 17)

target_link_libraries(app PRIVATE pthread)
