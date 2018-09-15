#include <QWidget>
#include <QTimer>
#include <QFile>
//#include <stdlib.h>
#include <vector>
using namespace std;


class spielfeld : public QWidget{
    Q_OBJECT
public:
    spielfeld(QWidget *parent = 0);

    void start(){
        timer->start(20);
        increment=1;
    }
    void stop() {
        timer->stop();
        increment=0;
    }
    void serialize(QFile &file);
    void deserialize(QFile &file);
    void resetGame();

    bool lifeLost;

    enum objectType{square, circle};

private:
    QTimer *timer;
    QTimer *delay;
    int increment;

    int y1=50, y2=50, y3=50;
    int x1, x2, x3;
    int keyPressed;
    int x=225, lifes, points;
    int random;
    int speed1, speed2, speed3;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private slots:
    void startTimer(){start();};
};


class quadrat{
public:
    int getX(){return x;}
    int getVelo(){return velocity;}
private:
    int x= rand() % 490;
    int velocity = 2;
};

class kreis{
public:
    int getX(){return x;}
    int getVelo(){return velocity;}
private:
    int x= rand() % 490;
    int velocity = 3;
};

class kreis2{
public:
    int getX(){return x;}
    int getVelo(){return velocity;}
private:
    int x= rand() & 490;
    int velocity = 5;
};
