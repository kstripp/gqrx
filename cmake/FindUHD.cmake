########################################################################
# Find the library for the USRP Hardware Driver
########################################################################


# - Try to find Gr-UHD
# Once done, this will define 
#
#  UHD_FOUND - system has gr-uhd
#  UHD_INCLUDE_DIRS - the UHD include directories
#  UHD_LIBRARIES - link these to use UHD

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(gnuradio-uhd_PKGCONF gnuradio-uhd)

# Include dir
find_path(UHD_INCLUDE_DIR
	NAMES gnuradio/gr_uhd_usrp_source.h
	PATHS ${GNURADIO-UHD_PKGCONF_INCLUDE_DIRS}
	)

# Finally the library itself
find_library(UHD_LIBRARY
	NAMES gnuradio-uhd
	PATHS ${GNURADIO-UHD_PKGCONF_LIBRARY_DIRS}
	)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(UHD_PROCESS_INCLUDES UHD_INCLUDE_DIR )
set(UHD_PROCESS_LIBS UHD_LIBRARY )
libfind_process(gnuradio-uhd)


########################################################################

#INCLUDE(FindPkgConfig)
#PKG_CHECK_MODULES(PC_UHD QUIET uhd)
#
#FIND_PATH(
#    UHD_INCLUDE_DIRS
#    NAMES uhd/config.hpp
#    HINTS $ENV{UHD_DIR}/include
#        ${PC_UHD_INCLUDEDIR}
#    PATHS /usr/local/include
#          /usr/include
#)
#
#FIND_LIBRARY(
#    UHD_LIBRARIES
#    NAMES uhd
#    HINTS $ENV{UHD_DIR}/lib
#        ${PC_UHD_LIBDIR}
#    PATHS /usr/local/lib
#          /usr/lib
#)
#
#INCLUDE(FindPackageHandleStandardArgs)
#FIND_PACKAGE_HANDLE_STANDARD_ARGS(UHD DEFAULT_MSG UHD_LIBRARIES UHD_INCLUDE_DIRS)
#MARK_AS_ADVANCED(UHD_LIBRARIES UHD_INCLUDE_DIRS)
