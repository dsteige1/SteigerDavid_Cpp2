#include <QtGui>
#include "spielfeld.h"
#include <iostream>
using namespace std;
#include <QBrush>
#include <QMessageBox>
#include <vector>
//#include <stdlib.h>

spielfeld::spielfeld(QWidget *parent):QWidget(parent){
    setPalette(QPalette(QColor(250, 250, 250)));
    setFixedSize(500,500);
    setAutoFillBackground(true);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    delay=new QTimer(this);

    increment=0;
    points=0;
    lifes=3;
    lifeLost = false;
}

void spielfeld::paintEvent(QPaintEvent * ){
    QPainter avatar, objekt1, objekt2, objekt3, punkte, life;

    /********/
    //Avatar//
    /********/

    avatar.begin(this);

    avatar.setBrush(Qt::BDiagPattern);
    avatar.drawRect(x,480,60,20);

    avatar.end();

    /*******/
    //Score//
    /*******/

    punkte.begin(this);

    if(increment)points++;
    QString score = "Score: " + QString::number(points);  //QString::number() turns ins into string, so that I can print it on meinSpielfeld via drawText()
    punkte.setFont(QFont("Arial", 18, QFont::Bold));
    punkte.drawText(20,30, score);

    punkte.end();

    /*******/
    //Leben//
    /*******/

    life.begin(this);

    if(lifes==3)
        life.setBrush(Qt::SolidPattern);
    life.drawEllipse(400,20,20,20);
    if(lifes>=2)
        life.setBrush(Qt::SolidPattern);
    life.drawEllipse(430,20,20,20);
    if(lifes>=1)
        life.setBrush(Qt::SolidPattern);
    life.drawEllipse(460,20,20,20);

    life.end();

    /*********/
    //Objekte//
    /*********/

    if(y1==500){
        y1=50;
        lifeLost=false;
    }
    if(y2==500){
        y2=50;
        lifeLost=false;
    }
    if(y3==500){
        y3=50;
        lifeLost=false;
    }


    objekt1.begin(this);

    class quadrat *gegner1;
    gegner1 = new quadrat;

    speed1=gegner1->getVelo();

    if(y1==50)
        x1=gegner1->getX();

    objekt1.setBrush(Qt::SolidPattern);
    objekt1.drawRect(x1,y1, 30,30);

    objekt1.end();

    objekt2.begin(this);

    class kreis *gegner2;
    gegner2= new kreis;

    speed2=gegner2->getVelo();

    if(y2==50)
        x2=gegner2->getX();

    objekt2.setBrush(Qt::Dense6Pattern);
    objekt2.drawEllipse(x2,y2, 30,30);

    objekt2.end();

    objekt3.begin(this);

    class kreis2 *gegner3;
    gegner3= new kreis2;

    speed3=gegner3->getVelo();

    if(y3==50)
        x3=gegner3->getX();

    objekt3.setBrush(Qt::HorPattern);
    objekt3.drawEllipse(x3,y3, 30,30);

    objekt3.end();

    //Movement

    if(increment){
        y1+=speed1;
        y2+=speed2;
        y3+=speed3;
    }

    //Kollisions-Check

    float minimum = 30, jetzt;
    int xDiff, yDiff;

    /*Check if the object has already been hit or not (bool lifeLost).
     Otherwhise the collision would be detected with every click of the timer and all lifes are gone with a second ('one' collision).
    */

    if(lifeLost==false){

        xDiff= (x1+15) - (x+30);
        yDiff= (y1+15) - (480+10);

        jetzt= sqrt((float) (xDiff * xDiff + yDiff * yDiff) );
        if (jetzt < minimum){
            lifes--;
            lifeLost=true;
            stop();
            delay->singleShot(500, this, SLOT(startTimer()));
            return;
        }

        xDiff= (x2+15) - (x+30);
        yDiff= (y2+15) - (480+10);

        jetzt= sqrt((float) (xDiff * xDiff + yDiff * yDiff) );
        if (jetzt < minimum){
            lifes--;
            lifeLost=true;
            stop();
            delay->singleShot(500, this, SLOT(startTimer()));
            return;
        }

        xDiff= (x3+15) - (x+30);
        yDiff= (y3+15) - (480+10);

        jetzt= sqrt((float) (xDiff * xDiff + yDiff * yDiff) );
        if (jetzt < minimum){
            lifes--;
            lifeLost=true;
            stop();
            delay->singleShot(500, this, SLOT(startTimer()));
            return;
        }
    }

    if(lifes==0){

        stop();

        QPainter painter;

        painter.begin(this);
        painter.setFont(QFont("Arial", 30, QFont::Bold));
        painter.drawText(150,250, "Game Over!!");
        painter.end();

        delay->singleShot(3000, this, SLOT(startTimer()));

        resetGame();
    }

    //Avatar cannot leave the Spielfeld

    if(x<-10) x=480;
    if(x>480) x=-10;
}

void spielfeld::resetGame(){

    increment=0;
    points=0;
    lifes=3;
    lifeLost = false;

    y1=50;
    y2=50;
    y3=50;
    x=225;
}

void spielfeld::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_Left){
        x-=20;
    }
    else if (event->key() == Qt::Key_Right){
        x+=20;
    }
    update();
}

void spielfeld::serialize(QFile &file){

    QTextStream out(&file);

    out << "MeinSavegame" << endl;

    out  << "x " << y1 <<" "<< y2 <<" "<<
            y3 <<" "<< x1 <<" "<< x2 <<" "<< x3 <<
            " "<< x <<" "<< points <<" "<< lifes;

}

void spielfeld::deserialize(QFile &file){

    char c;
    QString test;

    QTextStream in(&file);

    in >> test;
    if (test != "MeinSavegame")
    {
        QMessageBox::warning(this, tr("Formatfehler"),
                             tr("Das ist keine Savegame-Datei!"),QMessageBox::Ok);
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

        in >> y1 >> y2 >> y3 >> x1 >> x2 >> x3 >> x >> points >> lifes;

    }

    update();
}
