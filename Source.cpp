#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

enum figure_list
{
	Empty = 0,
	First = 1,
	Circ = First,
	Rect,
	Hex,
	Last
};

class Rectangle {
public:
	double x1;//x_topleft
	double y2;//y_topleft
	double x2;//x_downright
	double y1;//y_downright

	double getX1()
	{
		return x1;//x_topleft
	}

	double getY2()
	{
		return y2;//y_topleft
	}

	double getX2()
	{
		return x2;//x_downright
	}

	double getY1()
	{
		return y1;//y_downright
	}

	double getLength()
	{
		return x2 - x1;
	}

	double getWidth()
	{
		return y1 - y2;
	}

	double getSquare()
	{
		return getLength() * getWidth();
	}

	Rectangle getBoundingRect()
	{
		return *this;
	}

	void setCoordinates(double x_topleft, double y_topleft, double x_downright, double y_downright)//setX & setY
	{
		x1 = x_topleft;
		y2 = y_topleft;
		x2 = x_downright;
		y1 = y_downright;
	}

	void print_rec()
	{
		cout << "bounding rectangle: " << endl
		 << "x1 = " << x1 << " y1 = " << y1 << endl
		 << "x2 = " << x2 << " y2 = " << y2 << endl;
	}

};

class Circle{
public:
	double x_centre;
	double y_centre;
	double radius;

	Rectangle getBoundingRect()
	{
		Rectangle R;

		//x1 ---> x_topleft
		//y2 ---> y_topleft
		//x2 ---> x_downright
		//y1 ---> y_downright

		//x1 y2
		R.x1 = x_centre - radius;
		R.y2 = y_centre + radius;

		//x2 y2
		R.x2 = x_centre + radius;
		R.y1 = y_centre - radius;

		return R;
	}

	double getX_Centre()
	{
		return x_centre;
	}

	double getY_Centre()
	{
		return y_centre;
	}

	double getRadius()
	{
		return radius;
	}

	double getSquare()
	{
		return (3.1415 * pow(radius, 2));
	}

	void setCoordinates(double x_in, double y_in)//setX & setY
	{
		x_centre = x_in;
		y_centre = y_in;
	}

	void setRadius(double rad)
	{
		radius = rad;
	}

	void printCircle()
	{
		cout << "CIRCLE" << endl;
		cout << "Radius: " << radius << endl;
		cout << "x: " << x_centre << " y: " << y_centre << endl;
	}

};

class Hexagon {
public:
	double x_centre;//HOW ?????
	double y_centre;//HOW ?????
	double sRadius;
	double bRadius;
	double length;
	//bRadius == length

	double getX_Centre()
	{
		return x_centre;
	}

	double getY_Centre()
	{
		return y_centre;
	}

	double getSRadius()
	{
		return sRadius;
	}

	double getBRadius()
	{
		return bRadius;
	}

	double getLength()
	{
		return length;
	}

	double getSquare()
	{
		return ((3 * sqrt(3) * pow(length,2))/(2));
	}

	Rectangle getBoundingRect()
	{
		Rectangle R;

		//x1 y1
		R.x1 = x_centre - sRadius;
		R.y1 = y_centre + bRadius;

		//x2 y2
		R.x2 = x_centre + sRadius;
		R.y2 = y_centre - bRadius;

		return R;
	}

	void setCoordinates(double x_in, double y_in)
	{
		x_centre = x_in;
		y_centre = y_in;
	}

	void setSRadius(double sRad)
	{
		this->sRadius = sRad;
	}

	void setBRadius(double bRad)
	{
		this->bRadius = bRad;
	}

	void setLength(double len)
	{
		this->length = len;
	}

	void printHexagon()
	{
		cout << "HEXAGON" << endl;
	}

};

class Figure
{
public:
	int type_id = figure_list::Empty;//enum 
	void* fptr = nullptr;
};

