#pragma once

#include "Libraries.h"
#include <iostream>
#include <fstream>
#include <string>

class Shader {
public:
	GLuint programId;

	Shader(std::string vertex_shader, std::string frag_shader) {
		programId = glCreateProgram();
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		std::ifstream stream;
		stream.open(vertex_shader, std::ios::in);
		std::string line = "", content_vert, content_frag;

		while(!stream.eof()) {
			std::getline(stream, line);
			content_vert.append(line + "\n");
		}

		stream.close();

		stream.open(frag_shader, std::ios::in);

		while(!stream.eof()) {
			std::getline(stream, line);
			content_frag.append(line + "\n");
		}

		stream.close();

		const char *vs = content_vert.c_str();
		const char *fs = content_frag.c_str();

		glShaderSource(VertexShaderID, 1, &vs, NULL);
		glCompileShader(VertexShaderID);

		glShaderSource(FragmentShaderID, 1, &fs, NULL );
		glCompileShader(FragmentShaderID );

		glAttachShader(programId, VertexShaderID);
		glAttachShader(programId, FragmentShaderID);
		glLinkProgram(programId);

		glDetachShader(programId, VertexShaderID);
		glDetachShader(programId, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
	}


};
