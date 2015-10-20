// classes example
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

//template <class T>
class Point{
//  friend class Circle<T>;
    double x, y;
  public:
  Point(double x1, double y1) : x(x1), y(y1)  { }
  Point() {}
  //  void set_values (T,T);
//    const getX() const { return x; }
  const double & getX() const {return x;}
  const double & getY() const{ return y; }
};


void printResult (vector<Point> result);

//template <class T>
class Circle {
  Point centre;
  double  radius;

public:

  Circle ( double x, double y, double radius1) {
    centre = Point(x,y);
    //Radius has to be a positive number
    assert (radius1 >0) ;
      radius = radius1;

 }

 Circle (Point centre2, double radius2) {
   centre = centre2;
   assert (radius2 >0) ;
   radius = radius2;
 }

 Point & getCentre()  {return centre;}

const double & getRadius() const{ return radius; }

 vector<Point > findIntersect ( Circle b);

void testCase(Circle b, vector <Point> Empty) {
   vector<Point> result = findIntersect(b);
   printResult(result);
   //clear memory
   result.swap(Empty);
 }
};



vector <Point>  Circle :: findIntersect ( Circle B) {
vector <Point> result;


//Get all the parameters
Point A = getCentre();
double Ax = getCentre().getX();
double Ay = getCentre().getY();
double Ar = getRadius();

double Bx = B.getCentre().getX();
double By = B.getCentre().getY();
double Br = B.getRadius();

//assert that two circles are not overlaped and identical
assert (!(Ax== Bx && Ay == By && Ar == Br));

// Find the distance between two centres
double centreDistance = sqrt( pow((Ax-Bx),2) + pow((Ay-By),2) );

//Check if two circles are too far apart and do not have intersect (cetreDistance < Ar + Br)
// or one circle is inside another one without any interesection (centreDistance < abs (Ar -Br))
if ((centreDistance > Ar + Br ) | (centreDistance <abs(Ar-Br))) {
  cout << "Two circles are two far apart to have interesection \n";
  //return an empty vector of Point
  return result;
}
else{
  //2D coordinates of intersections and temp
  double x1,y1, x2, y2, temp;

// Two circles will have at least one at most 2 intersection
// solve two quadratiic equation for the positions intersections
// (1) (x-Ax)^2 + (y-Ay)^2 = Ar^2
// (2) (x-Bx)^2 + (y-By)^2 = Br^2
// after transformation, the two equations will be
// (1) x = dy + e
// (2) a^2 + by + c = 0
// d = (Ay -By)/(Bx-Ax) and e = (Ax^2 + Ay^2 - Ar^2 -Bx^2 -By^2 + Ar^2)/ 2(Ax-Bx)
// a = (d^2 + 1); b= 2(de-dAx-Ay) and c= (e^2 - 2eAx + Ax^2 + Ay^2 - Ar^2)

// if (Bx == Ax), d and e will not be valid because of the denominator (Ax -Bx)
if (Ax == Bx) {
// after transformation, the two equation will be:
// (1) (x - Ax)^2 = Ar^2 - (y-Ay)^2
// (2) y = ((Ar^2 - Br^2)/(By-Ay) + Ay + By)/2
// note: (By -Ay) is definitely non-zero here because of previous filtering
// From (1): x1 = Ax + temp and x2 = Ax - temp
// where temp = sqrt(Ar^2 - (y-Ay)^2)
assert (By != Ay); //Just to make sure

y1 = ((Ar*Ar - Br*Br)/(By-Ay) + Ay + By)/2;
y2 = y1;
temp = sqrt(Ar*Ar -(y1-Ay)*(y1-Ay));
x1 = Ax + temp;
x2 = Ax - temp;

}
else {
assert (Bx!= Ax);
double d = (Ay - By)/ (Bx-Ax);
double e = (Ax*Ax + Ay*Ay -Ar*Ar - Bx*Bx - By*By + Br*Br)/ (2* (Ax-Bx));
double a = d*d + 1;
double b = 2*(d*e - d*Ax -Ay);
double c = e*e -2*e*Ax + Ax*Ax + Ay*Ay -Ar*Ar;


// the solution for equation (2) is
// y1 = (-b + sqrt(b^2 - 4ac))/2a and y2 = (-b - sqrt(b^2 - 4ac))/2a
// where b^2-4ac >=0
// when b^2 - 4ac = 0, (1) has one solution y = -b/2a and the two circles have 1 intersection.
temp = b*b -4*a*c;
//Make sure temp is a non negative number
assert (temp >=0);

// equation (2) has only 1 solution
if (temp == 0) {
  y1 = b/(-2*a);
  x1 = d*y1 + e;
}
else {
  //Coordinates for the first intersection
  y1 = (-b + sqrt(temp))/(2*a);
  x1 = d*y1 + e;

  //Coordinates for the second intersection
  y2 = (-b - sqrt(temp))/(2*a);
  x2 = d*y2 + e;
}
}

//Push coordinates into result
result.push_back(Point(x1, y1));
//Push the second coordinates (if applicable) into result
if (temp!=0) result.push_back(Point(x2,y2));

return result;
}

}


