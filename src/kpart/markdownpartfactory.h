/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
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