bool intersection(const Rectangle a, const Rectangle b)
{
	double ax1 = a.x1;
	double ay1 = a.y1;
	double ax2 = a.x2;
	double ay2 = a.y2;

	double bx1 = b.x1;
	double by1 = b.y1;
	double bx2 = b.x2;
	double by2 = b.y2;

	
	// ax2 < bx1 ---> no intersection on X
	// bx2 < ax1 ---> no intersection on X
	// ay2 < by1 ---> no intersection on Y
	// by2 < ay1 ---> no intersection on Y

	// (ax2 < bx1) || (bx2 < ax1) ---> no intersection on X
	// (ay2 < by1) || (by2 < ay1) ---> no intersection on Y

	//(no X) || (no Y) ---> no intersection
	//( (ax2 < bx1) || (bx2 < ax1) ) || ( (ay2 < by1) || (by2 < ay1) ) ---> no intersection

	if ( ((ax2 < bx1) || (bx2 < ax1)) || ((ay2 < by1) || (by2 < ay1)) )
	{
		return false;// no intersection
	}
	else
	{
		return true;// intersection
	}
}

int random_int(int left_border, int right_border)
{
	return left_border + rand() % (right_border - left_border + 1);
}

Figure* createRectangle()
{
	Figure* newFigure = new Figure;

	newFigure->type_id = figure_list::Rect;

	// random number in [left, right]
	int left = 1;
	int right = 20;

	Rectangle* newRectangle = new Rectangle;

	newRectangle->x1 = random_int(left, right);
	newRectangle->y1 = random_int(left, right);
	int len = random_int(left, right);
	int wid = random_int(left, right);
	newRectangle->x2 = newRectangle->x1 + len;
	newRectangle->y2 = newRectangle->y1 + wid;

	newFigure->fptr = newRectangle;

	return newFigure;
}

Figure* createCircle()
{
	Figure* newFigure = new Figure;
	
	newFigure->type_id = figure_list::Circ;

	// random number in [left, right]
	int left = 3;
	int right = 20;

	//min and max value of radius
	int rad_min = 1;
	int rad_max = 7;

	Circle* newCircle = new Circle;
	newCircle->radius = random_int(rad_min, rad_max);
	newCircle->setCoordinates(random_int(left, right), random_int(left, right));

	newFigure->fptr = newCircle;

	return newFigure;
}

Figure* createHexagon()
{
	Figure* newFigure = new Figure;

	newFigure->type_id = figure_list::Hex;

	// random number in [left, right]
	int left = 1;
	int right = 20;

	//how should I describe hexagon?

	Hexagon* newHexagon = new Hexagon;
	//filling hexagon

	newFigure->fptr = newHexagon;

	return newFigure;
}

Figure* createFigure()
{
	int type = random_int(figure_list::Circ, figure_list::Rect);

	switch (type)
	{
		case figure_list::Circ:
		{
			return createCircle();
			break;
		}

		case figure_list::Rect:
		{
			return createRectangle();
			break;
		}

		case figure_list::Hex:
		{
			return createHexagon();
			break;
		}

		default:
			//cout << "createFigure error!" << endl;
			break;
	}

	return nullptr;
}

Rectangle Bounding_Rect(Figure* f)
{
	switch (f->type_id)
	{
		case figure_list::Circ:
		{

			Circle* Cir_ptr;
			Cir_ptr = static_cast<Circle*>(f->fptr);
			return Cir_ptr->getBoundingRect();
			break;
		}
		case figure_list::Rect:
		{

			Rectangle* Rec_ptr;
			Rec_ptr = static_cast<Rectangle*>(f->fptr);
			return Rec_ptr->getBoundingRect();
			break;
		}
		case figure_list::Hex:
		{

			Hexagon* Hex_ptr;
			Hex_ptr = static_cast<Hexagon*>(f->fptr);
			return Hex_ptr->getBoundingRect();
			break;
		}
		default:
			//cout << "type_id error in vector's element" << endl;
			break;
	}
}

