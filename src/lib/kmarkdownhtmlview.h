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

#ifndef KMARKDOWNHTMLVIEW_H
#define KMARKDOWNHTMLVIEW_H

#include <QObject>
#include <QPoint>

class KMarkdownHtmlView : public QObject
{
    Q_OBJECT

public:
    explicit KMarkdownHtmlView(QObject *parent);

    QPoint scrollPosition() const;

public Q_SLOTS:
    void setScrollPosition(int x, int y);
    void emitRenderingDone();

Q_SIGNALS:
    void requestSetScrollPosition(int x, int y);
    void renderingDone();

private:
    QPoint m_scrollPosition;
};


inline QPoint KMarkdownHtmlView::scrollPosition() const
{
    return m_scrollPosition;
}

#endif
