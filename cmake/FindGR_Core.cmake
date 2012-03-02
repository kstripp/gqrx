########################################################################
# Find the GNU Radio Core libraries
########################################################################

# - Try to find gr_core
# Once done, this will define 
#
#  GR_CORE_FOUND - system has gnuradio-core
#  GR_CORE_INCLUDE_DIRS - the GR_CORE include directories
#  GR_CORE_LIBRARIES - link these to use GR_CORE

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(gnuradio-core_PKGCONF gnuradio-core)

# Include dir
find_path(GR_CORE_INCLUDE_DIR
	NAMES gnuradio/gr_core_api.h
	PATHS ${GNURADIO-GR_CORE_PKGCONF_INCLUDE_DIRS}
	)

# Finally the library itself
find_library(GR_CORE_LIBRARY
	NAMES gnuradio-core
	PATHS ${GNURADIO-GR_CORE_PKGCONF_LIBRARY_DIRS}
	)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(GR_CORE_PROCESS_INCLUDES GR_CORE_INCLUDE_DIR )
set(GR_CORE_PROCESS_LIBS GR_CORE_LIBRARY )
libfind_process(gnuradio-core)

