#include "game.hpp"

#include <glad/glad.h>

GLuint vao;
GLuint vbo;

GLuint programID;

const char* vertShader = R"(#version 430 core
layout (location = 0) in vec3 inPos;
void main()
{
  gl_Position = vec4(inPos, 1.0);
}
)";

const char* fragShader = R"(#version 430 core
layout (location = 0) out vec4 outColor;
void main()
{
  outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
)";

Game::Game(const Nexus::ApplicationInfo &appInfo)
  : Application(appInfo)
{
  GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertID, 1, &vertShader, nullptr);
  glCompileShader(vertID);

  int success = 0;
  glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[1024] = {0};
    glGetShaderInfoLog(vertID, 1024, nullptr, infoLog);
    NX_GAME_ERROR("Failed to Compile Vertex Shader: ", infoLog);
    return;
  }

  GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragID, 1, &fragShader, nullptr);
  glCompileShader(fragID);

  success = 0;
  glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[1024] = {0};
    glGetShaderInfoLog(fragID, 1024, nullptr, infoLog);
    NX_GAME_ERROR("Failed to Compile Fragment Shader: ", infoLog);
    return;
  }

  programID = glCreateProgram();
  glAttachShader(programID, vertID);
  glAttachShader(programID, fragID);
  glLinkProgram(programID);

  success = 0;
  glGetProgramiv(programID, GL_LINK_STATUS, &success);
  if (!success)
  {
    char infoLog[1024] = {0};
    glGetProgramInfoLog(programID, 1024, nullptr, infoLog);
    NX_GAME_ERROR("Failed to Link Program: ", infoLog);
    return;
  }

  glDetachShader(programID, vertID);
  glDetachShader(programID, fragID);
  glDeleteShader(vertID);
  glDeleteShader(fragID);
  
  float vertices[] = {
    -0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,

     0.5f,  0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
  };

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Game::~Game()
{
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);

  glDeleteProgram(programID);
}

void Game::Init()
{
}

void Game::Update(float dt)
{
}

void Game::Render(float dt)
{
  glUseProgram(programID);
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
  glUseProgram(0);
}
