#include <iostream>
#include <string>
#define MAX 10
#define INF 999

using namespace std;

class Graph {
	private:
		int cost[MAX][MAX];
		int cities;
		string cityName[MAX];

	public:
		Graph() : cities(0) { }

		void create();
		void display();

int prims(){
    int near[MAX]={0},t[MAX][2];
    int stv;
    string city;
    cout<<"Enter starting city: ";
    cin>>city;
    for(int i=0;i<cities;i++){
        if(cityName[i]==city){
            stv=i;
            break;
        }       
    }
    int mincost=0;
    near[stv]=-1;
    
    for (int i = 0; i < cities; i++) {
        if(i!=stv){
            near[i]=stv;
        }
    }
    int r=0; // for row of near array
    
    for (int i = 1; i < cities; i++) {
        int min=INF;
		int j=-1;
        for (int k = 0; k < cities; k++) {
            if(near[k]!=-1 && cost[k][near[k]]<min){
                min=cost[k][near[k]]; //finding minimum cost edge
                j=k; 
            }
        }
        t[i-1][0]=j;
        t[i-1][1]=near[j];
        mincost= mincost+cost[j][near[j]];
        near[j]=-1;
        

        for (int k = 0; k < cities; k++) {
            if(near[k]!=-1 && cost[k][near[k]]>cost[k][j]){
                near[k]=j;
            }
        }
    }
	cout<<"Edges of minimum cost spanning tree are: "<<endl;
	for (int i = 0; i < cities-1; i++) {
		cout<<cityName[t[i][0]]<<" - "<<cityName[t[i][1]]<<endl;
	}
	return mincost;
}
};


void Graph::create() {
	cout << "\nEnter number of cities: ";
	cin >> cities;
	cout << "\n";	
	
	cout << "Enter the names of the cities:" << endl;
    	for (int i = 0; i < cities; i++) {
        	cout << "City " << i + 1 << ": ";
        	cin >> cityName[i];
    	}
    	cout << "\n";
  
	for (int i = 0; i < cities; i++) { 
	        for (int j = 0; j < cities; j++) {
			if (i == j)
				cost[i][j] = 0;
		        else
                		cost[i][j] = INF; 
       	 	}
    	}
   
	for (int i = 0; i < cities; i++) {
        	for (int j = i + 1; j < cities; j++) {
            		char edge;
            		cout << "Is there an edge between city " << cityName[i] << " and city " << cityName[j] << "? (y/n): ";
            		cin >> edge;

            		if (edge == 'y' || edge == 'Y') {
                		cout << "Enter cost between city " << cityName[i] << " and city " << cityName[j] << ": ";
                		cin >> cost[i][j];
                		cout << "\n";
                		cost[j][i] = cost[i][j];
            		}
        	}
    	}
}


void Graph::display() {
	cout << "\nAdjacency Matrix:\n";
	cout << "\t";
	
	for (int i = 0; i < cities; i++) {
        	cout << cityName[i] << "\t";
    	}
    	cout << endl;

    	for (int i = 0; i < cities; i++) {
        	cout << cityName[i] << "\t";
        	for (int j = 0; j < cities; j++) {
            		if (cost[i][j] == INF)
                		cout << "INF\t";
            		else
                		cout << cost[i][j] << "\t";
        	}
        	cout << endl;
    	}
}






int main() {
	Graph g;
    	g.create();
    	g.display();
        cout<<"Minimum cost: "<<g.prims()<<endl;
	

    	return 0;
}