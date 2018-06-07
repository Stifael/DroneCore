add_library(dronecore_offboard ${PLUGIN_LIBRARY_TYPE}
    offboard.cpp
    offboard_impl.cpp
)

target_link_libraries(dronecore_offboard
    dronecore
)

target_include_directories(dronecore_offboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES
    offboard.h
    DESTINATION ${dronecore_install_include_dir}
)

install(TARGETS dronecore_offboard
    #EXPORT dronecore-targets
    DESTINATION ${dronecore_install_lib_dir}
)
