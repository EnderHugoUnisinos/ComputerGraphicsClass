/*
 * Hello Triangle - Código adaptado de:
 *   - https://learnopengl.com/#!Getting-started/Hello-Triangle
 *   - https://antongerdelan.net/opengl/glcontext2.html
 *
 * Adaptado por: Rossana Baptista Queiroz
 *
 * Disciplinas:
 *   - Processamento Gráfico (Ciência da Computação - Híbrido)
 *   - Processamento Gráfico: Fundamentos (Ciência da Computação - Presencial)
 *   - Fundamentos de Computação Gráfica (Jogos Digitais)
 *
 * Descrição:
 *   Este código é o "Olá Mundo" da Computação Gráfica, utilizando OpenGL Moderna.
 *   No pipeline programável, o desenvolvedor pode implementar as etapas de
 *   Processamento de Geometria e Processamento de Pixel utilizando shaders.
 *   Um programa de shader precisa ter, obrigatoriamente, um Vertex Shader e um Fragment Shader,
 *   enquanto outros shaders, como o de geometria, são opcionais.
 *
 * Histórico:
 *   - Versão inicial: 07/04/2017
 *   - Última atualização: 18/03/2025
 *
 */

 #include <iostream>
 #include <string>
 #include <assert.h>
 #include <cmath>
 
 using namespace std;
 
 // GLAD
 #include <glad/glad.h>
 
 // GLFW
 #include <GLFW/glfw3.h>
 
 // Protótipo da função de callback de teclado
 void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
 
 // Protótipos das funções
 int setupShader();
 int setupFloorGeometry();
 int setupWallGeometry();
 int setupWindowGeometry();
 int setupRoofGeometry();
 
 // Dimensões da janela (pode ser alterado em tempo de execução)
 const GLuint WIDTH = 500, HEIGHT = 500;
 
 // Código fonte do Vertex Shader (em GLSL): ainda hardcoded
 const GLchar *vertexShaderSource = R"(
  #version 400
  layout (location = 0) in vec3 position;
  layout (location = 1) in vec3 color;
  out vec3 vColor;
  void main()
  {
     vColor = color;
     gl_Position = vec4(position, 1.0);
  }
  )";
 
 // Código fonte do Fragment Shader (em GLSL): ainda hardcoded
 const GLchar *fragmentShaderSource = R"(
  #version 400
  in vec3 vColor;
  out vec4 color;
  void main()
  {
      color = vec4(vColor,1.0);
  }
  )";
 
 // Função MAIN
 int main()
 {
     // Inicialização da GLFW
     glfwInit();
 
     // Muita atenção aqui: alguns ambientes não aceitam essas configurações
     // Você deve adaptar para a versão do OpenGL suportada por sua placa
     // Sugestão: comente essas linhas de código para desobrir a versão e
     // depois atualize (por exemplo: 4.5 com 4 e 5)
     //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
     //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
     //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
     //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
 
     // Ativa a suavização de serrilhado (MSAA) com 8 amostras por pixel
     glfwWindowHint(GLFW_SAMPLES, 8);
 
     // Essencial para computadores da Apple
     // #ifdef __APPLE__
     //	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
     // #endif
 
     // Criação da janela GLFW
     GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Triangulos Coloridos -- Ender", nullptr, nullptr);
     if (!window)
     {
         std::cerr << "Falha ao criar a janela GLFW" << std::endl;
         glfwTerminate();
         return -1;
     }
     glfwMakeContextCurrent(window);
 
     // Fazendo o registro da função de callback para a janela GLFW
     glfwSetKeyCallback(window, key_callback);
 
     // GLAD: carrega todos os ponteiros d funções da OpenGL
     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
     {
         std::cerr << "Falha ao inicializar GLAD" << std::endl;
         return -1;
     }
 
     // Obtendo as informações de versão
     const GLubyte *renderer = glGetString(GL_RENDERER); /* get renderer string */
     const GLubyte *version = glGetString(GL_VERSION);	/* version as a string */
     cout << "Renderer: " << renderer << endl;
     cout << "OpenGL version supported " << version << endl;
 
     // Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
     int width, height;
     glfwGetFramebufferSize(window, &width, &height);
     glViewport(0, 0, width, height);
 
     // Compilando e buildando o programa de shader
     GLuint shaderID = setupShader();
 
     // Gerando um buffer simples, com a geometria de um triângulo
     GLuint VAO0 = setupFloorGeometry();
     GLuint VAO1 = setupWallGeometry();
     GLuint VAO2 = setupWindowGeometry();
     GLuint VAO3 = setupRoofGeometry();
 
 
     glUseProgram(shaderID); // Reseta o estado do shader para evitar problemas futuros
 
     double prev_s = glfwGetTime();	// Define o "tempo anterior" inicial.
     double title_countdown_s = 0.1; // Intervalo para atualizar o título da janela com o FPS.
 
     float colorValue = 0.0;
     // Loop da aplicação - "game loop"
     while (!glfwWindowShouldClose(window))
     {
         // Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
         glfwPollEvents();
 
         // Limpa o buffer de cor
         glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // cor de fundo
         glClear(GL_COLOR_BUFFER_BIT);
 
         glLineWidth(10);
         glPointSize(20);
 
         glBindVertexArray(VAO0); // Conectando ao buffer de geometria
         glDrawArrays(GL_LINE_LOOP, 0, 2);   

         glBindVertexArray(VAO1); // Conectando ao buffer de geometria
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);   
         
         glBindVertexArray(VAO2); // Conectando ao buffer de geometria
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);   
         
         glBindVertexArray(VAO3); // Conectando ao buffer de geometria
         glDrawArrays(GL_TRIANGLES, 0, 3);   

         glfwSwapBuffers(window);
     }
     // Pede pra OpenGL desalocar os buffers
     glDeleteVertexArrays(1, &VAO0);
     // Finaliza a execução da GLFW, limpando os recursos alocados por ela
     glfwTerminate();
     return 0;
 }
 
 // Função de callback de teclado - só pode ter uma instância (deve ser estática se
 // estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
 // ou solta via GLFW
 void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
 {
     if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         glfwSetWindowShouldClose(window, GL_TRUE);
 }
 
 // Esta função está bastante hardcoded - objetivo é compilar e "buildar" um programa de
 //  shader simples e único neste exemplo de código
 //  O código fonte do vertex e fragment shader está nos arrays vertexShaderSource e
 //  fragmentShader source no iniçio deste arquivo
 //  A função retorna o identificador do programa de shader
 int setupShader()
 {
     // Vertex shader
     GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
     glCompileShader(vertexShader);
     // Checando erros de compilação (exibição via log no terminal)
     GLint success;
     GLchar infoLog[512];
     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
     if (!success)
     {
         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                   << infoLog << std::endl;
     }
     // Fragment shader
     GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
     glCompileShader(fragmentShader);
     // Checando erros de compilação (exibição via log no terminal)
     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
     if (!success)
     {
         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                   << infoLog << std::endl;
     }
     // Linkando os shaders e criando o identificador do programa de shader
     GLuint shaderProgram = glCreateProgram();
     glAttachShader(shaderProgram, vertexShader);
     glAttachShader(shaderProgram, fragmentShader);
     glLinkProgram(shaderProgram);
     // Checando por erros de linkagem
     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
     if (!success)
     {
         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
         std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                   << infoLog << std::endl;
     }
     glDeleteShader(vertexShader);
     glDeleteShader(fragmentShader);
 
     return shaderProgram;
 }
 
 int setupFloorGeometry()
 {
     GLfloat vertices[] = {
         // x   y     z    r   g    b
         // T0
          -1.5, -0.8, 0.0, 0.0, 1.0, 0.0,  // v0
           1.5, -0.8, 0.0, 0.0, 1.0, 0.0  // v1
     };
 
     GLuint VBO, VAO;
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
     glEnableVertexAttribArray(1);
 
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);
 
     return VAO;
 }
 
 int setupWallGeometry()
 {
     GLfloat vertices[] = {
         // x   y     z    r   g    b
         // T0
          -0.6,-0.8, 0.0, 0.0, 0.2, 0.5,  // v0
           0.6,-0.8, 0.0, 0.0, 0.2, 0.5,  // v1
           0.6, 0.5, 0.0, 0.0, 0.2, 0.5,  // v2
          -0.6, 0.5, 0.0, 0.0, 0.2, 0.5,  // v3
          -0.6,-0.8, 0.0, 0.0, 0.2, 0.5,  // v0
     };
 
     GLuint VBO, VAO;
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
     glEnableVertexAttribArray(1);
 
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);
 
     return VAO;
 }
 
 int setupWindowGeometry()
 {
     GLfloat vertices[] = {
         // x   y     z    r   g    b
         // T0
          -0.3,-0.4, 0.0, 0.5, 0.5, 0.5,  // v0
           0.3,-0.4, 0.0, 0.5, 0.5, 0.5,  // v1
           0.3, 0.2, 0.0, 0.9, 0.9, 0.9,  // v2
          -0.3, 0.2, 0.0, 0.9, 0.9, 0.9,  // v3
          -0.3,-0.4, 0.0, 0.5, 0.5, 0.5,  // v0
     };
 
     GLuint VBO, VAO;
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
     glEnableVertexAttribArray(1);
 
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);
 
     return VAO;
 }
 
 int setupRoofGeometry()
 {
     GLfloat vertices[] = {
         // x   y     z    r   g    b
         // T0
          -0.7, 0.5, 0.0, 0.5, 0.1, 0.0,  // v0
           0.7, 0.5, 0.0, 0.5, 0.1, 0.0,  // v1
           0.0, 0.9, 0.0, 0.5, 0.1, 0.0  // v2
     };
 
     GLuint VBO, VAO;
     glGenBuffers(1, &VBO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
     glGenVertexArrays(1, &VAO);
     glBindVertexArray(VAO);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
     glEnableVertexAttribArray(0);
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
     glEnableVertexAttribArray(1);
 
     glBindBuffer(GL_ARRAY_BUFFER, 0);
     glBindVertexArray(0);
 
     return VAO;
 }