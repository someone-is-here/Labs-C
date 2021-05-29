//#include "map.h"
//#include <QPushButton>
//#include <QAbstractButton>
//#include <QSize>
//#include <QDebug>
//#include <QString>
//#include <QLabel>
//#include <QGraphicsDropShadowEffect>

//Map::Map() {
//    this->resize(1600, 1000);

//    QBrush* brush = new QBrush();
//    QPalette* palette = new QPalette();
//    brush->setTextureImage(QImage("D:\\QT\\Projects\\SeaBattle\\sea1.jpg"));
//    palette->setBrush(QPalette::Background, *brush);
//    this->setPalette(*palette);

//    QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\icon.jpg");
//    QIcon buttonIcon(pixmap);
//    this->setWindowIcon(buttonIcon);

//    SetField();
//    SetField(700, 50, false);
//    num = array[index];
//}

//void Map::ButtonClicked() {
//    QObject* sender = this->sender();
//    QPushButton* button = qobject_cast<QPushButton*>(sender);
//    PlaceShip(button);
//}
//void Map::ChangeButtonClicked(){


//}

//bool Map::CheckShip(QPushButton* button) {
//    bool checked = true;
//    if (list.indexOf(button) > 9 && list.indexOf(button) <= 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
//        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//                qDebug() << "If Checked";
//                checked = false;
//         }
//        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10])|| listWithShips.contains(list[list.indexOf(button) + 1])) {
//            qDebug() << "If Checked";
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) == 0) {
//        qDebug() << "Checked 0()";
//        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) == 9) {
//        qDebug() << "Checked 9()";
//        if (listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10])) {
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) == 90) {
//        qDebug() << "Checked 90()";
//        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) < 9 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
//        qDebug() << "Up checked";
//        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) ||listWithShips.contains(list[list.indexOf(button) + 10])) {
//            checked = false;
//        }
//        if (listWithShips.contains(list[list.indexOf(button) + 1])) {
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) > 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
//        qDebug() << "Down Checked";
//        if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 - 1])|| listWithShips.contains(list[list.indexOf(button) - 10])) {
//            checked = false;
//        }
//        if (listWithShips.contains(list[list.indexOf(button) + 1])) {
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) % 10 == 0 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
//        qDebug() << "Checked not Left()";
//        if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//            checked = false;
//        }
//        if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
//            checked = false;
//        }
//    }
//    else if (list.indexOf(button) % 10 == 9 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
//         qDebug() << "Checked not Right()";
//        if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1])|| listWithShips.contains(list[list.indexOf(button) - 1])) {
//            checked = false;
//        }
//        if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
//            checked = false;
//        }
//    }
//    return checked;
//}
////        if (listWithShips.contains(button)) {
////            button->setIcon(QIcon());
////            button->setGraphicsEffect(new QGraphicsDropShadowEffect());
////            listWithShips.removeAt(listWithShips.indexOf(button));
////            if (listWithShips.size() >= 2) {
////                for (int i = 0; i < listWithShips.size(); i++) {
////                    if (vertical == 0) {
////                        if (!listWithShips.contains(list[list.indexOf(listWithShips[i]) + 1]) && !listWithShips.contains(list[list.indexOf(listWithShips[i]) - 1])) {
////                            QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
////                            effect->setColor("Red");
////                            effect->setOffset(0);
////                            effect->setBlurRadius(20);
////                            list[list.indexOf(listWithShips[i])]->setGraphicsEffect(effect);
////                        }
////                    }
////                    if (vertical == 1) {
////                        if (!listWithShips.contains(list[list.indexOf(listWithShips[i]) + 10]) && !listWithShips.contains(list[list.indexOf(listWithShips[i]) - 10])) {
////                            QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
////                            effect->setColor("Red");
////                            effect->setOffset(0);
////                            effect->setBlurRadius(20);
////                            list[list.indexOf(listWithShips[i])]->setGraphicsEffect(effect);
////                        }

////                    }
////                }
////            }
////            else if (array[index]-(num-listWithShips.size()) == 1) {
////                vertical = -1;
////            }
////            return;
////        }
////        if (array[index] - (num - listWithShips.size()) >= 1) {
////            if (vertical == -1 && list.indexOf(listWithShips[listWithShips.size() - 1]) >= 0) {
////                if (list.indexOf(button) % 10 == list.indexOf(listWithShips[listWithShips.size() - 1]) % 10) {
////                    vertical = 1;
////                    qDebug() << "set vertical";
////                }
////                else if (list.indexOf(button) == list.indexOf(listWithShips[listWithShips.size() - 1]) - 1 || list.indexOf(button) == list.indexOf(listWithShips[listWithShips.size() - 1]) + 1) {
////                    vertical = 0;
////                    qDebug() << "set horizontal";
////                }
////                else {
////                    return;
////                }
////            }
////            if (array[index]-(num-listWithShips.size()) >= 1) {
////                if (!CheckRemoveShip(button, listWithShips[listWithShips.size() - 1])) {
////                    return;
////                }

////            }
////        }
//void Map::ShadowShip(){


//}

//void Map::PlaceShip(QPushButton* button) {
//    QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\ship.png");
//    QIcon buttonIcon(pixmap);
//    bool checked = true;

//    if(index == 10){
//        return;
//    }

//    if (listWithShips.size() < num) {
//        //удалить можно по краям и одиночный кораблик
//            //------------------------wrong functioin not using i
//                if (list.indexOf(button) > 9 && list.indexOf(button) <= 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
//                    if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 - 1])|| listWithShips.contains(list[list.indexOf(button) - 10])) {
//                            qDebug() << "If Checked";
//                            checked = false;
//                        }
//                    if((listWithShips.contains(list[list.indexOf(button) + 1])) || listWithShips.contains(list[list.indexOf(button) - 1])){
//                        qDebug() << "If Checked";
//                        checked = false;
//                    }
//                    if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10])) {

