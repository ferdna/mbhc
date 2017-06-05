#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    screen = qApp->primaryScreen();
    qDebug() << "dots per inch: " << (double)screen->physicalDotsPerInch();

    connect(ui->actionE_xit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->actionPrint, SIGNAL(triggered(bool)), this, SLOT(print_bolts()));

    connect(ui->actionpixels, SIGNAL(triggered(bool)), this, SLOT(menu_actionpixels()));
    connect(ui->actionmm, SIGNAL(triggered(bool)), this, SLOT(menu_actionmm()));
    connect(ui->actioninches, SIGNAL(triggered(bool)), this, SLOT(menu_actioninches()));

    connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(btnclicked1()));

    defaultPen.setColor(Qt::black);
    defaultBrush.setColor(Qt::transparent);

    scene = new QGraphicsScene(this);
    //scene->setBackgroundBrush(Qt::green);
    scene->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setBackgroundBrush(Qt::black);

    /*inch_to_mm(1);
    inch_to_px(1, 300);
    mm_to_in(1);
    mm_to_px(1, 300);
    px_to_in(1, 300);
    px_to_mm(1, 300);*/

    generate_centerholebolt();
    generate_outsideholebolt();
    generate_circlebolts(ui->sb_number->value(), ui->sb_holedia->value(), ui->sb_circledia->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::menu_actionpixels()
{
    mainUnit = unitPixels;
    ui->ch_holecdia->setSuffix("px");
    ui->ch_holecx->setSuffix("px");
    ui->ch_holecy->setSuffix("px");
    ui->oh_holecdia->setSuffix("px");
    ui->oh_holecx->setSuffix("px");
    ui->oh_holecy->setSuffix("px");
    ui->sb_holedia->setSuffix("px");
    ui->sb_circledia->setSuffix("px");
}

void MainWindow::menu_actionmm()
{
    mainUnit = unitMM;
    ui->ch_holecdia->setSuffix("mm");
    ui->ch_holecx->setSuffix("mm");
    ui->ch_holecy->setSuffix("mm");
    ui->oh_holecdia->setSuffix("mm");
    ui->oh_holecx->setSuffix("mm");
    ui->oh_holecy->setSuffix("mm");
    ui->sb_holedia->setSuffix("mm");
    ui->sb_circledia->setSuffix("mm");
}

void MainWindow::menu_actioninches()
{
    mainUnit = unitInches;
    ui->ch_holecdia->setSuffix("in");
    ui->ch_holecx->setSuffix("in");
    ui->ch_holecy->setSuffix("in");
    ui->oh_holecdia->setSuffix("in");
    ui->oh_holecx->setSuffix("in");
    ui->oh_holecy->setSuffix("in");
    ui->sb_holedia->setSuffix("in");
    ui->sb_circledia->setSuffix("in");
}
void MainWindow::setGlobalUnits(unitTypes unittype)
{
    mainUnit = unittype;
}

void MainWindow::btnclicked1()
{
    qDebug() << "button press.";
    qDebug() << "scene size: " << scene->width() << "x" <<scene->height();

    foreach (QGraphicsItem *item, scene->items())
        delete item;

    generate_centerholebolt();
    generate_outsideholebolt();
    generate_circlebolts(ui->sb_number->value(), ui->sb_holedia->value(), ui->sb_circledia->value());
}

void MainWindow::generate_centerholebolt()
{
    if (!ui->ch_checkBox->isChecked())
        return;

    centerBolt1 = new QGraphicsEllipseItem();
    centerBolt1->setPen(defaultPen);
    centerBolt1->setBrush(defaultBrush);
    centerBolt1->setRect(0,0,any_to_px(mainUnit,ui->ch_holecdia->value(), 0),any_to_px(mainUnit,ui->ch_holecdia->value(), 0));
    centerBolt1->setPos(ui->graphicsView->rect().center().x() + any_to_px(mainUnit,ui->ch_holecx->value(), 0) - (centerBolt1->rect().width()/2) , ui->graphicsView->rect().center().y() + any_to_px(mainUnit,ui->ch_holecy->value(), 0) - (centerBolt1->rect().height()/2));
    scene->addItem(centerBolt1);

    qDebug() << "center ch_holecx pos: " << any_to_px(mainUnit,ui->ch_holecx->value(), 0);
    qDebug() << "center ch_holecy pos: " << any_to_px(mainUnit,ui->ch_holecy->value(), 0);
    qDebug() << "center bolt pos: " << centerBolt1->pos();
}

void MainWindow::generate_outsideholebolt()
{
    if (!ui->oh_checkBox->isChecked())
        return;

    outsideBolt1 = new QGraphicsEllipseItem();
    outsideBolt1->setPen(defaultPen);
    outsideBolt1->setBrush(defaultBrush);
    outsideBolt1->setRect(0,0,any_to_px(mainUnit,ui->oh_holecdia->value(), 0),any_to_px(mainUnit,ui->oh_holecdia->value(), 0));
    outsideBolt1->setPos(ui->graphicsView->rect().center().x() + any_to_px(mainUnit,ui->oh_holecx->value(), 0) - (outsideBolt1->rect().width()/2) , ui->graphicsView->rect().center().y() + any_to_px(mainUnit,ui->oh_holecy->value(), 0) - (outsideBolt1->rect().height()/2));
    scene->addItem(outsideBolt1);

    qDebug() << "center oh_holecx pos: " << any_to_px(mainUnit,ui->oh_holecx->value(), 0);
    qDebug() << "center oh_holecy pos: " << any_to_px(mainUnit,ui->oh_holecy->value(), 0);
    qDebug() << "outside bolt pos: " << outsideBolt1->pos();
}

void MainWindow::generate_circlebolts(double number, double holedia, double circledia)
{
    if (!ui->checkBox_2->isChecked())
        return;

    qDebug() << "haw many: " << number;

    const double radVal = 360 / number;
    qDebug() << "360/number: " << radVal;

    //scene->createItemGroup()
    //listBolt = scene->createItemGroup(scene->selecteditems());

    for(int i=0; i <= number-1; i++)
    {
        qDebug() << ">> starting circle.";
        QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(); //0,any_to_px(mainUnit,ui->sb_circledia->value(), 0),any_to_px(mainUnit,ui->sb_holedia->value(), 0),any_to_px(mainUnit,ui->sb_holedia->value(), 0)
        circle->setPen(defaultPen);
        circle->setBrush(defaultBrush);
        //scene->
        circle->setRect(scene->sceneRect().center().x(),
                        any_to_px(mainUnit,ui->sb_circledia->value(), 0),
                        any_to_px(mainUnit,ui->sb_holedia->value(), 0),
                        any_to_px(mainUnit,ui->sb_holedia->value(), 0));
        //qDebug() << "center of masterbolt: " << centerBolt1->rect().center();

        //scene->sceneRect().center()
        //ui->graphicsView->rect().center()
        qDebug() << "center of graphicsView: " << scene->sceneRect().center();
        circle->setTransformOriginPoint(scene->sceneRect().center());
        circle->setRotation(radVal * i);

        circle->setFlag(QGraphicsItem::ItemIsMovable, false);
        listBolts.append(circle);
        scene->addItem(circle);
    }

    qDebug() << "circles in list: "<< listBolts.count();
}

void MainWindow::export_topdf()
{
    QMessageBox::warning(this, tr("MBHC - Machinist Bolt Hole Calculator."),tr("this function has not been implemented yet."),QMessageBox::Ok);
    return;
}

void MainWindow::print_bolts()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPrinterName("");
    QPrintDialog dialog (&printer, this);
    if (!dialog.exec())
        return;

    QPainter painter(&printer);
    scene->render(&painter);
}

