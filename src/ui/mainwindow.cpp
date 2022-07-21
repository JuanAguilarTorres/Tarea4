#include "mainwindow.h"
#include "excepcionEliminarIncorrecto.h"
#include "excepcionAgregarDuplicado.h"
#include "excepcionEditarIncorrecto.h"
#include "excepcionCampoInvalido.h"
#include "ui_mainwindow.h"
#include "tienda.h"
#include "producto.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <fstream>

Tienda *laTienda = new Tienda();

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

    ui->listaProductos->sortItems();
}

void MainWindow::on_btnImportar_clicked()
{
    Tienda *tiendaVacia = new Tienda();
    laTienda = tiendaVacia;
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
        std::string archivoString = QTextStream(&archivo).readAll().toStdString();
        std::istringstream stream(archivoString);
        laTienda->CargarDesdeStreamBinario(&stream);
        this->actualizarLista();
        this->ui->lineNombre->setText(QString::fromStdString(laTienda->getNombre()));
        this->ui->lineDirWeb->setText(QString::fromStdString(laTienda->getSitioWeb()));
        this->ui->lineDirFisica->setText(QString::fromStdString(laTienda->getLocalizacion()));
        this->ui->lineTelefono->setText(QString::fromStdString(laTienda->getNombre()));
        }
}


void MainWindow::on_btnAgregar_clicked()
{
    try{
        laTienda->agregarProducto((this->ui->lineIdProducto->text()).toInt(), (this->ui->lineNombreProducto->text()).toStdString(), (this->ui->lineExistencia->text()).toInt());
        this->ui->lineIdProducto->clear();
        this->ui->lineNombreProducto->clear();
        this->ui->lineExistencia->clear();
        this->actualizarLista();
    }catch(excepcionAgregarDuplicado e)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error. El Id ya está en uso.");
        msgbox->open();
    }catch(excepcionCampoInvalido e)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error. Rellene todos los campos, asegúrese que el Id sea mayor o igual a 1.");
        msgbox->open();
    }catch(...){
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error.");
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
    }catch(...)
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
    }catch(...)
    {
        QMessageBox* msgbox = new QMessageBox(this);
        msgbox->setWindowTitle("Notificación");
        msgbox->setText("Error eliminando. Por favor asegúrese que el Id proporcionado esté en uso.");
        msgbox->open();
    }
}




void MainWindow::on_lineNombre_editingFinished()
{
    laTienda->setNombre((this->ui->lineNombre->text()).toStdString());
}


void MainWindow::on_lineDirWeb_editingFinished()
{
    laTienda->setSitioWeb((this->ui->lineDirWeb->text()).toStdString());
}


void MainWindow::on_lineDirFisica_editingFinished()
{
    laTienda->setLocalizacion((this->ui->lineDirFisica->text()).toStdString());
}


void MainWindow::on_lineTelefono_editingFinished()
{
    laTienda->setTelefono((this->ui->lineDirWeb->text()).toStdString());
}


void MainWindow::on_btnGuardar_clicked()
{
    QString archivoDireccion = QFileDialog::getExistingDirectory (this, "Guardar archivo", QDir::homePath());
    if (archivoDireccion == "")
    {
        QMessageBox::information(this, "Archivo", "Cancelado");
    }else
    {
        QMessageBox::information(this, "Archivo", archivoDireccion + "/tienda.dat");
        QFile file(archivoDireccion + "/tienda.dat");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
             QTextStream out(&file);
             std::ostringstream* streamSalida = new ostringstream;
             laTienda->GuardarEnStreamBinario(streamSalida);

             std::string str =  streamSalida->str();

             out << QString::fromStdString(str);
        }
        file.close();
    }
}

