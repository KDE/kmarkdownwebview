/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef KMARKDOWNVIEWPAGE_H
#define KMARKDOWNVIEWPAGE_H

#include <kmarkdownview-config.h>

#ifdef USE_QTWEBKIT
#include <QWebPage>
#else
#include <QWebEnginePage>
#endif

class KMarkdownViewPage : public
#ifdef USE_QTWEBKIT
    QWebPage
#else
    QWebEnginePage
#endif
{
    Q_OBJECT

public:
#ifdef USE_QTWEBKIT
    typedef QWebSettings WebSettings;
#else
    typedef QWebEngineSettings WebSettings;
#endif
public:
#ifdef USE_QTWEBKIT
    explicit KMarkdownViewPage(QObject* parent);
#else
    KMarkdownViewPage(QWebEngineProfile* profile, QObject* parent);
#endif
    ~KMarkdownViewPage() override;

Q_SIGNALS:
    void openUrlRequested(const QUrl& url);

protected:
#ifdef USE_QTWEBKIT
    bool acceptNavigationRequest(QWebFrame* frame, const QNetworkRequest& request, NavigationType type) override;
#else
    bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame) override;
#endif
};

#endif