double MainWindow::inch_to_mm(double inches)
{
    if (inches <= 0)
        return 0;

    double inchesval = inches / inchesinmm;
    qDebug() << "inches(" << inches << ") to mm = " << inchesval << "mm";
    return inchesval;
}

double MainWindow::inch_to_px(double inches, double dpi)
{
    if (inches <= 0)
        return 0;

    if (dpi <= 0)
        dpi = (double)screen->physicalDotsPerInch();

    double pixelsval = dpi * inches;
    qDebug() << "inches(" << inches << "@" << dpi << "dpi) to pixels = " << pixelsval << "px";
    return pixelsval;
}

double MainWindow::mm_to_in(double mm)
{
    if (mm <= 0)
        return 0;

    double mmval = mm * inchesinmm;
    qDebug() << "mm(" << mm << ") to inches = " << mmval << "in";
    return mmval;
}

double MainWindow::mm_to_px(double mm, double dpi)
{
    if (mm <= 0)
        return 0;

    if (dpi <= 0)
        dpi = (double)screen->physicalDotsPerInch();

    double mmval = dpi * inchesinmm;
    qDebug() << "mm(" << mm << "@" << dpi << "dpi) to pixels = " << mmval << "px";
    return mmval;
}

double MainWindow::any_to_px(unitTypes utype, double anyVal, double dpi)
{
    if (utype == unitPixels || anyVal <= 0)
        return 0;

    if (dpi <= 0)
        dpi = (double)screen->physicalDotsPerInch();

    double pixelsVal;
    if (utype == unitMM)
    {
        pixelsVal = dpi * inchesinmm;
        qDebug() << "mm(" << anyVal << "@" << dpi << "dpi) to pixels = " << pixelsVal << "px";
    }

    if (utype == unitInches)
    {
        pixelsVal = dpi * anyVal;
        qDebug() << "inches(" << anyVal << "@" << dpi << "dpi) to pixels = " << pixelsVal << "px";
    }

    return pixelsVal;
}

double MainWindow::px_to_in(double pixels, double dpi)
{
    if (pixels <= 0)
        return 0;

    if (dpi <= 0)
        dpi = (double)screen->physicalDotsPerInch();

    double inchesval = pixels / dpi;
    qDebug() << "pixels(" << pixels << "@" << dpi << "dpi) to inches = " << inchesval << "in";
    return inchesval;
}

double MainWindow::px_to_mm(double pixels, double dpi)
{
    if (pixels <= 0)
        return 0;

    if (dpi <= 0)
        dpi = (double)screen->physicalDotsPerInch();

    double mmval = pixels / (dpi * inchesinmm) ;
    qDebug() << "pixels(" << pixels << "@" << dpi << "dpi) to mm = " << mmval << "mm";
    return mmval;
}
