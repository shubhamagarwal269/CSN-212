#include<iostream>
#include<bits/stdc++.h>

# define PI          3.141592653589793238462643383279502884L /* pi */

using namespace std;

struct node
{
	int x; // x coordinate of a point 
	int y; // y coordinate of a point 
	double angle; // angle with reference to the leftmost point
};

bool a_sort(node one, node two)
{
	return (one.angle<two.angle)?1:0; // to sort the points on basis of angles
}

void display(node a)
{
	cout<<"("<<a.x<<","<<a.y<<") "<<endl; // to display a node value in the code
}

bool check_left(node p,node q,node r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
    if (val > 0)
        return 1; // if value is greater than zero than p,q and r form a clockwise pair
    return 0;

}

int main()
{
	int n;
	cout<<"no of points(greater than 2): ";
	cin>>n;
	vector<node> coord(n);
	for(int i=0;i<n;i++)
	{
		cout<<"Enter x coordinate of node"<<i+1<<": ";
		cin>>coord[i].x;
		cout<<"Enter y coordinate of node"<<i+1<<": ";
		cin>>coord[i].y;
	}// to input the values of points of the graph
	
	node leftmost = coord[0];
    for (int i = 1; i < n; i++)
    {
        if (leftmost.x>coord[i].x)
        {
        	leftmost = coord[i];	
		} 
	}//find the leftmost point in a graph
	
	
	for(int i=0;i<n;i++)
	{
		if(coord[i].x!=leftmost.x || coord[i].y!=leftmost.y)
		{
			
			display(coord[i]);
			if(coord[i].y-leftmost.y!=0)
			{
				coord[i].angle = atan(double(coord[i].x-leftmost.x)/(-coord[i].y+leftmost.y))*180/PI; //angle wrt to leftmost point
				if(coord[i].angle<0)
					coord[i].angle+=180;//if angle is less than 0 than add 180 to make positive
				
			}
			else
			{
				coord[i].angle = 90; // if both have same y coordinate than assign angle of 90 degrees
				cout<<coord[i].angle<<endl;
			}
		}
	}
	
	sort(coord.begin(),coord.end(),a_sort); //sort points according to angle
	
	stack<node> points; // to store points that will be in the hull
	stack<node> prev; // to store previous point to this point that was added in the hull

	points.push(leftmost);//push the leftmost and the lowest angle point in the hull
	points.push(coord[1]);

	prev.push(leftmost);
		
	
	for(int i=2;i<n;i++)
	{
	//now if we turn left from previous point to next point then we add the next point in hull....else if we have to turn right 
	//then we pop our stack till rotattion is left only
		if(check_left(prev.top(),coord[i],points.top()))//check_left turn
		{
			prev.push(points.top());
			points.push(coord[i]);// add points in our stack
		}
		
		else
		{
			while(!check_left(prev.top(),coord[i],points.top()))//while we get left turn from previous point
			{
				points.pop();
				prev.pop();// pop the points
			}
			
			prev.push(points.top());
			
			points.push(coord[i]);//now add new point in our stack
			
		}
	}
	
	while(!points.empty())//display the ans
	{
		display(points.top());
		points.pop();
	}
	
}
