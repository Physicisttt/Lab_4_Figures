#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

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
		Rectangle R;

		//x1 y1
		R.x1 = x1;
		R.y1 = y1;

		//x2 y2
		R.x2 = x2;
		R.y2 = y2;

		return R;
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
		cout << "your rectangle: " << endl
		 << "x1 = " << x1 << "y1 = " << y1 << endl
		 << "x2 = " << x2 << "y2 = " << y2 << endl;
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
		this->radius = rad;
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

};

class Figure
{
public:
	int type_id = 0;//enum 
	void* fptr = nullptr;
};

enum figure_list
{
	First = 1,
	Circ = First,
	Rect, 
	Hex, 
	Last
};

bool intersection(Rectangle a, Rectangle b)
{
	double ax1 = a.getBoundingRect().getX1();
	double ay1 = a.getBoundingRect().getY1();
	double ax2 = a.getBoundingRect().getX2();
	double ay2 = a.getBoundingRect().getY2();

	double bx1 = b.getBoundingRect().getX1();
	double by1 = b.getBoundingRect().getY1();
	double bx2 = b.getBoundingRect().getX2();
	double by2 = b.getBoundingRect().getY2();

	
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
	newRectangle->y2 = random_int(left, right);
	newRectangle->x2 = random_int(left, right);
	newRectangle->y1 = random_int(left, right);

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
	const int a = 3;
	const int b = 12;

	const int n = 1;
	const int m = 3;

	int rand_type = random_int(n, m);
	rand_type = 1;

	switch (rand_type)
	{
		case 1://circle
		{
			return createCircle();
			break;
		}

		case 2://rectangle
		{
			
			break;
		}

		case 3://hexagon
		{
			
			break;
		}

		default:
			break;
	}


	//new element of choosen class

	//
}

void fillScene(vector<Figure> &scene)
{
	/*cout << "what do you want?" << endl;
	cout << "1 - add new figure" << endl << "0 - stop" << endl;
	char action;
	cin >> action;

	switch (action)
	{
	case 0:
		{
		cout << "finish.." << endl;
		break;
		}

	case 1:
	{
		cout << "choose the figure" << endl;
		
	}

	default:
		break;
	}
	*/
	int type = 0;
	for (int i = 0; i < scene.size(); i++)
	{
		type = random_int(figure_list::Circ, figure_list::Rect);

		switch (type)
		{
			case 1:
			{
				scene[i].type_id = type;
				//scene[i].fptr = createCircle();
				scene[i].fptr = createCircle()->fptr;
				break;
			}

			case 2:
			{
				scene[i].type_id = type;
				scene[i].fptr = createRectangle()->fptr;
				break;
			}

			case 3:
			{
				scene[i].type_id = type;
				scene[i].fptr = createHexagon()->fptr;
				break;
			}

			default:
				break;
		}
		//scene[i].fptr = createFigure();
	}
}
//Circle* Cir_ptr;
//Cir_ptr = static_cast<Circle*>(Scene[i].fptr);//if null


