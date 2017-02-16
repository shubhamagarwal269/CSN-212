#include<bits/stdc++.h>

using namespace std;

struct tree
{
	struct tree * l_child;
	struct tree * r_child;
	int val_left;
	int val_right;
	int max_v=INT_MIN;
};

void diff_functions(struct tree** node);
void build_tree(struct tree** node,int value_left,int value_right)
{
	
	if((*node)!=NULL)
	{
		if((*node)->val_left<=value_left)
			build_tree(&((*node)->r_child),value_left,value_right);
		else
			build_tree(&((*node)->l_child),value_left,value_right);	
	}
	else
	{
		*node = ( struct tree * ) malloc ( sizeof ( struct tree ) ) ;
		(*node)->val_left=value_left;
		(*node)->val_right=value_right;
		(*node)->l_child=NULL;
		(*node)->r_child=NULL;
		(*node)->max_v=value_right;
	}
}

int num_of_nodes(struct tree** root,int ans)
{
	if(*root!=NULL)
	{
		ans= ans+1+num_of_nodes(&((*root)->r_child),ans)+num_of_nodes(&((*root)->l_child),ans);
		return ans;	
	}
	else
		return 0;
}



void print_left(struct tree** root)
{
	
	if(*root!=NULL)
	{
		print_left(&((*root)->l_child));
		cout<<(*root)->val_left<<" ";
		print_left(&((*root)->r_child));
	}
}

void print_right(struct tree** root)
{
	
	if(*root!=NULL)
	{
		print_right(&((*root)->l_child));
		cout<<(*root)->val_right<<" ";
		print_right(&((*root)->r_child));
	}
}

void print_max(struct tree** root)
{
	
	if(*root!=NULL)
	{
		print_max(&((*root)->l_child));
		cout<<(*root)->max_v<<" ";
		print_max(&((*root)->r_child));
	}
}

void assign_max(struct tree** node)
{
	if((*node)!=NULL)
	{
		assign_max(&((*node)->l_child));
		assign_max(&((*node)->r_child));
		if((*node)->r_child==NULL && (*node)->l_child!=NULL)
		{
			(*node)->max_v=max((*node)->val_right,(*node)->l_child->max_v);
		}
		else if((*node)->l_child==NULL && (*node)->r_child!=NULL)
		{
			(*node)->max_v=max((*node)->val_right,(*node)->r_child->max_v);
		}
		else if((*node)->l_child==NULL && (*node)->r_child==NULL) 	
		{
			(*node)->max_v=(*node)->val_right;
		}
		else
		{
			(*node)->max_v=max((*node)->val_right,(*node)->l_child->max_v);
			(*node)->max_v=max((*node)->max_v,(*node)->r_child->max_v);
		}
	}
}

void display(struct tree** node)
{
	if(*node==NULL)
		cout<<"Sorry but tree is empty."<<endl;
	else
	{
		cout<<"Printing left, right and max values of nodes using inorder traversal"<<endl;
		cout<<"Left values: ";
		print_left(node);
		cout<<endl;
		cout<<"Right values: ";
		print_right(node);
		cout<<endl;
		cout<<"Max values: ";
		print_max(node);
		cout<<endl;
	}
	diff_functions(node);
}

void insert(struct tree** node)
{
	int n,x_left,x_right;
	cout<<"Number of nodes you want to insert: ";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cout<<"Left value of "<<i+1<<" node: ";
		cin>>x_left;
		cout<<endl;
		cout<<"Right value of "<<i+1<<" node: ";
		cin>>x_right;
		cout<<endl;
		build_tree(node,x_left,x_right);	
	}
	assign_max(node);
	cout<<"Building an interval tree.....Tree builded successfully :)"<<endl;
	diff_functions(node);	
}


struct tree** find(struct tree ** root)  // node with minimum key in the subtree rooted at root
{
  while(((*root)->l_child) != NULL) 
  	(*root) = (*root)->l_child;
  
  return root;
}

struct tree* Delete_i(struct tree ** root, int int_left)
{
  if((*root) == NULL) 
  	return *root;
  else if(int_left < (*root)->val_left) 
  	(*root)->l_child = Delete_i(&((*root)->l_child),int_left);
  else if(int_left > (*root)->val_left) 
  	(*root)->r_child = Delete_i(&((*root)->r_child), int_left);
  else 
  {
    if(((*root)->l_child) == NULL && &((*root)->r_child) == NULL)
	{
      delete root;
      *root = NULL;
    } 
	else if(((*root)->l_child) == NULL)
	{
      struct tree** temp = root;
      (*root) = (*root)->r_child;
      delete temp;
    } 
	else if(((*root)->r_child) == NULL)
	{
      struct tree** temp = root;
      (*root) = (*root)->l_child;
      delete temp;
    } 
	else
	{
      struct tree** temp = find((&(*root)->r_child));
     (*root)->val_left = (*temp)->val_left;
      (*root)->max_v=max(max((*root)->r_child->max_v,(*root)->l_child->max_v),(*root)->val_right);
      (*root)->r_child = Delete_i(&((*root)->r_child), (*temp)->val_left);
    }
  }
  return *root;
}

bool isOverlapThere(int i1_left,int i1_right, int i2_left,int i2_right)
{
    if (i1_left <= i2_right && i2_left <= i1_right)
        return true;
    return false;
}

int search(struct tree **root, int int_left, int int_right)
{
   
    if (*root == NULL) 
	{
		cout<<"Tree is empty"<<endl;
	};
 
    
    if (isOverlapThere((*root)->val_left,(*root)->val_right,int_left,int_right))
        return (*root)->val_left;
 
   
    if ((*root)->l_child != NULL && (*root)->l_child->max_v >= int_left)
        return search((&(*root)->l_child), int_left,int_right);
 
    
    return search((&(*root)->r_child), int_left,int_right);
}
 

void diff_functions(struct tree** node)
{
	int response;
		cout<<"Welcome to Interval-Tree.\nWhat operation do you want to perform?\n1. Insert \t2. Delete \t3.Search \t4.Display(Inorder)"<<endl;
		cin>>response;
		if(response==1)
			insert(node);
		else if(response==2)
		{
			int int_left;
			cout<<"Which interval to delete: ";
			cin>>int_left;
			*node=Delete_i(node,int_left);
		}
			
		else if(response==3)
			{
				int int_left,int_right;
				cout<<"Enter lower limit: ";
				cin>>int_left;
				cout<<"Enter higher limit: ";
				cin>>int_right;
				cout<<"Your data is present in node with left value: ";
				cout<<search(node,int_left,int_right)<<endl;
				diff_functions(node);
			}
		else
			display(node);
}
int main()
{
		int n,x_left,x_right;
		struct tree * root  = NULL;	
		diff_functions(&root);
}