//                        qDebug() << "If Checked";
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) == 0) {
//                    qDebug() << "Checked 0()";
//                    if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) == 9) {
//                    qDebug() << "Checked 9()";
//                    if (listWithShips.contains(list[list.indexOf(button) + 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) == 90) {
//                    qDebug() << "Checked 90()";
//                    if (listWithShips.contains(list[list.indexOf(button) - 10 + 1])|| listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) == 99) {
//                    qDebug() << "Checked 99()";
//                    if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) - 10]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) < 9 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
//                    qDebug() << "Up checked";
//                    if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1]) ||listWithShips.contains(list[list.indexOf(button) + 10])) {
//                        checked = false;
//                    }
//                    if (listWithShips.contains(list[list.indexOf(button) + 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) > 90 && list.indexOf(button) % 10 != 0 && list.indexOf(button) % 10 != 9) {
//                    qDebug() << "Down Checked";
//                    if (listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 - 1])|| listWithShips.contains(list[list.indexOf(button) - 10])) {
//                        checked = false;
//                    }
//                    if (listWithShips.contains(list[list.indexOf(button) + 1]) || listWithShips.contains(list[list.indexOf(button) - 1])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) % 10 == 0 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
//                    qDebug() << "Checked not Left()";
//                    if (listWithShips.contains(list[list.indexOf(button) + 10 + 1]) || listWithShips.contains(list[list.indexOf(button) - 10 + 1]) || listWithShips.contains(list[list.indexOf(button) + 1])) {
//                        checked = false;
//                    }
//                    if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
//                        checked = false;
//                    }
//                }
//                else if (list.indexOf(button) % 10 == 9 && list.indexOf(button) > 9 && list.indexOf(button) <= 90) {
//                     qDebug() << "Checked not Right()";
//                    if (listWithShips.contains(list[list.indexOf(button) - 10 - 1]) || listWithShips.contains(list[list.indexOf(button) + 10 - 1])|| listWithShips.contains(list[list.indexOf(button) - 1])) {
//                        checked = false;
//                    }
//                    if (listWithShips.contains(list[list.indexOf(button) + 10]) || listWithShips.contains(list[list.indexOf(button) - 10])) {
//                        checked = false;
//                    }
//                }
//        if (checked) {
//            int currIndex = list.indexOf(button) / 10;
//            for(int i = 0; i < array[index]; i++){
//                if(listWithShips.contains(list[list.indexOf(button)+i])){
//                    return;
//                }
//                if((list.indexOf(button) + i) / 10 != currIndex){
//                    return;
//                }
//                if(!CheckShip(list[list.indexOf(button)+i])){
//                    return;
//                }
//            }
//            for(int i = 0; i < array[index]; i++){
//                listWithShips.append(list[list.indexOf(button) + i]);
//                list[list.indexOf(button) + i]->setIcon(buttonIcon);
//                list[list.indexOf(button) + i]->setIconSize(QSize(50, 50));
//            }
//            num += array[++index];
//        }
//}
//    else {
//        qDebug() << listWithShips;
//    }
//}
//void Map::SetField(int x, int y, bool flag) {
//    int num = 0;
//    int copyX = x;
//    for (int i = 0; i < fieldSize * fieldSize; i++) {
//        QPushButton* button = new QPushButton(tr(""), this);
//        button->setGeometry(QRect(QPoint(x, y), QSize(50, 50)));
//        list.append(button);
//        if (i != 0 && (i + 1) % 10 == 0) {
//            y += 50;
//            x = copyX;
//        }
//        else {
//            x += 50;
//        }
//        if(flag){
//            connect(button, SIGNAL(clicked()), this, SLOT(ButtonClicked()));
//        }
//    }
//    if(copyX == 50){
//        QPushButton* button = new QPushButton(tr(""), this);
//        button->setGeometry(QRect(QPoint(copyX + 30, y + 80), QSize(80, 80)));

//        QPixmap pixmap("D:\\QT\\Projects\\SeaBattle\\change.png");
//        QIcon buttonIcon(pixmap);
//        button->setIcon(buttonIcon);
//        button->setIconSize(QSize(80, 80));
//        connect(button, SIGNAL(clicked()), this, SLOT(ChangeButtonClicked()));
//    }
//    char ch = 'A';
//    x = copyX - 50; y = 50;
//    for (int i = 0; i < 10; i++, y += 50) {
//        QLabel* label = new QLabel(tr(""), this);
//        label->setFont(QFont("Times", 12, QFont::Bold));
//        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
//        effect->setColor(QColor("Yellow"));
//        effect->setXOffset(1.5);
//        effect->setYOffset(1.5);
//        label->setGraphicsEffect(effect);
//        label->setText(static_cast<QString>(ch++));
//        label->setGeometry(QRect(QPoint(x, y), QSize(50, 50)));
//        label->setAlignment(Qt::AlignCenter);
//    }
//    num = 1;
//    x = copyX; y = 0;
//    for (int i = 0; i < 10; i++, x += 50) {
//        QLabel* label = new QLabel(tr(""), this);
//        label->setFont(QFont("Times", 12, QFont::Bold));
//        label->setNum(num++);
//        QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
//        effect->setColor(QColor("Yellow"));
//        effect->setXOffset(1.5);
//        effect->setYOffset(1.5);
//        label->setGraphicsEffect(effect);
//        label->setGeometry(QRect(QPoint(x, y), QSize(50, 50)));
//        label->setAlignment(Qt::AlignCenter);
//    }
//}

