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
	/*在main函数中调用glfwInit函数来初始化GLFW
	  使用glfwWindowsHint函数来配置GLFW
	  第一个参数代表一个选项：可以从很多GLFW_开头的枚举值
	  第二个参数接受一个整形，用来设置该选项的值
	  https://www.glfw.org/docs/latest/window.html#window_hints
	  将主版本号(Major)和次版本号(Minor)都设为3。我们同样明确告诉GLFW我们使用的是核心模式(Core-profile)，并且不允许用户调整窗口的大小。
	*/

	GLFWwindow* windows = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (windows == nullptr) {
		std::cout << "Failed to create glfw windows" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(windows);
	/*
	  glfwCreateWindows 需要窗口的宽和高作为参数，第三个参数是窗口的名称
	*/

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	/*
	  glew 用来管理OpenGL的函数指针
	  我们在初始化GLEW之前设置glewExperimental变量的值为GL_TRUE，这样做能让GLEW在管理OpenGL的函数指针时
	  更多地使用现代化的技术，如果把它设置为GL_FALSE的话可能会在使用OpenGL的核心模式时出现一些问题。
	*/
	int width, height;
	glfwGetFramebufferSize(windows, &width, &height);
	glViewport(0, 0, width, height);

	/*
	  图形渲染管线的第一个部分是顶点着色器(Vertex Shader)，它把一个单独的顶点作为输入。顶点着色器主要的目的是把3D坐标转为另一种3D坐标（后面会解释），
	  同时顶点着色器允许我们对顶点属性进行一些基本处理。

	  图元装配(Primitive Assembly)阶段将顶点着色器输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），
	  并所有的点装配成指定图元的形状；本节例子中是一个三角形。图元装配阶段的输出会传递给几何着色器(Geometry Shader)。
	  
	  几何着色器把图元形式的一系列顶点的集合作为输入，它可以通过产生新顶点构造出新的（或是其它的）图元来生成其他形状。例子中，它生成了另一个三角形。
	  
	  几何着色器的输出会被传入光栅化阶段(Rasterization Stage)，这里它会把图元映射为最终屏幕上相应的像素，生成供片段着色器(Fragment Shader)使用的片段(Fragment)。
	  在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。
	
	*/

	GLfloat vertices[] = {
		-0.5f,-0.5f,0.0f,
		 0.5f,-0.5f,0.0f,
		 0.0f,0.5f,0.0f
	};
	/*
	由于OpenGL是在3D空间中工作的，而我们渲染的是一个2D三角形，我们将它顶点的z坐标设置为0.0。
	这样子的话三角形每一点的深度都是一样的，从而使它看上去像是2D的。
	*/





	while (!glfwWindowShouldClose(windows)) {
		/*检查事件*/
		glfwPollEvents();
		/*渲染*/
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		/*
		  除了glClear之外，我们还调用了glClearColor来设置清空屏幕所用的颜色。
		  当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。
		*/
		/*交换缓冲*/
		glfwSwapBuffers(windows);
		glfwSetKeyCallback(windows, key_callback);
	}
	/*
	  glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后游戏循环便结束了，之后为我们就可以关闭应用程序了。
	  glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等），然后调用对应的回调函数（可以通过回调方法手动设置）。我们一般在游戏循环的开始调用事件处理函数。
	  glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。	
	*/
	glfwTerminate();
	return 0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}