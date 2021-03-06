//
// Canadian Hydrological Model - The Canadian Hydrological Model (CHM) is a novel
// modular unstructured mesh based approach for hydrological modelling
// Copyright (C) 2018 Christopher Marsh
//
// This file is part of Canadian Hydrological Model.
//
// Canadian Hydrological Model is free software: you can redistribute it and/or
// modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Canadian Hydrological Model is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Canadian Hydrological Model.  If not, see
// <http://www.gnu.org/licenses/>.
//

#include "coordinates.hpp"

namespace math
{
    namespace gis
    {

        Point_2 point_from_bearing_latlong(Point_3 src, double bearing, double distance)
        {
            // http://stackoverflow.com/questions/1125144/how-do-i-find-the-lat-long-that-is-x-km-north-of-a-given-lat-long
            double Latitude = src.y();
            double Longitude = src.x();
            double PI = M_PI;
            double DegreesToRadians = PI / 180.0;
            double RadiansToDegrees = 180.0/PI;

            double EarthRadius = 6378137.0;
            double latA = Latitude * DegreesToRadians;
            double lonA = Longitude * DegreesToRadians;
            double angularDistance = distance / EarthRadius;
            double trueCourse = bearing * DegreesToRadians;

            double lat = asin(
                    sin(latA) * cos(angularDistance) +
                    cos(latA) * sin(angularDistance) * cos(trueCourse));

            double dlon = atan2(
                    sin(trueCourse) * sin(angularDistance) * cos(latA),
                    cos(angularDistance) - sin(latA) * sin(lat));

            double lon = ( fmod( lonA + dlon + PI , PI*2) ) - PI;

            return Point_2(lat * RadiansToDegrees,lon * RadiansToDegrees);

        }

        Point_2 point_from_bearing_UTM(Point_3 src, double bearing, double distance)
        {

            double DegreesToRadians = M_PI / 180.0;

            bearing = bearing * DegreesToRadians;

            double dist_x = distance * sin(bearing);
            double dist_y = distance * cos(bearing);

            return Point_2(src.x() + dist_x, src.y() + dist_y);
        }

        double distance_latlong(Point_3 pt1, Point_3 pt2)
        {
            double PI = M_PI;
            double DegreesToRadians = PI / 180.0;

            double lat1=pt1.y() * DegreesToRadians;
            double lon1=pt1.x() * DegreesToRadians;

            double lat2=pt2.y() * DegreesToRadians;
            double lon2=pt2.x() * DegreesToRadians;

            double R = 6378137.0;; // metres, earth r
            double phi1 = lat1;
            double phi2 = lat2;
            double delta_phi = (lat2-lat1);
            double delta_lon = (lon2-lon1);

            double a = sin(delta_phi/2.) * sin(delta_phi/2.) +
                    cos(phi1) * cos(phi2) *
                    sin(delta_lon/2.) * sin(delta_lon/2.);
            double c = 2. * atan2(sqrt(a), sqrt(1.-a));

            double d = R * c;

            return d;
        }

        double distance_UTM(Point_3 pt1, Point_3 pt2)
        {
            Point_2 p1(pt1.x(),pt1.y());
            Point_2 p2(pt2.x(),pt2.y());

            return sqrt( CGAL::squared_distance(p1,p2) );
        }

        boost::function<double(Point_3 pt1, Point_3 pt2)> distance;
        boost::function<Point_2(Point_3 src, double bearing, double distance)> point_from_bearing;


        double bearing_to_polar(double bearing)
        {
            double h = 450. - bearing;
            if (h > 360.)
                h = h-360.;

            return h * M_PI/180.;

        }

        Vector_2 polar_to_cartesian(double theta)
        {
            Vector_2 v(cos(theta ), sin(theta ));
            return v;
        }

        Vector_2 bearing_to_cartesian(double bearing)
        {
            return polar_to_cartesian(bearing_to_polar(bearing));
        }

        double cartesian_to_bearing(Vector_2 cart)
        {
            double phi = atan2(cart.y(), cart.x());
            phi =  M_PI/2.0 - phi;
            if (phi < 0.0)
                phi += 2.0 * M_PI;
            return phi * 180.0/M_PI;
        }
    }
}