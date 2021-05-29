#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QList>
#include <QButtonGroup>
#include <QObject>
#include <QPushButton>
#include <QQueue>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionStart_triggered();
    void on_actionExit_triggered();
    void on_actionRotate_triggered();
    void ButtonClicked();
    void ChangeButtonClicked();
    void on_actionDelete_triggered();
    void on_actionDefault_triggered();
private:
    Ui::MainWindow *ui;
    int fieldSize = 10;
    QVector<int> field;
    QVector<bool> visited;
    QList<QPushButton*> list;
    QList<QPushButton*> listOpponents;
    QList<QPushButton*> listWithShips;
    QList<QPushButton*> listWithShipsOponents;
    QQueue<int> queue;
    QQueue<int> queueOpponents;
    QList<QPushButton*> helpForRemoving;
    QList<QPushButton*> helpForRemovingOpponetents;
    QList<QPair<int,QList<QPushButton*>>> listWithPairsOpponents;
    QList<QPair<int,QList<QPushButton*>>> listWithPairs;
    QList<int> moves;
    int num = 0;
    bool injured = false;
    bool ifSelected = false;
    bool move = true;
    bool start = false;
    void SetField(QList<QPushButton*>& list, int x = 100, int y = 50, bool flag = true);
    bool CheckShip(QPushButton* button, QList<QPushButton*> list, QList<QPushButton*> listWithShips);
    void ShadowShip(int index, QList<QPushButton*>& list, QList<QPushButton*>& listWithShips);
    bool PlaceShip(QPushButton *button,QList<QPushButton*>& listWithShips, QList<QPushButton*> list, QQueue<int>& queue, bool setIcon = true);
    void PlaceOpponentsShip();
    bool CheckRotateShip(QPushButton* button, QList<QPushButton*> list, QList<QPushButton*> listWithShips);
    void Rotate(QList<QPushButton*>& list, QList<QPushButton*>& listWithShips, bool setIcon = true);
    void PlaceEmptyCells(QList<QPushButton*> list, QList<QPushButton*> listHelpForRemoving,bool setMove);
    void Processing(QList<QPair<int,QList<QPushButton*>>>& listWithPairs,QList<QPushButton*> list, QList<QPushButton*>& listWithShips,QList<QPushButton*>& helpForRemoving,QPushButton* button,bool setMove);
    void GameResult(bool isWin = true);
   // void ComputerProcessingMove();
};

#endif // MAINWINDOW_H
