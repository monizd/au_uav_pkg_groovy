/***************************************************
 Coder: Jacob Dalton Conaway - jdc0019@auburn.edu
 Reviewer/Tester: Kayla Casteel - klc0025@auburn.edu
 Senior Design - Spring 2013
 This file was generated by qt-ROS and modified
 ***************************************************/

/*****************************************************************************
 ** Ifdefs
 *****************************************************************************/

#ifndef AU_UAV_GUI_QNODE_HPP_
#define AU_UAV_GUI_QNODE_HPP_

/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include <ros/ros.h>
#include <QThread>
#include <QStringListModel>
#include "au_uav_gui/Telemetry.h"

/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

//namespace au_uav_gui {
/*****************************************************************************
 ** Class
 *****************************************************************************/

class QNode: public QThread
{
    Q_OBJECT
public:
    QNode(int argc, char** argv);
    virtual ~QNode();
    bool init();
    void run();
    void telemetryCallback(
        const au_uav_gui::Telemetry::ConstPtr& msg);
    QString getPackagePath();

signals:
    void rosShutdown();
    void newCoordinates(double latitude, double longitude, double bearing,
                        int planeID);
    void updateWayPoint(double wp_Latitude, double wp_Longitude, int planeID);
    void updatePlaneInfo(int planeID, double currentLatitude,
                         double currentLongitude, double currentAltitude, double groundSpeed,
                         double targetBearing, int currentWaypointIndex,
                         double distanceToDestination);
    void filePathSent();
public slots:
    void sendFilePath();

private:
    int init_argc;
    char** init_argv;
    ros::Publisher chatter_publisher;
    ros::Publisher shutdown_pub;
    ros::Subscriber telem_sub;
    ros::ServiceClient sendFileNameClient;
};

//}  // namespace au_uav_gui

#endif /* au_uav_gui_QNODE_HPP_ */
