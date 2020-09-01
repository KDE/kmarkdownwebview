/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "kmarkdownviewpage.h"

#ifdef USE_QTWEBKIT
#include <QWebSettings>
#include <QNetworkRequest>
#else
#include <QWebEngineSettings>
#endif

#ifdef USE_QTWEBKIT
KMarkdownViewPage::KMarkdownViewPage(QObject* parent)
    : QWebPage(parent)
{
#else
KMarkdownViewPage::KMarkdownViewPage(QWebEngineProfile* profile, QObject* parent)
    : QWebEnginePage(profile, parent)
{
#endif
    settings()->setAttribute(WebSettings::JavascriptEnabled, true);
    settings()->setAttribute(WebSettings::PluginsEnabled, false);
    settings()->setAttribute(WebSettings::LocalContentCanAccessRemoteUrls, false);
    settings()->setAttribute(WebSettings::LocalContentCanAccessFileUrls, true);
#ifdef DEBUG_WEB
#ifdef USE_QTWEBKIT
    settings()->setAttribute(WebSettings::DeveloperExtrasEnabled, true);
#endif
#endif
}

KMarkdownViewPage::~KMarkdownViewPage() = default;

#ifdef USE_QTWEBKIT
bool KMarkdownViewPage::acceptNavigationRequest(QWebFrame* frame,
                                                const QNetworkRequest& request,
                                                NavigationType type)
{
    Q_UNUSED(type);
    Q_UNUSED(frame);

    const QUrl url = request.url();
    // Only allow qrc:/index.html.
    if (url.scheme() == QLatin1String("qrc")) {
        return true;
    }

    Q_EMIT openUrlRequested(url);
    return false;
}
#else
bool KMarkdownViewPage::acceptNavigationRequest(const QUrl& url,
                                                NavigationType type,
                                                bool isMainFrame)
{
    Q_UNUSED(type);
    Q_UNUSED(isMainFrame);

    // Only allow qrc:/index.html.
    if (url.scheme() == QLatin1String("qrc")) {
        return true;
    }

    Q_EMIT openUrlRequested(url);
    return false;
}
#endif
