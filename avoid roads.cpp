#include<bits/stdc++.h>

using namespace std;

bool restrict_right(int a,int b,vector< vector<int> >not_allowed_right,int n ) //this function returns 0 if path from (a,b) to (a+1,b) is restricted
{
	for(int i=0;i<n;i++)
	{
		if(not_allowed_right[i][0]==a && not_allowed_right[i][1]==b)
		{
			return 1;
		}
	}
	return 0;
}

bool restrict_top(int a,int b,vector< vector<int> >not_allowed_top,int n ) //this function returns 0 if path from (a,b) to (a,b+1) is restricted
{
	for(int i=0;i<n;i++)
	{
		if(not_allowed_top[i][0]==a && not_allowed_top[i][1]==b)
		{
			return 1;
		}
	}
	return 0;
}

int main()
{
	int width,height;
	cout<<"Enter the width: ";
	cin>>width;
	cout<<"Enter the height: ";
	cin>>height;
	
	int n;
	cout<<"No. of bad elements: ";
	cin>>n;
	string bad[n],s1,s2,s3,s4;
	int length[n];
	for(int i=0;i<n;i++)
	{
		cin>>s1>>s2>>s3>>s4;
		bad[i]=s1+" "+s2+" "+s3+" "+s4;
		length[i]=s1.length()+s2.length()+s3.length()+s4.length()+3;
	}
	
	for(int i=0;i<n;i++)
		cout<<bad[i]<<endl;
				
	vector< vector<int> >not_allowed_right(n,vector< int >( 2 ) ); //vector containing elements who are blocked in right direction
	vector< vector<int> >not_allowed_top(n,vector< int >( 2 ) );   //vector containing elements who are blocked in top direction
	for(int i=0;i<n;i++)
	{
		not_allowed_top[i][0]=-1;//initialize with -1
		not_allowed_top[i][1]=-1;
	}
	for(int i=0;i<n;i++)
	{
		not_allowed_right[i][0]=-1;
		not_allowed_right[i][1]=-1;
	}
	
	int nar=0; // iteration index of not_allowed_right
	int nat=0; // iteration index of not_allowed_top
	
	for(int i=0;i<n;i++)
	{
		bool prev=1; // showing previous char was space
		int num=1; // showing number to be extracted from that string...eg "10 5 6 7"...element 6 will have num=3
		int a,b,c,d;
		for(int j=0;j<length[i];j++)
		{
			if(bad[i][j]!=' ' && prev==1)
			{
				if(num==1)
					a=(int)bad[i][j]-48;//int value of char'0' is 48 so 48 is subtracted
				else if(num==2)
					b=(int)bad[i][j]-48;
				else if(num==3)
					c=(int)bad[i][j]-48;
				else
					d=(int)bad[i][j]-48;
				
				prev=0;
			}
			else if(bad[i][j]!=' ' && prev==0)//if previous value was not space then we have to multiply prev found with 10 and then add
			{
				if(num==1)
					a=10*a+(int)bad[i][j]-48;
				else if(num==2)
					b=10*b+(int)bad[i][j]-48;
				else if(num==3)
					c=10*c+(int)bad[i][j]-48;
				else
					d=10*d+(int)bad[i][j]-48;
			}
			else
			{
				num++;
				prev=1;
			}
		}
		//cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
		if(c==a+1 && b==d)
		{
			not_allowed_right[nar][0]=a;
			not_allowed_right[nar][1]=b;
			nar++;
		}
		if(c==a-1 && b==d)
		{
			not_allowed_right[nar][0]=c;
			not_allowed_right[nar][1]=d;
			nar++;
		}
		if(c==a && b==d+1)
		{
			not_allowed_top[nat][0]=c;
			not_allowed_top[nat][1]=d;
			nat++;
		}
		if(c==a && b==d-1)
		{
			not_allowed_top[nar][0]=a;
			not_allowed_top[nar][1]=b;
			nat++;
		}
	}
	
	
	long long dp[101][101];//dp array
	dp[0][0]=1;
	for(int i=0;i<=width;i++)
	{
		for(int j=0;j<=height;j++)
		{
			if(i>0 && !restrict_right(i-1,j,not_allowed_right,n))//if you can go from (i-1,j) to (i,j)
				dp[i][j]+=dp[i-1][j];
			if(j>0 && !restrict_top(i,j-1,not_allowed_top,n))//if you can go from (i,j-1) to (i,j)
				dp[i][j]+=dp[i][j-1];
		}
	}
	cout<<dp[width][height]<<endl;//print final answer
}
