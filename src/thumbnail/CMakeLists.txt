set(markdownthumbcreator_SRCS
    markdowncreator.cpp
    markdownsourcedocument.cpp
)

add_library(kmarkdownwebviewthumbnail MODULE ${markdownthumbcreator_SRCS})

target_link_libraries(kmarkdownwebviewthumbnail
    KMarkdownWebView
    KF5::KIOWidgets
)

install(TARGETS kmarkdownwebviewthumbnail DESTINATION ${KDE_INSTALL_QTPLUGINDIR})


install(FILES kmarkdownwebviewthumbnail.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR})

