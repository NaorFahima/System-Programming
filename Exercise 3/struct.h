#pragma once

typedef struct {
	float x; // Coordinates of Vertex
	float y;
	float z;
} Vertex;



typedef struct {
	int size;	// Number of vertexes of the face
	int* vertex;	// Array of Ids of the vertexes
} Face;



typedef struct {
	// Array of all Vertexes
	int numberOfVertexes;
	Vertex* vertexes;
	// Array of all Faces
	int  numberOfFaces;
	Face* faces;
} Object;

typedef struct {
	Object* object;
	struct Scene* next;
} Scene;


enum FileType { TextFormat, BinaryFormat };
