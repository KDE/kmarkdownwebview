/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef MARKDOWNBROWSEREXTENSION_H
#define MARKDOWNBROWSEREXTENSION_H

// KF headers
#include <KParts/BrowserExtension>

class MarkdownPart;
class KActionCollection;

class MarkdownBrowserExtension : public KParts::BrowserExtension
{
    Q_OBJECT

public:
    explicit MarkdownBrowserExtension(MarkdownPart* part);

    int xOffset() override;
    int yOffset() override;

public Q_SLOTS:
    void copy();

    void updateCopyAction(bool enabled);
    void requestOpenUrl(const QUrl& url);
    void requestOpenUrlNewWindow(const QUrl& url);
    void requestContextMenu(const QPoint& globalPos, const QUrl& linkUrl, const QString& linkText,
                            bool hasSelection, bool forcesNewWindow);

private:
    MarkdownPart* m_part;
    // needed to memory manage the context menu actions
    KActionCollection* m_contextMenuActionCollection;
};

#endif
