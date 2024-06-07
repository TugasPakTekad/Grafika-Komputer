#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"camera.h"
#include"texture.h"

const int windowWidth = 800;
const int windowHeight = 800;

const int jumlahObjek = 14;
const int jumlahIndices = 14;

//properti Gelas
const int jumlahIrisan = 50;
const float jariJari = 0.1f;
const float tinggiGelas = 0.2f;
const float PI = 3.14159265359f;

//properti piring
const float tinggiPiring = 0.05f;

//properti sendok
const int latDivs = 18;
const int lonDivs = 36;

float rectangleVertices[] =
{
	// Coords    // texCoords
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f,

	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f,  1.0f,  0.0f, 1.0f
};

GLfloat permukaanMeja[] =
{
	// Koordinat simpul		// Warna		//Texture kordinat	//Normals
	// Front face
	-0.5f, 0.05f,  0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	0.0f, 0.1f, 0.1f,//kiri bawah 0
	 0.5f, 0.05f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	0.0f, 0.1f, 0.1f,//kanan bawah 1
	 0.5f, 0.1f,  0.5f,		0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.1f, 0.05f,//kanan atas 2
	-0.5f, 0.1f,  0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f, 0.1f, 0.05f,//kiri atas 3

	// Back face
	-0.5f, 0.05f, -0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	0.0f, 0.1f, -0.1f,//kiri bawah 4
	 0.5f, 0.05f, -0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	0.0f, 0.1f, -0.1f,//kanan bawah 5
	 0.5f, 0.1f, -0.5f,		0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.1f, -0.05f,//kanan atas 6
	-0.5f, 0.1f, -0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f, 0.1f, -0.05f,//kiri atas 7

	// Top face
	-0.5f,  0.1f,  0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	0.0f, 0.2f, 0.0f,//kiri bawah 8
	 0.5f,  0.1f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	0.0f, 0.2f, 0.0f,//kanan bawah 9
	 0.5f,  0.1f, -0.5f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	0.0f, 0.2f, 0.0f,//kanan atas 10
	-0.5f,  0.1f, -0.5f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f, 0.2f, 0.0f,//kiri atas 11

	// Bottom face
	-0.5f, 0.05f,  0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	0.0f, -0.05f, 0.0f,//kiri bawah 12
	 0.5f, 0.05f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	0.0f, -0.05f, 0.0f,//kanan bawah 13
	 0.5f, 0.05f, -0.5f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	0.0f, -0.05f, 0.0f,//kanan atas 14
	-0.5f, 0.05f, -0.5f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.0f, -0.05f, 0.0f,//kiri atas 15

	//left face
	-0.5f, 0.05f, -0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.1f, 0.1f, 0.0f,//kiri bawah 16
	-0.5f, 0.05f,  0.5f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	-0.1f, 0.1f, 0.0f,//kanan bawah 17
	-0.5f, 0.1f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	-0.1f, 0.1f, 0.0f,//kanan atas 18
	-0.5f, 0.1f, -0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.1f, 0.1f, 0.0f,//kiri atas 19

	//right face
	0.5f, 0.05f, -0.5f,		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	0.1f, 0.1f, 0.0f,//kiri bawah 20
	0.5f, 0.05f,  0.5f,		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	0.1f, 0.1f, 0.0f,//kanan bawah 21
	0.5f, 0.1f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	0.1f, 0.1f, 0.0f,//kanan atas 22
	0.5f, 0.1f, -0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.1f, 0.1f, 0.0f//kiri atas 23
};

GLfloat kakiMeja[] =
{
	//front face
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.5f, -0.3f, 0.6f,//0
	-0.45f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.45f,-0.3f, 0.6f,//1
	-0.45f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.45f,-0.3f, 0.6f,//2
	-0.5f, -0.1f,  0.5f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.5f, -0.3f, 0.6f,//3

	//back face						  
	-0.5f, -0.5f,  0.45f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.5f, -0.3f, 0.35f,//4
	-0.45f, -0.5f, 0.45f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.45f,-0.3f, 0.35f,//5
	-0.45f, -0.1f, 0.45f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.45f,-0.3f, 0.35f,//6
	-0.5f, -0.1f,  0.45f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.5f, -0.3f, 0.35f,//7

	//bottom face						  
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.5f, -0.6f, 0.5f,//8
	-0.45f, -0.5f, 0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.45f, -0.6f, 0.5f,//9
	-0.45f, -0.5f, 0.45f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.45f, -0.6f, 0.45f,//10
	-0.5f, -0.5f,  0.45f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.5f, -0.6f, 0.45f,//11

	//left face
	-0.5f, -0.5f,  0.45f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.6f, -0.3f, 0.47f,//12
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.6f, -0.3f, 0.47f,//13
	-0.5f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.6f, -0.3f, 0.47f,//14
	-0.5f, -0.1f,  0.45f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.6f, -0.3f, 0.47f,//15

	//right face
	-0.45f, -0.5f,  0.45f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.35f, -0.3f, 0.47f,//16
	-0.45f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.35f, -0.3f, 0.47f,//17
	-0.45f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.35f, -0.3f, 0.47f,//18
	-0.45f, -0.1f,  0.45f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.35f, -0.3f, 0.47f //19
};

