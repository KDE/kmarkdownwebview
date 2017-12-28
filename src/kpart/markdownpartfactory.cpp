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

#include "markdownpartfactory.h"

#include "markdownpart.h"
#include "markdownpartconfig.h"

// KF
#include <KLocalizedString>


MarkdownPartFactory::MarkdownPartFactory()
    : m_aboutData(QStringLiteral("kmarkdownwebviewpart"),
                  i18n("KMarkdownWebViewPart"),
                  QStringLiteral(KMARKDOWNWEBVIEW_VERSION),
                  i18n("For the rendered display of Markdown files in a webpage-like layout"),
                  KAboutLicense::LGPL_V2_1
                 )
{
    m_aboutData.addAuthor(i18n("Friedrich W. H. Kossebau"), i18n("Author"), QStringLiteral("kossebau@kde.org"));
}

MarkdownPartFactory::~MarkdownPartFactory() = default;

QObject* MarkdownPartFactory::create(const char* iface,
                                     QWidget* parentWidget, QObject* parent,
                                     const QVariantList& args, const QString& keyword)
{
    Q_UNUSED(keyword );

    const bool wantBrowserView = (args.contains(QStringLiteral("Browser/View")) ||
                                 (strcmp(iface, "Browser/View") == 0));
    const MarkdownPart::Modus modus =
        wantBrowserView ? MarkdownPart::BrowserViewModus :
        /* else */        MarkdownPart::ReadOnlyModus;

    MarkdownPart* part = new MarkdownPart(parentWidget, parent, m_aboutData, modus);

    return part;
}

