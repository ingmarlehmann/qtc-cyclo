#include "cycloplugin.h"
#include "cycloconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <extensionsystem/pluginmanager.h>
#include <coreplugin/editormanager/ieditor.h>
#include <coreplugin/editormanager/documentmodel.h>

//#include <cppeditor/cppeditor.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QModelIndex>

#include <QtPlugin>

using namespace Cyclo::Internal;

CYCLOPlugin::CYCLOPlugin()
{
    // Create your members
}

CYCLOPlugin::~CYCLOPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool CYCLOPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    QAction *action = new QAction(tr("Cyclo action"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
    connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("Cyclo"));
    menu->addAction(cmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    connect (Core::DocumentModel::model (),
               SIGNAL (dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
               SLOT (handleDocumentsChange(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

    return true;
}

void CYCLOPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag CYCLOPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void CYCLOPlugin::triggerAction()
{
    ExtensionSystem::PluginManager* pm
            = ExtensionSystem::PluginManager::instance();

    QList<QObject*> objects
            = pm->allObjects();

    QString editors(QString::fromLocal8Bit("test"));

    Q_FOREACH(QObject* obj, objects)
    {
        //if(qobject_cast<Core::IEditor*>(obj)){
            QString objInfo = QString(QString::fromLocal8Bit("%1 (%2)"))
                    .arg(obj->objectName())
                    .arg(QString::fromLocal8Bit(obj->metaObject()->className()));

            qDebug() << objInfo;

            editors.append(objInfo);
        //}
    }

    QMessageBox::information(Core::ICore::mainWindow(),
                             tr("Action triggered"),
                             editors);
}

void CYCLOPlugin::handleDocumentsChange(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles)
{
    Q_UNUSED(roles);
    qDebug() << "Document data changed: topLeft: " << topLeft.column() << " " << topLeft.row() << " bottomRight: " << bottomRight.column() << " " << bottomRight.row();
}
