/*
 *   Copyright (C) 2017 by Friedrich W. H. Kossebau <kossebau@kde.org>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .
 */

#include "kmarkdownviewpage.h"

#include <QWebEngineSettings>

KMarkdownViewPage::KMarkdownViewPage(QObject* parent)
    : QWebEnginePage(parent)
{
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, false);
    settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
}


KMarkdownViewPage::~KMarkdownViewPage() = default;

bool KMarkdownViewPage::acceptNavigationRequest(const QUrl& url,
                                                QWebEnginePage::NavigationType type,
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