void printResult (vector<Point> result) {
cout << "There is "<< result.size() << " intersection(s) between two circles: \n" ;
    for (int i = 0; i < result.size(); i ++)
      cout << "Intersection " << i << ": [" << result[i].getX() << " ," << result[i].getY() << "]" << endl;
    //cout << "[" << i << "]" << endl;
}


int main () {
  Circle H(0,0,3);
  vector <Point> result;

  // Test case 1: Circles are too far apart
  cout << "\nTest case 2: Circles are too far apart to have intersection: H(0,0,3) and T1(9,9,1) \n";
  H.testCase(Circle (9,9,1), result);


  //Test case 2: Circles inside each other
  cout << "\nTest case 2: Circles inside each other: H(0,0,3) and T2(1,1,1) \n";
  H.testCase(Circle (1,1,1), result);


  //Test case 3: Circles inside each other
  cout << "\nTest case 3: Circles inside each other: H(0,0,3) and T3(1,1,9) \n";
  H.testCase(Circle (1,1,9), result);


  //Test case 4: Circles have 1 intersection: 1 cirlce is inside another one
  cout << "\nTest case 4: Circles have 1 intersection (1 cirlce is inside another one): H(0,0,3) and T4(2,0,1) \n";
  H.testCase(Circle (2,0,1), result);


  //Test case 5: Circles have 1 intersection: 2 circles are outside each other
  cout << "\nTest case 5: Circles have 1 intersection (2 cirlces are outside each): H(0,0,3) and T5(4,0,1) \n";
  H.testCase(Circle (4,0,1), result);


  //Test case 6: Circles have 2 intersections
  cout << "\nTest case 6: Circles have 2 intersections: H(0,0,3) and T6(4,0,2) \n";
  H.testCase(Circle (4,0,2), result);


  //Test case 7: Circles have 2 intersections
  cout << "\nTest case 7: Circles have 2 intersections: H(0,0,3) and T7(0,-3,3) \n";
  H.testCase(Circle (0,-3,3), result);

  //Test case 8: Two exact circles are overlapped // Will raise an error
  cout << "\nTest case 8: Two exact circles are overlapped: H(0,0,3) and T8(0,0,3) \n";
  //H.testCase(Circle (0,0,3), result);

/**

  Circle T2 (4,0,2);
  result = H.findIntersect(T2);
  cout << "size of result is: " << result.size() << endl;
  printResult(result);
  result.clear();
  cout << "size of result is: " << result.size() << endl;


Circle T1 (9,9,1);
result = H.findIntersect(T1);
cout << "size of result is: " << result.size() << endl;
printResult(result);


/

  //mypair <int> myobject (100, 75);
  Point  rect (2,3);
  Circle S (rect, 3);
  cout << "S.getCentre().getX(): " << S.getCentre().getX() << endl;
  cout << "S.getRadius(): " << S.getRadius() << endl;

//  Circle <int> CirlceA(*rect, 4);
   Circle A(1,-1,4);
//  int X = rect.getX();
  Point B = A.getCentre();
  cout << "A.getCentre().getX(): " << A.getCentre().getX() << endl;
//  cout << "X: " << X << endl;
cout << "A.getRadius(): " << A.getRadius() << endl;

result = S.findIntersect(A);
  printResult(result);

  **/
    return 0;
}
