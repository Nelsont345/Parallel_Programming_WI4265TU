# Threads support
if( USE_Threads )
  find_package( Threads REQUIRED )
endif()

# Add an executable for each C-source file
file( GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c )
foreach( src ${SRC} )
  string( REPLACE ".c" "" name ${src} )
  add_executable( ${name} ${src} )
  target_link_libraries( ${name} ${CMAKE_THREAD_LIBS_INIT} m )
endforeach()
