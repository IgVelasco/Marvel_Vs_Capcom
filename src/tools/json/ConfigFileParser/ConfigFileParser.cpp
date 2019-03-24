/*
 * ConfigFileParser.cpp
 *
 *  Created on: 23 mar. 2019
 *      Author: sebastian
 */

#include "ConfigFileParser.h"

const string DEFAULT_CONFIG_FILE_PATH = "config/config_default.json";
const string ERROR = "ERROR";
const string INFO = "INFO";
const string DEBUG = "DEBUG";

ConfigFileParser::ConfigFileParser() {
	this->filePath = DEFAULT_CONFIG_FILE_PATH;
	cout << "Usando archivo de configuración por default ubicado en '" + DEFAULT_CONFIG_FILE_PATH << endl; // Esto va al log
}

ConfigFileParser::ConfigFileParser(string path) {
	if(!this->fileExists(path)) {
		cout << "Usando archivo de configuración por default ubicado en '" + DEFAULT_CONFIG_FILE_PATH << endl; // Esto va al log
		this->filePath = DEFAULT_CONFIG_FILE_PATH;
	} else {
		cout << "Usando archivo de configuración ubicado en '" + path << endl; // Esto va al log
		this->filePath = path;
	}
}

bool ConfigFileParser::fileExists(string path) {
	cout << "Verificando existencia del archivo de configuración '" + path << endl; // Esto va al log
	try {
		ifstream i(path.c_str());
		if(i.good()) {
			cout << "El archivo '" + path + "' existe." << endl; // Esto va al log
			return true;
		}
		else {
			throw runtime_error("El archivo '" + path + "' no existe.");
		}
	} catch(exception& e) {
		cout << "**ERROR** " + string(e.what()) << endl; // Esto va al log
		return false;
	}
}

void ConfigFileParser::parse() {
	cout << "Iniciando validación del archivo de configuración." << endl; // Esto va al log
	ifstream i(this->filePath.c_str());
	try {
		this->config = json::parse(i);
	} catch(exception& e) {
		cout << "**ERROR** " + string(e.what()) << endl; // Esto va al log
	}

	json defaultConfig;
	if(this->filePath != DEFAULT_CONFIG_FILE_PATH) {
		ifstream i(DEFAULT_CONFIG_FILE_PATH.c_str());
		defaultConfig = json::parse(i);
	}

	this->validateLogLevel(defaultConfig);
	this->validateBattlefield(defaultConfig);
	this->validateCharacters(defaultConfig);
	this->validateWindow(defaultConfig);
}

void ConfigFileParser::validateLogLevel(json defaultConfig) {
	cout << "Validando nivel de log..." << endl; // Esto va al log
	if(this->config.find("log") == this->config.end()) {
		this->logError("log", "Nivel de log no especificado.");
		this->replaceByDefault("log", defaultConfig, "");
	} else {
		string logErrorLevel = this->config["log"];
		if(logErrorLevel != ERROR && logErrorLevel != INFO && logErrorLevel != DEBUG) {
			this->logError("log", "No existe el nivel de log especificado.");
			this->replaceByDefault("log", defaultConfig, "");
		}
	}
	cout << "Nivel de log validado OK." << endl; // Esto va al log
}

void ConfigFileParser::validateBattlefield(json defaultConfig) {
	cout << "Validando battlefield..." << endl; // Esto va al log
	if(this->config.find("battlefield") == this->config.end()) {
		this->logError("battlefield", "Battlefield no especificado.");
		this->replaceByDefault("battlefield", defaultConfig, "");
	} else {
		json battlefield = this->config["battlefield"];
		if(!battlefield.is_array()) {
			this->logError("battlefield", "Battlefield no es un array.");
			this->replaceByDefault("battlefield", defaultConfig, "");
		} else {
			if(battlefield.empty()) {
				this->logError("battlefield", "Battlefield está vacío.");
				this->replaceByDefault("battlefield", defaultConfig, "");
			} else {
				cout << "Verificando si todos los elementos tienen el atributo 'background' y dentro de este un 'filepath'" << endl; // Esto va al log
				for(json::iterator it = battlefield.begin(); it != battlefield.end(); ++it) {
					if(it->find("background") == it->end()) {
						this->logError("battlefield", "Hay un background no especificado.");
						this->replaceByDefault("battlefield", defaultConfig, "");
						break;
					} else {
						if((*it)["background"].find("filepath") == (*it)["background"].end()) {
							this->logError("battlefield", "Hay un filepath no especificado.");
							this->replaceByDefault("battlefield", defaultConfig, "");
							break;
						}
					}
				}
			}
		}
	}
	cout << "Battlefield validado OK." << endl; // Esto va al log
}

void ConfigFileParser::validateCharacters(json defaultConfig) {
	cout << "Validando characters..." << endl; // Esto va al log
	if(this->config.find("characters") == this->config.end()) {
		this->logError("characters", "Characters no especificado.");
		this->replaceByDefault("characters", defaultConfig, "");
	} else {
		json characters = this->config["characters"];
		if(!characters.is_array()) {
			this->logError("characters", "Characters no es un array.");
			this->replaceByDefault("characters", defaultConfig, "");
		} else {
			if(characters.empty()) {
				this->logError("characters", "Characters está vacío.");
				this->replaceByDefault("characters", defaultConfig, "");
			} else {
				cout << "Verificando si todos los elementos tienen los atributos necesarios." << endl; // Esto va al log
				for(json::iterator it = characters.begin(); it != characters.end(); ++it) {
					if(it->find("name") == it->end()) {
						this->logError("characters", "Hay un name no especificado.");
						this->replaceByDefault("characters", defaultConfig, "");
						break;
					}
					if(it->find("filepath") == it->end()) {
						this->logError("characters", "Hay un filepath no especificado.");
						this->replaceByDefault("characters", defaultConfig, "");
						break;
					}
					if(it->find("height") == it->end()) {
						this->logError("characters", "Hay un height no especificado.");
						this->replaceByDefault("characters", defaultConfig, "");
						break;
					}
					if(it->find("width") == it->end()) {
						this->logError("characters", "Hay un width no especificado.");
						this->replaceByDefault("characters", defaultConfig, "");
						break;
					}
				}
			}
		}
	}
	cout << "Characters validado OK." << endl; // Esto va al log
}

void ConfigFileParser::validateWindow(json defaultConfig) {
	cout << "Validando window..." << endl; // Esto va al log
	if(this->config.find("window") == this->config.end()) {
		this->logError("window", "Window no especificado.");
		this->replaceByDefault("window", defaultConfig, "");
	} else {
		json window = this->config["window"];
		if(window.find("height") == window.end()) {
			this->logError("window", "Height no especificado.");
			this->replaceByDefault("window", defaultConfig, "height");
		}
		if(window.find("width") == window.end()) {
			this->logError("window", "Width no especificado.");
			this->replaceByDefault("window", defaultConfig, "width");
		}
	}
	cout << "Window validado OK." << endl; // Esto va al log
}

void ConfigFileParser::logError(string key, string errorMsg) {
	cout << "**ERROR** " + errorMsg << endl; // Esto va al log
	cout << "Usando " + key + " por default." << endl; // Esto va al log
}

void ConfigFileParser::replaceByDefault(string key, json defaultConfig, string subKey) {
	if(!subKey.empty()) {
		this->config[key][subKey] = defaultConfig[key][subKey];
	} else {
		this->config[key] = defaultConfig[key];
	}
}

json ConfigFileParser::getConfig() {
	return this->config;
}
