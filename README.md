# Markdown Viewer KPart (webtech-based)

## Introduction

This repository contains a Markdown viewer KParts plugin. It allows KParts-using applications to display files in markdown format in rendered view.

It is inspired by the [WebEngine Markdown Editor Example](ttps://doc.qt.io/qt-5/qtwebengine-webenginewidgets-markdowneditor-example.html)
from the Qt documentation. The plain text file data is fed into a webpage via a QWebChannel or QtWebKit bridge, where a JavaScript library creates HTML from it which then is displayed.

[markdown.css](http://kevinburke.bitbucket.org/markdowncss/) is a markdown-friendly stylesheet created by Kevin Burke. [marked.min.js](https://github.com/chjj/marked) is a markdown parser and compiler designed for speed written by Christopher Jeffrey and qwebchannel.js is part of the [QWebChannel](https://doc.qt.io/qt-5/qwebchannel.html) module.

This KPart should serve as intermediate solution until some native Qt-based implementation is done.

## Contact

Feedback welcome, email kossebau AT kde org or catch me on freenode irc in #kdevelop.

(Note: This file was happily edited with the support of this plugin. )
