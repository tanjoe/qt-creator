/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://qt.nokia.com/contact.
**
**************************************************************************/

#include "indenter.h"
#include "basetexteditor.h"
#include "tabsettings.h"

using namespace TextEditor;

Indenter::Indenter()
{}

Indenter::~Indenter()
{}

bool Indenter::isElectricCharacter(const QChar &ch) const
{
    return doIsElectricalCharacter(ch);
}

void Indenter::indentBlock(QTextDocument *doc,
                           const QTextBlock &block,
                           const QChar &typedChar,
                           BaseTextEditor *editor)
{
    doIndentBlock(doc, block, typedChar, editor);
}

void Indenter::indent(QTextDocument *doc,
                      const QTextCursor &cursor,
                      const QChar &typedChar,
                      BaseTextEditor *editor)
{
    doIndent(doc, cursor, typedChar, editor);
}

void Indenter::reindent(QTextDocument *doc, const QTextCursor &cursor, BaseTextEditor *editor)
{
    doReindent(doc, cursor, editor);
}

bool Indenter::doIsElectricalCharacter(const QChar &) const
{
    return false;
}

void Indenter::doIndentBlock(QTextDocument *doc,
                             const QTextBlock &block,
                             const QChar &typedChar,
                             BaseTextEditor *editor)
{
    Q_UNUSED(doc);
    Q_UNUSED(block);
    Q_UNUSED(typedChar);
    Q_UNUSED(editor);
}

void Indenter::doIndent(QTextDocument *doc, const QTextCursor &cursor, const QChar &typedChar, BaseTextEditor *editor)
{
    if (cursor.hasSelection()) {
        QTextBlock block = doc->findBlock(cursor.selectionStart());
        const QTextBlock end = doc->findBlock(cursor.selectionEnd()).next();
        do {
            indentBlock(doc, block, typedChar, editor);
            block = block.next();
        } while (block.isValid() && block != end);
    } else {
        indentBlock(doc, cursor.block(), typedChar, editor);
    }
}

void Indenter::doReindent(QTextDocument *doc, const QTextCursor &cursor, BaseTextEditor *editor)
{
    if (cursor.hasSelection()) {
        QTextBlock block = doc->findBlock(cursor.selectionStart());
        const QTextBlock end = doc->findBlock(cursor.selectionEnd()).next();

        const TabSettings &ts = editor->tabSettings();

        // skip empty blocks
        while (block.isValid() && block != end) {
            QString bt = block.text();
            if (ts.firstNonSpace(bt) < bt.size())
                break;
            indentBlock(doc, block, QChar::Null, editor);
            block = block.next();
        }

        int previousIndentation = ts.indentationColumn(block.text());
        indentBlock(doc, block, QChar::Null, editor);
        int currentIndentation = ts.indentationColumn(block.text());
        int delta = currentIndentation - previousIndentation;

        block = block.next();
        while (block.isValid() && block != end) {
            ts.reindentLine(block, delta);
            block = block.next();
        }
    } else {
        indentBlock(doc, cursor.block(), QChar::Null, editor);
    }
}
