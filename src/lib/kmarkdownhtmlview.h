/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
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
