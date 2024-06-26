#include "q_tools.h"
#include "boost/lexical_cast.hpp"
#include <bits/stdc++.h>
#include <string>
using namespace std;
using boost::bad_lexical_cast;
using boost::lexical_cast;

void updateLabel(QLabel *label, std::string data) {
  label->setText(QString(data.c_str()));
}

void update_cells(Ui_BMS *ui, const Cells *cells) {
  updateLabel(ui->c1_2,
              lexical_cast<string>(((cells->voltage[0] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_3,
              lexical_cast<string>(((cells->voltage[1] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_4,
              lexical_cast<string>(((cells->voltage[2] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_5,
              lexical_cast<string>(((cells->voltage[3] * 0.38) + 0.3) / 1000));
  updateLabel(ui->c1_6,
              lexical_cast<string>(((cells->voltage[4] * 0.38) + 0.3) / 1000));
}