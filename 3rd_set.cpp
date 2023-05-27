#include<iostream>
#include<iomanip>
#include<fstream>
#include<conio.h>
using namespace std;
//it will print a line

int MIN(int num1, int num2)
{
	if(num1<num2)
		return num1;
	else
		return num2;
}
struct node_for_stack
{
	int data;
	struct node_for_stack* link;
};

class Stack
{
	struct node_for_stack* top;
	public:
	bool isEmpty()	{return top == NULL;}
	void push(int data)
	{
		struct node_for_stack* temp;
		temp = new node_for_stack;
		if (!temp)
		{cout << "\nMemory Overflow";}
		temp->data = data;
		temp->link = top;
		top = temp;
	}
	
	int peek()
	{
		if (!isEmpty())
			return top->data;
		else
			return 0;
	}
	
	void pop()
	{
		struct node_for_stack *temp=new node_for_stack;
		if (isEmpty())
		{cout << "\nStack Underflow" << endl; return;}
		else
		{
			temp = top;
			top = top->link;
			temp->link = NULL;
		}
	}
	
	void display()
	{
		struct node_for_stack* temp=top;
		if (isEmpty())	{cout << "\nStack Underflow";	return;}
		
		while (temp != NULL)
		{
			cout << temp->data << " -> ";
			temp = temp->link;
		}
	}
	
	
	node_for_stack* find(int n)
	{
		struct node_for_stack* temp=top;
		if (isEmpty())	false;
		while (temp != NULL)
		{
			if(temp->data==n)
				return temp;
			temp = temp->link;
		}
		return NULL;
	}
	
	void Find_and_update_value(int n)
	{
		struct node_for_stack *temp=find(n);
		if(temp!=NULL) {temp->data=n; return;}
		else	{push(n);}
	}
		
};

struct node_for_list
{
	int num;
	int total;
	struct node_for_list* next=NULL;
};
class list
{	
	private:
		node_for_list *head,*tail;
		int size;
	public:
	list()	
	{
		tail=head=NULL; 
		size=0;
	}
	
	bool is_empty()	
	{
		return(head==NULL);
	}
	
	int get_Size()	
	{	
		return size;
	}
	
	node_for_list* get_tail() {return tail;}
	
	node_for_list* get_head() {return head;}
	
	void add_edge(int v1, int v2=-1)
	{	
		node_for_list *temp=new node_for_list;
		if(temp==NULL) 
		{
				cout<<"\nLink list over flow\n";	
				return;
		}

		temp->num=v1;
		
		if(v2!=-1) 
			temp->total=v2;
		
		if(head==NULL)	
		{	head=temp;
			tail=temp;	
			temp=NULL;
		}
		else	
		{	tail->next=temp; 
			tail=temp; 
			temp=NULL;
		}
		size++;		
	}
	
	node_for_list *find(int n)
	{
		node_for_list *temp=head;
		int count=1;
		while(temp!=NULL)
		{
			if(temp->num==n)
				return temp;
			temp=temp->next;
			count++;
		}
		return NULL;
	}

	
	void update(int n, int v, int inc=0)
	{
		node_for_list *temp=find(n);
		if(temp!=NULL) {  
			if(inc==1) temp->total++;
			else temp->total=v;
			return;
		}
		else	{add_edge(n,v);}
	}
	void diplay(char index='f')
	{
		node_for_list *temp=head;
		int count=1;
		while(temp!=NULL)
		{
			cout<<setw(8)<<temp->num;
			if(index=='y')	{
				cout<<setw(5)<<" --> ";
				cout<<setw(8)<<temp->total;
			}
			cout<<setw(3)<<left<<" | ";
			if(count%12==0) 	cout<<endl;
			temp=temp->next;
			count++;
		}
	}
};

struct node_for_graph
{
	int index;
	list l;
	struct node_for_graph *next=NULL;
};


class Graph          
{	
	private:
		int total_nodes;
		int total_edges;		
		node_for_graph *head,*tail;
	
	public:
		Graph()	
		{	
			tail=head=NULL; 
			total_nodes=0; 
			total_edges=0;
		}
	
	void Set_Total_edges(int edges) 
		{
			total_edges=edges;
		} 
		
	int get_Total_nodes()	
		{	
			return total_nodes;
		}
	
	int get_Total_edges()	
		{
			return total_edges;
		}
	
	node_for_graph* get_tail()	
		{return tail;}
	
	node_for_graph* get_head()	
		{return head;}
	
	bool is_empty()	
		{return(head==NULL);}
	
	node_for_graph* Find(int id)
	{
 		node_for_graph *temp=head;
		while(temp!=NULL)
		{
			if(temp->index==id)		
				return temp;
			temp=temp->next;
		}
		return NULL;
	}
	
	void add_edge(int v1,int v2=-10)
	{	
		node_for_graph *finded_node=Find(v1);
		if(finded_node!=NULL) 
		if(finded_node->index==v1)	
		{
			if(v2!=-10) finded_node->l.add_edge(v2);	
				return;
		}
			
		node_for_graph *temp=new node_for_graph;
			
		if(temp==NULL) {
			cout<<"\nLink list over flow\n";
			return;}
		
		temp->index=v1;
		if(v2!=-10)	temp->l.add_edge(v2);
		total_nodes++;
		if(head==NULL)	{head=temp;	tail=temp;	temp=NULL;}
		else {tail->next=temp; tail=temp; temp=NULL;}
	}

