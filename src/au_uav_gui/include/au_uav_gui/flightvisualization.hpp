/***************************************************
 Coder: Jacob Dalton Conaway - jdc0019@auburn.edu
 Reviewer/Tester: Kayla Casteel - klc0025@auburn.edu
 Senior Design - Spring 2013
 Sources are in-line
 ***************************************************/

#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTimer>
#include <QMap>
#include <QMenu>
#include <QListWidget>

struct PlaneData {
    double latitude;
    double longitude;
    bool planeActive;
};

namespace Ui
{
class Form;
}

class FlightVisualization: public QWidget
{
    Q_OBJECT

public:
    explicit FlightVisualization(QWidget *parent = 0);
    ~FlightVisualization();
    void closePopupWindows();

public slots:
    void updateCoordinates(double latitude, double longitude, double bearing, int planeID);
    void updateWayPoint(double wp_Latitude, double wp_Longitude, int planeID);
    void updatePlaneInfo(int planeID, double currentLatitude,
                         double currentLongitude, double currentAltitude, double groundSpeed,
                         double targetBearing, int currentWaypointIndex,
                         double distanceToDestination);

private slots:
    void setMapCenter(double latitude, double longitude);
    void updateMarker(double latitude, double longitude, double bearing,
                      int planeID);
    void updateFlightPath(double latitude, double longitude, int planeID);
    void toggleFlightPath(int state);
    void toggleWayPoints(int state);
    void toggleAutoCenter(int state);
    void toggleAutoFit(int state);
    void setWayPoint(double wp_Latitude, double wp_Longitude, int planeID);
    void adjustMapCenter();
    void loadFinished(bool okay);
    void resetFlightPaths();
    void setCurrentPlane(int comboIndex);
    void showPlaneSelector();
    void togglePlaneVisibility(QListWidgetItem * item);
private:
    Ui::Form *ui;
    PlaneData activePlanes[64];
    QTimer _timer;
    bool firstMessage;
    bool autoFitMap;
    int currentPlane;
    QString directionFromDegrees(float degrees);
    void resetPlaneInfo();

    QMap<int, int> comboIndexToPlaneIDMap;
    QListWidget* popupPlaneSelector;
};

#endif // FORM_H
