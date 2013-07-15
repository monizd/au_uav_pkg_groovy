#ifndef _COLLISION_AVOIDANCE_H_
#define _COLLISION_AVOIDANCE_H_

#include <vector>

#include "au_uav_ros/Telemetry.h"

#include "au_uav_ros/standardFuncs.h"
#include "au_uav_ros/planeObject.h"
#include "au_uav_ros/simPlaneObject.h"
#include "au_uav_ros/ripna.h"
#include "au_uav_ros/ipn.h"

namespace au_uav_ros {
	class CollisionAvoidance {
	private:
		
	public:
		virtual void avoid(int id, 
				std::map<int, PlaneObject> planes, 
				std::map<int, SimPlaneObject> simPlanes,
				std::vector<waypoint> &wps);
		void distrubuted_avoid(int id, 
				std::map<int, PlaneObject> planes, 
				std::map<int, SimPlaneObject> simPlanes,
				waypoint &wps);
		void astar_planPath(std::map<int, PlaneObject> planes,
						std::map<int, SimPlaneObject> simPlanes,
						std::map<int, std::vector<waypoint> > &allPlanesPath);
	};
}
#endif
