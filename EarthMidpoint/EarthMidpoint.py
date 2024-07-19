"""
EarthMidpoint.py

Benjamin Alexander

7/17/2024

Assignment: Write a module/package in Python or Javascript that implements a function with the following characteristics:
1.       Input: two locations (“from” and “to”) each defined by a pair of latitude/longitude coordinates
2.       Output: The midpoint on the shortest path between these two locations on the surface of the Earth
Bonus points: Returning a path of N coordinates evenly spaced along the path

Copyright (c) 2024 Benjamin Alexander. All rights reserved.
"""

import math

"""
Below Class allows us to create and store objects with a latitude and Longitude
"""
class Coordinate:
    
  def __init__(this):
    this.Lat = float(input('enter Latitude: '))
    this.Long = float(input('enter Longitude: '))
    
  def __init__(this, lat, long):
    this.Lat = lat
    this.Long = long
    
"""
The below function finds the midpoint between two geographical points on a map

We use the Formula given from https://www.movable-type.co.uk/scripts/latlong.html
φ1 = lat1 * math.PI/180
φ2 = lat2 * math.PI/180
λ1 = lon1* math.PI/180
Δλ = (lon2-lon1) * math.PI/180

Bx = cos φ2 ⋅ cos Δλ
By = cos φ2 ⋅ sin Δλ
φm = atan2( sin φ1 + sin φ2, √(cos φ1 + Bx)² + By² )
λm = λ1 + atan2(By, cos(φ1)+Bx)
λm = (λm+540)%360-180
"""
def FindMidPoint(coordinateFrom, coordinateTo):
    LatFrom = math.radians(coordinateFrom.Lat) 
    LatTo = math.radians(coordinateTo.Lat) 
    LongFrom =math.radians(coordinateFrom.Long) 
    LongDelta = math.radians(coordinateTo.Long - coordinateFrom.Long)
    
    Bx = math.cos(LatTo) * math.cos(LongDelta)
    By = math.cos(LatTo) * math.sin(LongDelta)
    lat3 = math.atan2(math.sin(LatFrom) + math.sin(LatTo), math.sqrt((math.cos(LatFrom) + Bx) * (math.cos(LatFrom) + Bx) + By * By))
    lon3 = LongFrom + math.atan2(By, math.cos(LatFrom) + Bx)
    lon3 = (lon3 + 3 * math.pi) % (2 * math.pi) - math.pi #normalize Longitude

    newCo = Coordinate(math.degrees(lat3), math.degrees(lon3))
    return newCo

"""    
The Below Function finds a path of N coordinates evenly spaced along the path
To find and display a path of N points, we need a start point, distance between our start and end points and our bearing

First we calculate the distance and bearing.

Then we divide our distance by our N

Finally we can save a list of points by looping N times and finding that specific point with start point, current distance, and bearing
""" 
def FindPath(coordinateFrom, coordinateTo):
    N = float(input('\nEnter number of points to add to our path: '))
    
    Distance = FindDistance(coordinateFrom, coordinateTo)
    Bearing = FindBearing(coordinateFrom, coordinateTo)
    
    if N <= 0 :
        return
    elif N==1:
        FindMidPoint(coordinateFrom, coordinateTo)
    else :
        Paths = []
                
        StepDistance = Distance/(N+1)
                
        i=StepDistance
        while i < Distance:
            Paths.append(GetPathOnPoint(coordinateFrom, i, Bearing))
            i += StepDistance

        return Paths
    
