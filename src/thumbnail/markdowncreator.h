/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
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
