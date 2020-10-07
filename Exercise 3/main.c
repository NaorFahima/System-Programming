/*
 ============================================================================
 Name        : Task_3.c
 Author      : Ram Fridman, Naor Fahima
 ID's     : 203783907, 315783563
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#include "struct.h"


int main(void) {

	Scene* scene;
	Scene* scene1, * scene2;
//
//	// Create a Scene of Objects received 
//// from files GoingMerry.obj, Donald.obj, Pony_cartoon.obj
	scene = createScene("Donald.obj","GoingMerry.obj","Pony_cartoon.obj",  NULL);

//
//	// Print out all Vertexes
	perform(scene, printVertexes, "INT","The number of vertexes of all objects in Main Scene is");
//
//	// Count the number of all Triangular faces of all objects in Scene 
	perform(scene, printFaces, "INT", "The number of Triangular faces of all objects in Main Scene is");
//
//	// Count the total area of all Triangular faces of all objects in Scene 
	perform(scene, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects in Main Scene is");
//

//	// Save the world to file in Text and in Binary formats
	saveScene(scene, "FirstScene.txt", TextFormat);
	saveScene(scene, "SecondScene.dat", BinaryFormat);
//
//	// Retrieve the saved data
	scene1 = loadScene("FirstScene.txt", TextFormat);
	scene2 = loadScene("SecondScene.dat", BinaryFormat);
//

///	// Check Retrieve the saved data of text format
	printf("\n");
	perform(scene1, printVertexes, "INT", "The number of vertexes of all objects in Text File is");
	perform(scene1, printFaces, "INT", "The number of Triangular faces of all objects in Text File is");
	perform(scene1, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects in Text File is");
//
//	// Check Retrieve the saved data of binary format
	printf("\n");
	perform(scene2, printVertexes, "INT", "The number of vertexes of all objects in Binary File is");
	perform(scene2, printFaces, "INT", "The number of Triangular faces of all objects in Binary File is");
	perform(scene2, getTotalArea, "DOUBLE", "The total area of Triangular faces of all objects in Binary File is");
//
//	// Make transformation based on the original object defined in file Donald.obj
	 transformObject("Donald.obj", "StrangeDonald.obj");
//
//
//	// Free all memory allocated for the Scene
	freeScene(scene);
	freeScene(scene1);
	freeScene(scene2);

	return EXIT_SUCCESS;
}
