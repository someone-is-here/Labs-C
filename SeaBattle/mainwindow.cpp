#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QSize>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>
#include <QApplication>
#include <QProcess>
#include <QThread>
#include <QDir>
#include <QUrl>
#include <QMovie>
#include <QtTest/QTest>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1600, 1000);

    QBrush* brush = new QBrush();
    QPalette* palette = new QPalette();
    brush->setTextureImage(QImage("D:\\QT\\Projects\\SeaBattle\\img\\sea1.jpg"));
    palette->setBrush(QPalette::Background, *brush);
    this->setPalette(*palette);

    QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\img\\icon.jpg");
    QIcon buttonIcon(pixmap);
    this->setWindowIcon(buttonIcon);

    SetField(list);
    int array[10] = { 4,3,3,2,2,2,1,1,1,1 };
    for (int i = 0; i < 10; i++) {
        queue.append(array[i]);
    }

    int index = 0;
    num = array[index];

    for (int i = 0; i < fieldSize * fieldSize; i++) {
        field.push_back(i);
        visited.push_back(false);
    }
}
MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::on_actionStart_triggered() {
    if (!start && queue.size() == 0) {
        SetField(listOpponents, 700, 50, false);
        PlaceOpponentsShip();
        start = true;
    }
}
void MainWindow::PlaceOpponentsShip() {
    if (listWithShipsOponents.size() != 0) {
        QIcon icon;
        for (auto but : listWithShipsOponents) {
            but->setIcon(icon);
        }
        listWithShipsOponents.clear();
    }
    int array[10] = { 4,3,3,2,2,2,1,1,1,1 };
    for (int i = 0; i < 10; i++) {
        queueOpponents.append(array[i]);
    }
    int i = 0;
    num = array[i];

    while (queueOpponents.size() != 0) {
        i = rand() % listOpponents.size();
        if (!listWithShipsOponents.contains(listOpponents[i])) {
            if (queueOpponents.size() > 0) {
                if (rand() % 2 && queueOpponents.head() > 1 && PlaceShip(listOpponents[i], listWithShipsOponents, listOpponents, queueOpponents, false)) {
                    PlaceShip(listOpponents[i], listWithShipsOponents, listOpponents, queueOpponents, false);
                    Rotate(listOpponents, listWithShipsOponents, false);
                }
                else {
                    PlaceShip(listOpponents[i], listWithShipsOponents, listOpponents, queueOpponents, false);
                }
            }
        }
    }
}
void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}
void MainWindow::on_actionRotate_triggered() {
    if (!start) {
        Rotate(list, listWithShips);
    }
}
void MainWindow::Rotate(QList<QPushButton*>& list, QList<QPushButton*>& listWithShips, bool setIcon) {
    QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\img\\ship.png");
    QIcon buttonIcon(pixmap);
    QList<QPushButton*> helpList;
    QIcon icon;
    int index = 0;
    int check = -1;
    if (ifSelected) {
        for (int i = 0; i < listWithShips.size(); i++) {
            if (listWithShips[i]->graphicsEffect() != nullptr) {
                if (check == -1 && i + 1 < listWithShips.size() && list.indexOf(listWithShips[i]) / 10 == list.indexOf(listWithShips[i + 1]) / 10) check = 1;
                else if (check == -1) check = 0;
                if (list.indexOf(listWithShips[i]) + index < list.size() && check) {
                    helpList.append(list[list.indexOf(listWithShips[i]) + index]);
                    listWithShips[listWithShips.indexOf(listWithShips[i])]->setIcon(icon);
                    listWithShips[listWithShips.indexOf(listWithShips[i])]->setGraphicsEffect(nullptr);
                    listWithShips.removeAt(i);
                    i--;
                    index += 9;
                }
                else if (!check && list.indexOf(listWithShips[i]) + index >= 0) {
                    helpList.append(list[list.indexOf(listWithShips[i]) + index]);
                    listWithShips[listWithShips.indexOf(listWithShips[i])]->setIcon(icon);
                    listWithShips[listWithShips.indexOf(listWithShips[i])]->setGraphicsEffect(nullptr);
                    listWithShips.removeAt(i);
                    i--;
                    index -= 9;
                }
                else {
                    if (check) {
                        index -= 9;
                        for (int j = helpList.size() - 1; j >= 0; j--, index -= 9) {
                            listWithShips.insert(i, list[list.indexOf(helpList[j]) - index]);
                            if (setIcon) {
                                list[list.indexOf(helpList[j]) - index]->setIcon(buttonIcon);
                                list[list.indexOf(helpList[j]) - index]->setIconSize(QSize(50, 50));
                            }
                        }
                    }
                    else {
                        index += 9;
                        for (int j = helpList.size() - 1; j >= 0; j--, index += 9) {
                            listWithShips.insert(i, list[list.indexOf(helpList[j]) - index]);
                            if (setIcon) {
                                list[list.indexOf(helpList[j]) - index]->setIcon(buttonIcon);
                                list[list.indexOf(helpList[j]) - index]->setIconSize(QSize(50, 50));
                            }
                        }
                    }
                    i += helpList.size();
                    while (i + 1 < listWithShips.size() && listWithShips[i]->graphicsEffect() != nullptr) {
                        listWithShips[i++]->setGraphicsEffect(nullptr);
                    }
                    listWithShips[i]->setGraphicsEffect(nullptr);
                    ifSelected = false;
                    helpList.clear();
                    return;
                }
            }
        }
        if (check) {
            index -= 9;
            int counter = 0;
            for (int i = 0; i < helpList.size(); i++) {
                if (CheckRotateShip(helpList[i], list, listWithShips)) {
                    counter++;
                }
            }
            if (counter == helpList.size()) {
                for (int i = 0; i < helpList.size(); i++) {
                    listWithShips.append(helpList[i]);
                    if (setIcon) {
                        helpList[i]->setIcon(buttonIcon);
                        helpList[i]->setIconSize(QSize(50, 50));
                    }
                }
            }
            else {
                for (int j = helpList.size() - 1; j >= 0; j--, index -= 9) {
                    listWithShips.push_front(list[list.indexOf(helpList[j]) - index]);
                    if (setIcon) {
                        list[list.indexOf(helpList[j]) - index]->setIcon(buttonIcon);
                        list[list.indexOf(helpList[j]) - index]->setIconSize(QSize(50, 50));
                    }
                }
            }
        }
        if (!check) {
            index += 9;
            int counter = 0;
            for (int i = 0; i < helpList.size(); i++) {
                if (CheckShip(helpList[i], list, listWithShips)) {
                    counter++;
                }
            }
            if (counter == helpList.size()) {
                for (int i = 0; i < helpList.size(); i++) {
                    listWithShips.append(helpList[i]);
                    if (setIcon) {
                        helpList[i]->setIcon(buttonIcon);
                        helpList[i]->setIconSize(QSize(50, 50));
                    }

                }
            }
            else {
                for (int j = helpList.size() - 1; j >= 0; j--, index += 9) {
                    listWithShips.push_front(list[list.indexOf(helpList[j]) - index]);
                    if (setIcon) {
                        list[list.indexOf(helpList[j]) - index]->setIcon(buttonIcon);
                        list[list.indexOf(helpList[j]) - index]->setIconSize(QSize(50, 50));
                    }
                }
            }
        }
    }
    ifSelected = false;
    helpList.clear();
}
bool MainWindow::CheckRotateShip(QPushButton* button, QList<QPushButton*> list, QList<QPushButton*> listWithShips) {
    bool checked = true;
    if (list.indexOf(button) > 9 && list.indexOf(button) <= 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
        if (listWithShips.contains(list[list.indexOf(button) - 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 0) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 9) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 90) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 99) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) > 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
        if (listWithShips.contains(list[list.indexOf(button) + 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) % 10 == 0 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) % 10 == 9 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
            checked = false;
        }
    }
    return checked;
}
void MainWindow::ButtonClicked() {
    QObject* sender = this->sender();
    QPushButton* button = qobject_cast<QPushButton*>(sender);
    if (queue.size() >= 0 && !start) {
        PlaceShip(button, listWithShips, list, queue);
    }
    if (queue.size() == 0 && !move) {
        while (!move && queue.size() == 0) {
            if (moves.size() == 0) {
                int pos = rand() % (field.size());
                Processing(listWithPairs, list, listWithShips, helpForRemoving, list[field[pos]], true);
            }
            else {
                while (!moves.isEmpty() && !field.contains(moves[0])) {
                    moves.pop_front();
                }
                Processing(listWithPairs, list, listWithShips, helpForRemoving, list[moves[0]], true);
            }
            if (!listWithShips.size()) {
                GameResult(false);
            }
        }
    }
}
void MainWindow::ChangeButtonClicked() {
    QObject* sender = this->sender();
    QPushButton* button = qobject_cast<QPushButton*>(sender);
    if (!listWithShipsOponents.size()) {
        GameResult();
    }
    if (!visited[listOpponents.indexOf(button)]) {
        Processing(listWithPairsOpponents, listOpponents, listWithShipsOponents, helpForRemovingOpponetents, button, false);
        if (!move)ButtonClicked();
    }
}
void MainWindow::GameResult(bool isWin) {
    if (!isWin) {
        QPixmap pixmap2("D:\\QT\\Projects\\SeaBattle\\img\\ship.png");
        QIcon buttonIconShip(pixmap2);
        for (int i = 0; i < listWithShipsOponents.size(); i++) {
            listWithShipsOponents[i]->setIcon(buttonIconShip);
            listWithShipsOponents[i]->setIconSize(QSize(50, 50));
        }
    }
    QMessageBox msgBox;
    msgBox.setGeometry(this->width() / 2, this->height() / 2, 100, 100);
    if (isWin) {
        msgBox.setText("You win the game!");
    }
    else {
        msgBox.setText("You loose the game!");
    }
    msgBox.setInformativeText("Do you want to play another one?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    QPixmap pixmap(50, 50);
    pixmap.load("D:\\QT\\Projects\\SeaBattle\\img\\icon1.png");
    msgBox.setIconPixmap(pixmap);

    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        break;
    case QMessageBox::No:
        on_actionExit_triggered();
        break;
    }
}
void MainWindow::Processing(QList<QPair<int, QList<QPushButton*>>>& listWithPairs, QList<QPushButton*> list, QList<QPushButton*>& listWithShips, QList<QPushButton*>& helpForRemoving, QPushButton* button, bool setMove) {
    if (queueOpponents.size() == 0 && queue.size() == 0) {
        QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\img\\nothing.jpg");
        QIcon nothing(pixmap);

        QPixmap pixmap1("D:\\QT\\Projects\\SeaBattle\\img\\noShip.png");
        QIcon buttonIconWithoutShip(pixmap1);

        QPixmap pixmap2("D:\\QT\\Projects\\SeaBattle\\img\\ship.png");
        QIcon buttonIconShip(pixmap2);

        QList<QPushButton*> listHelpForRemoving;

        if (listWithShips.contains(button)) {
            if (helpForRemoving.contains(button)) {
                for (int i = 0; i < listWithPairs.size(); i++) {
                    if (listWithPairs[i].second.contains(button)) {
                        listWithPairs[i].first--;
                        if (setMove && injured) {
                            int statBut = moves[moves.size() - 1];
                            int diff = statBut - list.indexOf(button);
                            if (!moves.isEmpty() && !injured) moves.clear();
                            if (diff != 0) {
                                bool flag1 = true, flag2 = true;
                                for (int k = 1; k < fieldSize / 2; k++) {
                                    if (statBut + diff * k >= 0 && statBut + diff * k < fieldSize * fieldSize) {
                                        if (!field.contains(statBut + diff * k) && flag1) flag1 = false;
                                        moves.push_back(statBut + diff * k);
                                    }
                                    if (statBut - diff * k >= 0 && statBut - diff * k < fieldSize * fieldSize) {
                                        if (!field.contains(statBut - diff * k) && flag2) flag2 = false;
                                        moves.push_back(statBut - diff * k);
                                    }
                                }
                                moves.push_front(list.indexOf(button));
                                injured = false;
                            }
                        }
                        break;
                    }
                }
            }
            else {
                int counter = 0;
                if (!helpForRemoving.contains(list[list.indexOf(button)])) {
                    int j = list.indexOf(button) + 1;
                    if (j % 10 != 0) {
                        while (j < list.size() && listWithShips.contains(list[j])) {
                            if (j % 10 != 0)counter++;
                            else break;
                            helpForRemoving.append(list[j]);
                            listHelpForRemoving.append(list[j]);
                            j++;
                        }
                    }
                    j = list.indexOf(button) + 10;
                    while (j < list.size() && listWithShips.contains(list[j])) {
                        helpForRemoving.append(list[j]);
                        listHelpForRemoving.append(list[j]);
                        counter++;
                        j += 10;
                    }

                    j = list.indexOf(button) - 10;
                    while (j >= 0 && listWithShips.contains(list[j])) {
                        helpForRemoving.append(list[j]);
                        listHelpForRemoving.append(list[j]);
                        counter++;
                        j -= 10;
                    }

                    j = list.indexOf(button) - 1;
                    if (j % 10 != 9) {
                        while (j >= 0 && listWithShips.contains(list[j])) {
                            if (j % 10 != 9)counter++;
                            else break;
                            helpForRemoving.append(list[j]);
                            listHelpForRemoving.append(list[j]);
                            j--;
                        }
                    }
                    listHelpForRemoving.append(button);
                    helpForRemoving.append(button);
                    if (setMove) {
                        if (list.indexOf(button) + 1 < list.size() && field.contains(list.indexOf(button) + 1))moves.push_back(list.indexOf(button) + 1);
                        if (list.indexOf(button) - 1 >= 0 && field.contains(list.indexOf(button) - 1))moves.push_back(list.indexOf(button) - 1);
                        if (list.indexOf(button) + 10 < list.size() && field.contains(list.indexOf(button) + 10))moves.push_back(list.indexOf(button) + 10);
                        if (list.indexOf(button) - 10 >= 0 && field.contains(list.indexOf(button) - 10)) moves.push_back(list.indexOf(button) - 10);
                        moves.push_back(list.indexOf(button));
                        pos = list.indexOf(button);
                    }
                    listWithPairs.append(QPair<int, QList<QPushButton*>>(counter, listHelpForRemoving));
                    listHelpForRemoving.clear();
                    if (setMove)injured = true;
                }
            }
            list[list.indexOf(button)]->setIcon(buttonIconShip);
            list[list.indexOf(button)]->setIconSize(QSize(50, 50));

            QMovie* movie = new QMovie("D:\\QT\\Projects\\SeaBattle\\3.gif");
            QLabel* processLabel = new QLabel(tr(""), this);

            processLabel->setPixmap(pixmap2);
            processLabel->setGeometry(list[list.indexOf(button)]->geometry());
            movie->setScaledSize(QSize(50, 50));
            processLabel->setMovie(movie);

            movie->start();
            processLabel->show();

            mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("D:\\QT\\Projects\\SeaBattle\\1.mp3")));
            mediaPlayer->setVolume(50);

            mediaPlayer->play();
            QTest::qWait(2020);

            movie->stop();
            processLabel->clear();

            list[list.indexOf(button)]->setIcon(buttonIconWithoutShip);
            list[list.indexOf(button)]->setIconSize(QSize(50, 50));
            listWithShips.removeOne(button);
            helpForRemoving.removeOne(button);

            if (!setMove) {
                visited[list.indexOf(button)] = true;
            }

            if (field.contains(list.indexOf(button)) && setMove) {
                field.removeOne(list.indexOf(button));
                if (moves.size() - 1 >= 0 && moves.indexOf(list.indexOf(button)) != moves.size() - 1)moves.removeOne(list.indexOf(button));
            }
            for (int i = 0; i < listWithPairs.size(); i++) {
                if (listWithPairs[i].first == 0) {
                    PlaceEmptyCells(list, listWithPairs[i].second, setMove);
                    if (!moves.isEmpty() && setMove && helpForRemoving.size() == 0 && listWithPairs.size() == 1)moves.clear();
                    listWithPairs.removeAt(i);
                    injured = false;
                    break;
                }
            }
        }
        else {
            if (field.contains(list.indexOf(button)) && setMove) {
                list[list.indexOf(button)]->setIcon(nothing);
                list[list.indexOf(button)]->setIconSize(QSize(50, 50));
            }
            else if (!setMove) {
                list[list.indexOf(button)]->setIcon(nothing);
                list[list.indexOf(button)]->setIconSize(QSize(50, 50));
                visited[list.indexOf(button)] = true;
            }
            mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::toNativeSeparators("D:\\QT\\Projects\\SeaBattle\\2.mp3")));
            mediaPlayer->setVolume(50);
            mediaPlayer->play();
            if (field.contains(list.indexOf(button)) && setMove) {
                if (!moves.isEmpty() && moves.contains(list.indexOf(button))) {
                    moves.removeOne(list.indexOf(button));
                }
                if (field.contains(list.indexOf(button))) {
                    field.removeOne(list.indexOf(button));
                }
            }
            move = setMove;
            QTest::qWait(1000);
        }
    }
}
bool MainWindow::CheckShip(QPushButton* button, QList<QPushButton*> list, QList<QPushButton*> listWithShips) {
    bool checked = true;
    if (list.indexOf(button) > 9 && list.indexOf(button) <= 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 0) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 9) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 90) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) == 99) {
        if (listWithShips.contains(list[list.indexOf(button) - 10])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) < 9 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) > 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) % 10 == 0 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
            checked = false;
        }
    }
    else if (list.indexOf(button) % 10 == 9 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
        if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
            checked = false;
        }
        if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
            checked = false;
        }
    }
    return checked;
}
void MainWindow::ShadowShip(int index, QList<QPushButton*>& list, QList<QPushButton*>& listWithShips) {
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setColor("Red");
    effect->setOffset(0);
    effect->setBlurRadius(20);

    int currIndex = list.indexOf(listWithShips[index]);
    int currIndex2 = list.indexOf(listWithShips[index]);
    int copyIndex = index;

    listWithShips[index]->setGraphicsEffect(effect);

    if (index - 1 >= 0) {
        while (list.indexOf(listWithShips[index - 1]) == currIndex - 1 || list.indexOf(listWithShips[index - 1]) == currIndex - 10) {
            QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
            effect->setColor("Red");
            effect->setOffset(0);
            effect->setBlurRadius(20);
            listWithShips[--index]->setGraphicsEffect(effect);
            if (index - 1 < 0) break;
            if (list.indexOf(listWithShips[index]) == currIndex - 1) { currIndex--; }
            else currIndex -= 10;
        }
    }
    if (copyIndex + 1 < listWithShips.size()) {
        while (list.indexOf(listWithShips[copyIndex + 1]) == currIndex2 + 1 || list.indexOf(listWithShips[copyIndex + 1]) == currIndex2 + 10) {
            QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
            effect->setColor("Red");
            effect->setOffset(0);
            effect->setBlurRadius(20);
            listWithShips[++copyIndex]->setGraphicsEffect(effect);
            if (copyIndex + 1 >= listWithShips.size()) break;

            if (list.indexOf(listWithShips[copyIndex]) == currIndex2 + 1) { currIndex2++; }
            else  currIndex2 += 10;
        }
    }
}
bool MainWindow::PlaceShip(QPushButton* button, QList<QPushButton*>& listWithShips, QList<QPushButton*> list, QQueue<int>& queue, bool setIcon) {
    QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\img\\ship.png");
    QIcon buttonIcon(pixmap);
    bool checked = true;
    if (listWithShips.contains(button) && !ifSelected) {
        ShadowShip(listWithShips.indexOf(button), list, listWithShips);
        ifSelected = true;
    }
    else if (listWithShips.contains(button)) {
        for (auto but : listWithShips) {
            but->setGraphicsEffect(nullptr);
        }
        ifSelected = false;
    }
    else {
        if (queue.size() == 0) {
            return false;
        }
        if (listWithShips.size() < num) {
            if (list.indexOf(button) > 9 && list.indexOf(button) <= 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
                if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
                    checked = false;
                }
                if ((listWithShips.contains(list[list.indexOf(button) + 1])) || listWithShips.contains(list[list.indexOf(button) - 1])) {
                    checked = false;
                }
                if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) == 0) {
                if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) == 9) {
                if (listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) == 90) {
                if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) == 99) {
                if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) < 9 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
                if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10])) {
                    checked = false;
                }
                if (listWithShips.contains(list[list.indexOf(button) + 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) > 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
                if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
                    checked = false;
                }
                if (listWithShips.contains(list[list.indexOf(button) + 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) % 10 == 0 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
                if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
                    checked = false;
                }
                if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
                    checked = false;
                }
            }
            else if (list.indexOf(button) % 10 == 9 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
                if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
                    checked = false;
                }
                if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
                    checked = false;
                }
            }
            if (checked) {
                int currIndex = list.indexOf(button) / 10;
                for (int i = 0; i < queue.head(); i++) {
                    if (list.indexOf(button) + i >= list.size()) return false;
                    if (listWithShips.contains(list[list.indexOf(button) + i])) {
                        return false;
                    }
                    if ((list.indexOf(button) + i) / 10 != currIndex) {
                        return false;
                    }
                    if (!CheckShip(list[list.indexOf(button) + i], list, listWithShips)) {
                        return false;
                    }
                }
                for (int i = 0; i < queue.head(); i++) {
                    listWithShips.append(list[list.indexOf(button) + i]);
                    if (setIcon) {
                        list[list.indexOf(button) + i]->setIcon(buttonIcon);
                        list[list.indexOf(button) + i]->setIconSize(QSize(50, 50));
                    }
                }
                num += queue.head();
                queue.pop_front();
                return true;
            }
        }
        else {
            return false;
        }
    }
    return true;
}
void MainWindow::SetField(QList<QPushButton*>& list, int x, int y, bool flag) {
    int num = 0;
    int copyX = x;
    for (int i = 0; i < fieldSize * fieldSize; i++) {
        QPushButton* button = new QPushButton(tr(""), this);
        button->setGeometry(QRect(QPoint(x, y), QSize(50, 50)));
        button->setFocusPolicy(Qt::NoFocus);
        list.append(button);
        if (!flag) {
            button->show();
        }
        if (i != 0 && (i + 1) % 10 == 0) {
            y += 50;
            x = copyX;
        }
        else {
            x += 50;
        }
        if (flag) {
            connect(button, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
        }
        else {
            connect(button, SIGNAL(clicked()), this, SLOT(ChangeButtonClicked()));
        }
    }

    char ch = 'A';
    x = copyX - 50; y = 50;
    for (int i = 0; i < 10; i++, y += 50) {
        QLabel* label = new QLabel(tr(""), this);
        label->setFont(QFont("Times", 12, QFont::Bold));
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
        effect->setColor(QColor("Yellow"));
        effect->setXOffset(1.5);
        effect->setYOffset(1.5);
        label->setGraphicsEffect(effect);
        label->setText(static_cast<QString>(ch++));
        label->setGeometry(QRect(QPoint(x, y), QSize(50, 50)));
        label->setAlignment(Qt::AlignCenter);
        if (!flag) {
            label->show();
        }
    }
    num = 1;
    x = copyX; y = 10;

    for (int i = 0; i < 10; i++, x += 50) {
        QLabel* label = new QLabel(tr(""), this);
        label->setFont(QFont("Times", 12, QFont::Bold));
        label->setNum(num++);
        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
        effect->setColor(QColor("Yellow"));
        effect->setXOffset(1.5);
        effect->setYOffset(1.5);
        label->setGraphicsEffect(effect);
        label->setGeometry(QRect(QPoint(x, y), QSize(50, 50)));
        label->setAlignment(Qt::AlignCenter);
        if (!flag) {
            label->show();
        }
    }
}
void MainWindow::on_actionDelete_triggered() {
    if (!start) {
        int counter = 0;
        if (ifSelected) {
            QIcon icon;
            for (int i = 0; i < listWithShips.size(); i++) {
                if (listWithShips[i]->graphicsEffect() != nullptr) {
                    listWithShips[i]->setIcon(icon);
                    listWithShips[i]->setGraphicsEffect(nullptr);
                    listWithShips.removeAt(i);
                    i--;
                    counter++;
                }
                ifSelected = false;
            }
        }
        queue.push_front(counter);
        num -= counter;
    }
}
void MainWindow::on_actionDefault_triggered() {
    if (!start) {
        if (listWithShips.size() != 0) {
            QIcon icon;
            for (auto but : listWithShips) {
                but->setIcon(icon);
            }
            listWithShips.clear();
            queue.clear();
            int array[10] = { 4,3,3,2,2,2,1,1,1,1 };
            for (int i = 0; i < 10; i++) {
                queue.append(array[i]);
            }
            int index = 0;
            num = array[index];
        }
        int i = 0;
        while (queue.size() != 0) {
            i = rand() % list.size();
            if (!listWithShips.contains(list[i])) {
                if (queue.size() > 0) {
                    if (rand() % 2 && queue.head() > 1 && PlaceShip(list[i], listWithShips, list, queue)) {
                        PlaceShip(list[i], listWithShips, list, queue);
                        Rotate(list, listWithShips);
                    }
                    else {
                        PlaceShip(list[i], listWithShips, list, queue);
                    }
                }
            }
        }
    }

}
void MainWindow::PlaceEmptyCells(QList<QPushButton*> list, QList<QPushButton*> listHelpForRemoving, bool setMove) {
    QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\img\\nothing.jpg");
    QIcon buttonIcon(pixmap);
    for (int i = 0; i < listHelpForRemoving.size(); i++) {
        if (list.indexOf(listHelpForRemoving[i]) > 9 && list.indexOf(listHelpForRemoving[i]) <= 90 && list.indexOf(listHelpForRemoving[i]) % 10 != 0 && list.indexOf(listHelpForRemoving[i]) % 10 != 9) {
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIconSize(QSize(50, 50));
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIconSize(QSize(50, 50));
            list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIconSize(QSize(50, 50));
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIconSize(QSize(50, 50));
            if (setMove) {
                field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 + 1);
                field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 - 1);
                field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 + 1);
                field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 - 1);
            }
            else {
                visited[list.indexOf(listHelpForRemoving[i]) + 10 + 1] = true;
                visited[list.indexOf(listHelpForRemoving[i]) + 10 - 1] = true;
                visited[list.indexOf(listHelpForRemoving[i]) - 10 + 1] = true;
                visited[list.indexOf(listHelpForRemoving[i]) - 10 - 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 1 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 1])) {
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 1);
                else visited[list.indexOf(listHelpForRemoving[i]) + 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 10 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 10])) {
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10);
                else visited[list.indexOf(listHelpForRemoving[i]) + 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) - 10 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10] = true;
            }
        }
        else if (list.indexOf(listHelpForRemoving[i]) == 0) {
            if (list.indexOf(listHelpForRemoving[i]) + 10 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 10])) {
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10);
                else visited[list.indexOf(listHelpForRemoving[i]) + 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 1 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 1])) {
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 1);
                else visited[list.indexOf(listHelpForRemoving[i]) + 1] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIconSize(QSize(50, 50));
            if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 + 1);
            else visited[list.indexOf(listHelpForRemoving[i]) + 10 + 1] = true;
        }
        else if (list.indexOf(listHelpForRemoving[i]) == 9) {
            if (list.indexOf(listHelpForRemoving[i]) + 10 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 10])) {
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10);
                else visited[list.indexOf(listHelpForRemoving[i]) + 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 1] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIconSize(QSize(50, 50));
            if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 - 1);
            else visited[list.indexOf(listHelpForRemoving[i]) + 10 - 1] = true;
        }
        else if (list.indexOf(listHelpForRemoving[i]) == 90) {
            if (list.indexOf(listHelpForRemoving[i]) - 10 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 1 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 1])) {
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 1);
                else visited[list.indexOf(listHelpForRemoving[i]) + 1] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIconSize(QSize(50, 50));
            if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 + 1);
            else visited[list.indexOf(listHelpForRemoving[i]) - 10 + 1] = true;
        }
        else if (list.indexOf(listHelpForRemoving[i]) == 99) {
            if (list.indexOf(listHelpForRemoving[i]) - 10 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 1] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIconSize(QSize(50, 50));
            if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 - 1);
            else visited[list.indexOf(listHelpForRemoving[i]) - 10 - 1] = true;
        }
        else if (list.indexOf(listHelpForRemoving[i]) < 9 && list.indexOf(listHelpForRemoving[i]) % 10 != 0 && list.indexOf(listHelpForRemoving[i]) % 10 != 9) {
            if (list.indexOf(listHelpForRemoving[i]) - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 1 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 1])) {
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 1);
                else visited[list.indexOf(listHelpForRemoving[i]) + 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 10 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 10])) {
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10);
                else visited[list.indexOf(listHelpForRemoving[i]) + 10] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIconSize(QSize(50, 50));
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIconSize(QSize(50, 50));
            if (setMove) {
                field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 + 1);
                field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 - 1);
            }
            else {
                visited[list.indexOf(listHelpForRemoving[i]) + 10 + 1] = true;
                visited[list.indexOf(listHelpForRemoving[i]) + 10 - 1] = true;
            }
        }
        else if (list.indexOf(listHelpForRemoving[i]) > 90 && list.indexOf(listHelpForRemoving[i]) % 10 != 0 && list.indexOf(listHelpForRemoving[i]) % 10 != 9) {
            if (list.indexOf(listHelpForRemoving[i]) - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 1 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 1])) {
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 1);
                else visited[list.indexOf(listHelpForRemoving[i]) + 1] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) - 10 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIconSize(QSize(50, 50));
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIconSize(QSize(50, 50));
            if (setMove) {
                field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 - 1);
                field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 + 1);
            }
            else {
                visited[list.indexOf(listHelpForRemoving[i]) - 10 - 1] = true;
                visited[list.indexOf(listHelpForRemoving[i]) - 10 + 1] = true;
            }

        }
        else if (list.indexOf(listHelpForRemoving[i]) % 10 == 0 && list.indexOf(listHelpForRemoving[i]) > 9 && list.indexOf(listHelpForRemoving[i]) <= 90) {
            if (list.indexOf(listHelpForRemoving[i]) - 10 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 10 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 10])) {
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10);
                else visited[list.indexOf(listHelpForRemoving[i]) + 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 1 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 1])) {
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 1);
                else visited[list.indexOf(listHelpForRemoving[i]) + 1] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 + 1]->setIconSize(QSize(50, 50));
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) - 10 + 1]->setIconSize(QSize(50, 50));
            if (setMove) {
                field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 + 1);
                field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 + 1);
            }
            else {
                visited[list.indexOf(listHelpForRemoving[i]) + 10 + 1] = true;
                visited[list.indexOf(listHelpForRemoving[i]) - 10 + 1] = true;
            }
        }
        else if (list.indexOf(listHelpForRemoving[i]) % 10 == 9 && list.indexOf(listHelpForRemoving[i]) > 9 && list.indexOf(listHelpForRemoving[i]) <= 90) {
            if (list.indexOf(listHelpForRemoving[i]) - 10 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) + 10 < list.size() && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) + 10])) {
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) + 10]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10);
                else visited[list.indexOf(listHelpForRemoving[i]) + 10] = true;
            }
            if (list.indexOf(listHelpForRemoving[i]) - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 1] = true;
            }
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIcon(buttonIcon);
            list[list.indexOf(listHelpForRemoving[i]) + 10 - 1]->setIconSize(QSize(50, 50));
            if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) + 10 - 1);
            else visited[list.indexOf(listHelpForRemoving[i]) + 10 - 1] = true;
            if (list.indexOf(listHelpForRemoving[i]) - 10 - 1 >= 0 && !listHelpForRemoving.contains(list[list.indexOf(listHelpForRemoving[i]) - 10 - 1])) {
                list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIcon(buttonIcon);
                list[list.indexOf(listHelpForRemoving[i]) - 10 - 1]->setIconSize(QSize(50, 50));
                if (setMove)field.removeOne(list.indexOf(listHelpForRemoving[i]) - 10 - 1);
                else visited[list.indexOf(listHelpForRemoving[i]) - 10 - 1] = true;
            }
        }
    }
}
