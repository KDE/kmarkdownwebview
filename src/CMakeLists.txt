add_definitions(-DTRANSLATION_DOMAIN=\"kmarkdownwebview\")

add_subdirectory(lib)

add_subdirectory(kpart)

# QtWebEngine has no API yet for offscreen rendering of pages
if(USE_QTWEBKIT)
add_subdirectory(thumbnail)
endif()
