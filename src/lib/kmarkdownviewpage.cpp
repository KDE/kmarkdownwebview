/*
 * Copyright (C) 2017 by Friedrich W. H. Kossebau <kossebau@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see <http://www.gnu.org/licenses/>.
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

    const auto url = request.url();
    // Only allow qrc:/index.html.
    if (url.scheme() == QLatin1String("qrc")) {
        return true;
    }

    emit openUrlRequested(url);
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

    emit openUrlRequested(url);
    return false;
}
#endif
