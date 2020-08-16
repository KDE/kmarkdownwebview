/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef MARKDOWNSOURCEDOCUMENT_H
#define MARKDOWNSOURCEDOCUMENT_H

#include <kabstractmarkdownsourcedocument.h>

class MarkdownSourceDocument : public KAbstractMarkdownSourceDocument
{
    Q_OBJECT

public:
    explicit MarkdownSourceDocument(QObject *parent) : KAbstractMarkdownSourceDocument(parent) {}

    void setText(const QString& text);

    QString text() const override;

private:
    QString m_text;
};

#endif
