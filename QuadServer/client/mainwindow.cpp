#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdio>
#include <QInputDialog>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <SDL.h>
#include <QTimer>

SDL_Joystick *js;
int t_fix=1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
int vals[4]={0,0,0,0};
int oldvals[4]={0,0,0,0};
QTcpSocket *sock;

void MainWindow::update(int s,int v) {
    while(vals[s]<v) {
        vals[s]++;
        send(s,vals[s]);
    }
    while(vals[s]>v) {
        vals[s]--;
        send(s,vals[s]);
    }
    //send(s,v);
}
void MainWindow::send(int s,int v) {
    union {
        char dat[8];
        int vals[2];
    } info;
    /*if(oldvals[s]==v) {
        return;
    }*/
    oldvals[s]=v;
    info.vals[0]=s;
    info.vals[1]=v;
    printf("%d: %d\n",s,v);
    if(sock) {
        sock->write(info.dat,8);
    }
}

void MainWindow::on_slider1_valueChanged(int position)
{
    update(0,position);
}

void MainWindow::on_slider2_valueChanged(int position)
{
    update(1,position);
}

void MainWindow::on_slider3_valueChanged(int position)
{
    update(2,position);
}

void MainWindow::on_slider4_valueChanged(int position)
{
    update(3,position);
}
QTimer *timer;
void MainWindow::on_actionOpen_IP_triggered()
{
    QString ip = QInputDialog::getText(this,"Gimme Ur IP","where is robit");
    if(sock) {
        delete sock;
    }
    if(timer) {
        delete timer;
    }
    sock = new QTcpSocket();
    sock->connectToHost(ip,1337);
    ui->slider1->setValue(0);
    ui->slider2->setValue(0);
    ui->slider3->setValue(0);
    ui->slider4->setValue(0);
    js = SDL_JoystickOpen(0);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerEvent()));
    timer->start(10);
    t_fix=1;
}

void MainWindow::on_stopbutton_pressed()
{
    ui->slider1->setValue(0);
    ui->slider2->setValue(0);
    ui->slider3->setValue(0);
    ui->slider4->setValue(0);
    t_fix=1;
}

void MainWindow::timerEvent() {
    //fl,fr,rl,rr
    int i;
    SDL_JoystickUpdate();
//    int thrust[4]={0,0,0,0};
    short throttle = SDL_JoystickGetAxis(js,3);
    short rotate = SDL_JoystickGetAxis(js,2);
    short forward = SDL_JoystickGetAxis(js,1);
    short strafe = SDL_JoystickGetAxis(js,0);
    send(0,throttle);
    send(1,rotate);
    send(2,forward);
    send(3,strafe);
}
