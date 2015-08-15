#include <math.h>
#include <Arduino.h>
#include <GPS_Nav.h>

/* Earth Radius in Kilometers.*/
static const double EARTH_RADIUS = 6372.797560856;
/* Earth Diameter in Kilometers, used for max int. (I know it could probably be much smaller, but meh)*/
static const int MAX_DISTANCE = 12742;


//=============================================================================
// misc functions
//=============================================================================

closest_point_result getClosestPointSpherical(gps_location start_point, gps_location locations[], int num_locations)
{
  gps_location test_point;
  gps_location closest_point;
  float closest_distance = MAX_DISTANCE;
  float distance;
  closest_point_result result;

  // This is slow and probably can be done nicer, but I'll only worry about that if I have to
  // starting at 1 because we already got the first one up top
  int i;
  for (i = 0; i < num_locations; i++)
  {
    test_point = locations[i];
    distance = getDistanceSpherical(start_point, test_point);
    if (distance<closest_distance)
    {
      closest_point = test_point;
      closest_distance = distance;
    }
  };

  result.distance = closest_distance;
  result.position = closest_point;

  return result;
}

double convertDegMinToDecDeg (float degMin) {
  double min = 0.0;
  double decDeg = 0.0;
 
  //get the minutes, fmod() requires double
  min = fmod((double)degMin, 100.0);
 
  //rebuild coordinates in decimal degrees
  degMin = (int) ( degMin / 100 );
  decDeg = degMin + ( min / 60 );
 
  return decDeg;
}

//=============================================================================
// Bearing
//=============================================================================

float getBearingSpherical( gps_location current_position, gps_location destination )
{
  double x;
  double y;

  float bearing;

  double delta_longitude = radians(destination.longitude) - radians(current_position.longitude);

  y = cos(radians(destination.latitude)) * sin(delta_longitude);
  x = cos(radians(current_position.latitude)) * sin(radians(destination.latitude)) -
      sin(radians(current_position.latitude)) * cos(radians(destination.latitude)) * cos(delta_longitude);

  bearing = atan2(y,x);

  return bearing;
}

float getBearingPlanar( gps_location current_position, gps_location destination )
{
  float bearing;
  float slope;
  
  slope = (destination.longitude - current_position.longitude) / (destination.latitude - current_position.latitude);
  bearing = atan(slope);

  return bearing;
}


//=============================================================================
// Distance
//=============================================================================


float getDistanceSpherical(gps_location point_0, gps_location point_1)
{
  double delta_lon = radians(point_1.longitude - point_0.longitude);
  double delta_lat = radians(point_1.latitude - point_0.latitude);

  double a =  pow(sin(delta_lat * 0.5),2)+ cos(radians(point_0.latitude)) * cos(radians(point_1.latitude)) * pow(sin(delta_lon * 0.5),2);
  double c = 2.0 * atan2(sqrt(a), sqrt(1-a));
  return EARTH_RADIUS * c;

}