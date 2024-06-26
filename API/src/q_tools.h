#include "../build/ui_bms_api.h"
#include "protocol.h"
#include <QtWidgets/QLabel>

void updateLabel(QLabel *label, std::string data);
void update_cells(Ui_BMS *ui, const Cells *cells);