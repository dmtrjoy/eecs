find_program(SPHINX_EXECUTABLE
    NAMES sphinx-build
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(Sphinx
    REQUIRED_VARS SPHINX_EXECUTABLE
)