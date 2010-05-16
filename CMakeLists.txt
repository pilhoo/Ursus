SET(CMAKE_VERBOSE_MAKEFILE ON)

ADD_DEFINITIONS(-Wall -O2 -ggdb)

project ( ursus )

find_package ( KDE4 REQUIRED )
include_directories ( ${KDE4_INCLUDES} )

set ( ursus_SRCS
 main.cpp
 player.cpp
 playlistdroppointer.cpp
 playlistitem.cpp
 playlistwidget.cpp
 metainforesolver.cpp
 playlisttabs.cpp
 playlisttabbar.cpp
 mainwin.cpp
 trayicon.cpp
#  miniwin.cpp
 ursusapp.cpp
 )
qt4_automoc(${ursus_SRCS})

add_subdirectory(icons)

kde4_add_executable ( ursus ${ursus_SRCS} )
target_link_libraries ( ursus ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS} ${KDE4_PHONON_LIBS})

install(FILES ursus.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR})
install(TARGETS ursus DESTINATION ${BIN_INSTALL_DIR})
install(FILES ursusui.rc DESTINATION  ${DATA_INSTALL_DIR}/ursus)
