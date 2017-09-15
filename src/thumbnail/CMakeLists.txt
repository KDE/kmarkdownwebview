set(markdownthumbcreator_SRCS
    markdowncreator.cpp
    markdownsourcedocument.cpp
)

add_library(markdownthumbnail MODULE ${markdownthumbcreator_SRCS})

target_link_libraries(markdownthumbnail
    KMarkdownWebView
    KF5::KIOWidgets
)

install(TARGETS markdownthumbnail DESTINATION ${KDE_INSTALL_QTPLUGINDIR})


install(FILES markdownthumbnail.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

