#include <windows.h>
#include <iostream>
#include "services/HeThongQLNS.h"

using namespace std;

int main() {
    // Thiet lap UTF-8 cho Console de hien thi tieng Viet
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    HeThongQLNS heThong;
    heThong.menuChinh();

    return 0;
}
