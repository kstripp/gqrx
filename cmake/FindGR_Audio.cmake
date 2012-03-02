########################################################################
# Find the GNU Radio Audio libraries
########################################################################

# - Try to find gr_audio
# Once done, this will define 
#
#  GR_AUDIO_FOUND - system has gnuradio-audio
#  GR_AUDIO_INCLUDE_DIRS - the GR_AUDIO include directories
#  GR_AUDIO_LIBRARIES - link these to use GR_AUDIO

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(gnuradio-audio_PKGCONF gnuradio-audio)

# Include dir
find_path(GR_AUDIO_INCLUDE_DIR
	NAMES gnuradio/gr_audio_api.h
	PATHS ${GNURADIO-GR_AUDIO_PKGCONF_INCLUDE_DIRS}
	)

# Finally the library itself
find_library(GR_AUDIO_LIBRARY
	NAMES gnuradio-audio
	PATHS ${GNURADIO-GR_AUDIO_PKGCONF_LIBRARY_DIRS}
	)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(GR_AUDIO_PROCESS_INCLUDES GR_AUDIO_INCLUDE_DIR )
set(GR_AUDIO_PROCESS_LIBS GR_AUDIO_LIBRARY )
libfind_process(gnuradio-audio)

