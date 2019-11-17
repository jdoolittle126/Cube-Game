#include "ShaderManager.h"
#include "Libraries.h"

GLuint ShaderManager::build_shader(std::string fragment_loc, std::string vertex_loc) {
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	int success;
	char infoLog[512];

	std::ifstream stream;
	stream.open(vertex_loc, std::ios::in);
	std::string line = "", content_vert, content_frag;
	while(!stream.eof()) {
		std::getline(stream, line);
		content_vert.append(line + "\n");
	}

	stream.close();
	stream.open(fragment_loc, std::ios::in);

	while(!stream.eof()) {
		std::getline(stream, line);
		content_frag.append(line + "\n");
	}

	stream.close();

    const char *vs = content_vert.c_str();
    const char *fs = content_frag.c_str();
	
	glShaderSource(VertexShaderID, 1, &vs, NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(VertexShaderID, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	glShaderSource(FragmentShaderID, 1, &fs, NULL );
	glCompileShader(FragmentShaderID );

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(FragmentShaderID, 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void ShaderManager::create_shader(std::string reference_name, std::string fragment_loc, std::string vertex_loc) {
	shaders.insert(std::pair<std::string, GLuint>(reference_name, build_shader(fragment_loc, vertex_loc)));
}

GLuint ShaderManager::use_shader(std::string reference_name) {
	glUseProgram(shaders.at(reference_name));
	return shaders.at(reference_name);
}

std::map<std::string, GLuint> ShaderManager::get_shaders() {
	return shaders;
}
