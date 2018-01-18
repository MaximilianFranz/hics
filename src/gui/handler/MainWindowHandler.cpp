#include "MainWindowHandler.h"

MainWindowHandler::MainWindowHandler(std::list<NetInfo> &neuralNets, std::list<PlatformInfo> &platforms,
                  std::list<OperationMode> &operationModes) :
startWidgetHandler(neuralNets, platforms, operationModes){
    mainWindow.addWidgetToStack(startWidgetHandler.getStartWidget());
    mainWindow.setCurrentWidget(startWidgetHandler.getStartWidget());
}
