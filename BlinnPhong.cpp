#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<bits/stdc++.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
int screenWidth = 800;
int screenHeight = 600;
void checkShaderError(GLuint);
void framebuffer_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normV;\n"
"out vec3 normVFrag;\n"
"out vec4 fragPos;\n"
"uniform mat4 model, view, projection;\n"
"void main() {\n"
	"gl_Position = projection * view * model * vec4(position, 1.0f);\n"
	"normVFrag = normV;\n"
	"fragPos = model * vec4(position, 1.0f);\n"
"}\0";
const char* objFragShaderSource = "#version 330 core\n"
"in vec3 normVFrag;\n"
"in vec4 fragPos;\n"
"out vec4 outColor;\n"
"uniform vec3 lightColor;\n"
"uniform vec3 lightPos;\n"
"uniform vec3 cameraPos;\n"
"uniform vec3 objColor;\n"
"uniform float specularStrength;\n"
"void main() {\n"
	"vec3 fragPosV3 = vec3(fragPos.x, fragPos.y, fragPos.z);\n"
	"vec3 norm = normalize(normVFrag);\n"
	"vec3 vec2Light = normalize(lightPos - fragPosV3);\n"
	"vec3 vec2Camera = normalize(cameraPos - fragPosV3);\n"
	"vec3 ambient = 0.1 * lightColor;\n"
	"vec3 diffuse = max(dot(norm, vec2Light), 0.0) * lightColor;\n"
	"vec3 specular = lightColor * specularStrength * pow(max(dot(norm, normalize((vec2Light + vec2Camera)/2)), 0.0), 256);\n"//Blinn-Phong
	"outColor = vec4(ambient+ diffuse + specular, 1.0)*vec4(objColor, 1.0f);\n"
"}\0";
const char* lightFragShaderSource = "#version 330 core\n"
"out vec4 outColor;\n"
"uniform vec3 color;\n"
"void main() {\n"
	"outColor = vec4(color, 1.0f);"
"}\0";
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "TEST", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD ERR" << std::endl;
		return -1;
	}

	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vShader); checkShaderError(vShader);
	GLuint lightFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(lightFragShader, 1, &lightFragShaderSource, NULL);
	glCompileShader(lightFragShader); checkShaderError(lightFragShader);
	GLuint objFragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(objFragShader, 1, &objFragShaderSource, NULL);
	glCompileShader(objFragShader); checkShaderError(objFragShader);

	GLuint lightProg = glCreateProgram();
	glAttachShader(lightProg, vShader);
	glAttachShader(lightProg, lightFragShader);
	glLinkProgram(lightProg);
	GLuint objProg = glCreateProgram();
	glAttachShader(objProg, vShader);
	glAttachShader(objProg, objFragShader);
	glLinkProgram(objProg);

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	GLuint vao, vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (sizeof(float)), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * (sizeof(float)), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	glm::vec3 cameraPos = glm::vec3(0.0, 0.0, 3.0f);
	glm::vec3 lightPos(2.0f, 0.3f, 2.0f);
	float fov = 45.0, specularStrength = 0.5f;
	float pitch = 0.0f, yaw = 90.0f;
	float radius = 3.0f;
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.4, 0.3, 0.2, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cameraPos = glm::vec3(radius * std::cos(pitch)* std::cos(yaw), radius * std::sin(pitch), radius * std::cos(pitch) * std::sin(yaw));

		glm::mat4 model = glm::mat4(1.0f);
		
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(fov), (float)(800.0 / 600.0), 0.1f, 100.0f);
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec3 objColor = glm::vec3(1.0f, 1.0f, 0.0f);

		glUseProgram(lightProg);
		glBindVertexArray(vao);

		glUniform3fv(glGetUniformLocation(lightProg, "color"),1, glm::value_ptr(lightColor));

		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(.2f));
		glUniformMatrix4fv(glGetUniformLocation(lightProg, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(lightProg, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lightProg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 36);
		//-----------------------------------------------------------------------------
		glUseProgram(objProg);
		glBindVertexArray(vao);

		glUniform3fv(glGetUniformLocation(objProg, "objColor"), 1, glm::value_ptr(objColor));
		glUniform3fv(glGetUniformLocation(objProg, "lightColor"), 1, glm::value_ptr(lightColor));
		glUniform3fv(glGetUniformLocation(objProg, "cameraPos"), 1, glm::value_ptr(glm::vec3(cameraPos)));
		glUniform3fv(glGetUniformLocation(objProg, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform1f(glGetUniformLocation(objProg, "specularStrength"), specularStrength);

		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(objProg, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(objProg, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(objProg, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GL_TRUE) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GL_TRUE) {
			yaw += 0.003f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GL_TRUE) {
			yaw -= 0.003f;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GL_TRUE) {
			pitch -= 0.003f;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GL_TRUE) {
			pitch += 0.003f;
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GL_TRUE) {
			fov += 0.1f;
			fov = std::min(fov, 85.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GL_TRUE) {
			fov -= 0.1f;
			fov = std::max(fov, 10.0f);
		}
		if (glfwGetKey(window, GLFW_KEY_1) == GL_TRUE) {
			specularStrength += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_2) == GL_TRUE) {
			specularStrength -= 0.01f;
			specularStrength = std::max(specularStrength, 0.0f);
		}
	}
	glfwTerminate();
	return 0;
}
void checkShaderError(GLuint shader) {
	int success;
	char errMsg[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, errMsg);
		std::cout << errMsg << std::endl;
		exit(-1);
	}
	return;
}
