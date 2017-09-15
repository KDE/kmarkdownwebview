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

#include <QWebEnginePage>

class KMarkdownViewPage : public QWebEnginePage
{
    Q_OBJECT

public:
    KMarkdownViewPage(QWebEngineProfile* profile, QObject* parent);
    ~KMarkdownViewPage() override;

Q_SIGNALS:
    void openUrlRequested(const QUrl& url);

protected:
    bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame) override;
};

#endif
