/* This is a code for COMP 201 assignment 3.
 * In this code, Floyd-Warshall algorithm is implemented
 * to find the shortest paths between any two cities
 * in a given graph of cities.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lookup_string(char *); 
const int INF = 1e7;  

/* Array of vertices. 
 * Each element of the str array contains a city name and 
 * its index in str becomes the city's numeric id.
 */
typedef struct vertices 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of cities in the array
	int city_count;
	// This attribute is the array of city names
	char (* str)[30];
} 
vertices;

/* Array of edges. 
 * Each element of the edge array contains the ids of two cities 
 * connected directy by a road and the length of the road.
 */
typedef struct edges 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of roads in the array
	int edge_count;
	// This attribute is the array of road information
	int (* edge)[3];
} 
edges;

vertices cities;

edges roads;

/* A two-dimensional array that shows 
 * the length of the shortest path connecting 
 * any two cities.
 */
int **city_graph;

/* A two-dimensional array that shows the direction 
 * to the shortest path between any two cities.
 */
int **shortest_paths;

/* A function that implements Floyd-Warshall algorithm. 
 * This algorithm finds the shortest path between 
 * any two vertices in a given graph.
 */
void floydWarshall()  
{  
	for (int k = 0; k < cities.city_count; k++) 
	{  
		for (int i = 0; i < cities.city_count; i++) 
		{  
			for (int j = 0; j < cities.city_count; j++) 
			{  

				// We cannot cross a road that doesn't exist  
				if ((city_graph[i][k] == INF) || (city_graph[k][j] == INF))  
				{
					continue;
				}  

				if (city_graph[i][j] > (city_graph[i][k] + city_graph[k][j])) 
				{  
					city_graph[i][j] = city_graph[i][k] + city_graph[k][j];  
					shortest_paths[i][j] = shortest_paths[i][k];  
				}  
			}  
		}  
	}  
} 

/* A function that initializes the values in 
 * city_graph and shortest_paths arrays.
 */
void initialise()  
{  
	for (int i = 0; i < cities.city_count; i++) 
	{  
		for (int j = 0; j < cities.city_count; j++) 
		{	

			// No edge between node i and j  
			if (city_graph[i][j] == INF)  
			{
				shortest_paths[i][j] = -1;
			}  
			else
			{
				shortest_paths[i][j] = j;
			}  
		}  
	}  
}

/* A function that inserts the name of a new city 
 * to the cities array.
 */
int insert_to_cities(char str[30]) 
{
	// Write your code here
	// Check if the city name already exists in the array 
	// If it does, return the array index of the city 
	int index = lookup_string(str);
	// If the city name doesn't exist, it is inserted to the cities array, and
	// return the array index of the city
	if(index == -1){
		if (cities.size < (cities.city_count + 1) * sizeof (char *)){
		cities.str = realloc(cities.str, (cities.city_count + 1) * sizeof (char [30]));
		cities.size = (cities.city_count + 1) * sizeof (char *);
	  }
		strcpy(*(cities.str + cities.city_count), str);
		index = cities.city_count;
		cities.city_count++;
		return index;
	}
	return index;
	// If the dynamically allocated size of cities array is not large enough, 
	// the size of cities array is enlarged and the city name is inserted 
	// to the newly added region


	// Return the array index of the city.
}
/* A function that inserts the road
 * to the road array
 */
insert_to_road(int fCityIndex, int sCityIndex, int dist){
	if (roads.size < (roads.edge_count + 1) * sizeof (int [3])){
		printf("The size of edge array is not enough\n");
		roads.edge = realloc(roads.edge, (roads.edge_count + 1) * sizeof (int [3]));
		roads.size = (roads.edge_count + 1) * sizeof (int [3]);
	}
	roads.edge[roads.edge_count][0] = fCityIndex;
	roads.edge[roads.edge_count][1] = sCityIndex;
	roads.edge[roads.edge_count][2] = dist;
	roads.edge_count++;
}
/* A function that looks up if a city name
 * is already in the cities array. 
 */
int lookup_string(char str[30]) 
{
	for(int i = 0; i < cities.city_count; i++) {
		if(strncmp(str, cities.str[i], 30) == 0)
			return i;
	}
	printf("city %s is not found\n", str);
	return -1;
}

