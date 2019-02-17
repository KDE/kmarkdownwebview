cmake_minimum_required(VERSION 3.0)

project(kmarkdownwebview VERSION 0.5.5)

set(QT_MIN_VERSION "5.6.0")
set(KF_MIN_VERSION "5.25.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(GenerateExportHeader)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Widgets
)

find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    Parts
    KIO # for thumbnails
)

# pass -DUSE_QTWEBKIT=TRUE to enforce usage of webkit
if (NOT USE_QTWEBKIT)
    find_package(Qt5WebEngineWidgets "5.7.0" CONFIG QUIET)
    set_package_properties(Qt5WebEngineWidgets PROPERTIES
        PURPOSE "Required for markdown display, fallback is Qt5WebKitWidgets"
        URL "https://qt.io/"
        TYPE RECOMMENDED
    )
    if(NOT Qt5WebEngineWidgets_FOUND)
        set(USE_QTWEBKIT TRUE)
    endif()
endif()

if(USE_QTWEBKIT)
    find_package(Qt5WebKitWidgets CONFIG QUIET)
    set_package_properties(Qt5WebKitWidgets PROPERTIES
        PURPOSE "Required for markdown display, if Qt5WebEngineWidgets is not available"
        URL "https://qt.io/"
        TYPE REQUIRED)
endif()

add_definitions(
    -DQT_DEPRECATED_WARNINGS
    -DQT_DISABLE_DEPRECATED_BEFORE=0x050600
    -DQT_NO_SIGNALS_SLOTS_KEYWORDS
    -DQT_STRICT_ITERATORS
    -DQT_USE_QSTRINGBUILDER
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_NO_URL_CAST_FROM_STRING
)

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
