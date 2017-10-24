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
