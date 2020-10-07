#include "struct.h"

//create the Scene
Scene* createScene(char* fileName, ...);

//create the object
Object* createObject(char* filename);

//Create a vertex in the Object
void createVertex(char* str, Object* object);

//Create a face in the object
void createFace(char* str, Object* object);

//return the number of objects inside the program
int sizeScene(Scene* myScene);

//add scene to the linked list of the scenes
void addScene(Scene** scene, Object* myObject);

//saves a binary file made of all the scenes in the program
void saveBinary(FILE* f, Scene* scene);

//saves a text file made of all the scenes in the program
void saveText(FILE* f, Scene* scene);

//decide which save is running and manage it to the right file format
void saveScene(Scene* scene, char* fileName, enum FileType type);

//loads the scenes from a text file
Scene* loadText(FILE* f);

//loads the scenes from a binary file
Scene* loadBinary(FILE* f);

//decide which load to run and manage it to the right file format
Scene* loadScene(char* fileName, enum FileType type);

//transform an obj file to another obj file while making its vertex.x value mulitplied by 0.3
void transformObject(char* originalObjectFileName, char* deformedObjectFileName);

//calculates the number of faces in a single object 
void printFaces(Object* ptr, void* numberOfTriangularFaces);

//returns the number of vertexes in a single object 
void printVertexes(Object* ptr, void* numberOfVertexes);

//calculates the distance between 2 points in a triangle
double calculateDist(Vertex* one, Vertex* two);

//calculates the area of all triangles in a single object
void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces);

//free all the memory which was used in the program
void freeScene(Scene* scene);