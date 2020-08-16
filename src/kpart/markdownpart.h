/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef MARKDOWNPART_H
#define MARKDOWNPART_H

// KF
#include <KParts/ReadOnlyPart>

// Qt
#include <QByteArray>
#include <QPoint>

class MarkdownBrowserExtension;
class MarkdownSourceDocument;
class KMarkdownView;
class SearchToolBar;
class KAboutData;

class MarkdownPart : public KParts::ReadOnlyPart
{
    Q_OBJECT

public:
    enum Modus {
        ReadOnlyModus = 0,
        BrowserViewModus = 1
    };

    /**
     * Default constructor, with arguments as expected by MarkdownPartFactory
     */
    MarkdownPart(QWidget* parentWidget, QObject* parent, const KAboutData& aboutData, Modus modus);

    /**
     * Destructor
     */
    ~MarkdownPart() override;

    KMarkdownView* view() const;

    QAction* copySelectionAction() const;
    QAction* createCopyEmailAddressAction(QObject* parent, const QUrl& mailtoUrl);
    QAction* createCopyLinkTextAction(QObject* parent, const QString& text);
    QAction* createCopyLinkUrlAction(QObject* parent);
    QAction* createSaveLinkAsAction(QObject* parent);

    void copySelection();

protected: // KParts::ReadOnlyPart API
    bool openFile() override;

    bool doOpenStream(const QString& mimeType) override;
    bool doWriteStream(const QByteArray& data) override;
    bool doCloseStream() override;

    bool closeUrl() override;

private:
    void setupActions(Modus modus);
    void prepareViewStateRestoringOnReload();
    void restoreScrollPosition();

    void handleOpenUrlRequest(const QUrl& url);
    void requestContextMenu(const QPoint& globalPos,
                            const QUrl& linkUrl, const QString& linkText,
                            bool hasSelection, bool forcesNewWindow);
    void showHoveredLink(const QString& link);

    void copyLinkUrl();
    void saveLinkAs();
    void selectAll();

private:
    MarkdownSourceDocument* m_sourceDocument;
    KMarkdownView* m_widget;
    SearchToolBar* m_searchToolBar;
    QAction* m_copySelectionAction;
    QAction* m_selectAllAction;
    QAction* m_searchAction;
    QAction* m_searchNextAction;
    QAction* m_searchPreviousAction;

    MarkdownBrowserExtension* const m_browserExtension;

    QByteArray m_streamedData;

    QUrl m_previousUrl;
    QPoint m_previousScrollPosition;
};

inline KMarkdownView* MarkdownPart::view() const { return m_widget; }

#endif
