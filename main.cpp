#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include"shaderClass.h"
#include"camera.h"

const int windowWidth = 800;
const int windowHeight = 800;

const int jumlahObjek = 5;
const int jumlahIndices = 5;

//properti Gelas
const int jumlahIrisan = 50;
const float jariJari = 0.1f;
const float tinggiGelas = 0.2f;

//properti piring
const float tinggiPiring = 0.05f;

GLfloat permukaanMeja[] =
{
	// Koordinat simpul		// Warna
	// Front face
	-0.5f, -0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 0
	 0.5f, -0.1f,  0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 1
	 0.5f,  0.1f,  0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 2
	-0.5f,  0.1f,  0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 3

	// Back face
	-0.5f, -0.1f, -0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 4
	 0.5f, -0.1f, -0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 5
	 0.5f,  0.1f, -0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 6
	-0.5f,  0.1f, -0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 7

	// Top face
	-0.5f,  0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 8
	 0.5f,  0.1f,  0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 9
	 0.5f,  0.1f, -0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 10
	-0.5f,  0.1f, -0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 11

	// Bottom face
	-0.5f, -0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 12
	 0.5f, -0.1f,  0.5f,	0.0f, 1.0f, 0.0f, //kanan bawah 13
	 0.5f, -0.1f, -0.5f,	0.0f, 0.0f, 1.0f, //kanan atas 14
	-0.5f, -0.1f, -0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 15

	//left face
	-0.5f, -0.1f, -0.5f,	1.0f, 0.0f, 0.0f, //kiri bawah 16
	-0.5f, -0.1f,  0.5f,	1.0f, 0.0f, 0.0f, //kanan bawah 17
	-0.5f,  0.1f,  0.5f,	1.0f, 1.0f, 1.0f, //kanan atas 18
	-0.5f,  0.1f, -0.5f,	1.0f, 1.0f, 1.0f, //kiri atas 19

	//right face
	0.5f, -0.1f, -0.5f,		1.0f, 0.0f, 0.0f, //kiri bawah 20
	0.5f, -0.1f,  0.5f,		1.0f, 0.0f, 0.0f, //kanan bawah 21
	0.5f,  0.1f,  0.5f,		1.0f, 1.0f, 1.0f, //kanan atas 22
	0.5f,  0.1f, -0.5f,		1.0f, 1.0f, 1.0f //kiri atas 23
};

GLfloat kakiMeja[] =
{
	//front face
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  //0
	-0.3f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  //1
	-0.3f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f,  //2
	-0.5f, -0.1f,  0.5f,	1.0f, 1.0f, 1.0f,  //3

	//back face						  
	-0.5f, -0.5f,  0.3f,	1.0f, 0.0f, 0.0f,  //4
	-0.3f, -0.5f,  0.3f,	0.0f, 1.0f, 0.0f,  //5
	-0.3f, -0.1f,  0.3f,	0.0f, 0.0f, 1.0f,  //6
	-0.5f, -0.1f,  0.3f,	1.0f, 1.0f, 1.0f,  //7

	//bottom face						  
	-0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,  //8
	-0.3f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  //9
	-0.3f, -0.5f,  0.3f,	0.0f, 0.0f, 1.0f,  //10
	-0.5f, -0.5f,  0.3f,	1.0f, 1.0f, 1.0f,  //11

	//left face
	-0.5f, -0.5f,  0.3f,	1.0f, 0.0f, 0.0f,  //12
	-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  //13
	-0.5f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f,  //14
	-0.5f, -0.1f,  0.3f,	1.0f, 1.0f, 1.0f,   //15

	//left face
	-0.3f, -0.5f,  0.3f,	1.0f, 0.0f, 0.0f,  //16
	-0.3f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,  //17
	-0.3f, -0.1f,  0.5f,	0.0f, 0.0f, 1.0f,  //18
	-0.3f, -0.1f,  0.3f,	1.0f, 1.0f, 1.0f   //19
};

GLfloat taplakMeja[] =
{
	// Koordinat simpul		// Warna
	// Top face
	-0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f, //kiri bawah 0
	 0.5f,  0.1001f,  0.2f,		1.0f, 1.0f, 1.0f, //kanan bawah 1
	 0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f, //kanan atas 2
	-0.5f,  0.1001f,  -0.2f,	1.0f, 1.0f, 1.0f,  //kiri atas 3

	//right face
	0.50015f, -0.25f, 0.2f,		1.0f, 1.0f, 1.0f,	//kanan bawah depan 4
	0.50015f, -0.25f, -0.2f,	1.0f, 1.0f, 1.0f,	//kanan bawah belakang 5

	//left face
	-0.50015f, -0.25f, 0.2f,	1.0f, 1.0f, 1.0f,	//kiri bawah depan 6
	-0.50015f, -0.25f, -0.2f,	1.0f, 1.0f, 1.0f,	//kiri bawah belakang 7
};

GLfloat gelas[50 * 6 * 3 + 5];

GLfloat piringBulat[50 * 6 * 3 + 5];

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

GLuint gelasIndices[50 * 3 * 2 + 50];

GLuint piringBulatIndices[50 * 3 * 2 + 50];

