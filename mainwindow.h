#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QScreen>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//#if QT_VERSION >= QT_VERSION_CHECK(5, 8, 0)
//  Q_NAMESPACE
//#endif
enum unitTypes {unitPixels, unitMM, unitInches};


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    unitTypes mainUnit = unitInches;
    const double inchesinmm = 0.0393700787402;
    QScreen *screen;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *centerBolt1;
    QGraphicsEllipseItem *outsideBolt1;
    //QGraphicsItemGroup *listBolt;// = scene->createItemGroup(scene->selecteditems());
    QList<QGraphicsEllipseItem*> listBolts;
    QPen defaultPen;
    QBrush defaultBrush;

private slots:
    double inch_to_mm(double inches);
    double inch_to_px(double inches, double dpi);
    double mm_to_in(double mm);
    double mm_to_px(double mm, double dpi);
    double px_to_in(double pixels, double dpi);
    double px_to_mm(double pixels, double dpi);
    double any_to_px(unitTypes utype, double anyVal, double dpi);
    //
    void menu_actioninches();
    void menu_actionmm();
    void menu_actionpixels();
    void setGlobalUnits(unitTypes unittype);
    //
    void btnclicked1();
    void print_bolts();
    void export_topdf();
    //
    void generate_centerholebolt();
    void generate_outsideholebolt();
    void generate_circlebolts(double number, double holedia, double circledia);

};

#endif // MAINWINDOW_H
