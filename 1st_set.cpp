#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Node
{
	int value;
	Node* next;	
};

class List
{
public:
	Node* head = NULL;


	bool isEmpty() {
		if (head != NULL){
			return false;
		}
		else{
			return true;
		}
		
	}
	void insert_Tail(int num)	//***** Inserting node at end of list **********/
	{
		Node* newNode = new Node;
		newNode->value = num;
		Node* temp = new Node;
		bool f = isEmpty();
		if (f)
			head = newNode;
		else
		{
			Node* nNode = head;

			while (nNode->next != NULL)
			{
				nNode = nNode->next;
			}

			nNode->next = newNode;
		}
	}

	Node* get_head() {
		return head;
	}

	void deleteTailNode() {	// Delete from end
		Node* tempNode = head;
		Node* prevNode = NULL;

		while (tempNode->next != NULL) {
			prevNode = tempNode;
			tempNode = tempNode->next;
		}

		if (prevNode == NULL) {

			head = tempNode->next;
			delete tempNode;
		}

		else {
			prevNode->next = tempNode->next;
			delete tempNode;
		}
	}

	void listHeadDelete() //delete from start
	{
			Node* tempNode = head;
			head = head->next;
			delete tempNode;
		
	}

	int get_LSize() {
		Node* tNode = new Node;
		tNode = head;
		Node* curr_Node = new Node;
		int cnt = 0;
		while (tNode != NULL) {
			tNode = tNode->next;
			cnt++;
		}
		return cnt;
	}

	void PrintList()	// Display the list
	{
		Node* tNode = head;

		while (tNode != NULL) {
			cout << tNode->value << "-- , --";
			tNode = tNode->next;
		}
		cout << "-->" << endl;
	}
};

class Graph
{
public:
	// vertices;
	int maximum = 7000;
	int vrtx_added = 0;
	int*  vertices = new int[maximum];
	List *adj = new List[maximum];
	
	// Loading vertices from file

	 //Load edge from file
	void Store_dir_edges(string file)	{
		fstream inp;
		inp.open(file, ios::in);
		string line = "";
		string previous = "";

		getline(inp, line);getline(inp, line);
		getline(inp, line);getline(inp, line);
		
		while (getline(inp, line)){
			string vertex = "";
			string edg = "";
			bool tag = false;

			for (int i = 0; line[i] != '\0'; i++){
				if (line[i] == ' ' || line[i] == '\t' ){
					tag = true;
					continue;
				}

				if (tag == true){edg = edg + line[i];}
				else {
					vertex = vertex + line[i];}
			}
			string empty = "";
			if (edg != empty)
			{
				int v = stoi(vertex);
				int e = stoi(edg);
				AddEdg(v, e);
			}
		}
	}

	void Store_Vrtx(string f_name) {
		fstream f_inp;
		f_inp.open(f_name, ios::in);
		string line = "";
		string prev = "";

		getline(f_inp, line); getline(f_inp, line); getline(f_inp, line); getline(f_inp, line);

		while (getline(f_inp, line)) {
			string vertex = "";

			for (int i = 0; line[i] != '\t' && line[i] != '\0'; i++) {
				vertex = vertex + line[i];
			}

			if (prev != vertex) {
				int vrtx = stoi(vertex);
				vertices[vrtx_added] = vrtx;
				vrtx_added = vrtx_added + 1;
				prev = vertex;
			}
		}
	}

	//insert edge in graph
	void AddEdg(int source, int sink) {	
		
		for (int i = 0; i < vrtx_added; i++){
			if (vertices[i] == source){
				for (int j = 0; j < vrtx_added; j++) {

					if (vertices[j] == sink){
						adj[i].insert_Tail(sink); 
						return;
					}
				}
				
				vertices[vrtx_added] = sink;
				vrtx_added = vrtx_added + 1;
				AddEdg(source, sink);
				return;
			}
		}
		return;
	}

