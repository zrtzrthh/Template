#include <GLFW/glfw3.h>
#include <GL/gl.h>

float vertices[] = {
    -0.5f, -0.5f, 0.0f,  // ���½�
     0.5f, -0.5f, 0.0f,  // ���½�
     0.0f,  0.5f, 0.0f   // ����
};

void init()
{
  glViewport(0, 0, 640, 480);  // �����ӿڴ�С
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);  // ���ñ�����ɫ
  glEnableClientState(GL_VERTEX_ARRAY);  // ���ö�������
}

void render()
{
  glClear(GL_COLOR_BUFFER_BIT);  // �����ɫ������

  // ����������
  glVertexPointer(3, GL_FLOAT, 0, vertices);  // ���ö�������ָ��
  glDrawArrays(GL_TRIANGLES, 0, 3);  // ����������
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

  // ���� VSync �Է�ֹ֡��������
  glfwSwapInterval(0);

  // ��ʼ��OpenGL����
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
