/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "markdownsourcedocument.h"

void MarkdownSourceDocument::setText(const QString& text)
{
    m_text = text;

    emit textChanged(m_text);
}

QString MarkdownSourceDocument::text() const
{
    return m_text;
}