GLfloat taplakMeja[] =
{
	// Koordinat simpul		// Warna
	// Top face
	-0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,	0.0f, 0.2f, 0.0f,//kiri bawah 0
	 0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.0f, 0.2f, 0.0f,//kanan bawah 1
	 0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,	0.0f, 0.2f, 0.0f,//kanan atas 2
	-0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.0f, 0.2f, 0.0f,//kiri atas 3

	//right face
	0.50015f, 0.1001f,	0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,	0.05f, 0.1f, 0.0f, //kanan atas depan 4
	0.50015f, -0.25f,	0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,	0.1f, -0.1f, 0.0f,//kanan bawah depan 5
	0.50015f, -0.25f,	-0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,	0.1f, -0.1f, 0.0f,//kanan bawah belakang 6
	0.50025f, 0.1001f,	-0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,	0.05f, 0.1f, 0.0f, //kanan atas belakang 7

	//left face
	-0.50015f,  0.1001f, 0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f,	-0.05f, 0.1f, 0.0f,//kiri atas depan 8
	-0.50015f, -0.25f,	0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,	-0.1f, -0.1f, 0.0f,//kiri bawah depan 9
	-0.50015f, -0.25f,	-0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,	-0.1f, -0.1f, 0.0f,//kiri bawah belakang 10
	-0.50015f,  0.1001f,-0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,	-0.05f, 0.1f, 0.0f//kiri atas belakang 11
};

GLfloat gelas[jumlahIrisan * 8 * 3];

GLfloat alasGelas[jumlahIrisan * 8 * 2];

GLfloat piringBulat[jumlahIrisan * 8 * 3];

GLfloat alasPiringBulat[jumlahIrisan * 8 * 2];

GLfloat piringOval[jumlahIrisan * 8 * 3];

GLfloat alasPiringOval[jumlahIrisan * 8 * 3];

GLfloat sendok[(latDivs + 1) * (lonDivs + 1) * 8 * 3];

GLfloat gagangSendok[] =
{
	//bottom
	0.47f,0.0f,	0.15f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.05f, -0.1f, 0.0f,
	1.8f, 0.0f,	0.15f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.05f, -0.1f, 0.0f,
	1.8f, 0.0f,	-0.15f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.05f, -0.1f, 0.0f,
	0.47f,0.0f,	-0.15f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.05f, -0.1f, 0.0f,

	//top
	0.43f,0.1f,	0.15f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.05f, 0.2f, 0.0f,
	1.8f, 0.1f,	0.15f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.05f, 0.2f, 0.0f,
	1.8f, 0.1f,	-0.15f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	-0.05f, 0.2f, 0.0f,
	0.43f,0.1f,	-0.15f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.05f, 0.2f, 0.0f,

	//left side
	0.47f,0.0f,	0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.05f, 0.2f, 0.0f,
	1.8f, 0.0f,	0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.05f, 0.2f, 0.0f,
	1.8f, 0.1f,	0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,	-0.05f, 0.2f, 0.0f,
	0.43f,0.1f,	0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	-0.05f, 0.2f, 0.0f,

	//right side
	0.47f,0.0f,	-0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.05f, 0.2f, 0.0f,
	1.8f, 0.0f,	-0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	-0.05f, 0.2f, 0.0f,
	1.8f, 0.1f,	-0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,	-0.05f, 0.2f, 0.0f,
	0.43f,0.1f,	-0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,	-0.05f, 0.2f, 0.0f,

	//front side
	1.8f, 0.0f,	0.15f,	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,	1.9f, 0.05f, 0.0f,
	1.8f, 0.0f,	-0.15f,	0.0f, 0.0f, 1.0f, 1.0f, 0.0f,	1.9f, 0.05f, 0.0f,
	1.8f, 0.1f,	0.15f,	0.0f, 1.0f, 0.0f, 1.0f, 1.0f,	1.9f, 0.05f, 0.0f,
	1.8f, 0.1f,	-0.15f,	0.0f, 0.0f, 1.0f, 0.0f, 1.0f,	1.9f, 0.05f, 0.0f,

	//back side
	0.47f, 0.0f, 0.15f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.05f, 0.05f, 0.0f,
	0.47f, 0.0f, -0.15f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,	-0.05f, 0.05f, 0.0f,
	0.43f, 0.1f, 0.15f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	-0.05f, 0.05f, 0.0f,
	0.43f, 0.1f, -0.15f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.05f, 0.05f, 0.0f
};

GLfloat garpu[] =
{
	// Atas
	-0.4f,	0.1f,	-0.4f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.2f,	0.0f,	// 0
	0.0f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.2f,	0.0f,	// 1
	0.2f,	0.1f,	-0.4f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.2f,	0.0f,	// 2
	-0.4f,	0.1f,	-0.2f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.2f,	0.0f,	// 3
	-0.4f,	0.1f,	-0.1f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.2f,	0.0f,	// 4
	0.0f,	0.1f,	-0.1f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.2f,	0.0f,	// 5
	-0.4f,	0.1f,	0.1f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.2f,	0.0f,	// 6
	0.0f,	0.1f,	0.1f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.2f,	0.0f,	// 7
	-0.4f,	0.1f,	0.4f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.2f,	0.0f,	// 8
	0.0f,	0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.2f,	0.0f,	// 9
	0.2f,	0.1f,	0.4f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 10
	-0.4f,	0.1f,	0.2f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 11
	0.4f,	0.1f,	0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 12
	0.4f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.2f,	0.0f,	// 13

	// Bawah
	-0.4f,	0.0f,	-0.4f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 14
	0.0f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 15
	0.2f,	0.0f,	-0.4f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 16
	-0.4f,	0.0f,	-0.2f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 17
	-0.4f,	0.0f,	-0.1f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 18
	0.0f,	0.0f,	-0.1f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 19
	-0.4f,	0.0f,	0.1f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 20
	0.0f,	0.0f,	0.1f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 21
	-0.4f,	0.0f,	0.4f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 22
	0.0f,	0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 23
	0.2f,	0.0f,	0.4f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 24
	-0.4f,	0.0f,	0.2f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 25
	0.4f,	0.0f,	0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 0.0f,	0.2f,	0.0f,	// 26
	0.4f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.2f,	0.0f,	// 27
};

