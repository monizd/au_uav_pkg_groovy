/***************************************************
 Coder: Jacob Dalton Conaway - jdc0019@auburn.edu
 Reviewer/Tester: Kayla Casteel - klc0025@auburn.edu
 Senior Design - Spring 2013
 Sources are in-line
 TODO: Finish Commenting and Proofread Comments
 ***************************************************/

#include "au_uav_gui/mainwindow.hpp"
#include "ui_mainwindow.h"
#include "au_uav_gui/flightvisualization.hpp"
#include "au_uav_gui/missionplanner.hpp"
#include "au_uav_gui/qnode.hpp"
#include "au_uav_gui/constants.h"
#include <QTabWidget>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(int argc, char ** argv, QWidget * parent) :
    QMainWindow(parent), qnode(argc, argv), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout_au_uav_gui, SIGNAL(triggered()), this,
            SLOT(showAboutDialog()));
    connect(ui->actionLoad_Mission, SIGNAL(triggered()), &qnode,
            SLOT(sendFilePath()));
    connect(&qnode, SIGNAL(filePathSent()), this, SLOT(disableLoadMission()));
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    flightViz = new FlightVisualization(this);
    plannerApp = new MissionPlanner(this);

    plannerApp->setPackagePathAndLoadFavLocs(qnode.getPackagePath());
    setCentralWidget (flightViz);

    QTabWidget * tabWidget = new QTabWidget;
    tabWidget->addTab(flightViz, FLIGHT_VIZ_TAB_NAME);
    tabWidget->addTab(plannerApp, PLANNER_TAB_NAME);
    setCentralWidget(tabWidget);

    if (!qnode.init()) {
        tabWidget->setCurrentIndex(PLANNER_TAB_INDEX);
        //disable fv tab - ROS could be started, but our node is not running so there it will never connect
        tabWidget->setTabEnabled(FLIGHT_VIZ_INDEX, false);
        ui->actionLoad_Mission->setEnabled(false);
    }

    // m_pForm is already a pointer so no need to &
    // Do not put variable names inside just double, int, etc.
    QObject::connect(&qnode, SIGNAL(newCoordinates(double, double, double, int)), flightViz,
                     SLOT(updateCoordinates(double, double, double, int)));
    QObject::connect(&qnode, SIGNAL(updateWayPoint(double, double, int)), flightViz,
                     SLOT(updateWayPoint(double, double, int)));
    QObject::connect(&qnode, SIGNAL(updatePlaneInfo(int, double, double, double, double, double, int, double)),
                     flightViz, SLOT(updatePlaneInfo(int, double, double, double, double, double, int, double)));
}

//after the mission has been loaded, it cannot be loaded again
void MainWindow::disableLoadMission()
{
    ui->actionLoad_Mission->setEnabled(false);
    ui->actionLoad_Mission->setText(MISSION_LOADED_TEXT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO:change to using a slot like above
void MainWindow::closeEvent(QCloseEvent *event)
{
    flightViz->closePopupWindows();
//TODO:should shutdown ROS, but doesn't seem to work correctly
    delete &qnode;
}

void MainWindow::showAboutDialog()
{
    QMessageBox about_box(this);
    about_box.setText(ABOUT_TEXT);
    about_box.setWindowTitle(ABOUT_TITLE);
    about_box.setIconPixmap(QPixmap(MARKER_SOURCE_ICON_PATH));
    about_box.setParent(this);

    about_box.exec();
}
