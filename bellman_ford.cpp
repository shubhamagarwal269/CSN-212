//Shubham Agarwal
//14116063
//ECE 3rd year
//Bellman-Ford Algorithm


#include<bits/stdc++.h>
using namespace std;

int main()
{
	int v;
	cout<<"Enter the number of vertices: ";
	cin>>v;//no of vertices
	int e;
	cout<<"Enter the number of edges: ";
	cin>>e;//no of edges
	cout<<"Give information about all the edges: "<<endl;
	
	int graph[e][3];//first column for starting point of edge; second for ending point of edge and last one to store weight of edge
	
	for(int i=0;i<e;i++)
	{ //take input for matrix e
		cout<<"Starting vertex of edge (1-"<<v<<"): ";
		cin>>graph[i][0];
		graph[i][0]--;
		cout<<"Ending vertex of edge (1-"<<v<<"): ";
		cin>>graph[i][1];
		graph[i][1]--;
		cout<<"Weight of deirected edge: ";
		cin>>graph[i][2];
	}
	
	int shortest_path[v]; // this array will store the shortest_distance of every edge from the starting point
	shortest_path[0]=0;
	
	for(int i=1;i<v;i++)
		shortest_path[i]=INT_MAX; // setting all other distances to infinity
		
	// main algorithm
	int start_s=clock();
	for(int i=1;i<v;i++)//we will update weight for all the edges atmost vetices-1 times to get shortest weight if a negative cycle is not there
	{    
		for(int j=0;j<e;j++)
		{ //if shortest path to a vertex is not infinity then only we can apply the relaxation criteria
			if(shortest_path[graph[j][0]]!=INT_MAX)
			{//for an edge from u to v....if dist(v)>dist(u)+ weight(u,v) then update dist(v)
				if(shortest_path[graph[j][0]]+graph[j][2]<shortest_path[graph[j][1]])
				{
					shortest_path[graph[j][1]]=shortest_path[graph[j][0]]+graph[j][2];
				}
			}
		}
	}
	
	int flag =0; // to check for negative cycle
	cout<<endl;
	
	for(int j=0;j<e;j++)
	{ //if still dist(v)>dist(u)+ weight(u,v) then distance are still not shortest...that mens a negative cycle is there which can still reduce the weights
		if(shortest_path[graph[j][0]]+graph[j][2]<shortest_path[graph[j][1]])
		{
			cout<<"There is a negative cycle"<<endl;
			flag=1;
		}
	}
	
	if(flag==0)
	{	// print the final shorest distances from first vertex
		cout<<"The final minimum distances from first verterx in order are: "<<endl;	
		for(int i=0;i<v;i++)
			cout<<shortest_path[i]<<" ";
	}
	int stop_s=clock();
	cout << "time taken : " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl; // to get the running time of an algorithm
	//worst case of this algorithm is O(vertex*edge)
	//best case of this algorithm is O(edge)
	
	/*Some test cases
  (I)	no. of vertices = 5
	no. of edges = 8
	
	Starting Point		Ending Point	Weight
	1					2			   -1
	1					3				4
	2					3				3
	2					4				2
	2					5				2
	4					2				1
	4					3				5
	5					4			   -3
	
	
	Answer:  0 -1 2 -2 1
  
  (II)	no. of vertices = 6
	no. of edges = 8
	
	Starting Point		Ending Point	Weight
	1					2				10
	1					6				8
	2					4				2
	3					2				1
	4					3			   -2
	5					4			   -1
	5					2			   -4
	6					5				1
	
	
	Answer:  0 5 5 7 9 8	
	
	(III)	no. of vertices = 5
	no. of edges = 6
	
	Starting Point		Ending Point	Weight
	1					2				2
	2					5				5
	2					3				4
	1					4				1
	4					3			    3
	3					5			    1
	
	
	Answer:  0 2 4 1 5 	
	*/
}