void binding(GLuint& VAO, GLuint& VBO, GLuint& EBO, GLsizei vboSize ,GLfloat* vboName, GLsizei eboSize,GLuint* eboName)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vboSize, vboName, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboSize, eboName, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
		float sudut = 2 * 3.14159265359 / jumlahIrisan;
		float x = jariJari * cos(i * sudut);
		float z = jariJari * sin(i * sudut);

		//gelas
		// Bottom vertex
		gelas[i * 6 * 2] = x / 2;
		gelas[i * 6 * 2 + 1] = -tinggiGelas / 2.0f;
		gelas[i * 6 * 2 + 2] = z / 2;
		gelas[i * 6 * 2 + 3] = 1.0f; // Red color
		gelas[i * 6 * 2 + 4] = 0.0f; // Green color
		gelas[i * 6 * 2 + 5] = 0.0f; // Blue color

		//alas vertex
		gelas[i * 6 + 600] = x / 2;
		gelas[i * 6 + 601] = -tinggiGelas / 2.0f;
		gelas[i * 6 + 602] = z / 2;
		gelas[i * 6 + 603] = 0.4f; // Red color
		gelas[i * 6 + 604] = 0.2f; // Green color
		gelas[i * 6 + 605] = 0.5f; // Blue color
		
		// Top vertex
		gelas[i * 6 * 2 + 6] = x;
		gelas[i * 6 * 2 + 7] = tinggiGelas / 2.0f;
		gelas[i * 6 * 2 + 8] = z;
		gelas[i * 6 * 2 + 9] = 0.0f; // Red color
		gelas[i * 6 * 2 + 10] = 1.0f; // Green color
		gelas[i * 6 * 2 + 11] = 0.0f; // Blue color

		//piring
		// Bottom vertex
		piringBulat[i * 6 * 2] = x / 2;
		piringBulat[i * 6 * 2 + 1] = -tinggiPiring / 2.0f;
		piringBulat[i * 6 * 2 + 2] = z / 2;
		piringBulat[i * 6 * 2 + 3] = 1.0f; // Red color
		piringBulat[i * 6 * 2 + 4] = 0.0f; // Green color
		piringBulat[i * 6 * 2 + 5] = 0.0f; // Blue color

		//alas piring
		piringBulat[i * 6 + 600] = x / 2;
		piringBulat[i * 6 + 601] = -tinggiPiring / 2.0f;
		piringBulat[i * 6 + 602] = z / 2;
		piringBulat[i * 6 + 603] = 0.4f; // Red color
		piringBulat[i * 6 + 604] = 0.2f; // Green color
		piringBulat[i * 6 + 605] = 0.5f; // Blue color

		//top vertex
		piringBulat[i * 6 * 2 + 6] = x;
		piringBulat[i * 6 * 2 + 7] = tinggiPiring / 2.0f;
		piringBulat[i * 6 * 2 + 8] = z;
		piringBulat[i * 6 * 2 + 9] = 0.0f; // Red color
		piringBulat[i * 6 * 2 + 10] = 1.0f; // Green color
		piringBulat[i * 6 * 2 + 11] = 0.0f; // Blue color
	}

	for (int i = 0; i < jumlahIrisan; ++i) {
		//gelas
		// sisi
		gelasIndices[i * 6] = i * 2;
		gelasIndices[i * 6 + 1] = (i + 1) * 2;
		gelasIndices[i * 6 + 2] = (i + 1) * 2 + 1;

		gelasIndices[i * 6 + 3] = (i + 1) * 2 + 1;
		gelasIndices[i * 6 + 4] = i * 2 + 1;
		gelasIndices[i * 6 + 5] = i * 2;

		// alas
		gelasIndices[i + 300] = i * 2;

		//piring
		// sisi
		piringBulatIndices[i * 6] = i * 2;
		piringBulatIndices[i * 6 + 1] = (i + 1) * 2;
		piringBulatIndices[i * 6 + 2] = (i + 1) * 2 + 1;

		piringBulatIndices[i * 6 + 3] = (i + 1) * 2 + 1;
		piringBulatIndices[i * 6 + 4] = i * 2 + 1;
		piringBulatIndices[i * 6 + 5] = i * 2;

		// alas
		piringBulatIndices[i + 300] = i * 2;
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

	//piringBulat
	binding(VAO[4], VBO[4], EBO[4], sizeof(piringBulat), piringBulat, sizeof(piringBulatIndices), piringBulatIndices);

	GLuint scaleUniform = glGetUniformLocation(shaderProgram.ID, "scale");
	GLuint translationUniform = glGetUniformLocation(shaderProgram.ID, "translation");

	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.212f, 0.228f, 0.255f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		//permukaan meja
		glUniform1f(scaleUniform, 0.0f);
		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[0]);
		glDrawElements(GL_TRIANGLES, sizeof(permukaanMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[1]);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices)/sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri meja
		glUniform3f(translationUniform, 0.8f, 0.0f, 0.0f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices)/sizeof(int), GL_UNSIGNED_INT, 0);//kaki kanan meja
		glUniform3f(translationUniform, 0.8f, 0.0f, -0.8f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kanan belakang
		glUniform3f(translationUniform, 0.0f, 0.0f, -0.8f);
		glDrawElements(GL_TRIANGLES, sizeof(kakiMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);//kaki kiri belakang

		//Taplak meja
		glUniform3f(translationUniform, 0.0f, 0.0f, 0.0f);
		glBindVertexArray(VAO[2]);
		glDrawElements(GL_TRIANGLES, sizeof(taplakMejaIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//gelas
		glUniform1f(scaleUniform, -0.5f);
		glUniform3f(translationUniform, 0.0f, 0.15001f, -0.3f);
		glBindVertexArray(VAO[3]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(gelasIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		//piringBulat
		glUniform1f(scaleUniform, 0.0f);
		glUniform3f(translationUniform, -0.4f, 0.126f, 0.0f);
		glBindVertexArray(VAO[4]);
		glDrawElements(GL_TRIANGLE_FAN, sizeof(piringBulatIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(jumlahObjek, VAO);
	glDeleteBuffers(jumlahObjek, VBO);
	glDeleteBuffers(jumlahIndices, EBO);
	shaderProgram.Delete();
	glfwTerminate();
	return 0;
}