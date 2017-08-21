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
