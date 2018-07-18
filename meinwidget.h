#include <QWidget>
#include "spielfeld.h"
#include <QPushButton>

class meinWidget : public QWidget{
    Q_OBJECT
public:
    meinWidget(QWidget *parent = 0);

    enum state { running, paused };
    state status=paused;;

    QPushButton *starter=new QPushButton(tr("Start"));      //Button is initiated here, so that I can change the name via the Slots

private:
    spielfeld *meinSpielfeld = new spielfeld;
    int count=1;

private slots:
    void start();
    void load();
    void save();
};