	void display()
	{
		int* ptr = &vrtx_added;
		
		for (int i = 0; i < vrtx_added; i++) {
			cout << "-:- " << ptr[i];
			adj[i].PrintList();
			cout <<"\n";
		}
	}

//-------------------------------------------------------------------------------------------------------------------------
	int Brdg()
	{
		bool* Is_visitd;
		int* disc_time;
		int* lwvalue;
		int* vPrnt;
		int cnt_brdgs = 0;
		Is_visitd = new bool[vrtx_added];
		disc_time = new int[vrtx_added];
		 lwvalue = new int[vrtx_added];
		vPrnt = new int[vrtx_added];	

		for (int i = 0; i < vrtx_added; i++) {
			vPrnt[i] = -1;
			Is_visitd[i] = false;
		}
		for (int i = 0; i < vrtx_added; i++) {
			bool flag = Is_visitd[i];
			if (flag)
			{
				BridgsU(i, Is_visitd, disc_time, lwvalue, vPrnt, cnt_brdgs);
			}
			else
			{
				//later
			}
		}

		return cnt_brdgs;
	}
	
	void BridgsU(int ind, bool* Isvisited, int* disctime, int* lwval, int* vparent, int& cnt)
	{
		static int Ntime = 0;
		Isvisited[ind] = true;
		Ntime++;
		disctime[ind] = Ntime;
		lwval[ind] = Ntime;

		Node* tempNode = adj[ind].get_head();

		while (tempNode != NULL)
		{
			for (int i = 0; i < vrtx_added; i++) {
				if (tempNode->value == vertices[i]) {
					if (vertices[i] != vertices[vparent[ind]]) {
						if (lwval[ind] > disctime[i])
						{
							lwval[ind] = disctime[i];
						}
					}
					else if (!Isvisited[i]) 
					{
						vparent[i] = ind ;
						BridgsU(i, Isvisited, disctime, lwval, vparent, cnt);

						if (disctime[ind] < lwval[i]) {
							cnt++;
						}
						if (lwval[ind] > lwval[i]) 
						{
							lwval[ind] = lwval[i];
						}
					}
					break;
				}
			}

			tempNode = tempNode->next;
		}
	}


	void indegreedistribution(int limit) {

		cout << "Vertex\tIn degree" << endl;

		for (int i = 0; i < limit - 1; i++)
		{
			cout << vertices[i] << "\t" << indegree(vertices[i]) / (float)vrtx_added << endl;
		}
	}


	int sourceNodes() {
		int count = 0;

		for (int i = 0; i < vrtx_added; i++)
		{
			
			if (indegree(vertices[i]) == 0)
			{
				count++;
			}
		}

		return count;
	}
	
	int indegree(int source) {
		int cnt = 0;
		for (int i = 0; i < vrtx_added; i++) {
			Node* tNode = adj[i].get_head();

			while (tNode != NULL) {

				if (tNode->value == source) {
					cnt = cnt + 1;
				}

				tNode = tNode->next;
			}
		}

		return cnt;
	}
};

/*

}*/

//-----------------------_______________________________________-----------------------//


int main()
{
	Graph Gr1;
	int Arr[7000];
	List adjacncylist[7000];
	int n = 0;
	string path = "fsts/CA-GrQc.txt";
	Gr1.Store_Vrtx(path);
	for (int n = 0; n < 10; n++)
	{
		cout<<"\t";
	}
	cout << "Graph Implimentation" << endl;

	Gr1.Store_dir_edges(path);


	int ch = 0;

	cout << "Choose one of the following \n 1 to display part 1\n 2 to display part 2\n 3 to display part 3\n";
	cin >> ch;

	while (1) {
		if (ch == 1) {
			cout << "**1st PART**" << endl << endl;
			cout << Gr1.sourceNodes() << endl;
			//cout << Gr1.sinkNodes() << endl;
			//cout << Gr1.isolatedNodes() << endl;
			//cout << Gr1.BridgsU() << endl;Gr1.
			//cout << Gr1.articulation() << endl;
			cout << "\n\t\tShortest path length distribution is :\n\n\n";
			//g.displayShortestPaths(30);
			//cout << g.finddiameter() << endl;
		}

		if (ch == 2) {
			cout << "**2nd PART**" << endl << endl;
			cout << "\nIn degree distribution is as follows (First 30):\n\n";
			//g.indegreedistribution(30);
			cout << "\nOut degree distribution is as follows (First 30):\n\n";
			//g.outdegreedistribution(30);

		}

		if (ch == 3) {
			cout << "**3rd PART**" << endl << endl;

		}

		else {
			cout << "Wrong output" << endl;
			break;
		}
	}
	return 0;

}