	void Display_All_nodes()
	{

		if(is_empty()) 
		{	cout<<"\n--No node available--\n";	
			return;
		}
		
		node_for_graph *temp=get_head();
		int lines=1;
		while(temp!=NULL)
		{
			cout<<setw(8)<<temp->index;
			cout<<setw(4)<<" - ";
			if(lines%14==0) cout<<endl;
			temp=temp->next;
			lines++;
		}
	}

};


list dist, low, present_in_stack;
list SSC_Size;
Stack myStack;
int Largest_SCC_Size=-1, count=0;
Graph SSC_SIZE_DISTRIBUTON;
Graph undirected_graph;
void BFS_Strongly_connected_componenet(int Source)
{
		static int time=0;
		dist.update(Source,time);
		low.update(Source,time);
		time++;
		myStack.push(Source);
		present_in_stack.add_edge(Source);
		struct node_for_list *temp_u=new node_for_list;
		if(undirected_graph.Find(Source)==NULL)	return;

	else
	{
		temp_u=undirected_graph.Find(Source)->l.get_head();
		while(temp_u!=NULL)
		{
			if(!(dist.find(temp_u->num)!=NULL))
			{
				BFS_Strongly_connected_componenet(temp_u->num);
				int Ans=MIN(low.find(Source)->total, low.find(temp_u->num)->total);
				low.update(Source,Ans);
			}
			
			else if(present_in_stack.find(temp_u->num)!=NULL){
				int Ans=MIN(low.find(Source)->total, dist.find(temp_u->num)->total);

				low.update(Source ,Ans);
			}
			temp_u=temp_u->next;
		}
	}
		struct node_for_list *l=low.find(Source);
		struct node_for_list *d=dist.find(Source);
		if(l!=NULL && d!=NULL) 
	
		if(l->total==d->total)
		{
			int Size=0;
			cout<<"\nSSC network =  ";
			while(myStack.peek()!=Source)
			{
				cout<<myStack.peek()<<"  ";
				Size++;
				present_in_stack.update(myStack.peek(),1);
				myStack.pop();
			}
			cout<<myStack.peek()<<"\n";
			Size++;
			present_in_stack.update(myStack.peek(),-1);
			if(Largest_SCC_Size<Size) Largest_SCC_Size=Size;
			SSC_Size.add_edge(++count,Size);
			myStack.pop();
		}
		
	}	
void Strongly_connected_componenet()
{
	node_for_graph *temp=undirected_graph.get_head();
	while(temp!=NULL)
	{

		if(!(present_in_stack.find(temp->index)))
			BFS_Strongly_connected_componenet(temp->index);
		temp=temp->next;

	}
	
}

void Size_distribution_for_SSC()
{
	
	node_for_list *temp=SSC_Size.get_head();
	int count=0;
	while(temp!=NULL)
		{
			SSC_SIZE_DISTRIBUTON.add_edge(temp->total,1);
			temp=temp->next;
			count++;
			}
	
	cout<<"\n Total Strongly connected networks  = "<<count<<endl;		
	
	cout<<"\nSize distribution of SCC Componenets\n\n";

	cout<<"\n\t\t\t\t\t\t\t\tnetwork"<<"---"<<" Size\n\n";
	cout<<endl;
	   int column=1;
		node_for_graph *size_temp=SSC_SIZE_DISTRIBUTON.get_head();
		while(size_temp!=NULL)
		{
			cout<<setw(7)<<size_temp->index;
			cout<<setw(5)<<left<<" --  ";
			cout<<setw(5)<<size_temp->l.get_Size();
			cout<<setw(4)<<"  | ";
			size_temp=size_temp->next;
			if(column%7==0) cout<<endl;
			column++;
			}		
}

void Out_degree()
{

	node_for_graph *new_node=undirected_graph.get_head();
	
	while(new_node!=NULL)
	{
		cout<<endl<<new_node->index<<" have following out degree \n";
		new_node->l.diplay();
		new_node=new_node->next;
	}

}


void Data_to_graph()
{
	ifstream myfile;
	myfile.open("CA-GrQc.txt", ios::in);
	if (myfile){
		cout<<"\nData fetched susccess fully : ";
	int total_edges=0;
	int from_node,to_node;
	
	//write a .............
	//getline()
	while(myfile>>from_node>>to_node)
	{	
		   	total_edges++;
		   	undirected_graph.add_edge(from_node,to_node);
	}
	undirected_graph.Set_Total_edges(total_edges);
}
	else{
		cout<<"\nError in loading file\n";
	}
	myfile.close();
}

main()
{
	Data_to_graph();
	Strongly_connected_componenet();   //must call for calculation data for part 12 and 13
	cout<<"\nLargest strongly connected network Size = "<<Largest_SCC_Size<<endl;   // for part 12
	Size_distribution_for_SSC();  //for part 13
//	undirected_graph.Display_All_nodes();
	cout<<"\nTotal nodes = "<<undirected_graph.get_Total_nodes();
	cout<<"\nTotal edges = "<<undirected_graph.get_Total_edges()<<endl;
	Out_degree();

}

