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
