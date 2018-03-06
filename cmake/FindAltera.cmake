find_program(AOCL_CMD aocl)

if (NOT AOCL_CMD)
	message(FATAL_ERROR "aocl not found! Please check your Altera SDK installation.")
endif()

set(AOCL_ARG_CFLAGS "compile-config")
set(AOCL_ARG_LINKFLAGS "link-config")
set(AOCL_ARCH "--arm")

execute_process(COMMAND ${AOCL_CMD} ${AOCL_ARG_CFLAGS} ${AOCL_ARCH}
    RESULT_VARIABLE AOCL_RESULT
    OUTPUT_VARIABLE AOCL_CFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if (NOT ${AOCL_RESULT} EQUAL 0)
    message(FATAL_ERROR "Failure while running ${AOCL_CMD} ${AOCL_ARG_CFLAGS} ${AOCL_ARCH}")
endif()
message(STATUS "Found Altera SDK: ${AOCL_CFLAGS}")

# include_directories() does not like having -I, so strip it
string(REPLACE "-I" "" AOCL_STRIPPED_CFLAGS ${AOCL_CFLAGS})

execute_process(COMMAND ${AOCL_CMD} ${AOCL_ARG_LINKFLAGS} ${AOCL_ARCH}
    RESULT_VARIABLE AOCL_RESULT
    OUTPUT_VARIABLE AOCL_LINKFLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE)

if (NOT ${AOCL_RESULT} EQUAL 0)
    message(FATAL_ERROR "Failure while running ${AOCL_CMD} ${AOCL_ARG_LINKFLAGS} ${AOCL_ARCH}")
endif()

message(STATUS "Found Altera SDK: ${AOCL_LINKFLAGS}")

set(OpenCL_LIBRARIES "${AOCL_LINKFLAGS}")
set(OpenCL_INCLUDE_DIRS "${AOCL_STRIPPED_CFLAGS}")

add_definitions(-DALTERA)
