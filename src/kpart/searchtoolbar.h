/*
    SPDX-FileCopyrightText: 2017 Friedrich W. H. Kossebau <kossebau@kde.org>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef SEARCHTOOLBAR_H
#define SEARCHTOOLBAR_H

#include <QWidget>
#include <QScopedPointer>

namespace Ui {
class SearchToolBar;
}
class KMarkdownView;

class SearchToolBar : public QWidget
{
    Q_OBJECT

public:
    explicit SearchToolBar(KMarkdownView* markdownView, QWidget* parent = nullptr);
    ~SearchToolBar() override;

    void hideEvent(QHideEvent* event) override;

public Q_SLOTS:
    void startSearch();
    void searchNext();
    void searchPrevious();

private Q_SLOTS:
    void searchIncrementally();

private:
    QScopedPointer<Ui::SearchToolBar> const m_ui;
    KMarkdownView* const m_markdownView;
};

#endif
