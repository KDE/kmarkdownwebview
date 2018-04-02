# Markdown Viewer KPart & Thumbnailer (webtech-based)

## Introduction

This repository contains software for the rendered display of Markdown documents:

* a Markdown viewer [KParts](https://api.kde.org/frameworks/kparts/html/index.html) plugin, which allows KParts-using applications to display files in Markdown format in the target format
* a Markdown file [KIO thumbnail generator](https://api.kde.org/frameworks/kio/html/classThumbCreator.html) plugin, which allows KIO-powered file managers & dialogs to show thumbnails and previews of files in Markdown format in the target format (currently only available when building against QtWebKit)

The software is inspired by the [WebEngine Markdown Editor Example](https://doc.qt.io/qt-5/qtwebengine-webenginewidgets-markdowneditor-example.html) from the Qt documentation. The plain text file data in the Markdown format is fed into a local webpage wrapped with C++/Qt, via a QWebChannel or QtWebKit bridge, where a JavaScript library creates HTML data from it, which then is inserted into that webpage and thus displayed.

The software should serve as intermediate solution until some native Qt-based implementation is done.

### Deployed 3rd-party software

[markdown.css](https://kevinburke.bitbucket.io/markdowncss/) is a markdown-friendly stylesheet created by Kevin Burke.
[Marked](https://github.com/markedjs/marked) is a markdown parser and compiler designed for speed written by Christopher Jeffrey.
And qwebchannel.js is part of the [QWebChannel](https://doc.qt.io/qt-5/qwebchannel.html) module.

## Building

KMarkdownWebView can be built with either QtWebEngine (preferred by the build system) or QtWebKit. Pass `-DUSE_QTWEBKIT=TRUE` to CMake to enforce the use of QtWebKit.

## Using

To use the KMarkdownWebView KParts plugin in a KParts-using applications, often you will need to configure that globally in the Plasma System Settings, and there in the "File Associations" page.
Select the MIME type "text/markdown" and in the "Embedding" tab in the "Service Preference Order" group make sure "Markdown Web View (kmarkdownwebviewpart)" is on top of the list.

To use the Markdown file KIO thumbnail generator plugin in KIO-powered file managers & dialogs, it needs to be enabled e.g. in Dolphin's Preferences, and there in the "General" page.
Select the "Previews" tab and enable the entry for "Markdown Files".

## Issues

Please report bugs and feature requests in the [KDE issue tracker](https://bugs.kde.org/enter_bug.cgi?product=kmarkdownwebview).

## Contact

Feedback welcome, email kossebau AT kde org or catch me on freenode irc in #kdevelop.

(*Note*: This file was happily edited with the support of this plugin.)
