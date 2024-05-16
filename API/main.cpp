#include "ui_bms_api.h"

using namespace Ui;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;  
    Ui_BMS ui;
    ui.setupUi(&window);

    window.show();
    return app.exec();
}
