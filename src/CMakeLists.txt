

file(GLOB vcs_source "*.cpp")
file(GLOB vcs_include "*.hpp")
source_group("include" FILES ${vcs_include})
source_group("source" FILES ${vcs_source})


add_executable("vc-sword" ${vcs_include} ${vcs_source} ${vcs_includes})
target_link_libraries("vc-sword" ${vcs_dependency_libs})
#add_precompiled_header(devl-test	${tilenet_library_pch_file})
