#include <QWidget>
#include "spielfeld.h"

class meinWidget : public QWidget{
    Q_OBJECT
public:
    meinWidget(QWidget *parent = 0);

    enum state { running, paused };
    state status=paused;;

private:
    spielfeld *meinSpielfeld = new spielfeld;
    int count=1;

private slots:
    void start();
    void stop();
    void load();
    void save();
};
