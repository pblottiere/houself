add_subdirectory (os)
add_subdirectory (common)

if(NOT OS_ONLY)
  add_subdirectory (arduino)
endif(NOT OS_ONLY)