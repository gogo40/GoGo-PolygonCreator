/*
   GoGo-PolygonCreator is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

Main Window

(c) 2015, Escrito por Péricles Lopes Machado <pericles.raskolnikoff@gmail.com>
*/

#include "main_window.h"
#include "ui_main_window.h"

#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QGeoCoordinate>
#include <QGeoPositionInfoSource>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->points->resizeColumnsToContents();

    position_info_ = QGeoPositionInfoSource::createDefaultSource(this);

    if (position_info_) {
        connect(position_info_, SIGNAL(positionUpdated(QGeoPositionInfo)),
                this, SLOT(position_updated(QGeoPositionInfo)));


        position_info_->startUpdates();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openDestinationButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(0,
                                                tr("Salvar pontos"),
                                                "",
                                                tr("CSV (*.csv)"));

    if (path == "") return;

    QStringList t = path.split(".");

    if (t.size() > 1) {
        if (t[t.size() - 1] != "csv") {
            path += ".csv";
        }
    } else {
        path += ".csv";
    }

    ui->path->setText(path);

    load(path);

    ui->points->resizeColumnsToContents();
}

void MainWindow::on_addPointButton_clicked()
{
    QString element = ui->element->text();
    QString point = ui->point->text();
    double lat = ui->latitude->value();
    double lon = ui->longitude->value();
    double alt = ui->altitude->value();
    int row = ui->points->rowCount();


    ui->points->setRowCount(row + 1);

    for (int j = 0; j < 5; ++j) {
        if (!ui->points->item(row, j)) {
            ui->points->setItem(row, j, new QTableWidgetItem(""));
        }
    }

    ui->points->item(row, 0)->setText(element);
    ui->points->item(row, 1)->setText(point);
    ui->points->item(row, 2)->setText(QString::number(lat, 'g', 10));
    ui->points->item(row, 3)->setText(QString::number(lon, 'g', 10));
    ui->points->item(row, 4)->setText(QString::number(alt, 'g', 10));

    ui->points->resizeColumnsToContents();
}

void MainWindow::on_savePointsButton_clicked()
{
    QString filename = ui->path->text();
    bool ok = save(filename);

    if (ok) {
        QMessageBox::warning(0, "File saved",
                             "Points saved in file '" + filename + "'");
    } else {
        QMessageBox::warning(0, "Error during file saving...",
                             "Points can't be saved in file  '" + filename + "'");
    }
}

void MainWindow::on_clearPointsButton_clicked()
{
    ui->points->setRowCount(0);
}

void MainWindow::update_position(double latitude, double longitude, double altitude)
{
    ui->latitude->setValue(latitude);
    ui->longitude->setValue(longitude);
    ui->altitude->setValue(altitude);
}

bool MainWindow::load(const QString &filename)
{
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        return false;
    }

    int row = 0;

    while (!file.atEnd()) {
        QString line = file.readLine();
        QStringList content = line.split(",");

        if (content.size() >= 5) {
            const QString& element = content.at(0);
            const QString& point = content.at(1);

            double lat = content.at(2).toDouble();
            double lon = content.at(3).toDouble();
            double alt = content.at(4).toDouble();

            ui->points->setRowCount(row + 1);

            for (int j = 0; j < 5; ++j) {
                if (!ui->points->item(row, j)) {
                    ui->points->setItem(row, j, new QTableWidgetItem(""));
                }
            }

            ui->points->item(row, 0)->setText(element);
            ui->points->item(row, 1)->setText(point);
            ui->points->item(row, 2)->setText(QString::number(lat, 'g', 10));
            ui->points->item(row, 3)->setText(QString::number(lon, 'g', 10));
            ui->points->item(row, 4)->setText(QString::number(alt, 'g', 10));

            ++row;
        }
    }

    file.close();

    return true;
}

bool MainWindow::save(const QString &filename)
{

    QFile f(filename);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) return false;

    QTextStream out(&f);

    int nc = ui->points->columnCount();
    int nr = ui->points->rowCount();

    for (int i = 0; i < nr; ++i) {
        for (int j = 0; j < nc; ++j) {
            if (j > 0) {
                out << ",";
            }
            out << ui->points->item(i, j)->text();
        }
        out << "\n";
    }
    return true;
}

void MainWindow::position_updated(QGeoPositionInfo p)
{
     if (!p.isValid()) return;

     QGeoCoordinate p_ = p.coordinate();

     update_position(p_.latitude(), p_.longitude(), p_.altitude());
}
