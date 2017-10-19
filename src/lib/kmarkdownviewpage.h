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
