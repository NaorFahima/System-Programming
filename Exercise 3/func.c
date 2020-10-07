
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> 
#include "func.h"
#include "struct.h"
#include <math.h>


#define SIZE 150


void createVertex(char* str, Object* object) {
	Vertex* myVertex = (Vertex*)malloc(sizeof(Vertex)); //making memory space for the vertex
	if (myVertex == NULL) {
		printf("No Memory for Vertex *");
		return NULL;
	}
	strtok(str, " "); // move past the 'v'
	myVertex->x = atof(strtok(NULL, " ")); //getting the x value
	myVertex->y = atof(strtok(NULL, " ")); //getting the y value
	myVertex->z = atof(strtok(NULL, " ")); //getting the z value
	object->vertexes[object->numberOfVertexes++] = *myVertex; //adding the vertex to the object
	object->vertexes = (Vertex*)realloc(object->vertexes, sizeof(Vertex) * (object->numberOfVertexes + 1)); 
	if (object->vertexes == NULL) {
		printf("No memory for new Vertex * space");
		return NULL;
	}
}

void createFace(char* str, Object* object) {
	Face* myFace = (Face*)malloc(sizeof(Face)); //making memory space for the face array
	if (myFace == NULL) {
		printf("No memory for Face *");
		return NULL;
	}
	myFace->vertex = (int*)malloc(sizeof(int)); //making memory space for the vertex array inside a face
	if (myFace->vertex == NULL) {
		printf("No memory for vertex * in face");
		return NULL;
	}
	myFace->size = 0;
	int location = 0;
	int copy = 0;
	char numbers[SIZE];
	for (int i = 2; i < strlen(str); i++) //taking the vertexes indexes from the file where the f char is, ignoring all the slashes
	{
		if (str[i] == ' ') {
			copy = 0;
		}
		if (str[i] == '/' && copy == 0) {
			numbers[location++] = ' ';
			copy = 1;
		}
		if (copy == 0) {
			numbers[location++] = str[i];
		}
	}
	numbers[location - 1] = NULL;
	char* token = strtok(numbers, " ");
	while (token != NULL) {
		myFace->vertex[myFace->size++] = atoi(token); //adding the vertex to the face
		myFace->vertex = (int*)realloc(myFace->vertex, sizeof(int) * (myFace->size + 1));
		if (myFace->vertex == NULL) {
			printf("No memory for new vertex in Face");
			return NULL;
		}
		token = strtok(NULL, " ");
	}
	object->faces[object->numberOfFaces++] = *myFace; //adding the face to the object
	object->faces = (Face*)realloc(object->faces, sizeof(Face) * (object->numberOfFaces + 1));
	if (object->faces == NULL) {
		printf("No memory for new Face");
		return NULL;
	}
}

Object* createObject(char* filename) { 
	char strLine[SIZE];
	char type[2];
	Object* myObject = (Object*)malloc(sizeof(Object)); //making memory space for the object array
	if (myObject == NULL) {
		printf("No Memory for Object");
		return NULL;
	}
	myObject->numberOfVertexes = 0;
	myObject->numberOfFaces = 0;
	myObject->vertexes = (Vertex*)malloc(sizeof(Vertex)); //making memory space for the vertexes array inside the object
	if (myObject->vertexes == NULL) {
		printf("No Memory for object vertexes");
		return NULL;
	}
	myObject->faces = (Face*)malloc(sizeof(Face)); //making memory space for the faces array inside the object
	if (myObject->faces == NULL) {
		printf("No Memory for object faces");
		return NULL;
	}
	FILE* f = fopen(filename, "r"); //open the obj file with reading permission 
	if (f == NULL) {
		printf("Failed opening the file.");
		return NULL;
	}
	while (!feof(f)) { //if the file didnt reach the end, keep reading
		fgets(strLine, SIZE, f);
		type[0] = strLine[0]; //if found 'v' or 'f' in the file
		type[1] = strLine[1]; //takes the next char after 'v' or 'f' 
		if (type[1] == ' ') {
			switch (type[0]) {
			case 'v':
				createVertex(strLine, myObject);
				break;
			case 'f':
				createFace(strLine, myObject);
				break;
			default:
				break;
			}
		}
	}
return myObject;
}

int sizeScene(Scene* myScene) { //counts the number of scenes in the program
	Scene* temp = myScene;
	int counter = 0;
	if (temp == NULL) {
	return counter;
	}
	counter++;
	while (temp->next != NULL) {
		temp = temp->next;
		counter++;
	}
	return counter;
}