GLfloat gagangGarpu[] =
{
	// Atas
	0.4f, 0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.0f,	0.0f,	// 0
	0.4f, 0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.05f,	0.0f,	// 1
	1.8f, 0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	-0.25f,	2.5f,	0.0f,	// 2
	1.8f, 0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	-0.25f,	2.5f,	0.0f,	// 3

	// kanan
	0.4f, 0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.05f,	0.0f,	// 4
	0.4f, 0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.05f,	0.0f,	// 5
	1.8f, 0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	-0.25f,	2.5f,	0.0f,	// 6
	1.8f, 0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	-0.25f,	2.5f,	0.0f,	// 7

	// kiri
	0.4f, 0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.0f,	0.0f,	// 8
	0.4f, 0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.0f,	0.0f,	// 9
	1.8f, 0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	-0.25f,	2.5f,	0.0f,	// 10
	1.8f, 0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	-0.25f,	2.5f,	0.0f,	// 11

	// depan
	0.4f, 0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.0f,	0.0f,	// 12
	0.4f, 0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.0f,	0.0f,	// 13
	0.4f, 0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.0f,	0.0f,	// 14
	0.4f, 0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.0f,	0.0f,	// 15

	// belakang
	1.8f, 0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.5f,	0.5f,	0.0f,	// 16
	1.8f, 0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.5f,	0.5f,	0.0f,	// 17
	1.8f, 0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.5f,	0.0f,	0.0f,	// 18
	1.8f, 0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.5f,	0.0f,	0.0f,	// 19

	// Bawah
	0.4f, 0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.0f,	0.0f,	// 20
	0.4f, 0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.0f,	0.0f,	// 21
	1.8f, 0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	0.0f,	0.0f,	0.0f,	// 22
	1.8f, 0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	0.0f,	0.0f,	0.0f,	// 23
};

GLfloat piringKotak[] =
{
	//Bawah
	-0.6f,	0.0f, 0.6f,		1.0f, 1.0f, 1.0f,	0.8f, 0.8f,	0.0f,	-0.1f,	0.0f,	// 0
	0.6f,	0.0f, 0.6f,		1.0f, 1.0f, 1.0f,	0.8f, 1.0f,	0.0f,	-0.1f,	0.0f,	// 1
	0.6f,	0.0f, -0.6f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,	0.0f,	-0.1f,	0.0f,	// 2
	-0.6f,	0.0f, -0.6f,	1.0f, 1.0f, 1.0f,	1.0f, 0.8f,	0.0f,	-0.1f,	0.0f,	// 3

	// Atas
	-1.6f,	0.7f,	1.6f,	1.0f, 1.0f, 1.0f,	0.3f, 0.3f,	0.0f,	0.2f,	0.0f,	// 4
	1.6f,	0.7f,	1.6f,	1.0f, 1.0f, 1.0f,	0.3f, 0.1f,	0.0f,	0.2f,	0.0f,	// 5
	1.6f,	0.7f,	-1.6f,	1.0f, 1.0f, 1.0f,	0.1f, 0.1f,	0.0f,	0.2f,	0.0f,	// 6
	-1.6f,	0.7f,	-1.6f,	1.0f, 1.0f, 1.0f,	0.1f, 0.3f,	0.0f,	0.2f,	0.0f,	// 7
};

GLfloat lampu[] =
{
	-0.1f,	0.3f,	0.1f,
	0.1f,	0.3f,	0.1f,
	0.1f,	0.5f,	0.1f,
	-0.1f,	0.5f,	0.1f,

	-0.1f,	0.3f,	-0.1f,
	0.1f,	0.3f,	-0.1f,
	0.1f,	0.5f,	-0.1f,
	-0.1f,	0.5f,	-0.1f
};

GLuint permukaanMejaIndices[] =
{
	0, 1, 2, 2, 3, 0,		// Front face
	4, 5, 6, 6, 7, 4,		// Back face
	8, 9, 10, 10, 11, 8,	// top face
	12, 13, 14, 14, 15, 12,	// bottom face
	16, 17, 18, 18, 19, 16,// left face
	20, 21, 22, 22, 23, 20	// right face
};

GLuint kakiMejaIndices[] =
{
	0, 1, 2, 2, 3, 0,		// Front face
	4, 5, 6, 6, 7, 4,		// back face
	8, 9, 10, 10, 11, 8,	// bottom face
	12, 13, 14, 14, 15, 12,		// left face
	16, 17, 18, 18, 19, 16		// right face
};

GLuint taplakMejaIndices[] =
{
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4,
	8, 9, 10, 10, 11, 8
};

GLuint gelasIndices[jumlahIrisan * 3 * 2];

GLuint alasGelasIndices[jumlahIrisan];

GLuint piringBulatIndices[jumlahIrisan * 3 * 2];

GLuint alasPiringBulatIndices[jumlahIrisan];

GLuint piringOvalIndices[jumlahIrisan * 3 * 2];

GLuint alasPiringOvalIndices[jumlahIrisan];

