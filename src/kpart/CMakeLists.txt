set(markdownpart_SRCS
    searchtoolbar.cpp
    markdownpartfactory.cpp
    markdownpart.cpp
    markdownsourcedocument.cpp
    markdownbrowserextension.cpp
)

ki18n_wrap_ui(markdownpart_SRCS searchtoolbar.ui)

add_library(kmarkdownwebviewpart  MODULE ${markdownpart_SRCS})


target_link_libraries(kmarkdownwebviewpart
    KMarkdownWebView
    KF5::I18n
    KF5::Parts
)

install( TARGETS kmarkdownwebviewpart  DESTINATION ${KDE_INSTALL_PLUGINDIR})
install(FILES kmarkdownwebviewpart.desktop  DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

install(
  FILES kmarkdownwebviewpartui.rc
  DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/kmarkdownwebviewpart
)

install(
    FILES org.kde.kmarkdownwebviewpart.metainfo.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
