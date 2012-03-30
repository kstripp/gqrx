#####################################################################
# Setup
#####################################################################
cmake_minimum_required( VERSION 2.6 )
project( gqrx )
set (gqrx_VERSION_MAJOR 0)
set (gqrx_VERSION_MINOR 0)
set ( CMAKE_BUILD_TYPE Release )

list (APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

configure_file(
	"${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
	)


#####################################################################
# Compiler flags
#####################################################################
add_definitions ( -Wall )

#TODO- this should probably be done with a config file
# rather than a compile option
add_definitions(-DVERSION="\"${VERSION_MAJOR}"."${VERSION_MINOR}"\")


#####################################################################
# Setup QT4
#####################################################################
find_package ( Qt4 REQUIRED )

include ( ${QT_USE_FILE} )
include_directories (
	${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
	${QT_QTCORE_INCLUDE_DIR} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR})

#####################################################################
# Setup GNURadio
#####################################################################

#TODO: The include directories here seem a bit hacky... 

#---GNU Radio Core-------------------------------
find_package( GR_Core REQUIRED )
include_directories( ${GR_CORE_INCLUDE_DIR} )
include_directories( ${GR_CORE_INCLUDE_DIR}/gnuradio )
set( gr_link_libs ${GR_CORE_LIBRARY})

#---GNU Radio FCD--------------------------------
option( USE_FCD "Use the FCD Driver" OFF )
if (USE_FCD)
	find_package ( FCD REQUIRED )
	include_directories( ${FCD_INCLUDE_DIR} )
	include_directories( ${GR_CORE_INCLUDE_DIR}/fcd )
	set( gr_link_libs ${gr_link_libs} ${FCD_LIBRARY})
	set( gqrx_HDRS ${gqrx_HDRS} dsp/rx_source_fcd.h )
	set( gqrx_SRCS ${gqrx_SRCS} dsp/rx_source_fcd.cpp )
endif(USE_FCD)

#---GNU Radio UHD--------------------------------
option( USE_UHD "Use the UHD Driver" ON )
if (USE_UHD)
	find_package ( UHD REQUIRED )
	include_directories( ${UHD_INCLUDE_DIR} )
	include_directories( ${GR_CORE_INCLUDE_DIR}/uhd )
	set( gr_link_libs ${gr_link_libs} ${UHD_LIBRARY})
	set( gqrx_HDRS ${gqrx_HDRS} dsp/rx_source_uhd.h )
	set( gqrx_SRCS ${gqrx_SRCS} dsp/rx_source_uhd.cpp )
endif(USE_UHD)

#---GNU Radio Audio------------------------------
find_package(GR_Audio REQUIRED )
include_directories( ${GR_AUDIO_INCLUDE_DIR} )
include_directories( ${GR_CORE_INCLUDE_DIR}/gnuradio )
set( gr_link_libs ${gr_link_libs} ${GR_AUDIO_LIBRARY})

#####################################################################
# Header files
#####################################################################
set ( gqrx_HDRS ${gqrx_HDRS}
	receiver.h
	dsp/rx_fft.h
	dsp/rx_filter.h
	dsp/rx_demod_fm.h
	dsp/rx_meter.h
	dsp/rx_demod_am.h
	dsp/resampler_ff.h
	dsp/sniffer_f.h
	dsp/afsk1200/filter-i386.h
	dsp/afsk1200/filter.h
	tlm/arissat/ss_types_common.h
	tlm/arissat/ss_stdint.h
	tlm/arissat/scale_therm.h
	tlm/arissat/scale_psu.h
	tlm/arissat/scale_ppt.h
	dsp/rx_source_base.h
	dsp/rx_agc_xx.h
	dsp/agc_impl.h
	dsp/correct_iq_cc.h
	)

#####################################################################
# Source files
#####################################################################
set ( gqrx_SRCS ${gqrx_SRCS}
	receiver.cpp
	main.cpp
	mainwindow.cpp
	qtgui/freqctrl.cpp
	qtgui/meter.cpp
	qtgui/plotter.cpp
	dsp/rx_fft.cpp
	dsp/rx_filter.cpp
	dsp/rx_demod_fm.cpp
	dsp/rx_meter.cpp
	qtgui/dockrxopt.cpp
	dsp/rx_demod_am.cpp
	qtgui/ioconfig.cpp
	qtgui/dockfcdctl.cpp
	qtgui/dockaudio.cpp
	dsp/resampler_ff.cpp
	qtgui/dockfft.cpp
	dsp/sniffer_f.cpp
	dsp/afsk1200/costabf.c
	dsp/afsk1200/cafsk12.cpp
	qtgui/dockiqplayer.cpp
	qtgui/afsk1200win.cpp
	qtgui/bpsk1000win.cpp
	qtgui/arissattlm.cpp
	tlm/arissat/scale_therm.c
	tlm/arissat/scale_psu.c
	tlm/arissat/scale_ppt.c
	dsp/rx_source_base.cpp
	dsp/rx_agc_xx.cpp
	dsp/agc_impl.cpp
	dsp/correct_iq_cc.cpp
	)

set ( gqrx_UIS
	qtgui/dockrxopt.ui
	mainwindow.ui
	qtgui/ioconfig.ui
	qtgui/dockfcdctl.ui
	qtgui/dockaudio.ui
	qtgui/dockfft.ui
	qtgui/dockiqplayer.ui
	qtgui/afsk1200win.ui
	qtgui/bpsk1000win.ui
	qtgui/arissattlm.ui
	)
QT4_WRAP_UI(UIS ${gqrx_UIS})

set ( gqrx_RSCS
	icons.qrc
	)
QT4_ADD_RESOURCES(RSCS ${gqrx_RSCS})

set ( gqrx_MOCS
	mainwindow.h
	qtgui/freqctrl.h
	qtgui/meter.h
	qtgui/plotter.h
	qtgui/dockrxopt.h
	qtgui/ioconfig.h
	qtgui/dockfcdctl.h
	qtgui/dockaudio.h
	qtgui/dockfft.h
	dsp/afsk1200/cafsk12.h
	qtgui/dockiqplayer.h
	qtgui/afsk1200win.h
	qtgui/bpsk1000win.h
	qtgui/arissattlm.h
	)
QT4_WRAP_CPP(MOCS ${gqrx_MOCS})

#####################################################################
# Compile and Link
#####################################################################
add_executable ( gqrx ${gqrx_SRCS} ${UIS} ${RSCS} ${TRS} ${MOCS} )
target_link_libraries ( gqrx  ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} )
target_link_libraries (gqrx ${gr_link_libs} )
