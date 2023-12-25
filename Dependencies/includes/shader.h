#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Shader {
    public:
	    unsigned int ID;
	    string VertexSource;
	    string FragmentSource;
        Shader() {}
        Shader(string source) {
            ParseShader(source);
            unsigned int shader = CreateShader(VertexSource,FragmentSource);
            ID=shader;

        }

        void ParseShader(const string& filepath) {
            fstream stream(filepath);

            enum class ShaderType {
                NONE = -1, VERTEX = 0, FRAGMENT = 1
            };

            string line;
            stringstream ss[2];
            ShaderType type = ShaderType::NONE;
            while (getline(stream, line)) {
                if (line.find("#shader") != string::npos) {
                    if (line.find("vertex") != string::npos) {
                        type = ShaderType::VERTEX;
                    }
                    else if (line.find("fragment") != string::npos) {
                        type = ShaderType::FRAGMENT;
                    }
                }
                else {
                    ss[(int)type] << line << '\n';
                }
            }
            VertexSource = ss[0].str();
            FragmentSource = ss[1].str();

            return;
        }

        unsigned int compileShader(unsigned int type, const string& source) {
            unsigned int id = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

            // Error handling
            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE) {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* message = (char*)alloca(length* sizeof(char));
                glGetShaderInfoLog(id, length, &length, message);
                std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << endl;
                std::cout << message << endl;
                glDeleteShader(id);
                return 0;
            }

            return id;
        }

        unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
             unsigned int program = glCreateProgram();
             unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
             unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

             glAttachShader(program, vs);
             glAttachShader(program, fs);
             glLinkProgram(program);
             glValidateProgram(program);

             glDeleteShader(vs);
             glDeleteShader(fs);

             return program;
         }

         void use() {
             glUseProgram(ID);
         }
};
#endif