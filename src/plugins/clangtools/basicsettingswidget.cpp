/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "basicsettingswidget.h"
#include "ui_basicsettingswidget.h"

#include "clangtoolsutils.h"

namespace ClangTools {
namespace Internal {

BasicSettingsWidget::BasicSettingsWidget(QWidget *parent)
    : QWidget(parent)
    , m_ui(new Ui::BasicSettingsWidget)
{
    m_ui->setupUi(this);
}

BasicSettingsWidget::~BasicSettingsWidget()
{
    delete m_ui;
}

Ui::BasicSettingsWidget *BasicSettingsWidget::ui()
{
    return m_ui;
}

} // namespace Internal
} // namespace ClangTools