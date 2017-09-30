# Markdown Viewer KPart & Thumbnailer (webtech-based)

## Introduction

This repository contains software for the rendered display of Markdown documents:
* a Markdown viewer [KParts](https://api.kde.org/frameworks/kparts/html/index.html) plugin which allows KParts-using applications to display files in Markdown format in the target format
* a Markdown file [KIO thumbnail generator](https://api.kde.org/frameworks/kio/html/classThumbCreator.html) plugin which allows KIO-powered file managers & dialogs to show thumbnails and previews of files in Markdown format in the target format (currently only available when building against QtWebKit)

The software is inspired by the [WebEngine Markdown Editor Example](ttps://doc.qt.io/qt-5/qtwebengine-webenginewidgets-markdowneditor-example.html) from the Qt documentation. The plain text file data is fed into a webpage via a QWebChannel or QtWebKit bridge, where a JavaScript library creates HTML from it which then is displayed.

The software should serve as intermediate solution until some native Qt-based implementation is done.

### Deployed 3rd-party software

[markdown.css](https://kevinburke.bitbucket.io/markdowncss/) is a markdown-friendly stylesheet created by Kevin Burke. [marked.min.js](https://github.com/chjj/marked) is a markdown parser and compiler designed for speed written by Christopher Jeffrey and qwebchannel.js is part of the [QWebChannel](https://doc.qt.io/qt-5/qwebchannel.html) module.

## Building

KMarkdownWebView can be built both with QtWebEngine (preferred by the build system) and QtWebKit. Pass `-DUSE_QTWEBKIT=TRUE` to CMake to enforce the use of QtWebKit.

## Issues

Please report bugs and feature requests in the [KDE issue tracker](https://bugs.kde.org/enter_bug.cgi?product=kmarkdownwebview).

## Contact

Feedback welcome, email kossebau AT kde org or catch me on freenode irc in #kdevelop.

(*Note*: This file was happily edited with the support of this plugin.)
