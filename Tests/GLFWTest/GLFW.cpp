#include <GLFW/glfw3.h>
#include <GL/gl.h>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,  // 左下角
     0.5f, -0.5f, 0.0f,  // 右下角
     0.0f,  0.5f, 0.0f   // 顶部
};

void init()
{
  glViewport(0, 0, 640, 480);  // 设置视口大小
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // 设置背景颜色
  glEnableClientState(GL_VERTEX_ARRAY);  // 启用顶点数组
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);  // 清除颜色缓冲区

  // 绘制三角形
  glVertexPointer(3, GL_FLOAT, 0, vertices);  // 设置顶点数组指针
  glDrawArrays(GL_TRIANGLES, 0, 3);  // 绘制三角形
}

int main(void)
{
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // 禁用 VSync 以防止帧交换问题
  glfwSwapInterval(0);

  // 初始化OpenGL设置
  init();

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window))
  {
    /* Render here */
    render();

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
