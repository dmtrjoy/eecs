find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile)
    set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/src)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)

    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
    file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

    add_custom_target(doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
else()
    message("Could not generate documentation since Doxygen is not installed")
endif()

find_package(Sphinx)

set(SPHINX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/sphinx)

add_custom_target(sphinx ALL
    COMMAND
        ${SPHINX_EXECUTABLE} -b html
        -Dbreathe_projects.eecs=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE_DIR} ${SPHINX_BUILD_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Sphinx"
    VERBATIM
)
