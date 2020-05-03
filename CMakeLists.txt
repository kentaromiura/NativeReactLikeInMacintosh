cmake_minimum_required(VERSION 3.0)

add_application(Dialog
    main.c
    dialog.c
    dialog.r
    dukbridge.c
    duktape.c
    )

target_link_libraries(Dialog -lm)

# Enable -ffunction-sections and -gc-sections to make the app as small as possible
# On 68K, also enable --mac-single to build it as a single-segment app (so that this code path doesn't rot)
set_target_properties(Dialog PROPERTIES COMPILE_OPTIONS -ffunction-sections)
if(CMAKE_SYSTEM_NAME MATCHES Retro68)
    set_target_properties(Dialog PROPERTIES LINK_FLAGS "-Wl,-gc-sections -Wl,--mac-single")

else()
    set_target_properties(Dialog PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
endif()
