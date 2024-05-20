#include "q_main_window.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Q_main_window window;  

    window.show();
    return app.exec();
}
