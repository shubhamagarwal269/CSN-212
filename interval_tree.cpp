//Progran of Interval Tree 
//Shubham Agarwal  14116063 ECE 3rd Year

#include<bits/stdc++.h>

using namespace std;

struct interval
{
	int left;//left value of interval
	int right;//right value of interval
};

struct tree
{
	struct tree * l_child;//left child of noode
	struct tree * r_child;//right child of node
	struct interval value; //value of interval of that node
	int max_v=INT_MIN; //initialized with minus infinity. This stores the max_v occuring in the subtree of any node
};


void diff_functions(struct tree* node);

struct tree* build_tree(struct tree* root,interval i)
{
	struct tree* temp = root;	//assign temp as root node
	if(temp!=NULL)
	{
		if(temp->value.left<=i.left)//if lower move to left
			temp->r_child=build_tree(temp->r_child,i);
		else//else move to right
			temp->l_child=build_tree(temp->l_child,i);
	}
	else
	{//when null occurs allocat new memory .
		struct tree* temp_n = new tree ;
		temp_n->value.left=i.left;
		temp_n->value.right=i.right;
		temp_n->l_child=NULL;
		temp_n->r_child=NULL;
		temp_n->max_v=i.right;
		return temp_n;
	}
	return root;
}

struct tree* assign_max(struct tree* root)//this functions update the key max_v in the tree
{
	struct tree* temp=root;
	if(temp!=NULL)
	{
		temp->l_child=assign_max(temp->l_child);//first update values from bottom
		temp->r_child=assign_max(temp->r_child);
		if(temp->r_child==NULL && temp->l_child!=NULL)
		{
			temp->max_v=max(temp->value.right,temp->l_child->max_v);//value of max_v is maximum of max_v on either side compared with right value of the node
		}
		else if(temp->l_child==NULL && temp->r_child!=NULL)
		{
			temp->max_v=max(temp->value.right,temp->r_child->max_v);
		}
		else if(temp->l_child==NULL && temp->r_child==NULL) 	
		{
			temp->max_v=temp->value.right;
		}
		else
		{
			temp->max_v=max(temp->value.right,temp->l_child->max_v);
			temp->max_v=max(temp->max_v,temp->r_child->max_v);
		}
	}
	else
		return NULL;
	
	return root;
}

void insert(struct tree* root)
{
	int n,x_left,x_right;

	cout<<"Number of nodes you want to insert: ";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Left value of "<<i+1<<" node: ";
		cin>>x_left;
		cout<<"Right value of "<<i+1<<" node: ";
		cin>>x_right;
		while(x_right<x_left)
		{
			cout<<"How be right value of interval smaller than left...Give right value again: ";
			cin>>x_right;
		}
		struct interval a;
		a.left=x_left;
		a.right=x_right;
		root=build_tree(root,a);
	}
	root=assign_max(root);
	cout<<"Building an interval tree.....Tree builded successfully :)"<<endl;
	diff_functions(root);	
}

void print(struct tree* root)
{
	struct tree* temp=root;
	
	if(temp!=NULL)
	{
		print(temp->l_child);
		cout<<"("<<temp->value.left<<" "<<temp->value.right<<")"<<" ";
		print(temp->r_child);
	}
}

void print_max(struct tree* root)
{
	struct tree* temp=root;
	if(temp!=NULL)
	{
		print_max(temp->l_child);
		cout<<temp->max_v<<" ";
		print_max(temp->r_child);
	}
}

bool isOverlapThere(interval i1, interval i2)//finds whether two intervals overlap or not
{
    if (i1.left <= i2.right && i2.left <= i1.right)
        return true;
    return false;
}

interval search(struct tree *root, interval i) // search for an interval in a tree
{
	struct tree* temp=root;
   
    if (temp == NULL) 
	{
		cout<<"Tree does not contain this interval"<<endl;
		interval k;
		k.left=INT_MIN;
		k.right=INT_MIN;
		return k;
	}
 
    
    if (isOverlapThere(temp->value,i))
        return temp->value;//if overlap is there return this value
 
   
    if (temp->l_child != NULL && temp->l_child->max_v >= i.left)
        return search(temp->l_child,i);//if l_child max is greater then definitely an overlap in left(if there is any overlap)
 
    
    return search(temp->r_child,i);//else check for overlap in right
}


struct tree* find_node_parent(struct tree * root,interval i)
{//find parent of node with articular interval value
	struct tree* temp=root;
	struct tree* temp_parent=NULL;	
   
    if (temp == NULL) 
	{
		cout<<"Tree does not contain this interval"<<endl;
		return NULL;
	}
	