GLuint sendokIndices[18 * 36 * 6];

GLuint gagangIndices[] =
{
	0, 1, 2, 2, 3, 0,
	8, 11, 9, 9, 10, 11,
	22, 20, 21, 21, 22, 23,
	15, 14, 12, 12, 13, 14,
	19, 17, 16, 16, 18, 19,
	6, 5, 4, 4, 7, 6
};

GLuint garpuindices[] =
{
	0, 1, 2, 3, 1, 0, 4, 5, 6, 6, 7, 5,
	8, 11, 9, 8, 9, 10, 7, 10, 9, 7, 12, 10,
	5, 12, 7, 13, 5, 12, 2, 5, 13, 1, 2, 5,		// atas

	14, 15, 16, 17, 15, 14, 18, 19, 20, 20, 21, 19,
	22, 25, 23, 22, 23, 24, 21, 24, 23, 21, 26, 24,
	19, 26, 21, 27, 19, 26, 16, 19, 27, 15, 16, 19,		// bawah

	8, 22, 10, 10, 24, 22, 10, 24, 12, 12, 26, 24,
	6, 20, 7, 7, 21, 20, 3, 17, 1, 1, 15, 17,		// kanan

	2, 16, 0, 0, 14, 16, 13, 27, 2, 2, 16, 27,
	5, 19, 4, 4, 18, 19, 9, 23, 11, 11, 25, 23,		// kiri

	0, 14, 3, 3, 17, 14, 4, 18, 6, 6, 20, 18, 11, 25, 8, 8, 22, 25,
	1, 15, 5, 5, 19, 15, 7, 21, 9, 9, 23, 21,		// depan

	12, 26, 13, 13, 27, 26		// belakang
};

GLuint gagangGarpuindices[] =
{
	0, 1, 2, 2, 3, 1,		// atas
	4, 5, 6, 6, 7, 5,		// kanan
	8, 9, 10, 10, 11, 9,	// kiri
	12, 13, 14, 14, 15, 13,	// depan
	16, 17, 18, 18, 19, 17,	// belakang
	20, 21, 22, 22, 23, 21,	// bawah
};

GLuint piringKotakindices[] =
{
	0, 1, 2, 0, 3, 2,
	1, 0, 4, 1, 5, 4,
	5, 6, 2, 5, 1, 2,
	7, 6, 2, 7, 3, 2,
	3, 0, 4, 3, 7, 4,
};

GLuint lampuIndices[] =
{
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 6, 7, 4,
	1, 5, 6, 6, 2, 1,
	4, 0, 3, 3, 7, 4,
	0, 1, 5, 5, 4, 0,
	3, 2, 6, 6, 7, 3
};

