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

GLfloat permukaanMeja[] =
{
	// Koordinat simpul		// Warna		//Texture kordinat	//Normals
	// Front face
	-0.5f, 0.05f,  0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.5f, 0.0f, 0.6f,//kiri bawah 0
	 0.5f, 0.05f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	 0.5f, 0.0f, 0.6f,//kanan bawah 1
	 0.5f, 0.1f,  0.5f,		0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	 0.5f, 0.0f, 0.6f,//kanan atas 2
	-0.5f, 0.1f,  0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.5f, 0.0f, 0.6f,//kiri atas 3

	// Back face
	-0.5f, 0.05f, -0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.5f, 0.0f, -0.6f,//kiri bawah 4
	 0.5f, 0.05f, -0.5f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,	 0.5f, 0.0f, -0.6f,//kanan bawah 5
	 0.5f, 0.1f, -0.5f,		0.0f, 0.0f, 1.0f, 1.0f, 1.0f,	 0.5f, 0.0f, -0.6f,//kanan atas 6
	-0.5f, 0.1f, -0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.5f, 0.0f, -0.6f,//kiri atas 7

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
	-0.5f, 0.05f, -0.5f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	-0.6f, 0.0f, -0.5f,//kiri bawah 16
	-0.5f, 0.05f,  0.5f,	1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	-0.6f, 0.0f, 0.5f,//kanan bawah 17
	-0.5f, 0.1f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	-0.6f, 0.0f, 0.5f,//kanan atas 18
	-0.5f, 0.1f, -0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	-0.6f, 0.0f, -0.5f,//kiri atas 19

	//right face
	0.5f, 0.05f, -0.5f,		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,	0.6f, 0.0f, -0.5f,//kiri bawah 20
	0.5f, 0.05f,  0.5f,		1.0f, 0.0f, 0.0f, 1.0f, 0.0f,	0.6f, 0.0f, 0.5f,//kanan bawah 21
	0.5f, 0.1f,  0.5f,		1.0f, 1.0f, 1.0f, 1.0f, 1.0f,	0.6f, 0.0f, 0.5f,//kanan atas 22
	0.5f, 0.1f, -0.5f,		1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	0.6f, 0.0f, -0.5f//kiri atas 23
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
	-0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//kiri bawah 0
	 0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f,//kanan bawah 1
	 0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f,//kanan atas 2
	-0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f,	0.0f, 1.0f,//kiri atas 3

	//right face
	0.50015f, -0.25f, 0.2f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,//kanan bawah depan 4
	0.50015f, -0.25f, -0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,//kanan bawah belakang 5

	//left face
	-0.50015f, -0.25f, 0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 0.0f,//kiri bawah depan 6
	-0.50015f, -0.25f, -0.2f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f//kiri bawah belakang 7
};

GLfloat gelas[jumlahIrisan * 8 * 3];

GLfloat alasGelas[jumlahIrisan * 8 + 7];

GLfloat piringBulat[jumlahIrisan * 8 * 3];

GLfloat alasPiringBulat[jumlahIrisan * 8 + 7];

GLfloat piringOval[jumlahIrisan * 8 * 3];

GLfloat alasPiringOval[jumlahIrisan * 8 + 7];

GLfloat sendok[(latDivs + 1) * (lonDivs + 1) * 8 + 8];

