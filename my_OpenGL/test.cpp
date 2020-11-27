#define GLEW_STATIC
#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	/*��main�����е���glfwInit��������ʼ��GLFW
	  ʹ��glfwWindowsHint����������GLFW
	  ��һ����������һ��ѡ����ԴӺܶ�GLFW_��ͷ��ö��ֵ
	  �ڶ�����������һ�����Σ��������ø�ѡ���ֵ
	  https://www.glfw.org/docs/latest/window.html#window_hints
	  �����汾��(Major)�ʹΰ汾��(Minor)����Ϊ3������ͬ����ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)�����Ҳ������û��������ڵĴ�С��
	*/

	GLFWwindow* windows = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (windows == nullptr) {
		std::cout << "Failed to create glfw windows" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(windows);
	/*
	  glfwCreateWindows ��Ҫ���ڵĿ�͸���Ϊ�����������������Ǵ��ڵ�����
	*/

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	/*
	  glew ��������OpenGL�ĺ���ָ��
	  �����ڳ�ʼ��GLEW֮ǰ����glewExperimental������ֵΪGL_TRUE������������GLEW�ڹ���OpenGL�ĺ���ָ��ʱ
	  �����ʹ���ִ����ļ����������������ΪGL_FALSE�Ļ����ܻ���ʹ��OpenGL�ĺ���ģʽʱ����һЩ���⡣
	*/
	int width, height;
	glfwGetFramebufferSize(windows, &width, &height);
	glViewport(0, 0, width, height);

	/*
	  ͼ����Ⱦ���ߵĵ�һ�������Ƕ�����ɫ��(Vertex Shader)������һ�������Ķ�����Ϊ���롣������ɫ����Ҫ��Ŀ���ǰ�3D����תΪ��һ��3D���꣨�������ͣ���
	  ͬʱ������ɫ���������ǶԶ������Խ���һЩ��������

	  ͼԪװ��(Primitive Assembly)�׶ν�������ɫ����������ж�����Ϊ���루�����GL_POINTS����ô����һ�����㣩��
	  �����еĵ�װ���ָ��ͼԪ����״��������������һ�������Ρ�ͼԪװ��׶ε�����ᴫ�ݸ�������ɫ��(Geometry Shader)��
	  
	  ������ɫ����ͼԪ��ʽ��һϵ�ж���ļ�����Ϊ���룬������ͨ�������¶��㹹����µģ����������ģ�ͼԪ������������״�������У�����������һ�������Ρ�
	  
	  ������ɫ��������ᱻ�����դ���׶�(Rasterization Stage)�����������ͼԪӳ��Ϊ������Ļ����Ӧ�����أ����ɹ�Ƭ����ɫ��(Fragment Shader)ʹ�õ�Ƭ��(Fragment)��
	  ��Ƭ����ɫ������֮ǰ��ִ�в���(Clipping)�����лᶪ�����������ͼ������������أ���������ִ��Ч�ʡ�
	
	*/

	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f,
		 0.5f,-0.5f,0.0f,
		 0.0f,0.5f,0.0f
	};
	/*
	����OpenGL����3D�ռ��й����ģ���������Ⱦ����һ��2D�����Σ����ǽ��������z��������Ϊ0.0��
	�����ӵĻ�������ÿһ�����ȶ���һ���ģ��Ӷ�ʹ������ȥ����2D�ġ�
	*/





	while (!glfwWindowShouldClose(windows)) {
		/*����¼�*/
		glfwPollEvents();
		/*��Ⱦ*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		/*
		  ����glClear֮�⣬���ǻ�������glClearColor�����������Ļ���õ���ɫ��
		  ������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ��
		*/
		/*��������*/
		glfwSwapBuffers(windows);
		glfwSetKeyCallback(windows, key_callback);
	}
	/*
	  glfwWindowShouldClose����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ϸѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
	  glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ���Ȼ����ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�������һ������Ϸѭ���Ŀ�ʼ�����¼���������
	  glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�	
	*/
	glfwTerminate();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}