void addScene(Scene** scene, Object* myObject) {
	Scene* p, *q;
	p = (Scene*)malloc(sizeof(Scene)); //making memory space for a scene
	if (p == NULL) {
		printf("No Memory for Scene");
		return NULL;
	}
	p->object = myObject; //assigning p to be the current object
	p->next = NULL; 
	if (*scene == NULL) {
		*scene = p;
	}
	else {
		q = *scene; //assigning q to be the current scene
		while (q->next) q = q->next; //pushing q to be the last object
		q->next = p; //making the next object after q to be p
	}
}

Scene* createScene(char* fileName, ...) {
	Scene* head = (Scene*) malloc(sizeof(Scene)); //making memory space for a scene
	if (head == NULL) {
		printf("No Memory for scene");
		return NULL;
	}
	Scene* temp;
	va_list allObjects;
	char* currentName;
	va_start(allObjects, fileName); //create an array of all the files names
	currentName = fileName; //assign the current file
	head->object = createObject(currentName); //create an object from the current file
	head->next = NULL;
	currentName = va_arg(allObjects, char*); //assign the next file name
	while (currentName != NULL) { //if file name is not NULL , keep running
		temp = (Scene*)malloc(sizeof(Scene)); //making memory space for a scene
		if (temp == NULL) {
			printf("No memory for temp scene");
			return NULL;
		}
			temp->object = createObject(currentName); //create an object from the current file
			temp->next = head; 
			head = temp;
			currentName = va_arg(allObjects, char*);  //assign the next file name
	}
	va_end(allObjects); 
	return head;
}

void saveBinary(FILE* f, Scene* scene) { 
	Scene* temp = scene;
	int size = sizeScene(scene); //assign the number of objects in the program
	fwrite(&size, sizeof(int), 1, f); 
	while (temp != NULL) { //keep running until there is no object to write
		Object* myObject = temp->object;
		fwrite(&myObject->numberOfVertexes, sizeof(int), 1, f); //saves the number of vertexes in an object
		fwrite(myObject->vertexes, sizeof(Vertex), myObject->numberOfVertexes, f); //saves the vertexes values inside an object
		fwrite(&myObject->numberOfFaces, sizeof(int), 1, f); //saves the number of faces in an object
			for (int i = 0; i < myObject->numberOfFaces; i++) {
				fwrite(&myObject->faces[i].size, sizeof(int), 1, f); //saves the size of each face 
				fwrite(myObject->faces[i].vertex, sizeof(int), myObject->faces[i].size, f); //saves the vertex indexes array of each face
			}
		temp = temp->next; //go to next object
	}
}

void saveText(FILE* f, Scene* scene) {
	Scene* temp = scene;
	fprintf(f, "%d\n", sizeScene(scene)); //assign the number of objects in the program
	while (temp != NULL) { //keep running until there is no object to write
		Object* myObject = temp->object;
		fprintf(f, "%d\n", myObject->numberOfVertexes); //saves the number of vertexes in an object
		for (int i = 0; i < myObject->numberOfVertexes; i++) {
			fprintf(f, "v %f %f %f\n", myObject->vertexes[i].x, myObject->vertexes[i].y, myObject->vertexes[i].z); //saves the vertexes values inside an object
		}
		fprintf(f, "%d\n", myObject->numberOfFaces); //saves the number of faces in an object
		for (int i = 0; i < myObject->numberOfFaces; i++) {
			fprintf(f, "f %d ", myObject->faces[i].size); //saves the size of each face 
			for (int j = 0; j < myObject->faces[i].size; j++) {
				fprintf(f, "%d ", myObject->faces[i].vertex[j]); //saves the vertex indexes array of each face
			}
			fprintf(f, "\n"); 
		}
		temp = temp->next; //go to next object
	}
}


void saveScene(Scene* scene, char* fileName, enum FileType type) {
	char* str;
	if (type == BinaryFormat) { //checking what is the File Type
		str = "wb+";
	}
	else {
		str = "w+";
	}
	FILE* f = fopen(fileName, str);
	if (f == NULL) { //checking if the file opened correctly
		printf("Failed opening the file.");
		return NULL;
	}
	if (scene != NULL) { //if there is a scene then saves by the file type
		switch (type) {

		case 0: // TextFormat
			saveText(f, scene);
			break;

		case 1: // BinaryFormat
			saveBinary(f, scene);
			break;

		default:
			printf("Wrong File Format!");
			break;
		}
	}
	fclose(f);
}

