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

#ifndef MARKDOWNPARTFACTORY_H
#define MARKDOWNPARTFACTORY_H

#include <KPluginFactory>
#include <KAboutData>


class MarkdownPartFactory : public KPluginFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.KPluginFactory" FILE "kmarkdownwebviewpart.json")
    Q_INTERFACES(KPluginFactory)

public:
    MarkdownPartFactory();
    ~MarkdownPartFactory() override;

    QObject* create(const char* iface,
                    QWidget* parentWidget, QObject* parent,
                    const QVariantList& args, const QString& keyword) override;

private:
    KAboutData m_aboutData;
};

#endif
