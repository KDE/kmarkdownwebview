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

#ifndef KMARKDOWNVIEW_H
#define KMARKDOWNVIEW_H

#include <kmarkdownview_export.h>
#include <kmarkdownview-config.h>

// Qt headers
#ifdef USE_QTWEBKIT
#include <QWebView>
#else
#include <QWebEngineView>
#endif
#include <QAction>

class KMarkdownViewPage;
class KAbstractMarkdownSourceDocument;
class KMarkdownHtmlView;
class QUrl;

class KMARKDOWNVIEW_EXPORT KMarkdownView : public
#ifdef USE_QTWEBKIT
    QWebView
#else
    QWebEngineView
#endif
{
    Q_OBJECT

public:
#ifdef USE_QTWEBKIT
    typedef QWebPage WebPage;
#else
    typedef QWebEnginePage WebPage;
#endif

public:
    explicit KMarkdownView(KAbstractMarkdownSourceDocument* sourceDocument, QWidget* parent = nullptr);
    ~KMarkdownView() override;

public:
    void copySelection();
    void copyLinkUrl();
    void saveLinkAs();
    void selectAllText();
    bool canCopyText() const;
    QPoint scrollPosition() const;
    void setScrollPosition(int x, int y);

Q_SIGNALS:
    void openUrlRequested(const QUrl& url);
    void contextMenuRequested(const QPoint& globalPos, const QUrl& linkUrl, const QString& linkText,
                              bool hasSelection, bool forcesNewWindow);
    void renderingDone();

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
#ifdef USE_QTWEBKIT
    void openUrlExternally(const QUrl& url);
#endif

private:
#ifndef USE_QTWEBKIT
    KMarkdownViewPage* m_viewPage = nullptr;
#endif

    KMarkdownHtmlView* const m_htmlView;
    KAbstractMarkdownSourceDocument* const m_sourceDocument;
};

inline void KMarkdownView::copySelection()
{
    triggerPageAction(WebPage::Copy);
}

inline void KMarkdownView::copyLinkUrl()
{
    triggerPageAction(WebPage::CopyLinkToClipboard);
}

inline void KMarkdownView::saveLinkAs()
{
    triggerPageAction(WebPage::DownloadLinkToDisk);
}

inline void KMarkdownView::selectAllText()
{
    triggerPageAction(WebPage::SelectAll);
}

inline bool KMarkdownView::canCopyText() const
{
    return pageAction(WebPage::Copy)->isEnabled();
}

#endif
