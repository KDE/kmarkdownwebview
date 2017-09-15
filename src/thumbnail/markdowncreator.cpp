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

#include "markdowncreator.h"

#include "markdownsourcedocument.h"

#include <kmarkdownview.h>

#include <QFile>
#include <QTextStream>
#include <QImage>
#include <QPainter>

extern "C"
{

Q_DECL_EXPORT ThumbCreator *new_creator()
{
    return new MarkdownCreator;
}

}

MarkdownCreator::MarkdownCreator()
{
}

MarkdownCreator::~MarkdownCreator()
{
    delete m_view;
}

bool MarkdownCreator::create(const QString& path, int width, int height, QImage& image)
{
    if (!m_view) {
        m_sourceDocument = new MarkdownSourceDocument(this);
        m_view = new KMarkdownView(m_sourceDocument);
        connect(m_view, &KMarkdownView::renderingDone, this, &MarkdownCreator::handleRenderingDone);
    }

    // reset
    m_renderingDone = false;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QTextStream textStream(&file);
    const QString text = textStream.readAll();
    file.close();

    m_sourceDocument->setText(text);

    if (!m_renderingDone) {
        const int t = startTimer(5000);
        m_eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
        killTimer(t);
    }

    QPixmap pixmap;
    // same logic as in HTML thumbnailer, motivation unknown
    if (width > 400 || height > 600) {
        if (height * 3 > width * 4) {
            pixmap = QPixmap(width, width * 4 / 3);
        } else {
            pixmap = QPixmap(height * 3 / 4, height);
        }
    } else {
        pixmap = QPixmap(400, 600);
    }
    pixmap.fill(Qt::transparent);

    const int borderX = pixmap.width() / width;
    const int borderY = pixmap.height() / height;
    const QRect clip (borderX, borderY, pixmap.width() - borderX * 2, pixmap.height() - borderY * 2);

    QPainter p (&pixmap);
    m_view->renderPage(&p, clip);

    image = pixmap.toImage();
    return true;
}

void MarkdownCreator::handleRenderingDone()
{
    m_renderingDone = true;

    m_eventLoop.quit();
}

void MarkdownCreator::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event);

    m_eventLoop.quit();
}

ThumbCreator::Flags MarkdownCreator::flags() const
{
    return None;
}
