/**************************************************************************
**
** Copyright (c) 2013 BogDan Vatra <bog_dan_ro@yahoo.com>
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef ANDROIDPACKAGEINSTALLATIONSTEP_H
#define ANDROIDPACKAGEINSTALLATIONSTEP_H

#include <qt4projectmanager/makestep.h>

namespace Android {
namespace Internal {

class AndroidPackageInstallationStep : public Qt4ProjectManager::MakeStep
{
    Q_OBJECT
    friend class AndroidPackageInstallationFactory;

public:
    enum AndroidDirectory { ProjectDirectory, BuildDirectory };
    explicit AndroidPackageInstallationStep(AndroidDirectory mode, ProjectExplorer::BuildStepList *bsl);
    bool init();

    bool fromMap(const QVariantMap &map);
    QVariantMap toMap() const;

private:
    AndroidPackageInstallationStep(ProjectExplorer::BuildStepList *bc,
        AndroidPackageInstallationStep *other);
    AndroidDirectory m_androidDirectory;
    static const Core::Id Id;
};

} // namespace Internal
} // namespace Android

#endif // ANDROIDPACKAGEINSTALLATIONSTEP_H
