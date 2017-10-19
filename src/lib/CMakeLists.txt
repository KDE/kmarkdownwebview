set(kmarkdownview_SRCS
    kmarkdownviewpage.cpp
    kmarkdownview.cpp
    kabstractmarkdownsourcedocument.cpp
    kmarkdownhtmlview.cpp
)

if(USE_QTWEBKIT)
qt5_add_resources(kmarkdownview_SRCS
    data/webkitdata.qrc
)
else()
qt5_add_resources(kmarkdownview_SRCS
    data/webenginedata.qrc
)
endif()

configure_file(kmarkdownview-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/kmarkdownview-config.h)

add_library(KMarkdownWebView SHARED ${kmarkdownview_SRCS})
generate_export_header(KMarkdownWebView BASE_NAME kmarkdownview)

if(USE_QTWEBKIT)
    target_link_libraries(KMarkdownWebView Qt5::WebKitWidgets)
else()
    target_link_libraries(KMarkdownWebView Qt5::WebEngineWidgets)
endif()

install(TARGETS KMarkdownWebView ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
