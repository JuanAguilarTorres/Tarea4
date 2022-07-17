#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./../../lib/include/tienda.h"
#include "./../../lib/include/producto.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>

//Inicio
Tienda *laTienda = new Tienda();
//---

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarLista()
{
    ui->listaProductos->clear();
    for (Producto *producto : laTienda->consultarProductos())
    {
       ui->listaProductos->addItem(QString::fromStdString(producto->obtenerString()));
    }
}

void MainWindow::on_btnImportar_clicked()
{
//    QString archivoDireccion = QFileDialog::getOpenFileName(this, "Abrir archivo", QDir::homePath());
//    if (archivoDireccion == "")
//    {
//        QMessageBox::information(this, "Archivo", "Cancelado");
//    }else
//    {
//        QMessageBox::information(this, "Archivo", archivoDireccion);
//        QFile archivo(archivoDireccion);
//        if (!archivo.open(QFile::ReadOnly|QFile::Text))
//        {
//            QMessageBox::warning(this,"Error","El archivo no se abrió");
//        }
//        std::string stream = QTextStream(&archivo).readAll().toStdString();

//        std::filebuf fb;
//        if (fb.open (archivoDireccion.toStdString(),std::ios::in))
//          {
//            std::istream entrada(&fb);
//            while (entrada)
//              std::cout << char(entrada.get());
//            fb.close();
//            laTienda->CargarDesdeStreamBinario(&entrada);
//          }

//    }
}


void MainWindow::on_btnAgregar_clicked()
{
    try{
        laTienda->agregarProducto((this->ui->lineIdProducto->text()).toInt(), (this->ui->lineNombreProducto->text()).toStdString(), (this->ui->lineExistencia->text()).toInt());
        this->ui->lineIdProducto->clear();
        this->ui->lineNombreProducto->clear();
        this->ui->lineExistencia->clear();
        this->actualizarLista();
    }catch(char const*message)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error agregando. Por favor asegúrese que el Id no esté en uso ya.");
        msgbox->open();
    }
}


void MainWindow::on_btnEditar_clicked()
{
    try{
        laTienda->editarProducto((this->ui->lineIdProducto->text()).toInt(), (this->ui->lineNombreProducto->text()).toStdString(), (this->ui->lineExistencia->text()).toInt());
        this->ui->lineIdProducto->clear();
        this->ui->lineNombreProducto->clear();
        this->ui->lineExistencia->clear();
        this->actualizarLista();
    }catch(char const*message)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error editando. Por favor asegúrese que el Id proporcionado esté en uso.");
        msgbox->open();
    }
}


void MainWindow::on_btnEliminar_clicked()
{
    try{
        laTienda->eliminarProducto((this->ui->lineIdProducto->text()).toInt());
        this->ui->lineIdProducto->clear();
        this->ui->lineNombreProducto->clear();
        this->ui->lineExistencia->clear();
        this->actualizarLista();
    }catch(char const*message)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error eliminando. Por favor asegúrese que el Id proporcionado esté en uso.");
        msgbox->open();
    }
}

