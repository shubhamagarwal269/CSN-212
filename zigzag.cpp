#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	cout<<"No. of elements in the array: ";
	cin>>n;
	
	int arr[n];
	
	for(int i=0;i<n;i++)
		cin>>arr[i];
	
	int ans[n][2];
	for(int i=0;i<n;i++)
		for(int j=0;j<2;j++)
			ans[i][j]=0;
	
	ans[0][0]=1; //longest zigzag subsequence ending at index i was with positive difference
	ans[0][1]=1; //longest zigzag subsequence ending at index i was with negative difference
	int sol=1; //contains the length of longest zigzag subsequence till now
	
	for(int i = 1; i < n; i++)
	{
		for(int j = i-1; j>= 0; j--) // look for elements less than i
		{
			if(arr[j] < arr[i]) //if previous element was small
				ans[i][0] = max(ans[j][1]+1,ans[i][0]); //check longest zigzag subsequence ending at index j was with -ve difference because this difference wiil be +ve
			else if(arr[j] > arr[i])
				ans[i][1] = max(ans[j][0]+1, ans[i][1]); //check longest zigzag subsequence ending at index j was with +ve difference because this difference wiil be -ve
		}
		sol = max(sol,max(ans[i][0],ans[i][1])); // answer of ith will be max of answers considering both +ve and -ve difference.
	}
	cout<<sol<<endl;
}
