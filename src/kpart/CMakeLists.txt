
configure_file(markdownpartconfig.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/markdownpartconfig.h)

set(markdownpart_SRCS
    searchtoolbar.cpp
    markdownpartfactory.cpp
    markdownpart.cpp
    markdownsourcedocument.cpp
    markdownbrowserextension.cpp
)

ki18n_wrap_ui(markdownpart_SRCS searchtoolbar.ui)

qt5_add_resources(markdownpart_SRCS
    markdownpart.qrc
)

add_library(kmarkdownwebviewpart  MODULE ${markdownpart_SRCS})
kcoreaddons_desktop_to_json(kmarkdownwebviewpart kmarkdownwebviewpart.desktop)


target_link_libraries(kmarkdownwebviewpart
    KMarkdownWebView
    KF5::I18n
    KF5::Parts
)

install(TARGETS kmarkdownwebviewpart  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf5/parts)
install(FILES kmarkdownwebviewpart.desktop  DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

install(
    FILES org.kde.kmarkdownwebviewpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
