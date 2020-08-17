/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
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

            QAction* action = m_part->copySelectionAction();
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
                const QMimeType mime = mimeDb.mimeTypeForFile(fileName);
                if (!mime.isDefault()) {
                    mimeType = mime.name();
                }
            }
        }

        QList<QAction*> linkActions;

        if (hasSelection) {
            QAction* action = m_part->copySelectionAction();
            linkActions.append(action);
        }

        if (linkUrl.scheme() == QLatin1String("mailto")) {
            QAction* action = m_part->createCopyEmailAddressAction(m_contextMenuActionCollection, linkUrl);
            m_contextMenuActionCollection->addAction(QStringLiteral("copylinklocation"), action);
            linkActions.append(action);
        } else {
            if (!linkText.isEmpty()) {
                QAction* action = m_part->createCopyLinkTextAction(m_contextMenuActionCollection, linkText);
                m_contextMenuActionCollection->addAction(QStringLiteral("copylinktext"), action);
                linkActions.append(action);
            }

            QAction* action = m_part->createCopyLinkUrlAction(m_contextMenuActionCollection);
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
