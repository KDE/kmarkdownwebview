/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "kmarkdownview.h"

#include "kmarkdownviewpage.h"
#include "kabstractmarkdownsourcedocument.h"
#include "kmarkdownhtmlview.h"

// Qt
#ifdef USE_QTWEBKIT
#include <QWebFrame>
#include <QWebHitTestResult>
#else
#include <QWebChannel>
#include <QWebEngineContextMenuData>
#include <QWebEngineProfile>
#endif
#include <QContextMenuEvent>


KMarkdownView::KMarkdownView(KAbstractMarkdownSourceDocument* sourceDocument, QWidget* parent)
#ifdef USE_QTWEBKIT
    : QWebView(parent)
    , m_viewPage(new KMarkdownViewPage(this))
#else
    : QWebEngineView(parent)
    , m_viewPage(new KMarkdownViewPage(new QWebEngineProfile(this), this))
#endif
    , m_htmlView(new KMarkdownHtmlView(this))
    , m_sourceDocument(sourceDocument)
{
    setPage(m_viewPage.data());
    connect(m_viewPage.data(), &KMarkdownViewPage::openUrlRequested, this, &KMarkdownView::openUrlRequested);
    connect(m_viewPage.data(), &KMarkdownViewPage::linkHovered, this, &KMarkdownView::linkHovered);

    QAction* copyAction = pageAction(WebPage::Copy);
    connect(copyAction, &QAction::changed, this, [&] {
        emit copyTextEnabledChanged(pageAction(WebPage::Copy)->isEnabled());
    });
    QAction* selectAllAction = pageAction(WebPage::SelectAll);
    connect(selectAllAction, &QAction::changed, this, [&] {
        emit selectAllEnabledChanged(pageAction(WebPage::SelectAll)->isEnabled());
    });

#ifdef USE_QTWEBKIT
    QWebFrame* frame = m_viewPage->mainFrame();
    frame->addToJavaScriptWindowObject(QStringLiteral("sourceTextObject"), m_sourceDocument);
    frame->addToJavaScriptWindowObject(QStringLiteral("viewObject"), m_htmlView);
#else
    auto* channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("sourceTextObject"), m_sourceDocument);
    channel->registerObject(QStringLiteral("viewObject"), m_htmlView);
    m_viewPage->setWebChannel(channel);
#endif
    connect(m_htmlView, &KMarkdownHtmlView::renderingDone, this, &KMarkdownView::renderingDone);

    setUrl(QUrl(QStringLiteral("qrc:/kmarkdownwebview/index.html")));
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

void KMarkdownView::renderPage(QPainter* painter, const QRect& clip)
{
#ifdef USE_QTWEBKIT
    QWebFrame* mainFrame = page()->mainFrame();
    page()->setViewportSize(mainFrame->contentsSize());
    mainFrame->render(painter, QWebFrame::ContentsLayer, clip);
#else
    Q_UNUSED(painter);
    Q_UNUSED(clip);
    // TODO: used for thumbnailing of page, but QtWebEngine seems to not yet support offscreen rendering
#endif
}

void KMarkdownView::findText(const QString& text, WebPage::FindFlags findFlags)
{
    page()->findText(text, findFlags);
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
        hasSelection = !result.selectedText().isEmpty();
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
