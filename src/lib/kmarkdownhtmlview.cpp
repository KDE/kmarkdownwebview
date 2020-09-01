/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "kmarkdownhtmlview.h"


KMarkdownHtmlView::KMarkdownHtmlView(QObject *parent)
    : QObject(parent)
{}


void KMarkdownHtmlView::setScrollPosition(int x, int y)
{
    m_scrollPosition = QPoint(x, y);
}

void KMarkdownHtmlView::emitRenderingDone()
{
    Q_EMIT renderingDone();
}