	else if(temp->value.left==i.left&&temp->value.right==i.right)
 	{
 		cout<<"Sorry you can not delete the root node"<<endl;
		return NULL;
	}
    else
    {
    	while(temp!=NULL && (temp->value.left!=i.left||temp->value.right!=i.right))
    	{
    		temp_parent=temp;
    		if(temp->l_child!=NULL && i.left<temp->value.left)//if small look in left half
				temp=temp->l_child;
			else
				temp=temp->r_child;	//else in right half
		}
		if (temp == NULL) 
		{
			cout<<"Tree does not contain this interval"<<endl;
			return NULL;//if not found
		}
	}
	return temp_parent;
}

struct tree* find_largest(struct tree* root)
{
	//finds largets left valued node in a tree
	struct tree* temp=root;
	while(temp->r_child!=NULL)
		temp=temp->r_child;
	
	return temp;
}

struct tree* Delete_i(struct tree * root, interval i)
{//deletes a node
	struct tree* temp_parent=new tree;

	if(find_node_parent(root,i)!=NULL)
	{
		temp_parent=find_node_parent(root,i);
		struct tree* temp_del=NULL;
		int relation=1;	//node to be deleted is located on left of parent
		if(i.left<temp_parent->value.left)
			temp_del=temp_parent->l_child;
		else 
		{
			temp_del=temp_parent->r_child;
			relation=2;	//node to be deletd is located on right of parent
		}	
		
		if(temp_del->l_child==NULL && temp_del->r_child==NULL)	
		{//deletion of leaf node
			if(relation==1)
				temp_parent->l_child=NULL;
			else 
				temp_parent->r_child=NULL;
	
			return root;
		}
		
		else if(temp_del->l_child==NULL && temp_del->r_child!=NULL)	
		{	//deletion of one sided node(right sided
			if(relation==1)	
				temp_parent->l_child=temp_del->r_child;//assign temp_del's right child to trmp_del's position
			else 
				temp_parent->r_child=temp_del->r_child;
			return root;
		}
		
		else if(temp_del->l_child!=NULL && temp_del->r_child==NULL)	
		{	//deletion of one sided node(left sided)
			if(relation==1)	
				temp_parent->l_child=temp_del->l_child;//assign temp_del's left child to trmp_del's position
			else 
				temp_parent->r_child=temp_del->l_child;
			return root;
		}
		else
		{//there are children on both sides of temp_del
				struct tree* replace_del=find_largest(temp_del->l_child);//find largest node in left subtree of temp_del and replace temp_del with it
				
				replace_del->r_child=temp_del->r_child;
				if(replace_del==temp_del->l_child)
				{
					replace_del->l_child=NULL;
				}
				else
					replace_del->l_child=temp_del->l_child;
				if(relation==1)	
					temp_parent->l_child=replace_del;
				else 
					temp_parent->r_child=replace_del;
				return root;
		}
	}
	else
	{
		return NULL;//if parent is null ...return null
	}
}

void diff_functions(struct tree* root)
{//continuously running function to perform different operations on tree
	int response;
		cout<<"Welcome to Interval-Tree.\nWhat operation do you want to perform?\n1. Insert \t2. Delete \t3.Search \t4.Display(Inorder)"<<endl;
		cin>>response;
		if(response==1)//insertion
			insert(root);
		else if(response==2)//deletion
		{
			int int_left,int_right;
			cout<<"Which interval to delete: ";
			print(root);
			cout<<endl;
			cout<<"Give left val: ";
			cin>>int_left;
			cout<<"Give right val: ";
			cin>>int_right;
			interval i;
			i.left=int_left;
			i.right=int_right;
			struct tree* temp=Delete_i(root,i);
			if(temp!=NULL)
			{
				root=temp;
				root=assign_max(root);
			}
			diff_functions(root);
		}
			
		else if(response==3)//searching for an interval
		{
			int int_left,int_right;
			cout<<"Enter lower limit: ";
			cin>>int_left;
			cout<<"Enter higher limit: ";
			cin>>int_right;
			while(int_right<int_left)
			{
				cout<<"How be right value of interval smaller than left...Give right value again: ";
				cin>>int_right;
			}
			struct interval i;
			i.left=int_left;
			i.right=int_right;
			if(search(root,i).left!=INT_MIN)
			{
				cout<<"Your data is overlapping with node: ";
				cout<<"("<<search(root,i).left<<" "<<search(root,i).right<<")"<<endl;
			}
			diff_functions(root);	
		}
		else//displaying in order
		{
			cout<<"Node Values: ";
			print(root);
			cout<<endl;
			cout<<"Max values corresponding to node: ";
			print_max(root);
			cout<<endl;
			diff_functions(root);
		}
}
int main()
{//main function
		struct tree * root  = NULL;	
		diff_functions(root);
}
