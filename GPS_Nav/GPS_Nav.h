#ifndef GPS_NAV_H
#define GPS_NAV_H

#include <Adafruit_GPS.h>


typedef struct {
  double latitude;
  double longitude;
} gps_location;

typedef struct {
  float distance;
  gps_location position;
} closest_point_result;

typedef struct {
  bool parsed;
  bool fix;
  bool has_fixed;
  int quality;
  gps_location position; 
} gps_results;

double convertDegMinToDecDeg (float degMin);

float getBearingSpherical( gps_location current_position, gps_location destination );
float getBearingPlanar( gps_location current_position, gps_location destination );

//float get_bearing_gps_to_point_spherical(Adafruit_GPS gps, gps_location destination);
//float get_bearing_gps_to_point_planar(Adafruit_GPS gps, gps_location destination);

float getDistanceSpherical(gps_location point_0, gps_location point_1);
float getDistancePlanar(gps_location point_0, gps_location point_1);

closest_point_result getClosestPointSpherical(gps_location start_point, gps_location locations[], int num_locations);
closest_point_result getClosestPointPlanar(gps_location start_point, gps_location locations[], int num_locations);

#endif