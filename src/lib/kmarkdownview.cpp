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

#include "kmarkdownview.h"

#ifndef USE_QTWEBKIT
#include "kmarkdownviewpage.h"
#endif

#include "kabstractmarkdownsourcedocument.h"
#include "kmarkdownhtmlview.h"

// Qt
#ifdef USE_QTWEBKIT
#include <QWebPage>
#include <QWebFrame>
#include <QWebHitTestResult>
#else
#include <QWebChannel>
#include <QWebEngineContextMenuData>
#endif
#include <QContextMenuEvent>


KMarkdownView::KMarkdownView(KAbstractMarkdownSourceDocument* sourceDocument, QWidget* parent)
#ifdef USE_QTWEBKIT
    : QWebView(parent)
#else
    : QWebEngineView(parent)
    , m_viewPage(new KMarkdownViewPage(this))
#endif
    , m_htmlView(new KMarkdownHtmlView(this))
    , m_sourceDocument(sourceDocument)
{
#ifdef USE_QTWEBKIT
    auto page = this->page();
    page->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(this, &QWebView::linkClicked, this, &KMarkdownView::openUrlRequested);
#else
    setPage(m_viewPage);
    connect(m_viewPage, &KMarkdownViewPage::openUrlRequested, this, &KMarkdownView::openUrlRequested);
#endif

#ifdef USE_QTWEBKIT
    auto frame = page->mainFrame();
    frame->addToJavaScriptWindowObject("sourceTextObject", m_sourceDocument);
    frame->addToJavaScriptWindowObject("viewObject", m_htmlView);
#else
    QWebChannel* channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("sourceTextObject"), m_sourceDocument);
    channel->registerObject(QStringLiteral("viewObject"), m_htmlView);
    m_viewPage->setWebChannel(channel);
#endif
    connect(m_htmlView, &KMarkdownHtmlView::renderingDone, this, &KMarkdownView::renderingDone);

    setUrl(QUrl(QStringLiteral("qrc:/kmarkdownview/index.html")));
}

KMarkdownView::~KMarkdownView() = default;

QPoint KMarkdownView::scrollPosition() const
{
    return m_htmlView->scrollPosition();
}

void KMarkdownView::setScrollPosition(int x, int y)
{
    m_htmlView->requestSetScrollPosition(x, y);
}

void KMarkdownView::contextMenuEvent(QContextMenuEvent* event)
{
#ifdef USE_QTWEBKIT
    QWebHitTestResult result = page()->mainFrame()->hitTestContent(event->pos());
#else
    QWebEngineContextMenuData result = page()->contextMenuData();
#endif

    // default menu arguments
    bool forcesNewWindow = false;
    bool hasSelection = false;

    if (!result.linkUrl().isValid()) {
#ifdef USE_QTWEBKIT
        hasSelection = result.isContentSelected();
#else
        hasSelection = result.selectedText().isEmpty();
#endif
    } else {
#ifdef USE_QTWEBKIT
        // Show the OpenInThisWindow context menu item
        forcesNewWindow = (page()->currentFrame() != result.linkTargetFrame());
#endif
    }

    emit contextMenuRequested(event->globalPos(),
                              result.linkUrl(), result.linkText(),
                              hasSelection, forcesNewWindow);

    event->accept();
}
