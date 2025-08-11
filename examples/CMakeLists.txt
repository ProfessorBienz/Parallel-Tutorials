## Grab all .cpp files in test directory
file(GLOB CPP_SOURCES CONFIGURE_DEPENDS "*.cpp")

## Go through each CPP file
foreach(src ${CPP_SOURCES})
    
    ## Grab the name without full path or extension
    get_filename_component(exec_name ${src} NAME_WE)

    ## Create executable
    add_executable(${exec_name} ${src})

    # Link with MPI 
    target_link_libraries(${exec_name} tutorial ${MPI_LIBRARIES})
endforeach()
