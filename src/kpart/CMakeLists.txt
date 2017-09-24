set(markdownpart_SRCS
    markdownpartfactory.cpp
    markdownpart.cpp
    markdownsourcedocument.cpp
    markdownbrowserextension.cpp
)

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
    FILES org.kde.kmarkdownwebviewpart.appdata.xml
    DESTINATION ${KDE_INSTALL_METAINFODIR}
)
