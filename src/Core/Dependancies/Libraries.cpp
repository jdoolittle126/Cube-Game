#include "Libraries.h"

void log_error(std::string error) {
	std::cout << "ERROR::" << error << "\n";
}
void log_error(std::string error, char log[ERROR_LOG_SIZE]) {
	log_error(error);
	std::cout << "--- LOG BEGIN:\n" << log << "\n --- LOG END\n";
}

