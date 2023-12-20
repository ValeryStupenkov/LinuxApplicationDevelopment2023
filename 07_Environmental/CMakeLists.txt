cmake_minimum_required(VERSION 3.22)
project(rhasher C)
set(CMAKE_C_STANDARD 17)

option(READLINE "Set readline mode" false)

set(LIBS "")
find_library(LIB_RHASH rhash)
if (NOT LIB_RHASH)
	message(FATAL_ERROR "LIB_RHASH was not found")
endif ()
list(APPEND LIBS ${LIB_RHASH})

set(COMPILE_OPTIONS "")

if (READLINE)
    	find_library(LIB_READLINE readline REQUIRED)
    	if (NOT LIB_READLINE)
        	message(FATAL_ERROR "LIB_READLINE was not found")
    	else ()
        	list(APPEND LIBS ${LIB_READLINE})
        	list(APPEND COMPILE_OPTIONS "READLINE=1")
    	endif ()
endif ()

add_executable(rhasher rhasher.c)
target_link_libraries(rhasher ${LIBS})
target_compile_definitions(rhasher PRIVATE ${COMPILE_OPTIONS})

add_custom_target(test DEPENDS rhasher test_md5 test_sha1)
add_custom_target(distclean COMMAND rm -r rhasher Makefile* CMakeFiles CMakeCache.txt* cmake_install.cmake input output)

find_program(MD5SUM md5sum)
if (MD5SUM)
	add_custom_target(test_md5 DEPENDS rhasher 
		COMMAND echo "test" > input 
		COMMAND md5sum input | cut -d ' ' -f 1 > output 
		COMMAND echo 'MD5 \"test' | ./rhasher | cut -d ' ' -f 2 | cmp output 
		COMMAND rm input output 
            	)
else()
    message(WARNING "md5sum has to be installed")
    add_custom_target(test_md5 DEPENDS rhasher)
endif()

find_program(SHA1SUM sha1sum)
if (SHA1SUM)
    	add_custom_target(test_sha1 DEPENDS rhasher 
            	COMMAND echo "test" > input 
		COMMAND sha1sum input | cut -d ' ' -f 1 > output 
		COMMAND echo 'SHA1 \"test' | ./rhasher | cut -d ' ' -f 2 | cmp output 
		COMMAND rm input output 
            	)
else()
    message(WARNING "sha1sum has to be installed")
    add_custom_target(test_sha1 DEPENDS rhasher)
endif()


