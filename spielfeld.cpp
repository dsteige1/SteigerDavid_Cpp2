#include <QtGui>
#include "spielfeld.h"
#include <iostream>
using namespace std;
#include <QBrush>
#include <QMessageBox>

spielfeld::spielfeld(QWidget *parent):QWidget(parent){
    setPalette(QPalette(QColor(250, 250, 250)));
    setFixedSize(500,500);
    setAutoFillBackground(true);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    increment=0;
    points=0;
    lifes=3;
}

void spielfeld::paintEvent(QPaintEvent * ){
    QPainter avatar, painter, punkte, life1, life2, life3;

    avatar.begin(this);
    avatar.setBrush(Qt::BDiagPattern);
    avatar.drawRect(x,480,60,20);
    avatar.end();

    punkte.begin(this);
    if(increment)points++;
    QString score = "Score: " + QString::number(points);  //QString::number() turns ins into string, so that I can print it on meinSpielfeld via drawText()
    punkte.setFont(QFont("Arial", 18, QFont::Bold));
    punkte.drawText(20,30, score);
    punkte.end();

    life1.begin(this);
    if(lifes==3) life1.setBrush(Qt::SolidPattern);
    life1.drawEllipse(400, 20, 20, 20);
    life1.end();

    life2.begin(this);
    if(lifes>=2) life2.setBrush(Qt::SolidPattern);
    life2.drawEllipse(430, 20, 20, 20);
    life2.end();

    life3.begin(this);
    if(lifes>=1)life3.setBrush(Qt::SolidPattern);
    life3.drawEllipse(460, 20, 20, 20);
    life3.end();

    painter.begin(this);
    painter.setBrush(Qt::SolidPattern);
    painter.drawRect(x1,y1, 30,30);
    painter.setBrush(Qt::Dense6Pattern);
    painter.drawEllipse(x2,y2, 30,30);
    painter.setBrush(Qt::HorPattern);
    painter.drawRect(x3,y3, 30,30);
    painter.end();


    if(increment){
        y1+=2;
        y2+=2;
        y3+=2;
    }

    if(y1==500) y1=50;
    if(y2==500) y2=50;
    if(y3==500) y3=50;

}

void spielfeld::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left){
        //keyPressed = Qt::Key_Left;
        x-=20;
    }
    else if (event->key() == Qt::Key_Right){
        //keyPressed = Qt::Key_Right;
        x+=20;
    }
    update();
}

void spielfeld::serialize(QFile &file){

    QTextStream out(&file);

    out << "MeinSavegame" << endl;

    out  << "x " << y1 <<" "<< y2 <<" "<< y3 <<" "<< x <<" "<< points <<" "<< lifes;

}

void spielfeld::deserialize(QFile &file){

    char c;
    QString test;

    QTextStream in(&file);

    in >> test;
    if (test != "MeinSavegame")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine Zechnungsdatei!"),QMessageBox::Ok);
        return;
    }

    in >> c;

    while (in.status() == QTextStream::Ok)
    {
        in >> c;
        if (in.status() == QTextStream::ReadPastEnd) break;

        if (c!='x')
        {
            QMessageBox::warning(this, tr("Objektfehler"),
                                 tr("Folgender Objekttyp ist unbekannt: ") + c,QMessageBox::Ok);
            return;
        }

    in >> y1 >> y2 >> y3 >> x >> points >> lifes;

    }

    update();
}