double GetSquare(Figure* f)
{
	switch (f->type_id)
	{
		case figure_list::Circ:
		{
			Circle* Cir_ptr;
			Cir_ptr = static_cast<Circle*>(f->fptr);
			return Cir_ptr->getSquare();
		}
		case figure_list::Rect:
		{
			Rectangle* Rec_ptr;
			Rec_ptr = static_cast<Rectangle*>(f->fptr);
			return Rec_ptr->getSquare();
		}
		case figure_list::Hex:
		{
			Hexagon* Hex_ptr;
			Hex_ptr = static_cast<Hexagon*>(f->fptr);
			return Hex_ptr->getSquare();
		}
		case figure_list::Empty:
		{
			return 0;
		}
	default:
		break;
	}
	return 0;//?????????
}

bool Scene_Intersection(Figure* f, vector<Figure>& scene)
{
	for (int i = 0; i < scene.size(); i++)
	{
		if (scene[i].fptr != nullptr)//not empty figure
		{
			Figure* oldFigure = &scene[i];
			if (intersection(Bounding_Rect(f), Bounding_Rect(oldFigure)))
			{
				return true;
			}
		}
		else//empty figure ---> no intersection
		{
			
		}
	}

	return false;
	//return true; //intersection
	//return false; // no intersection
}

void fillScene(vector<Figure>& scene)
{
	int i = -1;
	int attempts = 0;
	while (attempts <= 100)
	{
		attempts++;

		Figure* newFigure = createFigure();
		if (!Scene_Intersection(newFigure, scene))
		{
			i++;
			cout << "succesfully created figure " << i << " on " << attempts << " attempt" << endl;
			scene.resize(i + 1);
			scene[i].type_id = newFigure->type_id;
			scene[i].fptr = newFigure->fptr;

			attempts = 0;
		}
	}
}

double TotalSquareUsed(vector<Figure>& scene)
{
	double TotalSquare = 0;

	for (int i = 0; i < scene.size(); i++)
	{
		TotalSquare += GetSquare(&scene[i]);
	}
	
	return TotalSquare;
}

void PrintFigure(Figure* f)
{
	switch (f->type_id)
	{
	case figure_list::Circ:
	{
		Circle* Cir_ptr;
		Cir_ptr = static_cast<Circle*>(f->fptr);
		Cir_ptr->printCircle();
		Cir_ptr->getBoundingRect().print_rec();
		cout << endl;
		break;
	}

	case figure_list::Rect:
	{
		Rectangle* Rec_ptr;
		Rec_ptr = static_cast<Rectangle*>(f->fptr);
		cout << "RECTANGLE" << endl;
		Rec_ptr->print_rec();
		Rec_ptr->getBoundingRect().print_rec();
		cout << endl;
		break;
	}

	case figure_list::Hex:
	{
		Hexagon* Hex_ptr;
		Hex_ptr = static_cast<Hexagon*>(f->fptr);
		Hex_ptr->printHexagon();
		Hex_ptr->getBoundingRect().print_rec();
		cout << endl;
		break;
	}

	case figure_list::Empty:
	{
		cout << "EMPTY FIGURE!" << endl;
	}

	default:
		//cout << "createFigure error!" << endl;
		break;
	}
}

void PrintScene(vector<Figure>& scene)
{
	for (int i = 0; i < scene.size(); i++)
	{
		cout << "Figure " << i << " is ";
		PrintFigure(&scene[i]);
	}
}


int main(void)
{
	vector<Figure> Scene;

	/////////////////////////////////fill scene test/////////////////////////////////////////////////
	//Scene.resize(10);
	fillScene(Scene);

	cout << endl << "Scene:" << endl;
	PrintScene(Scene);
	
	cout << "Total Square Used = " << TotalSquareUsed(Scene) << endl;


	return 1;
}
