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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QGeoPositionInfo>

class QGeoPositionInfoSource;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openDestinationButton_clicked();

    void on_addPointButton_clicked();

    void on_savePointsButton_clicked();

    void on_clearPointsButton_clicked();


    void position_updated(QGeoPositionInfo p);

private:
    void update_position(double latitude, double longitude, double altitude);

    bool load(const QString& filename);
    bool save(const QString& filename);

    Ui::MainWindow *ui;

    QGeoPositionInfoSource* position_info_;
};

#endif // MAIN_WINDOW_H