"""   
Finds the distance between two latitude and longitude points
We use the Formula given from https://www.movable-type.co.uk/scripts/latlong.html

φ1 = lat1 * math.PI/180
φ2 = lat2 * math.PI/180
Δφ = (lat2-lat1) * math.PI/180;
Δλ = (lon2-lon1) * math.PI/180;
a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
c = 2 ⋅ atan2( √a, √(1-a) )
d = R ⋅ c
"""
def FindDistance(coordinateFrom, coordinateTo):
    R = 6378.137
    LatFrom = math.radians(coordinateFrom.Lat) 
    LatTo = math.radians(coordinateTo.Lat) 
    LatDelta = math.radians(coordinateTo.Lat - coordinateFrom.Lat)
    LongDelta = math.radians(coordinateTo.Long - coordinateFrom.Long)
    
    a = math.sin(LatDelta/2) * math.sin(LatDelta/2) + math.cos(LatFrom) * math.cos(LatTo) * math.sin(LongDelta/2) * math.sin(LongDelta/2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    d = R * c
    
    return d
    

""" 
Finds the bearing needed to reach point 1 from point 2
We use the Formula given from https://www.movable-type.co.uk/scripts/latlong.html

φ1 = lat1 * math.PI/180
φ2 = lat2 * math.PI/180
Δλ = (lon2-lon1) * math.PI/180;
θ = atan2( sin Δλ ⋅ cos φ2 , cos φ1 ⋅ sin φ2 - sin φ1 ⋅ cos φ2 ⋅ cos Δλ )
""" 
def FindBearing(coordinateFrom, coordinateTo):
    LatFrom = math.radians(coordinateFrom.Lat) 
    LatTo = math.radians(coordinateTo.Lat) 
    LongDelta = math.radians(coordinateTo.Long - coordinateFrom.Long)
    
    θ = math.atan2(math.sin(LongDelta) * math.cos(LatTo), math.cos(LatFrom) * math.sin(LatTo) - math.sin(LatFrom) * math.cos(LatTo) * math.cos(LongDelta))
    
    bearing = (θ*180/math.pi + 360) % 360 #normalize to compass bearing

    return bearing
    
    
""" 
finds the specific point given a start, distance traveled,a nd bearing
We use the Formula given from https://www.movable-type.co.uk/scripts/latlong.html

φ1 = lat1 * math.PI/180
φ2 = lat2 * math.PI/180
λ1 = lon1* math.PI/180
Δλ = (lon2-lon1) * math.PI/180

φ1 = lat1 * math.PI/180  
λ1 = lon1 * math.PI/180
φ2 = asin( sin φ1 ⋅ cos δ + cos φ1 ⋅ sin δ ⋅ cos θ )
λ2 = λ1 + atan2( sin θ ⋅ sin δ ⋅ cos φ1, cos δ − sin φ1 ⋅ sin φ2 )
"""
def GetPathOnPoint(coordinateFrom, distance, bearing):
    R = 6378.137
    Radbearing = (bearing*math.pi)/180

    LatFrom = math.radians(coordinateFrom.Lat) 
    LongFrom = math.radians(coordinateFrom.Long) 

    newlat = (math.asin(math.sin(LatFrom) * math.cos(distance/R) + math.cos(LatFrom) * math.sin(distance/R) * math.cos(Radbearing)))
    newlon = (LongFrom + math.atan2(math.sin(Radbearing) * math.sin(distance/R) * math.cos(LatFrom), math.cos(distance/R) - math.sin(LatFrom) * math.sin(newlat)))

    newlon = ((newlon + 3 * math.pi) % (2 * math.pi) - math.pi) #normalize Longitude
    
    newCo = Coordinate(math.degrees(newlat), math.degrees(newlon))
    return newCo
    
    
"""
Driver Code
"""

print("Enter first set of coordinates: ")
co1 = Coordinate(float(input('Latitude: ')), float(input('Longitude: ')))

print("\nEnter second set of coordinates: ")
co2 = Coordinate(float(input('Latitude: ')), float(input('Longitude: ')))

MidPoint = FindMidPoint(co1, co2)
print("\nOur midpoint in degrees =", MidPoint.Lat, MidPoint.Long)

Paths = FindPath(co1, co2)

for i, item in enumerate(Paths, start=1):
    print( "\nPoint", i, "=", item.Lat , item.Long)
    
input("\nEnter any key to quit.") 