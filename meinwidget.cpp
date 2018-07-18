#include <QtGui>
// nur notwendig, wenn Qt 5:
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
//Ende Qt 5
#include "meinWidget.h"

meinWidget::meinWidget(QWidget *parent):QWidget(parent){

    QPushButton *start = new QPushButton(tr("Start/Stop"));
    start->setFont(QFont("Arial", 18, QFont::Bold));
    connect(start, SIGNAL(clicked()), this, SLOT(start()));

    /*
    QPushButton *stop = new QPushButton(tr("Pause"));
    stop->setFont(QFont("Arial", 18, QFont::Bold));
    connect(stop, SIGNAL(clicked()), this, SLOT(stop()));
    */

    QPushButton *laden = new QPushButton(tr("Laden"));
    laden->setFont(QFont("Arial", 18, QFont::Bold));
    connect(laden, SIGNAL(clicked()), this, SLOT(load()));

    QPushButton *sichern = new QPushButton(tr("Sichern"));
    sichern->setFont(QFont("Arial", 18, QFont::Bold));
    connect(sichern, SIGNAL(clicked()), this, SLOT(save()));

    QPushButton *quit = new QPushButton(tr("Ende"));
    quit->setFont(QFont("Arial", 18, QFont::Bold));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    meinSpielfeld = new spielfeld;
    meinSpielfeld->setFocusPolicy(Qt::StrongFocus); // Needs to be set, that keyPressEvent() can be caught

    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->addWidget(start, 0,0);

    gridLayout->addWidget(laden, 2,0);
    gridLayout->addWidget(sichern, 3,0);
    gridLayout->addWidget(quit, 5,0);
    gridLayout->addWidget(meinSpielfeld, 0, 1, 6, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void meinWidget::start(){

    if(count % 2) meinSpielfeld->start();       // If count represents an odd number start() will be called
    else meinSpielfeld->stop();
    count++;
}

void meinWidget::stop(void){

    meinSpielfeld->stop();
    count++;
}

void meinWidget::load(void){

    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this, tr("Speichern als"), ".", tr("Savegame (*.sav)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geöffnet werden: ") + fileName,QMessageBox::Ok);
        }

        meinSpielfeld->deserialize(file);
        file.close();
        return;
    }
}

void meinWidget::save(void){

    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this, tr("Speichern als"), ".", tr("Savegame  (*.sav)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        meinSpielfeld->serialize(file);
        file.close();
        return;
    }
}
