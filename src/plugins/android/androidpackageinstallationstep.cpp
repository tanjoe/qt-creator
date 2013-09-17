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

#include "androidpackageinstallationstep.h"
#include "androidmanager.h"

#include <projectexplorer/buildsteplist.h>
#include <projectexplorer/target.h>
#include <projectexplorer/buildconfiguration.h>
#include <utils/hostosinfo.h>

#include <QDir>

using namespace Android::Internal;

const Core::Id AndroidPackageInstallationStep::Id = Core::Id("Qt4ProjectManager.AndroidPackageInstallationStep");
namespace {
const char ANDROIDDIRECTORY[] = "Android.AndroidPackageInstallationStep.AndroidDirectory";
}

AndroidPackageInstallationStep::AndroidPackageInstallationStep(AndroidDirectory mode,ProjectExplorer::BuildStepList *bsl)
    : MakeStep(bsl, Id), m_androidDirectory(mode)
{
    const QString name = tr("Copy application data");
    setDefaultDisplayName(name);
    setDisplayName(name);
}

AndroidPackageInstallationStep::AndroidPackageInstallationStep(ProjectExplorer::BuildStepList *bc, AndroidPackageInstallationStep *other)
    : MakeStep(bc, other)
{ }

bool AndroidPackageInstallationStep::init()
{
    ProjectExplorer::BuildConfiguration *bc = buildConfiguration();
    if (!bc)
        bc = target()->activeBuildConfiguration();
    QString dirPath;
    if (m_androidDirectory == ProjectDirectory)
        dirPath = AndroidManager::dirPath(target()).toString();
    else
        dirPath = bc->buildDirectory().appendPath((QLatin1String("android"))).toString();
    if (Utils::HostOsInfo::isWindowsHost())
        if (bc->environment().searchInPath(QLatin1String("sh.exe")).isEmpty())
            dirPath = QDir::toNativeSeparators(dirPath);
    setUserArguments(QString::fromLatin1("INSTALL_ROOT=\"%1\" install").arg(dirPath));

    return MakeStep::init();
}

bool AndroidPackageInstallationStep::fromMap(const QVariantMap &map)
{
    if (!MakeStep::fromMap(map))
        return false;
    m_androidDirectory = AndroidDirectory(map.value(QLatin1String(ANDROIDDIRECTORY)).toInt());
    return true;
}

QVariantMap AndroidPackageInstallationStep::toMap() const
{
    QVariantMap map = MakeStep::toMap();
    map.insert(QLatin1String(ANDROIDDIRECTORY), m_androidDirectory);
    return map;
}
