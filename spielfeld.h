#include <QWidget>
#include <QTimer>
#include <QFile>

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

private:
    QTimer *timer;
    int increment;

    int y1=50, y2=50, y3=50;
    int x1=50,x2=225,x3=430;
    int keyPressed;
    int x=225, lifes, points;

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
