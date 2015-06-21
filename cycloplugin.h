#ifndef CYCLO_H
#define CYCLO_H

#include "cyclo_global.h"

#include <extensionsystem/iplugin.h>

namespace Cyclo {
namespace Internal {

class CYCLOPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Cyclo.json")

public:
    CYCLOPlugin();
    ~CYCLOPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
    void handleDocumentsChange(const QModelIndex&, const QModelIndex&, const QVector<int>&);
};

} // namespace Internal
} // namespace Cyclo

#endif // CYCLO_H

