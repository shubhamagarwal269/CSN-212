#include<bits/stdc++.h>
using namespace std;
 

int binary_search(vector<int> &arr, int left, int right, int value) 
{
    while (right>left+1) 
	{
	    int mid;
		mid = (left+right)/2;
	    if (value<=arr[mid]) //if smaller look in left half
	        right=mid;
	    else
	        left=mid; //else in other half(right-half)
    }
   
   	return right;
}
 
int different_arrays(int arr[], int n)
{
	vector<int> solutions(10005); //contains max_length_increasing_subsequence 
	solutions[0]=arr[0];
	int k=1;
	for(int i=0;i<n;i++)
	{
		if(arr[i]<solutions[0])//take minimum element to starting
		{
			solutions[0]=arr[i];	
		}
		else if(solutions[k-1]<arr[i])
		{
        	solutions[k]=arr[i];//greater elements at last
        	k++;
		}
        else//else use binary search to place the ith element
		{
        	solutions[binary_search(solutions,-1,k-1,arr[i])]=arr[i];
		}   
	}
	return  k;//length of maximum increasing subsequence returned
}
 
int main()
{
	int t; //no of test cases
	cin>>t;
	int arr[20010]; // make array of twice the size so that we can write {4,3,2,1} as{4,3,2,1,2,3,4}
	while(t--)
	{
		int n; // number of guests invited
		cin>>n;
		for(int i=0;i<n;i++)
		{
			cin>>arr[i]; //array input
			arr[n+i]=arr[i]; //make {4,3,2,1} as{4,3,2,1,2,3,4}
		}
		int ans=0;
		for(int i=0;i<n;i++)
		{
			ans=max(ans,different_arrays(arr+i,n)); //check with array rotated by index i
		}
		cout<<ans<<endl;//print the max ans found
	}
	
}
