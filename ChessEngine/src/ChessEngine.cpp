#include <iostream>
#include "Data/DataManager.h"
#include "Engine/EngineManager.h"
#include "Interface/InterfaceManager.h"

int main(int, char**) {
    LoadData();
    StartEngine();
    StartInterface();
}