void binding(GLuint& VAO, GLuint& VBO, GLuint& EBO, GLsizei vboSize, GLfloat* vboName, GLsizei eboSize, GLuint* eboName)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vboSize, vboName, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, eboName, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Dinning_Table", 0, 0);
	if (window == NULL)
	{
		std::cout << "window gagal dibuka";
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	Shader shaderProgram("default.vert", "default.frag");
	Shader shadowMapProgram("shadow.vert", "shadow.frag");
	Shader shadowScene("scene.vert", "scene.frag");

	for (int i = 0; i <= jumlahIrisan; ++i) {
		float sudut = 2.0f * PI / jumlahIrisan;
		float x = jariJari * std::cos(i * sudut);
		float z = jariJari * std::sin(i * sudut);

		//gelas
		// Bottom vertex
		gelas[i * 11 * 2] = x / 2;
		gelas[i * 11 * 2 + 1] = -tinggiGelas / 2.0f;
		gelas[i * 11 * 2 + 2] = z / 2;
		gelas[i * 11 * 2 + 3] = 1.0f; // Red color
		gelas[i * 11 * 2 + 4] = 0.0f; // Green color
		gelas[i * 11 * 2 + 5] = 0.0f; // Blue color
		gelas[i * 11 * 2 + 6] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		gelas[i * 11 * 2 + 7] = 0.0f; // Texture coordinate v
		gelas[i * 11 * 2 + 8] = 0.0f; // normal x
		gelas[i * 11 * 2 + 9] = 0.0f; // normal y
		gelas[i * 11 * 2 + 10] = 0.0f; // normal z

		//alas vertex
		alasGelas[i * 11] = x / 2;
		alasGelas[i * 11 + 1] = -tinggiGelas / 2.0f;
		alasGelas[i * 11 + 2] = z / 2;
		alasGelas[i * 11 + 3] = 0.4f; // Red color
		alasGelas[i * 11 + 4] = 0.2f; // Green color
		alasGelas[i * 11 + 5] = 0.5f; // Blue color
		alasGelas[i * 11 + 6] = 0.3f * (x / jariJari) + 0.5f; // Texture coordinate u
		alasGelas[i * 11 + 7] = 0.2f * (z / jariJari) + 0.5f; // Texture coordinate v
		alasGelas[i * 11 + 8] = 0.0f;
		alasGelas[i * 11 + 9] = 0.2f;
		alasGelas[i * 11 + 10] = 0.0f;

		// Top vertex
		gelas[i * 11 * 2 + 11] = x;
		gelas[i * 11 * 2 + 12] = tinggiGelas / 2.0f;
		gelas[i * 11 * 2 + 13] = z;
		gelas[i * 11 * 2 + 14] = 0.0f; // Red color
		gelas[i * 11 * 2 + 15] = 1.0f; // Green color
		gelas[i * 11 * 2 + 16] = 0.0f; // Blue color
		gelas[i * 11 * 2 + 17] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		gelas[i * 11 * 2 + 18] = 1.0f; // Texture coordinate v
		gelas[i * 11 * 2 + 19] = 0.0f; // normal x
		gelas[i * 11 * 2 + 20] = 0.2f; // normal y
		gelas[i * 11 * 2 + 21] = 0.0f; // normal z

		//piring
		// Bottom vertex
		piringBulat[i * 11 * 2] = x / 2;
		piringBulat[i * 11 * 2 + 1] = -tinggiPiring / 2.0f;
		piringBulat[i * 11 * 2 + 2] = z / 2;
		piringBulat[i * 11 * 2 + 3] = 1.0f; // Red color
		piringBulat[i * 11 * 2 + 4] = 0.0f; // Green color
		piringBulat[i * 11 * 2 + 5] = 0.0f; // Blue color
		piringBulat[i * 11 * 2 + 6] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringBulat[i * 11 * 2 + 7] = 0.0f; // Texture coordinate v
		piringBulat[i * 11 * 2 + 8] = 0.0f; // normal x
		piringBulat[i * 11 * 2 + 9] = 0.0f; // normal y
		piringBulat[i * 11 * 2 + 10] = 0.0f; // normal z

		piringOval[i * 11 * 2] = x / 2;
		piringOval[i * 11 * 2 + 1] = -tinggiPiring / 2.0f;
		piringOval[i * 11 * 2 + 2] = z / 2;
		piringOval[i * 11 * 2 + 3] = 1.0f; // Red color
		piringOval[i * 11 * 2 + 4] = 0.0f; // Green color
		piringOval[i * 11 * 2 + 5] = 0.0f; // Blue color
		piringOval[i * 11 * 2 + 6] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringOval[i * 11 * 2 + 7] = 0.0f; // Texture coordinate v
		piringOval[i * 11 * 2 + 8] = 0.0f; // normal x
		piringOval[i * 11 * 2 + 9] = 0.0f; // normal y
		piringOval[i * 11 * 2 + 10] = 0.0f; // normal z

		//alas piring
		alasPiringBulat[i * 11] = x / 2;
		alasPiringBulat[i * 11 + 1] = -tinggiPiring / 2.0f;
		alasPiringBulat[i * 11 + 2] = z / 2;
		alasPiringBulat[i * 11 + 3] = 0.4f; // Red color
		alasPiringBulat[i * 11 + 4] = 0.2f; // Green color
		alasPiringBulat[i * 11 + 5] = 0.5f; // Blue color
		alasPiringBulat[i * 11 + 6] = 0.3f * (x / jariJari) + 0.5f; // Texture coordinate u
		alasPiringBulat[i * 11 + 7] = 0.2f * (z / jariJari) + 0.5f; // Texture coordinate v
		alasPiringBulat[i * 11 + 8] = 0.0f;
		alasPiringBulat[i * 11 + 9] = 0.2f;
		alasPiringBulat[i * 11 + 10] = 0.0f;

		alasPiringOval[i * 11] = x / 2;
		alasPiringOval[i * 11 + 1] = -tinggiPiring / 2.0f;
		alasPiringOval[i * 11 + 2] = z / 2;
		alasPiringOval[i * 11 + 3] = 0.4f; // Red color
		alasPiringOval[i * 11 + 4] = 0.2f; // Green color
		alasPiringOval[i * 11 + 5] = 0.5f; // Blue color
		alasPiringOval[i * 11 + 6] = 0.3f * (x / jariJari) + 0.5f; // Texture coordinate u
		alasPiringOval[i * 11 + 7] = 0.2f * (z / jariJari) + 0.5f; // Texture coordinate v
		alasPiringOval[i * 11 + 8] = 0.0f;
		alasPiringOval[i * 11 + 9] = 0.2f;
		alasPiringOval[i * 11 + 10] = 0.0f;

		//top vertex
		piringBulat[i * 11 * 2 + 11] = x;
		piringBulat[i * 11 * 2 + 12] = tinggiPiring / 2.0f;
		piringBulat[i * 11 * 2 + 13] = z;
		piringBulat[i * 11 * 2 + 14] = 0.0f; // Red color
		piringBulat[i * 11 * 2 + 15] = 1.0f; // Green color
		piringBulat[i * 11 * 2 + 16] = 0.0f; // Blue color
		piringBulat[i * 11 * 2 + 17] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringBulat[i * 11 * 2 + 18] = 1.0f; // Texture coordinate v
		piringBulat[i * 11 * 2 + 19] = 0.0f; // normal x
		piringBulat[i * 11 * 2 + 20] = 0.2f; // normal y
		piringBulat[i * 11 * 2 + 21] = 0.0f; // normal z

		piringOval[i * 11 * 2 + 11] = x;
		piringOval[i * 11 * 2 + 12] = tinggiPiring / 2.0f;
		piringOval[i * 11 * 2 + 13] = z / 1.3f;
		piringOval[i * 11 * 2 + 14] = 0.0f; // Red color
		piringOval[i * 11 * 2 + 15] = 1.0f; // Green color
		piringOval[i * 11 * 2 + 16] = 0.0f; // Blue color
		piringOval[i * 11 * 2 + 17] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringOval[i * 11 * 2 + 18] = 1.0f; // Texture coordinate v
		piringOval[i * 11 * 2 + 19] = 0.0f; // normal x
		piringOval[i * 11 * 2 + 20] = 0.2f; // normal y
		piringOval[i * 11 * 2 + 21] = 0.0f; // normal z
	}

	for (int i = 0; i < jumlahIrisan; i++) {
		//gelas
		// sisi
		gelasIndices[i * 6] = i * 2;
		gelasIndices[i * 6 + 1] = (i + 1) * 2;
		gelasIndices[i * 6 + 2] = (i + 1) * 2 + 1;

		gelasIndices[i * 6 + 3] = (i + 1) * 2 + 1;
		gelasIndices[i * 6 + 4] = i * 2 + 1;
		gelasIndices[i * 6 + 5] = i * 2;

		// alas
		alasGelasIndices[i] = i;

		//piring
		// sisi
		piringBulatIndices[i * 6] = i * 2;
		piringBulatIndices[i * 6 + 1] = (i + 1) * 2;
		piringBulatIndices[i * 6 + 2] = (i + 1) * 2 + 1;

		piringBulatIndices[i * 6 + 3] = (i + 1) * 2 + 1;
		piringBulatIndices[i * 6 + 4] = i * 2 + 1;
		piringBulatIndices[i * 6 + 5] = i * 2;

		piringOvalIndices[i * 6] = i * 2;
		piringOvalIndices[i * 6 + 1] = (i + 1) * 2;
		piringOvalIndices[i * 6 + 2] = (i + 1) * 2 + 1;

		piringOvalIndices[i * 6 + 3] = (i + 1) * 2 + 1;
		piringOvalIndices[i * 6 + 4] = i * 2 + 1;
		piringOvalIndices[i * 6 + 5] = i * 2;

		// alas
		alasPiringBulatIndices[i] = i;

		alasPiringOvalIndices[i] = i;
	}

	int vertexIndex = 0;
	int indexIndex = 0;
	float radiusX = 0.5f; // X-axis radius
	float radiusY = 0.3f; // Y-axis radius
	float radiusZ = 0.4f; // Z-axis radius
	for (int lat = 0; lat <= latDivs / 2; lat++) {
		float phi = PI * (float)lat / (float)latDivs;
		for (int lon = 0; lon <= lonDivs; lon++) {
			float theta = 2 * PI * (float)lon / (float)lonDivs;

			float x = radiusX * sinf(phi) * cosf(theta);
			float y = radiusY * cosf(phi);
			float z = radiusZ * sinf(phi) * sinf(theta);

			// Position (replace with actual calculations)
			sendok[vertexIndex++] = x;
			sendok[vertexIndex++] = y;
			sendok[vertexIndex++] = z;

			// Color (this is an example; use your actual color values)
			sendok[vertexIndex++] = 1.0f; // Red
			sendok[vertexIndex++] = 0.5f; // Green
			sendok[vertexIndex++] = 0.0f; // Blue

			//texture
			sendok[vertexIndex++] = theta / (2.0f * PI);
			sendok[vertexIndex++] = 1.0f - (phi / PI);

			//normal
			sendok[vertexIndex++] = 0.0f;
			sendok[vertexIndex++] = 0.2f;
			sendok[vertexIndex++] = 0.0f;

			// Calculate indices for the quad's two triangles
			if (lat < latDivs / 2 && lon < lonDivs) {
				int nextLat = lonDivs + 1;
				sendokIndices[indexIndex++] = lat * nextLat + lon;
				sendokIndices[indexIndex++] = (lat + 1) * nextLat + lon;
				sendokIndices[indexIndex++] = lat * nextLat + lon + 1;

				sendokIndices[indexIndex++] = lat * nextLat + lon + 1;
				sendokIndices[indexIndex++] = (lat + 1) * nextLat + lon;
				sendokIndices[indexIndex++] = (lat + 1) * nextLat + lon + 1;
			}
		}
	}

	// Define indices for handle (a simple rectangle)
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		sendokIndices[indexIndex++] = latDivs * (lonDivs + 1) + i;
		sendokIndices[indexIndex++] = latDivs * (lonDivs + 1) + j;
		sendokIndices[indexIndex++] = latDivs * (lonDivs + 1) + j + 4;

		sendokIndices[indexIndex++] = latDivs * (lonDivs + 1) + j + 4;
		sendokIndices[indexIndex++] = latDivs * (lonDivs + 1) + i + 4;
		sendokIndices[indexIndex++] = latDivs * (lonDivs + 1) + i;
	}

	GLuint VAO[jumlahObjek], VBO[jumlahObjek], EBO[jumlahIndices];
	glGenVertexArrays(jumlahObjek, VAO);
	glGenBuffers(jumlahObjek, VBO);
	glGenBuffers(jumlahIndices, EBO);

	//Meja
	binding(VAO[0], VBO[0], EBO[0], sizeof(permukaanMeja), permukaanMeja, sizeof(permukaanMejaIndices), permukaanMejaIndices);
	binding(VAO[1], VBO[1], EBO[1], sizeof(kakiMeja), kakiMeja, sizeof(kakiMejaIndices), kakiMejaIndices);

	//Taplak Meja
	binding(VAO[2], VBO[2], EBO[2], sizeof(taplakMeja), taplakMeja, sizeof(taplakMejaIndices), taplakMejaIndices);

	//gelas
	binding(VAO[3], VBO[3], EBO[3], sizeof(gelas), gelas, sizeof(gelasIndices), gelasIndices);
	binding(VAO[10], VBO[10], EBO[10], sizeof(alasGelas), alasGelas, sizeof(alasGelasIndices), alasGelasIndices);

	//piringBulat
	binding(VAO[4], VBO[4], EBO[4], sizeof(piringBulat), piringBulat, sizeof(piringBulatIndices), piringBulatIndices);
	binding(VAO[11], VBO[11], EBO[11], sizeof(alasPiringBulat), alasPiringBulat, sizeof(alasPiringBulatIndices), alasPiringBulatIndices);

	//sendok
	binding(VAO[5], VBO[5], EBO[5], sizeof(sendok), sendok, sizeof(sendokIndices), sendokIndices);
	binding(VAO[6], VBO[6], EBO[6], sizeof(gagangSendok), gagangSendok, sizeof(gagangIndices), gagangIndices);

	//garpu
	binding(VAO[7], VBO[7], EBO[7], sizeof(garpu), garpu, sizeof(garpuindices), garpuindices);
	binding(VAO[8], VBO[8], EBO[8], sizeof(gagangGarpu), gagangGarpu, sizeof(gagangGarpuindices), gagangGarpuindices);

	//piringOval
	binding(VAO[9], VBO[9], EBO[9], sizeof(piringOval), piringOval, sizeof(piringOvalIndices), piringOvalIndices);
	binding(VAO[12], VBO[12], EBO[12], sizeof(alasPiringOval), alasPiringOval, sizeof(alasPiringOvalIndices), alasPiringOvalIndices);

	//piringKotak
	binding(VAO[13], VBO[13], EBO[13], sizeof(piringKotak), piringKotak, sizeof(piringKotakindices), piringKotakindices);

	unsigned int rectVAO, rectVBO;
	glGenVertexArrays(1, &rectVAO);
	glGenBuffers(1, &rectVBO);
	glBindVertexArray(rectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rectangleVertices), &rectangleVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	Shader lightShader("light.vert", "light.frag");
	GLuint lightVAO, lightVBO, lightEBO;

	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);

	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lampu), lampu, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lampuIndices), lampuIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.0f, 0.5f, 2.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	//texture
	texture permukaanMejaTex("permukaan_meja.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	permukaanMejaTex.textureUnit(shaderProgram, "tex0", 0);
	permukaanMejaTex.Bind();
	permukaanMejaTex.Unbind();

	texture kakiMejaTex("kaki_meja.jpg", GL_TEXTURE_2D, GL_TEXTURE0 + 1, GL_RGB, GL_UNSIGNED_BYTE);
	kakiMejaTex.textureUnit(shaderProgram, "tex0", 1);
	kakiMejaTex.Bind();
	kakiMejaTex.Unbind();

	texture taplakMejaTex("taplak_meja.jpg", GL_TEXTURE_2D, GL_TEXTURE0 + 2, GL_RGB, GL_UNSIGNED_BYTE);
	taplakMejaTex.textureUnit(shaderProgram, "tex0", 2);
	taplakMejaTex.Bind();
	taplakMejaTex.Unbind();

	texture gelasTex("gelas.jpg", GL_TEXTURE_2D, GL_TEXTURE0 + 3, GL_RGB, GL_UNSIGNED_BYTE);
	gelasTex.textureUnit(shaderProgram, "tex0", 3);
	gelasTex.Bind();
	gelasTex.Unbind();

	texture piringTex("piring.jpg", GL_TEXTURE_2D, GL_TEXTURE0 + 4, GL_RGB, GL_UNSIGNED_BYTE);
	piringTex.textureUnit(shaderProgram, "tex0", 4);
	piringTex.Bind();
	piringTex.Unbind();

	texture sendokTex("sendok.jpg", GL_TEXTURE_2D, GL_TEXTURE0 + 5, GL_RGB, GL_UNSIGNED_BYTE);
	sendokTex.textureUnit(shaderProgram, "tex0", 5);
	sendokTex.Bind();
	sendokTex.Unbind();

	GLuint scaleUniform = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint translationUniform = glGetUniformLocation(shaderProgram.ID, "translation");
	GLuint rotationUniform = glGetUniformLocation(shaderProgram.ID, "rotation");

	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	// Framebuffer for Shadow Map
	unsigned int shadowMapFBO;
	glGenFramebuffers(1, &shadowMapFBO);

	// Texture for Shadow Map FBO
	unsigned int shadowMapWidth = 1024, shadowMapHeight = 1024;
	unsigned int shadowMap;
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// Prevents darkness outside the frustrum
	float clampColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	// Needed since we don't touch the color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 model = glm::mat4(1.0f);

		// Matrices needed for the light's perspective
		glm::mat4 orthgonalProjection = glm::ortho(-0.6f, 0.6f, -0.6f, 0.6f, 0.1f, 7.5f);
		glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 lightProjection = orthgonalProjection * lightView;

		shadowMapProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));

		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, shadowMapWidth, shadowMapHeight);
		glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);

		//permukaan meja
		model = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(permukaanMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//kaki meja
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.05f, 0.15f, -0.05f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.9f, 0.15f, -0.05f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.9f, 0.15f, -0.9f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.05f, 0.15f, -0.9f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja

		//taplak meja
		model = glm::mat4(1.0f);
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, sizeof(taplakMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//gelas
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.15001f, -0.3f));
		model = glm::scale(model, glm::vec3(0.5f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[3]);
		glDrawElements(GL_TRIANGLES, sizeof(gelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[10]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasGelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piring bulat
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.4f, 0.126f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[4]);
		glDrawElements(GL_TRIANGLES, sizeof(piringBulatIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[11]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasPiringBulatIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piring oval
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.126f, 0.4f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[9]);
		glDrawElements(GL_TRIANGLES, sizeof(piringOvalIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[12]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasPiringOvalIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piring kotak
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.4f, 0.1005f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[13]);
		glDrawElements(GL_TRIANGLES, sizeof(piringKotakindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//sendok
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.4f, 0.1f, 0.15f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(sendokIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[6]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//sendok 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.15f, 0.1f, 0.4f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(sendokIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[6]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//sendok 3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.4f, 0.1f, -0.15f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(sendokIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[6]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//garpu
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.4f, 0.1f, -0.15f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//garpu 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.15f, 0.1f, 0.4f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//garpu 3
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.4f, 0.1f, 0.15f));
		model = glm::scale(model, glm::vec3(0.05f));
		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shadowMapProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, windowWidth, windowHeight);
		glClearColor(0.212f, 0.228f, 0.255f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		shadowScene.Activate();
		glBindVertexArray(rectVAO);
		glActiveTexture(GL_TEXTURE0 + 6);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glUniform1i(glGetUniformLocation(shadowScene.ID, "depthMap"), 6);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));

		glActiveTexture(GL_TEXTURE0 + 6);
		glBindTexture(GL_TEXTURE_2D, shadowMap);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "shadowMap"), 6);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram, "camMatrix");

		glm::mat4 noRotation = glm::mat4(1.0f);
		glm::mat4 rotationMatrix = glm::mat4(1.0f);

		//permukaan meja
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, permukaanMejaTex.ID);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 0);
		glUniform1f(scaleUniform, 0.0f);
		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(noRotation));
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(permukaanMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//kaki meja
		glActiveTexture(GL_TEXTURE0 + 1);
		glBindTexture(GL_TEXTURE_2D, kakiMejaTex.ID);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 1);
		glUniform3f(translationUniform, 0.05f, 0.15f, -0.05f);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja
		glUniform3f(translationUniform, 0.9f, 0.15f, -0.05f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kanan meja
		glUniform3f(translationUniform, 0.9f, 0.15f, -0.9f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kanan belakang
		glUniform3f(translationUniform, 0.05f, 0.15f, -0.9f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri belakang

		//Taplak meja
		glActiveTexture(GL_TEXTURE0 + 2);
		glBindTexture(GL_TEXTURE_2D, taplakMejaTex.ID);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 2);
		taplakMejaTex.Bind();
		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, sizeof(taplakMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//gelas
		glActiveTexture(GL_TEXTURE0 + 3);
		glBindTexture(GL_TEXTURE_2D, gelasTex.ID);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 3);
		glUniform1f(scaleUniform, -0.5f);
		glUniform3f(translationUniform, 0.0f, 0.15001f, -0.3f);
		glBindVertexArray(VAO[3]);
		glDrawElements(GL_TRIANGLES, sizeof(gelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[10]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasGelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piringBulat
		glActiveTexture(GL_TEXTURE0 + 4);
		glBindTexture(GL_TEXTURE_2D, piringTex.ID);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 4);
		glUniform1f(scaleUniform, 0.0f);
		glUniform3f(translationUniform, -0.4f, 0.126f, 0.0f);
		glBindVertexArray(VAO[4]);
		glDrawElements(GL_TRIANGLES, sizeof(piringBulatIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[11]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasPiringBulatIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piringOval
		glUniform3f(translationUniform, 0.0f, 0.126f, 0.4f);
		glBindVertexArray(VAO[9]);
		glDrawElements(GL_TRIANGLES, sizeof(piringOvalIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[12]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasPiringOvalIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piringKotak
		glUniform1f(scaleUniform, -0.95f);
		glUniform3f(translationUniform, 0.4f, 0.1005f, 0.0f);
		glBindVertexArray(VAO[13]);
		glDrawElements(GL_TRIANGLES, sizeof(piringKotakindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//sendok;
		glActiveTexture(GL_TEXTURE0 + 5);
		glBindTexture(GL_TEXTURE_2D, sendokTex.ID);
		glUniform1i(glGetUniformLocation(shaderProgram.ID, "tex0"), 5);
		glUniform1f(scaleUniform, -0.95f);
		glUniform3f(translationUniform, -0.4f, 0.1f, 0.15f);
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(sendokIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[6]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//sendok2
		glUniform3f(translationUniform, 0.15f, 0.1f, 0.4f);
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(sendokIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[6]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//sendok3
		glUniform3f(translationUniform, 0.4f, 0.1f, -0.15f);
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glBindVertexArray(VAO[5]);
		glDrawElements(GL_TRIANGLES, sizeof(sendokIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[6]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Garpu
		glUniform3f(translationUniform, -0.4f, 0.1f, -0.15f);
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Garpu2
		glUniform3f(translationUniform, -0.15f, 0.1f, 0.4f);
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Garpu3
		glUniform3f(translationUniform, 0.4f, 0.1f, 0.15f);
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(rotationMatrix));
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		/*lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, sizeof(lampuIndices) / sizeof(int), GL_UNSIGNED_INT, 0);*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(jumlahObjek, VAO);
	glDeleteBuffers(jumlahObjek, VBO);
	glDeleteBuffers(jumlahIndices, EBO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	glDeleteBuffers(1, &lightEBO);
	permukaanMejaTex.Delete();
	kakiMejaTex.Delete();
	taplakMejaTex.Delete();
	gelasTex.Delete();
	piringTex.Delete();
	sendokTex.Delete();
	shaderProgram.Delete();
	glfwTerminate();
	return 0;
}