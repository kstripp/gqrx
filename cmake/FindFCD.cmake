########################################################################
# Find the library for the Funcube Dongle Hardware Driver
########################################################################

# - Try to find Gr-FCD
# Once done, this will define 
#
#  FCD_FOUND - system has gr-fcd
#  FCD_INCLUDE_DIRS - the FCD include directories
#  FCD_LIBRARIES - link these to use FCD

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(gnuradio-fcd_PKGCONF gnuradio-fcd)

# Include dir
find_path(FCD_INCLUDE_DIR
	NAMES fcd/fcd_source_c.h
	PATHS ${GNURADIO-FCD_PKGCONF_INCLUDE_DIRS}
	)

# Finally the library itself
find_library(FCD_LIBRARY
	NAMES gnuradio-fcd
	PATHS ${GNURADIO-FCD_PKGCONF_LIBRARY_DIRS}
	)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(FCD_PROCESS_INCLUDES FCD_INCLUDE_DIR )
set(FCD_PROCESS_LIBS FCD_LIBRARY )
libfind_process(gnuradio-fcd)

