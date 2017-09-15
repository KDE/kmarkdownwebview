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

#include <QWebEngineSettings>

KMarkdownViewPage::KMarkdownViewPage(QWebEngineProfile* profile, QObject* parent)
    : QWebEnginePage(profile, parent)
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