int main(void)
{
	vector<Figure> Scene;
	/*
	Scene.resize(5);

	Circle Cir_1;
	Cir_1.setCoordinates(3, 4);
	Cir_1.setRadius(2);

	Circle Cir_2;
	Cir_2.setCoordinates(7, 8);
	Cir_2.setRadius(1);

	Circle Cir_3;
	Cir_3.setCoordinates(3, 12);
	Cir_3.setRadius(2);

	Circle Cir_4;
	Cir_4.setCoordinates(3, 7);
	Cir_4.setRadius(1);

	Rectangle Rec_1;
	Rec_1.x1 = 8;
	Rec_1.y2 = 6;
	Rec_1.x2 = 14;
	Rec_1.y1 = 3;

	Rectangle Rec_2;
	Rec_2.x1 = 17;
	Rec_2.y2 = 8;
	Rec_2.x2 = 20;
	Rec_2.y1 = 5;

	Rectangle Rec_3;
	Rec_3.x1 = 11;
	Rec_3.y2 = 9;
	Rec_3.x2 = 16;
	Rec_3.y1 = 5;

	Rectangle Rec_4;
	Rec_4.x1 = 14;
	Rec_4.y2 = 3;
	Rec_4.x2 = 16;
	Rec_4.y1 = 1;

	Hexagon Hex_1;
	Hex_1.bRadius = 6;
	Hex_1.length = 6;
	Hex_1.sRadius = Hex_1.length * (sqrt(3) / 2);

	Scene[0].type_id = 1;
	Scene[0].fptr = &Cir_1;

	Scene[1].type_id = 1;
	Scene[1].fptr = &Cir_2;

	Scene[2].type_id = 2;
	Scene[2].fptr = &Rec_1;

	Scene[3].type_id = 2;
	Scene[3].fptr = &Rec_2;

	Scene[4].type_id = 3;
	Scene[4].fptr = &Hex_1;
	*/

	/*if ((Scene[0].type_id == figure_list::Circ) && (Scene[0].fptr != nullptr))
	{
		// Scene[0].fptr  void*
		// void* ==> Circle*
		// int a;
		// char c = (char)a;
		Circle* c_ptr;
		c_ptr = static_cast<Circle*>(Scene[0].fptr);//if null
		cout << "circle radius: " << c_ptr->getRadius() << endl;

	}

	double used_square = 0;
	for (int i = 0; i < Scene.size(); i++)
	{
		switch (Scene[i].type_id)
		{
			case figure_list::Circ:
			{
				cout << "figure " << i << " is Circle" << endl;
				Circle* Cir_ptr;
				Cir_ptr = static_cast<Circle*>(Scene[i].fptr);//if null
				cout << "Figure " << i << " Square = " << Cir_ptr->getSquare() << endl;
				used_square += Cir_ptr->getSquare();
				break;
			}
			case figure_list::Rect:
			{
				cout << "figure " << i << " is Rectangle" << endl;
				Rectangle* Rec_ptr;
				Rec_ptr = static_cast<Rectangle*>(Scene[i].fptr);//if null
				cout << "Figure " << i << " Square = " << Rec_ptr->getSquare() << endl;
				used_square += Rec_ptr->getSquare();
				break;
			}
			case figure_list::Hex:
			{
				cout << "figure " << i << " is Hexagon" << endl;
				Hexagon* Hex_ptr;
				Hex_ptr = static_cast<Hexagon*>(Scene[i].fptr);//if null
				cout << "Figure " << i << " Square = " << Hex_ptr->getSquare() << endl;
				used_square += Hex_ptr->getSquare();
				break;
			}
			case 0:
			{
				break;
			}
			default:
				break;
		}
	}
	cout << "Total Square used: " << used_square << endl;
	*/
	cout << endl << endl;

	/////////////////////////////////rectangles/////////////////////////////////////////////////
	/*
	cout << endl << "	RECTANGLES TEST" << endl;

	if (intersection(Rec_1, Rec_2)){
		cout << "intersection" << endl;
	}
	else{
		cout << "no intersection" << endl;
	}

	if (intersection(Rec_1, Rec_3)){
		cout << "intersection" << endl;
	}
	else{
		cout << "no intersection" << endl;
	}

	if (intersection(Rec_1, Rec_4)){
		cout << "intersection" << endl;
	}
	else{
		cout << "no intersection" << endl;
	}
	//////////////////////////////////circles////////////////////////////////////////////////
	
	cout << endl << "	CIRLES TEST" << endl;
	
	if (intersection(Cir_1.getBoundingRect(), Cir_2.getBoundingRect())) {
		cout << "intersection" << endl;
	}
	else {
		cout << "no intersection" << endl;
	}

	if (intersection(Cir_1.getBoundingRect(), Cir_3.getBoundingRect())) {
		cout << "intersection" << endl;
	}
	else {
		cout << "no intersection" << endl;
	}

	if (intersection(Cir_1.getBoundingRect(), Cir_4.getBoundingRect())) {
		cout << "intersection" << endl;
	}
	else {
		cout << "no intersection" << endl;
	}
	
	
	*/

	Figure* test1 = createFigure();

	cout << "test1 type_id = " << test1->type_id;
	cout << "test1 radius = ";//static_cast

	/////////////////////////////////fill scene test/////////////////////////////////////////////////
	Scene.resize(5);
	fillScene(Scene);

	cout << endl << "fillScene test" << endl;
	for (int i = 0; i < Scene.size(); i++)
	{
		cout << "type: " << Scene[i].type_id << endl;
		switch (Scene[i].type_id)
		{
		case figure_list::Circ:
		{
			cout << "figure " << i << " is Circle" << endl;
			Circle* Cir_ptr;
			Cir_ptr = static_cast<Circle*>(Scene[i].fptr);//if null
			Cir_ptr->getBoundingRect().print_rec();
			break;
		}
		case figure_list::Rect:
		{
			cout << "figure " << i << " is Rectangle" << endl;
			Rectangle* Rec_ptr;
			Rec_ptr = static_cast<Rectangle*>(Scene[i].fptr);//if null
			Rec_ptr->print_rec();
			//Rec_ptr->getBoundingRect().print_bound_rect();
			break;
		}
		case figure_list::Hex:
		{
			cout << "figure " << i << " is Hexagon" << endl;
			Hexagon* Hex_ptr;
			Hex_ptr = static_cast<Hexagon*>(Scene[i].fptr);//if null
			//Hex_ptr->getBoundingRect().print_bound_rect();
			break;
		}
		case 0:
		{
			cout << "HEEEEYYYY WHAAA HAPPEN' ????";
			break;
		}
		default:
			break;
		}
	}
	
	




	return 1;
}