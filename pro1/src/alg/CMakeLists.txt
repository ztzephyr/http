add_library(common_alg "")

# 只设置使用源文件，不使用头文件(需要明确指定使用何种语言编译目标)
target_sources(common_alg
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/alg_sort.h
        ${CMAKE_CURRENT_LIST_DIR}/alg_lru.h
)
# 指定使用C++编译目标文件
set_target_properties(common_alg PROPERTIES LINKER_LANGUAGE CXX)


#target_include_directories(common_alg
#    PUBLIC
#        ${CMAKE_CURRENT_LIST_DIR}
#)
