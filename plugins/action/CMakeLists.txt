add_library(dronecore_action ${PLUGIN_LIBRARY_TYPE}
    action.cpp
    action_impl.cpp
)

target_link_libraries(dronecore_action
    dronecore
)

target_include_directories(dronecore_action PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES
    action.h
    action_result.h
    DESTINATION ${dronecore_install_include_dir}
)

install(TARGETS dronecore_action
    DESTINATION ${dronecore_install_lib_dir}
)
