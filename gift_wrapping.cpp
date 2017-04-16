#include <bits/stdc++.h>
using namespace std;
 
struct node
{
	int x; // store x coordinate of a point
	int y; // store y coordinate of a point
};

int anti_clock(node p, node q, node r)
{
    int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y);
 
    if (val<0)
        return 1; // Checking if points are in counterclock wise orientation
        
    return 0; // clockwise 
}
 
void convex_Hull(vector<node> points)
{
   	
 	int n = points.size();
    int array[n];
    for(int i=0;i<n;i++)
    	array[i] = -1; //Initializing each value to -1
 
    int leftmost = 0;
    for(int i=1;i<n;i++)
    {
        if(points[i].x<points[leftmost].x) // Find the leftmost point
            leftmost = i;
 	}
 	
    int p=leftmost,r;
    
	do
    {
        r = (p+1) % n;
        for (int i = 0; i < n; i++)
            if (anti_clock(points[p], points[i], points[r])) //Checking for counterclockwise rotation
                r = i;
 
        array[p]=r;
        p=r;
    }
    while(p!=leftmost); //It should again reach the starting point
 
    for(int i=0;i<n;i++)
    {
        if (array[i] != -1)
            cout<<"("<<points[i].x<<","<<points[i].y<<")\n"; // display the ans
    }
}
 
int main()
{
	int n;
	cout<<"no of points(greater than 2): ";
	cin>>n;
	vector<node> coord(n);
	for(int i=0;i<n;i++)
	{
		cout<<"Enter x coordinate"<<i+1<<": ";
		cin>>coord[i].x;
		cout<<"Enter y coordinate"<<i+1<<": ";
		cin>>coord[i].y;
	}// to input the values of points of the graph
    convex_Hull(coord); //convex_hull function will find the hull
}
