# OpenMP support
if( USE_OpenMP )
  find_package( OpenMP REQUIRED )
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Add an executable for each C-source file
file( GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c )
foreach( src ${SRC} )
  string( REPLACE ".c" "" name ${src} )
  add_executable( ${name} ${src} )
  target_link_libraries( ${name} m )
endforeach()
