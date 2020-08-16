/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef KABSTRACTMARKDOWNSOURCEDOCUMENT_H
#define KABSTRACTMARKDOWNSOURCEDOCUMENT_H

#include <kmarkdownview_export.h>

#include <QObject>
#include <QString>


class KMARKDOWNVIEW_EXPORT KAbstractMarkdownSourceDocument : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text NOTIFY textChanged FINAL)

public:
    explicit KAbstractMarkdownSourceDocument(QObject *parent);

    virtual QString text() const = 0;

Q_SIGNALS:
    void textChanged(const QString& text);
};

#endif
