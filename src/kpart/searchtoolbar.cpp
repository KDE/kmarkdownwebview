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

#include "searchtoolbar.h"

#include "ui_searchtoolbar.h"

#include <kmarkdownview.h>

SearchToolBar::SearchToolBar(KMarkdownView* markdownView, QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::SearchToolBar)
    , m_markdownView(markdownView)
{
    m_ui->setupUi(this);

    connect(m_ui->hideButton, &QToolButton::clicked,
            this, &SearchToolBar::hide);
    connect(m_ui->searchTextEdit, &QLineEdit::textEdited,
            this, &SearchToolBar::searchIncrementally);
    connect(m_ui->matchCaseCheckButton, &QAbstractButton::toggled,
            this, &SearchToolBar::searchIncrementally);
    connect(m_ui->searchTextEdit, &QLineEdit::returnPressed,
            this, &SearchToolBar::searchNext);
    connect(m_ui->nextButton, &QToolButton::clicked,
            this, &SearchToolBar::searchNext);
    connect(m_ui->previousButton, &QToolButton::clicked,
            this, &SearchToolBar::searchPrevious);
    // TODO: disable next/previous buttons if no (more) search hits, color coding in text field
}

SearchToolBar::~SearchToolBar() = default;

void SearchToolBar::searchNext()
{
    const auto text = m_ui->searchTextEdit->text();
    if (text.isEmpty()) {
        startSearch();
        return;
    }

    KMarkdownView::WebPage::FindFlags findFlags = {};
    if (m_ui->matchCaseCheckButton->isChecked()) {
        findFlags |= KMarkdownView::WebPage::FindCaseSensitively;
    }

    m_markdownView->findText(text, findFlags);

}

void SearchToolBar::searchPrevious()
{
    const auto text = m_ui->searchTextEdit->text();
    if (text.isEmpty()) {
        startSearch();
        return;
    }

    KMarkdownView::WebPage::FindFlags findFlags = {KMarkdownView::WebPage::FindBackward};
    if (m_ui->matchCaseCheckButton->isChecked()) {
        findFlags |= KMarkdownView::WebPage::FindCaseSensitively;
    }

    m_markdownView->findText(text, findFlags);
}

void SearchToolBar::startSearch()
{
    show();
    m_ui->searchTextEdit->selectAll();
    m_ui->searchTextEdit->setFocus();
}

void SearchToolBar::searchIncrementally()
{
    KMarkdownView::WebPage::FindFlags findFlags = {};

    if (m_ui->matchCaseCheckButton->isChecked()) {
        findFlags |= KMarkdownView::WebPage::FindCaseSensitively;
    }

    // calling with changed text with added or removed chars at end will result in current
    // selection kept, if also matching new text
    // behaviour on changed case sensitivity though is advancing to next match even if current
    // would be still matching. as there is no control about currently shown match, nothing
    // we can do about it. thankfully case sensitivity does not happen too often, so should
    // not be too grave UX
    // at least with webengine 5.9.1 there is a bug when switching from no-casesensitivy to
    // casesensitivity, that global matches are not updated and the ones with non-matching casing
    // still active. no workaround so far.
    m_markdownView->findText(m_ui->searchTextEdit->text(), findFlags);
}

void SearchToolBar::hideEvent(QHideEvent* event)
{
    // finish search
    // passing emptry string to reset search, as told in API docs
    m_markdownView->findText(QString());

    QWidget::hideEvent(event);
}
