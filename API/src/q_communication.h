#include <QThread>
#include <cstdint>
#include <stdbool.h>

class SerialReaderThread : public QThread {
    Q_OBJECT
private:
    bool is_run;
public:
    SerialReaderThread(QObject *parent = nullptr) : QThread(parent) {}
    void run() override;

signals:
    void newData(const uint8_t* data);
};