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

#include "markdownbrowserextension.h"

#include "markdownpart.h"
#include <kmarkdownview.h>

// KF
#include <KActionCollection>
#include <KLocalizedString>

// Qt
#include <QMimeDatabase>

MarkdownBrowserExtension::MarkdownBrowserExtension(MarkdownPart* part)
    : KParts::BrowserExtension(part)
    , m_part(part)
    , m_contextMenuActionCollection(new KActionCollection(this))
{
     emit enableAction("copy", m_part->view()->isCopyTextEnabled());
}

void MarkdownBrowserExtension::copy()
{
    m_part->copySelection();
}

void MarkdownBrowserExtension::updateCopyAction(bool enabled)
{
    emit enableAction("copy", enabled);
}

void MarkdownBrowserExtension::requestOpenUrl(const QUrl& url)
{
    emit openUrlRequest(url);
}

void MarkdownBrowserExtension::requestOpenUrlNewWindow(const QUrl& url)
{
    emit createNewWindow(url);
}

void MarkdownBrowserExtension::requestContextMenu(const QPoint& globalPos,
                                                  const QUrl& linkUrl, const QString& linkText,
                                                  bool hasSelection, bool forcesNewWindow)
{
    // Clear the previous collection entries first...
    m_contextMenuActionCollection->clear();

    // default menu arguments
    PopupFlags flags = DefaultPopupItems | ShowBookmark;
    ActionGroupMap mapAction;
    QString mimeType;
    QUrl emitUrl;

    if (!linkUrl.isValid()) {
        emitUrl = m_part->url();
        mimeType = QStringLiteral("text/markdown");

        if (hasSelection) {
            flags |= ShowTextSelectionItems;

            QList<QAction*> selectActions;

            auto action = m_part->copySelectionAction();
            selectActions.append(action);

            mapAction.insert(QStringLiteral("editactions"), selectActions);
        }
    } else {
        flags |= IsLink;
        emitUrl = linkUrl;

        QMimeDatabase mimeDb;
        if (linkUrl.isLocalFile())
            mimeType = mimeDb.mimeTypeForUrl(linkUrl).name();
        else {
            const QString fileName = linkUrl.fileName();

            if (!fileName.isEmpty() && !linkUrl.hasFragment() && !linkUrl.hasQuery()) {
                auto mime = mimeDb.mimeTypeForFile(fileName);
                if (!mime.isDefault()) {
                    mimeType = mime.name();
                }
            }
        }

        QList<QAction*> linkActions;

        if (hasSelection) {
            auto action = m_part->copySelectionAction();
            linkActions.append(action);
        }

        if (linkUrl.scheme() == QLatin1String("mailto")) {
            auto action = m_part->createCopyEmailAddressAction(m_contextMenuActionCollection, linkUrl);
            m_contextMenuActionCollection->addAction(QStringLiteral("copylinklocation"), action);
            linkActions.append(action);
        } else {
            if (!linkText.isEmpty()) {
                auto action = m_part->createCopyLinkTextAction(m_contextMenuActionCollection, linkText);
                m_contextMenuActionCollection->addAction(QStringLiteral("copylinktext"), action);
                linkActions.append(action);
            }

            auto action = m_part->createCopyLinkUrlAction(m_contextMenuActionCollection);
            m_contextMenuActionCollection->addAction(QStringLiteral("copylinkurl"), action);
            linkActions.append(action);

            action = m_part->createSaveLinkAsAction(m_contextMenuActionCollection);
            m_contextMenuActionCollection->addAction(QStringLiteral("savelinkas"), action);
            linkActions.append(action);
        }

        mapAction.insert(QStringLiteral("linkactions"), linkActions);
    }

    if (!mapAction.isEmpty()) {
        KParts::OpenUrlArguments args;
        args.setMimeType(mimeType);
        KParts::BrowserArguments bargs;
        bargs.setForcesNewWindow(forcesNewWindow);

        emit popupMenu(globalPos, emitUrl, static_cast<mode_t>(-1), args, bargs, flags, mapAction);
    }
}

int MarkdownBrowserExtension::xOffset()
{
    return m_part->view()->scrollPosition().x();
}

int MarkdownBrowserExtension::yOffset()
{
    return m_part->view()->scrollPosition().y();
}
