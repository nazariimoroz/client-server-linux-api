project(client-server-linux-api)
cmake_minimum_required (VERSION 3.8)

add_executable (${PROJECT_NAME}
    main.cpp 
    server.h 
    client.h
    defines.h)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
