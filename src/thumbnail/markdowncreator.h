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

#ifndef MARKDOWNCREATOR_H
#define MARKDOWNCREATOR_H

#include <KIO/ThumbCreator>

#include <QObject>
#include <QEventLoop>

class KMarkdownView;
class MarkdownSourceDocument;

class MarkdownCreator : public QObject, public ThumbCreator
{
    Q_OBJECT

public:
    MarkdownCreator();
    ~MarkdownCreator() override;

    bool create(const QString& path, int width, int height, QImage& image) override;
    Flags flags() const override;

protected:
    void timerEvent(QTimerEvent* event) override;

private:
    void handleRenderingDone();

private:
    bool m_renderingDone = false;
    KMarkdownView* m_view = nullptr;
    MarkdownSourceDocument* m_sourceDocument = nullptr;

    QEventLoop m_eventLoop;
};

#endif
