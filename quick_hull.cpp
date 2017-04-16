#include<bits/stdc++.h>
using namespace std;

struct node
{
	int x;  // store x coordinate of a point
	int y; // store y coordinate of a point
};

void display(node a) // to display node value in the code
{
	cout<<"node value is ("<<a.x<<","<<a.y<<") "<<endl;
}

void display_vec(vector<node> a) // to display a set of points present in a vector
{
	for(int i=0;i<a.size();i++)
		cout<<"("<<a[i].x<<","<<a[i].y<<")   ";
	cout<<endl;
}

bool clock(node p,node q,node r)//check if orientation of p,q anr r is clockwise or not
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
    if (val < 0)
        return 1;
    return 0;

}

vector<node> find_points(node A, node B, vector<node> points) //to find all the points which are left of a line
{
	vector<node> final;
	for(int i=0;i<points.size();i++)
	{
		if(clock(A,B,points[i]))
			final.push_back(points[i]);
	}
	return final;
}


void find_hull(vector<node> points,node A,node B)
{
	if(points.size()==0)
		return;// if no points remain return .....base condition of recursion
		
	double dist = 0,k;
	int ans;
	for(int i=0;i<points.size();i++)
	{
		int x = points[i].x;
		int y = points[i].y;
		k = abs((B.y-A.y)*x-(B.x-A.x)*y+B.x*A.y-B.y*A.x)/sqrt(pow(B.y-A.y,2)+pow(B.x-A.x,2));//perpendicular distance of a point from a line
		
		if(k>dist)
		{
			dist = k;//find the point with maximum distance
			ans = i;
		}
	}

	
	vector<node> points1 = find_points(A,points[ans],points);//on left side of line joining A and max dist point

	vector<node> points2 = find_points(points[ans],B,points);//on left side of line joining max dist point and B

	find_hull(points1,A,points[ans]);
	find_hull(points2,points[ans],B);	
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
	cout<<endl;
	node leftmost = coord[0];
    for (int i = 1; i < n; i++)
    {
        if (leftmost.x>coord[i].x)
        {
        	leftmost = coord[i];	
		} 
	}
	// to find the leftmost point in the graph
	
	node rightmost = coord[0];
    for (int i = 1; i < n; i++)
    {
        if (rightmost.x<coord[i].x)
        {
        	rightmost = coord[i];	
		} 
	}
    // to find the leftmost point in the graph
	
	
	vector<node> points_up = find_points(leftmost,rightmost,coord);// find the points in the upper half
	find_hull(points_up,leftmost,rightmost);
	
	vector<node> points_down = find_points(rightmost,leftmost,coord);// find the points in the bottom half
	find_hull(points_down,rightmost,leftmost);
	
}
