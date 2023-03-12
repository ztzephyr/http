cmake_minimum_required(VERSION 3.14)
project(pro1)

set(CMAKE_CXX_STANDARD 11)

add_executable(pro1 
    main.cpp sort_test.h test_string.h 
    test_arr.h test_tree.h test_list.h
    util.h test_dfs.h test_hash.h 
    test_bfs.h test_dynamic.h 
    test_greedy.h test_backtrack.h 
    test_design.h test_stack.h)