void printPath(int u, int v)  
{  
	// Write your code here 
	if (u == v) {
		printf("%s\n", cities.str[u]);
		return;
	}
	printf("%s ", cities.str[u]);
	printPath(shortest_paths[u][v], v); 
} 

int main(int argc, char *argv[])
{
	// Write your code here

	// Allocate memory regions dynamically to cities array 
	// and roads array.
	cities.str = malloc(10 * sizeof(char[30]));
	cities.city_count = 0;
	cities.size = sizeof(char[30]);
	roads.edge = malloc(10 * sizeof(char[30]));
	roads.edge_count = 0;
	roads.size = sizeof(char[30]);
	// Read and parse the input file. Insert the city names to cities array.
	// The index of the city name in the cities array becomes the city id. 
	// Insert city ids and road lengths to roads array.
	FILE *input;
	input = fopen("input.txt", "r");
	if(input == NULL){
		printf("Input file couldn't open\n");
		return 0;
	}
	char line[50];
	while(fgets(line,50,input) != NULL ){ 
		if(strcmp(line, "\n")){ //to check the line is not empty
			char *fCity = strtok(line," ");//first city
			int fCityIndex = insert_to_cities(fCity);
		
			char *sCity = strtok(NULL, " "); //second city
			int sCityIndex = insert_to_cities(sCity);

			int dist = atoi(strtok(NULL, " ")); //length of the road
			insert_to_road(fCityIndex, sCityIndex, dist);
		}
	}
	// Allocate memory regions dynamically to city_graph, 
	// distance, and shortest_paths arrays.
	city_graph = (int**) malloc(cities.city_count * sizeof (int*) );
    for (int i = 0; i < cities.city_count; i++) {
        city_graph[i] = (int *) malloc(cities.city_count * sizeof (int));
		for(int j =0; j< cities.city_count; j++){
			if(i != j){
				city_graph[i][j] = INF; //all the roads will be INF between two cities at the beginning
			}
			else{
				city_graph[i][j] = 0; //there is no road from a city to itself
			}
		}
	}
	shortest_paths = (int**) malloc(cities.city_count * sizeof (int*) );
    for (int i = 0; i < cities.city_count; i++){
        shortest_paths[i] = (int *) malloc(cities.city_count * sizeof (int));
	}
	// Initialize the values in city_graph array with road lengths, 
	// such that the value in city_graph[i][j] is the road length 
	// between cities i and j if these cities are directly connected 
	// by a road 
	// For cities m and n that are not connected directly by a road, 
	// the value in city_graph[m][n] will be INF, 
	// which is a large value like 10M, 
	// that is assumed to be infinite. 
	for(int a = 0; a<roads.edge_count; a++){
		//add roads to city graph from roads struct
		int fCity = roads.edge[a][0];
		int sCity = roads.edge[a][1];
		int dist = roads.edge[a][2];

		city_graph[fCity][sCity] = dist;
		city_graph[sCity][fCity] = dist;
	}
	initialise();
	floydWarshall();
	while(1) {
		// prompt user to enter two city names
		char first[30];
		char second[30];
		printf("Write \"end\" to end the program\nEnter the cities: ");
		scanf("%s",first);
		if(!(strcmp(first, "end"))) break;
		scanf("%s", second);
		//search for city index
		int fIndex = lookup_string(first);
		int sIndex = lookup_string(second);
		// print the shortest path between the two cities
		if(fIndex != -1 && sIndex != -1){ //check the cities are in the graph to avoid segmentation fault
			printf("Output:\n");
			printPath(fIndex, sIndex);
			// print the length of the path
			printf("%d\n\n", city_graph[fIndex][sIndex]);
		}
	}
	free(cities.str);
	free(roads.edge);

	for (int i = 0; i < cities.city_count; i++)
		free(city_graph[i]);
	free(city_graph);

	for (int i = 0; i < cities.city_count; i++)
		free(shortest_paths[i]);
	free(shortest_paths);



	fclose(input);
	printf("Program ended");
	return 0;	
}
