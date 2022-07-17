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
    for (Producto *producto : laTienda->consultarProductos())
    {
       ui->listaProductos->addItem(QString::fromStdString(producto->obtenerString()));
    }
}

void MainWindow::on_btnImportar_clicked()
{
    QString archivoDireccion = QFileDialog::getOpenFileName(this, "Abrir archivo", QDir::homePath());
    if (archivoDireccion == "")
    {
        QMessageBox::information(this, "Archivo", "Cancelado");
    }else
    {
        QMessageBox::information(this, "Archivo", archivoDireccion);
        QFile archivo(archivoDireccion);
        if (!archivo.open(QFile::ReadOnly|QFile::Text))
        {
            QMessageBox::warning(this,"Error","El archivo no se abrió");
        }
        std::string stream = QTextStream(&archivo).readAll().toStdString();

        std::filebuf fb;
        if (fb.open (archivoDireccion.toStdString(),std::ios::in))
          {
            std::istream entrada(&fb);
            while (entrada)
              std::cout << char(entrada.get());
            fb.close();
            laTienda->CargarDesdeStreamBinario(&entrada);
          }

    }
}