GLfloat gagangSendok[] =
{
	//bottom
	0.47f,0.0f,	0.15f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.8f, 0.0f,	0.15f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.8f, 0.0f,	-0.15f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.47f,0.0f,	-0.15f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	//top
	0.43f,0.1f,	0.15f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.8f, 0.1f,	0.15f,	0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.8f, 0.1f,	-0.15f,	0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	0.43f,0.1f,	-0.15f,	1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	//left side
	0.47f,0.0f,	0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.8f, 0.0f,	0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.8f, 0.1f,	0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.43f,0.1f,	0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	//right side
	0.47f,0.0f,	-0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	1.8f, 0.0f,	-0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	1.8f, 0.1f,	-0.15f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	0.43f,0.1f,	-0.15f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	//front side
	1.8f, 0.0f,	0.15f,	0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	1.8f, 0.0f,	-0.15f,	0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	1.8f, 0.1f,	0.15f,	0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	1.8f, 0.1f,	-0.15f,	0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

	//back side
	0.47f, 0.0f, 0.15f,	1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	0.47f, 0.0f, -0.15f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	0.43f, 0.1f, 0.15f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	0.43f, 0.1f, -0.15f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

GLfloat garpu[] =
{
	// Atas
	-0.4f,	0.1f,	-0.4f, 1.0f, 0.0f, 0.0f,	// 0
	0.0f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 1
	0.2f,	0.1f,	-0.4f, 1.0f, 0.0f, 0.0f,	// 2
	-0.4f,	0.1f,	-0.2f,	0.0f, 1.0f, 0.0f,	// 3
	-0.4f,	0.1f,	-0.1f, 1.0f, 0.0f, 0.0f,	// 4
	0.0f,	0.1f,	-0.1f,	0.0f, 1.0f, 0.0f,	// 5
	-0.4f,	0.1f,	0.1f, 1.0f, 0.0f, 0.0f,		// 6
	0.0f,	0.1f,	0.1f,	0.0f, 1.0f, 0.0f,	// 7
	-0.4f,	0.1f,	0.4f, 1.0f, 0.0f, 0.0f,		// 8
	0.0f,	0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	// 9
	0.2f,	0.1f,	0.4f, 1.0f, 0.0f, 0.0f,		// 10
	-0.4f,	0.1f,	0.2f,	0.0f, 1.0f, 0.0f,	// 11
	0.4f,	0.1f,	0.2f,	1.0f, 1.0f, 1.0f,	// 12
	0.4f,	0.1f,	-0.2f, 1.0f, 0.0f, 0.0f,	// 13

	// Bawah
	-0.4f,	0.0f,	-0.4f, 1.0f, 0.0f, 0.0f,	// 14
	0.0f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 15
	0.2f,	0.0f,	-0.4f, 1.0f, 0.0f, 0.0f,	// 16
	-0.4f,	0.0f,	-0.2f,	0.0f, 1.0f, 0.0f,	// 17
	-0.4f,	0.0f,	-0.1f, 1.0f, 0.0f, 0.0f,	// 18
	0.0f,	0.0f,	-0.1f,	0.0f, 1.0f, 0.0f,	// 19
	-0.4f,	0.0f,	0.1f, 1.0f, 0.0f, 0.0f,		// 20
	0.0f,	0.0f,	0.1f,	0.0f, 1.0f, 0.0f,	// 21
	-0.4f,	0.0f,	0.4f, 1.0f, 0.0f, 0.0f,		// 22
	0.0f,	0.0f,	0.2f,	1.0f, 0.0f, 0.0f,	// 23
	0.2f,	0.0f,	0.4f, 1.0f, 0.0f, 0.0f,		// 24
	-0.4f,	0.0f,	0.2f,	0.0f, 1.0f, 0.0f,	// 25
	0.4f,	0.0f,	0.2f,	1.0f, 1.0f, 1.0f,	// 26
	0.4f,	0.0f,	-0.2f, 1.0f, 0.0f, 0.0f,	// 27
};

GLfloat gagangGarpu[] =
{
	// Atas
	0.4f,	0.1f,	0.2f, 1.0f, 0.0f, 0.0f,		// 0
	0.4f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 1
	1.8f,	0.1f,	0.2f, 1.0f, 0.0f, 0.0f,		// 2
	1.8f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 3

	// kanan
	0.4f,	0.1f,	-0.2f, 1.0f, 0.0f, 0.0f,	// 4
	0.4f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 5
	1.8f,	0.1f,	-0.2f, 1.0f, 0.0f, 0.0f,	// 6
	1.8f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 7

	// kiri
	0.4f,	0.0f,	0.2f, 1.0f, 0.0f, 0.0f,		// 8
	0.4f,	0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	// 9
	1.8f,	0.0f,	0.2f, 1.0f, 0.0f, 0.0f,		// 10
	1.8f,	0.1f,	0.2f,	1.0f, 0.0f, 0.0f,	// 11

	// depan
	0.4f,	0.1f,	0.2f, 1.0f, 0.0f, 0.0f,		// 12
	0.4f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 13
	0.4f,	0.0f,	0.2f, 1.0f, 0.0f, 0.0f,		// 14
	0.4f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 15
	
	// belakang
	1.8f,	0.1f,	0.2f, 1.0f, 0.0f, 0.0f,		// 16
	1.8f,	0.1f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 17
	1.8f,	0.0f,	0.2f, 1.0f, 0.0f, 0.0f,		// 18
	1.8f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 19

	// Bawah
	0.4f,	0.0f,	0.2f, 1.0f, 0.0f, 0.0f,		// 20
	0.4f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 21
	1.8f,	0.0f,	0.2f, 1.0f, 0.0f, 0.0f,		// 22
	1.8f,	0.0f,	-0.2f,	1.0f, 0.0f, 0.0f,	// 23
};

GLfloat piringKotak[] =
{
	//Bawah
	-0.6f,	0.0f,	0.6f,	1.0f, 0.0f, 0.0f,	// 0
	0.6f,	0.0f,	0.6f,	1.0f, 0.0f, 0.0f,	// 1
	0.6f,	0.0f,	-0.6f,	1.0f, 0.0f, 0.0f,	// 2
	-0.6f,	0.0f,	-0.6f,	1.0f, 0.0f, 0.0f,	// 3
	
	// Atas
	-1.6f,	0.7f,	1.6f,	0.0f, 0.0f, 1.0f,	// 4
	1.6f,	0.7f,	1.6f,	0.0f, 1.0f, 0.0f,	// 5
	1.6f,	0.7f,	-1.6f,	0.0f, 0.0f, 1.0f,	// 6
	-1.6f,	0.7f,	-1.6f,	0.0f, 1.0f, 0.0f,	// 7
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
	1, 4, 5, 5, 2, 1,
	0, 6, 7, 7, 3, 0
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
	0, 1, 3, 3, 2, 1,
	1, 0, 4, 4, 5, 1,
	2, 1, 5, 5, 6, 2,
	3, 2, 6, 6, 7, 3,
	0, 3, 7, 7, 4, 0,
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

void binding(GLuint& VAO, GLuint& VBO, GLuint& EBO, GLsizei vboSize ,GLfloat* vboName, GLsizei eboSize,GLuint* eboName)
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

	for (int i = 0; i <= jumlahIrisan; ++i) {
		float sudut = 2.0f * PI / jumlahIrisan;
		float x = jariJari * std::cos(i * sudut);
		float z = jariJari * std::sin(i * sudut);

		//gelas
		// Bottom vertex
		gelas[i * 8 * 2] = x / 2;
		gelas[i * 8 * 2 + 1] = -tinggiGelas / 2.0f;
		gelas[i * 8 * 2 + 2] = z / 2;
		gelas[i * 8 * 2 + 3] = 1.0f; // Red color
		gelas[i * 8 * 2 + 4] = 0.0f; // Green color
		gelas[i * 8 * 2 + 5] = 0.0f; // Blue color
		gelas[i * 8 * 2 + 6] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		gelas[i * 8 * 2 + 7] = 0.0f; // Texture coordinate v

		//alas vertex
		alasGelas[i * 8] = x / 2;
		alasGelas[i * 8 + 1] = -tinggiGelas / 2.0f;
		alasGelas[i * 8 + 2] = z / 2;
		alasGelas[i * 8 + 3] = 0.4f; // Red color
		alasGelas[i * 8 + 4] = 0.2f; // Green color
		alasGelas[i * 8 + 5] = 0.5f; // Blue color
		alasGelas[i * 8 + 6] = 0.3f * (x / jariJari) + 0.5f; // Texture coordinate u
		alasGelas[i * 8 + 7] = 0.2f * (z / jariJari) + 0.5f; // Texture coordinate v
		
		// Top vertex
		gelas[i * 8 * 2 + 8] = x;
		gelas[i * 8 * 2 + 9] = tinggiGelas / 2.0f;
		gelas[i * 8 * 2 + 10] = z;
		gelas[i * 8 * 2 + 11] = 0.0f; // Red color
		gelas[i * 8 * 2 + 12] = 1.0f; // Green color
		gelas[i * 8 * 2 + 13] = 0.0f; // Blue color
		gelas[i * 8 * 2 + 14] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		gelas[i * 8 * 2 + 15] = 1.0f; // Texture coordinate v

		//piring
		// Bottom vertex
		piringBulat[i * 8 * 2] = x / 2;
		piringBulat[i * 8 * 2 + 1] = -tinggiPiring / 2.0f;
		piringBulat[i * 8 * 2 + 2] = z / 2;
		piringBulat[i * 8 * 2 + 3] = 1.0f; // Red color
		piringBulat[i * 8 * 2 + 4] = 0.0f; // Green color
		piringBulat[i * 8 * 2 + 5] = 0.0f; // Blue color
		piringBulat[i * 8 * 2 + 6] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringBulat[i * 8 * 2 + 7] = 0.0f; // Texture coordinate v

		piringOval[i * 8 * 2] = x / 2;
		piringOval[i * 8 * 2 + 1] = -tinggiPiring / 2.0f;
		piringOval[i * 8 * 2 + 2] = z / 2;
		piringOval[i * 8 * 2 + 3] = 1.0f; // Red color
		piringOval[i * 8 * 2 + 4] = 0.0f; // Green color
		piringOval[i * 8 * 2 + 5] = 0.0f; // Blue color
		piringOval[i * 8 * 2 + 6] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringOval[i * 8 * 2 + 7] = 0.0f; // Texture coordinate v

		//alas piring
		alasPiringBulat[i * 8] = x / 2;
		alasPiringBulat[i * 8 + 1] = -tinggiPiring / 2.0f;
		alasPiringBulat[i * 8 + 2] = z / 2;
		alasPiringBulat[i * 8 + 3] = 0.4f; // Red color
		alasPiringBulat[i * 8 + 4] = 0.2f; // Green color
		alasPiringBulat[i * 8 + 5] = 0.5f; // Blue color
		alasPiringBulat[i * 8 + 6] = 0.3f * (x / jariJari) + 0.5f; // Texture coordinate u
		alasPiringBulat[i * 8 + 7] = 0.2f * (z / jariJari) + 0.5f; // Texture coordinate v
		
		alasPiringOval[i * 8] = x / 2;
		alasPiringOval[i * 8 + 1] = -tinggiPiring / 2.0f;
		alasPiringOval[i * 8 + 2] = z / 2;
		alasPiringOval[i * 8 + 3] = 0.4f; // Red color
		alasPiringOval[i * 8 + 4] = 0.2f; // Green color
		alasPiringOval[i * 8 + 5] = 0.5f; // Blue color
		alasPiringOval[i * 8 + 6] = 0.3f * (x / jariJari) + 0.5f; // Texture coordinate u
		alasPiringOval[i * 8 + 7] = 0.2f * (z / jariJari) + 0.5f; // Texture coordinate v

		//top vertex
		piringBulat[i * 8 * 2 + 8] = x;
		piringBulat[i * 8 * 2 + 9] = tinggiPiring / 2.0f;
		piringBulat[i * 8 * 2 + 10] = z;
		piringBulat[i * 8 * 2 + 11] = 0.0f; // Red color
		piringBulat[i * 8 * 2 + 12] = 1.0f; // Green color
		piringBulat[i * 8 * 2 + 13] = 0.0f; // Blue color
		piringBulat[i * 8 * 2 + 14] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringBulat[i * 8 * 2 + 15] = 1.0f; // Texture coordinate v

		piringOval[i * 8 * 2 + 8] = x;
		piringOval[i * 8 * 2 + 9] = tinggiPiring / 2.0f;
		piringOval[i * 8 * 2 + 10] = z / 1.3f;
		piringOval[i * 8 * 2 + 11] = 0.0f; // Red color
		piringOval[i * 8 * 2 + 12] = 1.0f; // Green color
		piringOval[i * 8 * 2 + 13] = 0.0f; // Blue color
		piringOval[i * 8 * 2 + 14] = static_cast<float>(i) / jumlahIrisan; // Texture coordinate u
		piringOval[i * 8 * 2 + 15] = 1.0f; // Texture coordinate v
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

			sendok[vertexIndex++] = theta / (2.0f * PI);
			sendok[vertexIndex++] = 1.0f - (phi / PI);

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
	//binding(VAO[7], VBO[7], EBO[7], sizeof(garpu), garpu, sizeof(garpuindices), garpuindices);
	//binding(VAO[8], VBO[8], EBO[8], sizeof(gagangGarpu), gagangGarpu, sizeof(gagangGarpuindices), gagangGarpuindices);

	//piringOval
	binding(VAO[9], VBO[9], EBO[9], sizeof(piringOval), piringOval, sizeof(piringOvalIndices), piringOvalIndices);
	binding(VAO[12], VBO[12], EBO[12], sizeof(alasPiringOval), alasPiringOval, sizeof(alasPiringOvalIndices), alasPiringOvalIndices);
	
  //piringKotak
	//binding(VAO[13], VBO[13], EBO[13], sizeof(piringKotak), piringKotak, sizeof(piringKotakindices), piringKotakindices);

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

	glm::vec3 lightPos = glm::vec3(0.0f, 0.45f, 0.0f);
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

	texture kakiMejaTex("kaki_meja.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	kakiMejaTex.textureUnit(shaderProgram, "tex0", 0);
	kakiMejaTex.Bind();
	kakiMejaTex.Unbind();

	texture taplakMejaTex("taplak_meja.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	taplakMejaTex.textureUnit(shaderProgram, "tex0", 0);
	taplakMejaTex.Bind();
	taplakMejaTex.Unbind();

	texture gelasTex("gelas.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	gelasTex.textureUnit(shaderProgram, "tex0", 0);
	gelasTex.Bind();
	gelasTex.Unbind();
	
	texture piringTex("piring.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	piringTex.textureUnit(shaderProgram, "tex0", 0);
	piringTex.Bind();
	piringTex.Unbind();
	
	texture sendokTex("sendok.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	sendokTex.textureUnit(shaderProgram, "tex0", 0);
	sendokTex.Bind();
	sendokTex.Unbind();

	GLuint scaleUniform = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint translationUniform = glGetUniformLocation(shaderProgram.ID, "translation");
	GLuint rotationUniform = glGetUniformLocation(shaderProgram.ID, "rotation");

	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.212f, 0.228f, 0.255f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);
		camera.Matrix(shaderProgram, "camMatrix");

		glm::mat4 noRotation = glm::mat4(1.0f);
		glm::mat4 rotationMatrix = glm::mat4(1.0f);

		//permukaan meja
		permukaanMejaTex.Bind();
		glUniform1f(scaleUniform, 0.0f);
		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glUniformMatrix4fv(rotationUniform, 1, GL_FALSE, glm::value_ptr(noRotation));
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(permukaanMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//kaki meja
		kakiMejaTex.Bind();
		glUniform3f(translationUniform, 0.05f, 0.15f, -0.05f);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices)/sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja
		glUniform3f(translationUniform, 0.9f, 0.15f, -0.05f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices)/sizeof(int), GL_UNSIGNED_INT, 0);//kaki kanan meja
		glUniform3f(translationUniform, 0.9f, 0.15f, -0.9f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kanan belakang
		glUniform3f(translationUniform, 0.05f, 0.15f, -0.9f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri belakang

		/*/Taplak meja
		taplakMejaTex.Bind();
		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, sizeof(taplakMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//gelas
		gelasTex.Bind();
		glUniform1f(scaleUniform, -0.5f);
		glUniform3f(translationUniform, 0.0f, 0.15001f, -0.3f);
		glBindVertexArray(VAO[3]);
		glDrawElements(GL_TRIANGLES, sizeof(gelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[10]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(alasGelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piringBulat
		piringTex.Bind();
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

		//sendok;
		sendokTex.Bind();
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
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Garpu2
		glUniform3f(translationUniform, -0.15f, 0.1f, 0.4f);
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
		//piringKotak
		glUniform3f(translationUniform, 0.4f, 0.1005f, 0.0f);
		glBindVertexArray(VAO[10]);
		glDrawElements(GL_TRIANGLES, sizeof(piringKotakindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//Garpu3
		glUniform3f(translationUniform, 0.4f, 0.1f, 0.15f);
		glBindVertexArray(VAO[7]);
		glDrawElements(GL_TRIANGLES, sizeof(garpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glBindVertexArray(VAO[8]);
		glDrawElements(GL_TRIANGLES, sizeof(gagangGarpuindices) / sizeof(int), GL_UNSIGNED_INT, 0);*/

		lightShader.Activate();
		camera.Matrix(lightShader, "camMatrix");
		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, sizeof(lampuIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

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