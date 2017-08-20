cmake_minimum_required(VERSION 3.0)

project(kmarkdownwebview)

set(REQUIRED_ECM_VERSION "5.23.0")
find_package(ECM ${REQUIRED_ECM_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(GenerateExportHeader)
include(FeatureSummary)

set(QT_MIN_VERSION "5.6.0")
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Widgets)

set(KF5_MIN_VERSION "5.23.0")
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    Parts
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
    find_package(Qt5WebChannel CONFIG QUIET)
endif()

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