Scene* loadText(FILE* f) {
	Scene* scene = NULL;
	int numOfObjects;
	char dummy;
	fscanf(f, "%d\n", &numOfObjects); //loads the number of objects
	for (int i = 0; i < numOfObjects; i++) {
		Object* myObject = (Object*)malloc(sizeof(Object)); //making memory space for object array
		if (myObject == NULL) {
			printf("myObject = null");
			return NULL;
		}
		fscanf(f, "%d\n", &myObject->numberOfVertexes); //loads the number of vertexes
		myObject->vertexes = (Vertex*)malloc((myObject->numberOfVertexes) * sizeof(Vertex)); //making memory space for vertex array of an object
		if (myObject->vertexes == NULL) {
			printf("myObject->vertexes = null");
			return NULL;
		}
		for (int i = 0; i < myObject->numberOfVertexes; i++) {
			fscanf(f, "%c %f %f %f\n", &dummy, &myObject->vertexes[i].x, &myObject->vertexes[i].y, &myObject->vertexes[i].z); //loads the vertex values of an object
		}
		fscanf(f, "%d\n", &myObject->numberOfFaces);
		myObject->faces = (Face*)malloc((myObject->numberOfFaces) * sizeof(Face)); //making memory space for face array of an object
		if (myObject->faces == NULL) {
			printf("No memory for object->vertexes");
			return NULL;
		}
		for (int i = 0; i < myObject->numberOfFaces; i++) {
			fscanf(f, "%c %d ", &dummy, &myObject->faces[i].size); //loads the number of vertexes indexes in a face
			myObject->faces[i].vertex = (int*)malloc(sizeof(int) * myObject->faces[i].size); //making memory space for vertex indexes array of a face
			for (int j = 0; j < myObject->faces[i].size; j++) {
				fscanf(f, "%d ", &myObject->faces[i].vertex[j]); //loads the vertexes indexes in a face
			}
			fscanf(f, "\n", &dummy);
		}
		addScene(&scene, myObject);
	}
return scene;
}

Scene* loadBinary(FILE* f) {
	Scene* scene = NULL;
	int numOfObjects;
	char dummy;
	fread(&numOfObjects, sizeof(int), 1, f); //loads the number of objects
	for (int i = 0; i < numOfObjects; i++) {
		Object* myObject = (Object*)malloc(sizeof(Object)); //making memory space for an object
		if (myObject == NULL) {
			printf("Object malloc wrong!");
			return NULL;
		}
		fread(&myObject->numberOfVertexes, sizeof(int), 1, f); //loads the number of vertexes
		myObject->vertexes = (Vertex*)malloc((myObject->numberOfVertexes) * sizeof(Vertex)); //making memory space for vertex array of an object
		if (myObject->vertexes == NULL) {
			printf("vertexes malloc wrong!");
			return NULL;
		}
		fread(myObject->vertexes, sizeof(Vertex), myObject->numberOfVertexes, f);  //loads the vertex values of an object
		fread(&myObject->numberOfFaces, sizeof(int), 1, f); //loads the number of faces of an object
		myObject->faces = (Face*)malloc((myObject->numberOfFaces) * sizeof(Face)); //making memory space for face array of an object
		if (myObject->faces == NULL) {
			printf("Faces malloc wrong!");
		}
		for (int i = 0; i < myObject->numberOfFaces; i++) {
			fread(&myObject->faces[i].size, sizeof(int), 1, f); //loads the number of vertexes indexes in a face
			myObject->faces[i].vertex = (int*)malloc(sizeof(int) * myObject->faces[i].size); //making memory space for vertex indexes array of a face
			if (myObject->faces[i].vertex == NULL) {
				printf("faces vertex num: %d malloc wrong!", i);
				return NULL;
			}
			fread(myObject->faces[i].vertex, sizeof(int), myObject->faces[i].size, f); //loads the vertexes indexes in a face
		}
		addScene(&scene, myObject);
	}
return scene;
}

Scene* loadScene(char* fileName, enum FileType type) {
	Scene* scene = NULL;
	char* str;
	if (type == BinaryFormat) { //check what is the file type and choose which permission to use
		str = "rb+";
	}
	else {
		str = "r+";
	}
	FILE* f = fopen(fileName, str);
	if (f == NULL) {
		printf("Failed opening the file.");
		return NULL;
	}
	switch (type) { //choose which file type operation to use

	case 0: // TextFormat
		scene = loadText(f);
		break;

	case 1: // BinaryFormat
		scene = loadBinary(f);
		break;

	default:
		printf("Wrong File Format!");
		break;
	}
	fclose(f);
	return scene;
}

