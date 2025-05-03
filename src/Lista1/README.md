Parte 1 - Teoria
1. O que é a GLSL? Quais os dois tipos de shaders são obrigatórios no pipeline programável da versão
atual que trabalhamos em aula e o que eles processam?

    GLSL é uma Linguagem associada ao OpenGL, usada para criar shaders que manipulam vértices, pixels e calculam iluminação.
    Os dois shaders obrigatorios são Vertex Shader e Fragment Shader


2. O que são primitivas gráficas? Como fazemos o armazenamento dos vértices na OpenGL?

    São formas basicas utilizadas para construir graficos (Pontos, Linhas, Triangulos, etc)
    Os vertices são armazenados em um Buffer chamado de VBO (Vertex Buffer Object)


3. Explique o que é VBO e VAO, e como se relacionam (se achar mais fácil, pode fazer um gráfico
representando a relação entre eles).

    VBO armazena os dados dos vertices, VAO organiza e guarda os estados dos VBOS

4. Como são feitas as chamadas de desenho na OpenGL? Para que servem as primitivas de desenho?

    As chamadas são feitas com glDrawArrays() e as primitivas de desenho servem para definir como os vertices serão conectados e renderizados.
