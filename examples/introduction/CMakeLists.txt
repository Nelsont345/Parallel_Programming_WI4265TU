# MPI support
if( USE_MPI )
  find_package( MPI REQUIRED )
  include_directories( SYSTEM ${MPI_INCLUDE_PATH} )
endif()

# Add an executable for each C-source file
file( GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c )
foreach( src ${SRC} )
  string( REPLACE ".c" "" name ${src} )
  add_executable( ${name} ${src} )
  target_link_libraries( ${name} ${MPI_C_LIBRARIES} m )
endforeach()