void transformObject(char* originalObjectFileName, char* deformedObjectFileName) {
	float num1, num2, num3;
	char strLine[SIZE];
	FILE* fSource, * fDest;
	fSource = fopen(originalObjectFileName, "r");  //open the source file for reading
	if (fSource == NULL) { // check if open file Source succeeded
		printf("Failed opening the file: %s", originalObjectFileName);
		return NULL;
	}
	fDest = fopen(deformedObjectFileName, "w");  //open the destination file for writing
	if (fDest == NULL) { // cheack if open file Dest succeeded
		printf("Failed opening the file: %s", deformedObjectFileName);
		return NULL;
	}
	while (!feof(fSource)) { //run until the file is ended
		fgets(strLine, SIZE, fSource); //read the line, max of SIZE
		if (strLine[0] == 'v' && strLine[1] == ' ') {
			strtok(strLine, " "); // move past the 'v'
			num1 = atof(strtok(NULL, " ")); //reads the x value
			num1 = num1 * 0.3; //multiply x by 0.3
			num2 = atof(strtok(NULL, " ")); //reads the y value
			num3 = atof(strtok(NULL, " ")); //reads the z value
			fprintf(fDest, "%c %f %f %f\n", 'v', num1, num2, num3); //writes the line with the calculated x to the destination file
		}
		else {
			fputs(strLine, fDest); //writes the line to the destination file
		}
	}
	fclose(fSource);
	fclose(fDest);
}

void printFaces(Object* ptr, void* numberOfTriangularFaces) {
	int count = 0;
	for (int i = 0; i < ptr->numberOfFaces; i++) { //run on the number of faces
		if (ptr->faces[i].size == 3) {
			count++; //counts all the triangles in an object
		}
	}
	*(int*)numberOfTriangularFaces = count;
}

void printVertexes(Object* ptr, void* numberOfVertexes) {
	*(int*)numberOfVertexes = ptr->numberOfVertexes; 
}

double calculateDist(Vertex * one, Vertex* two) {
	//calculates a distance between 2 points
	double distance = (pow((two->x - one->x),2) +
					  (pow((two->y - one->y), 2)) +
					  (pow((two->z - one->z), 2)));
	distance = sqrt(distance); 
	return distance;
}

void getTotalArea(Object* ptr, void* totalAreaOfTriangularFaces) {
	double totalArea = 0;
	double semiperimiter,currentArea = 0;
	double numOfDistances[3];
	for (int i = 0; i < ptr->numberOfFaces; i++) {
		if (ptr->faces[i].size == 3) {
				Vertex one = ptr->vertexes[ptr->faces[i].vertex[0]-1]; 
				Vertex two = ptr->vertexes[ptr->faces[i].vertex[1]-1];
				Vertex three = ptr->vertexes[ptr->faces[i].vertex[2]-1];
				numOfDistances[0] = calculateDist(&one, &two); //calculate first line of a triangle
				numOfDistances[1] = calculateDist(&two, &three); //calculate second line of a triangle
				numOfDistances[2] = calculateDist(&three, &one); //calculate third line of a triangle

				semiperimiter = 0.5 * (numOfDistances[0] + numOfDistances[1] + numOfDistances[2]); //calculate the semiperimiter of a triangle 
				currentArea = sqrt(semiperimiter * (semiperimiter - numOfDistances[0]) *
								  (semiperimiter - numOfDistances[1]) * (semiperimiter - numOfDistances[2])); //calculate the area of the current triangle
				totalArea = totalArea + currentArea; //calculate the total area of all the triangles of the current oject
		}
	}
	*(double*)totalAreaOfTriangularFaces = totalArea;
}

void perform(Scene* scene, void (*func)(Object*, void*), char* type, char* string) {
	int resultINT = 0, sumINT = 0;
	double resultDOUBLE = 0, sumDOUBLE = 0;
	int typeCheck = 0;
	
	//checks which data type to use
	if (strcmp(type, "INT") == 0)
		typeCheck = 1;
	else if (strcmp(type, "DOUBLE") == 0)
		typeCheck = 2;

	while (scene != NULL) {	//run on all the objects in the program
		switch (typeCheck)
		{
		case 1:
			func(scene->object, &resultINT); //calculate the function which has been asekd in the perform() call for one object
			sumINT += resultINT; //sum all the results of all the objects
			break;
		case 2:
			func(scene->object, &resultDOUBLE); //calculate the function which has been asekd in the perform() call
			sumDOUBLE += resultDOUBLE; //sum all the results of all the objects
			break;
		default:
			printf("NO METHOD TYPE HAS BEEN SELECTED!");
			break;
		}
		scene = scene->next;
	}
	//prints the right string for a specific data type
	printf("%s: ", string);
	if(typeCheck == 1)
		printf("%d \n", sumINT); 
	else if (typeCheck == 2)
		printf("%lf \n", sumDOUBLE);
}


void freeScene(Scene* scene) {
	if (scene == NULL) return;
	Scene* last = scene; //saves the last scene
	while (scene != NULL) { //run on all the objects
		free(scene->object->vertexes); //free all the vertexes space in an object
		for (int i = 0; i < scene->object->numberOfFaces; i++)
			free(scene->object->faces[i].vertex); //free all the vertex indexes array in a face
		free(scene->object->faces); //free all the faces in an object
		last = last->next; //make last as the next scene
		free(scene->object); //free the current object
		scene = last; //set scene as the next one
	}
	free(scene); //free the scene
}