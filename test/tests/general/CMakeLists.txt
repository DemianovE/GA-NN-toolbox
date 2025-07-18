# add PID tests
add_executable(test_pid_controller
        include/toolbox/general/pid_controller.h
        include/toolbox/general/signal_designer.h
        include/toolbox/general/systems_builder.h
        include/toolbox/general/plotting_toolbox.h

        src/toolbox/general/pid_controller.c
        src/toolbox/general/signal_designer.c
        src/toolbox/general/systems_builder.c
        src/toolbox/general/plotting_toolbox.c

        test/tests/general/test_pid_controller.c)

# add matrix test executable
add_executable(test_signal_designer
        test/tests/general/test_signal_designer.c
        # headers for the toolbox
        include/toolbox/general/signal_designer.h
        # executables of toolbox
        src/toolbox/general/signal_designer.c)

# add matrix test executable
add_executable(test_sort
        test/tests/general/test_sort.c
        # headers for the toolbox
        include/toolbox/general/sort.h
        # executables of toolbox
        src/toolbox/general/sort.c)

# add matrix test executable
add_executable(test_system_builder
        test/tests/general/test_system_builder.c
        # headers for the toolbox
        include/toolbox/general/systems_builder.h
        # executables of toolbox
        src/toolbox/general/systems_builder.c)

target_compile_features(test_pid_controller PRIVATE c_std_99)
target_link_libraries(test_pid_controller m unity_testlib)

target_compile_features(test_signal_designer PRIVATE c_std_99)
target_link_libraries(test_signal_designer m unity_testlib)

target_compile_features(test_sort PRIVATE c_std_99)
target_link_libraries(test_sort m unity_testlib)

target_compile_features(test_system_builder PRIVATE c_std_99)
target_link_libraries(test_system_builder m unity_testlib)

# add_test(NAME test_pid_controller  COMMAND test_pid_controller) # the test id temporary disabled due to CLI
# add_test(NAME test_signal_designer COMMAND test_signal_designer) # the test id temporary disabled due to CLI
add_test(NAME test_sort         COMMAND test_sort)
# add_test(NAME test_system_builder         COMMAND test_system_builder) # the test id temporary disabled due to CLI
