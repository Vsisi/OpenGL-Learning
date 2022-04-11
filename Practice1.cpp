#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<bits/stdc++.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
void checkShaderError(GLuint);
const char* vShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
//"layout (location = 1) in vec3 color;\n"
"layout (location = 1) in vec2 texCoord;\n"
//"layout (location = 2) in vec2 texCoord;\n"
//"out vec4 fColor;\n"
"out vec2 fTexCoord;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main(){\n"
"gl_Position = projection * view * model * vec4(position, 1.0f);\n"
//"fColor = vec4(color, 1.0f);\n"
"fTexCoord = texCoord;\n"
"}\0";
const char* fShaderSource = "#version 330 core\n"
"in vec2 fTexCoord;\n"
//"in vec4 fColor;\n"
"out vec4 fragColor;\n"
"uniform sampler2D texture0;\n"
"uniform sampler2D texture1;\n"
"void main(){\n"
"fragColor = mix(texture(texture0, fTexCoord), texture(texture1, fTexCoord), 0.2);\n"
//"fragColor = mix(texture(texture0, fTexCoord), texture(texture1, fTexCoord), 0.2) * fColor;\n"
"}\0";
void framebuffer_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
int main() {

	stbi_set_flip_vertically_on_load(true);


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "name", NULL, NULL);
	if (!window) {
		std::cout << "Window error" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Glad error" << std::endl;
		return -1;
	}

	GLuint vShader=glCreateShader(GL_VERTEX_SHADER), fShader=glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vShaderSource, NULL); 
	glShaderSource(fShader, 1, &fShaderSource, NULL); 
	glCompileShader(vShader); checkShaderError(vShader);
	glCompileShader(fShader); checkShaderError(fShader);

	GLuint prog = glCreateProgram();
	glAttachShader(prog, vShader);
	glAttachShader(prog, fShader);
	glLinkProgram(prog);

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vao, vbo, ebo, tex0, tex1;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);


	glGenTextures(1, &tex0);
	glBindTexture(GL_TEXTURE_2D, tex0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	int width1, height1, nrChannels1;
	unsigned char* data1 = stbi_load("C:\\sundries\\Download\\container.jpg", &width1, &height1, &nrChannels1, 0);
	if (data1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else {
		std::cout << "Texture 0 load error" << std::endl;
		return -1;
	}
	stbi_image_free(data1);

	glGenTextures(1, &tex1);
	glBindTexture(GL_TEXTURE_2D, tex1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	int width2, height2, nrChannels2;
	unsigned char* data2 = stbi_load("C:\\sundries\\Download\\awesomeface.png", &width2, &height2, &nrChannels2, 0);
	if (data2) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}else {
		std::cout << "Texture 1 load error" << std::endl;
		return -1;
	}
	stbi_image_free(data2);

	glUseProgram(prog);
	glUniform1i(glGetUniformLocation(prog, "texture0"), 0);
	glUniform1i(glGetUniformLocation(prog, "texture1"), 1);

	
	float fov = 45.0f;
	float width = 800.0f;
	float height = 600.0f;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
	float curTime = 0.0f, lastTime = 0.0f;
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5, 0.3, 0.2, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(prog);
		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex1);

		glm::vec3 cubePositions[] = {
		  glm::vec3(0.0f,  0.0f,  0.0f),
		  glm::vec3(2.0f,  5.0f, -15.0f),
		  glm::vec3(-1.5f, -2.2f, -2.5f),
		  glm::vec3(-3.8f, -2.0f, -12.3f),
		  glm::vec3(2.4f, -0.4f, -3.5f),
		  glm::vec3(-1.7f,  3.0f, -7.5f),
		  glm::vec3(1.3f, -2.0f, -2.5f),
		  glm::vec3(1.5f,  2.0f, -2.5f),
		  glm::vec3(1.5f,  0.2f, -1.5f),
		  glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, cameraPos);

			glm::mat4 projection = glm::mat4(1.0f);
			projection = glm::perspective(glm::radians(fov), float(width / height), 0.1f, 100.0f);
			glUniformMatrix4fv(glGetUniformLocation(prog, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(glGetUniformLocation(prog, "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(prog, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0

		glfwSwapBuffers(window);
		glfwPollEvents();
		curTime = glfwGetTime();
		std::cout << curTime << std::endl;
		float deltaTime = curTime - lastTime;
		lastTime = curTime;
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GL_TRUE) {
			glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GL_TRUE) {
			cameraPos.y -= 8.0f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GL_TRUE) {
			cameraPos.y += 2.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GL_TRUE) {
			cameraPos.x += 2.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GL_TRUE) {
			cameraPos.x -= 2.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GL_TRUE) {
			cameraPos.z += 2.5f * deltaTime;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GL_TRUE) {
			cameraPos.z -= 2.5f * deltaTime;
		}
	}

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
