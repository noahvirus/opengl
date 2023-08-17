#pragma once
#include "ShaderClass.h"
#include <vector>
#include <filesystem>
using namespace std;
class shader_control {
	vector<string> list_of_shaders[4];
	std::vector<Shader> currently_compiled;
	int current_shader;
	bool compile_is_queued;
	shader_control(string dir) {
		for (const auto& entry : filesystem::directory_iterator(dir+"/compute"))
			list_of_shaders[2].push_back(entry.path().string());
		for (const auto& entry : filesystem::directory_iterator(dir + "/fragment"))
			list_of_shaders[0].push_back(entry.path().string());
		for (const auto& entry : filesystem::directory_iterator(dir + "/vertex"))
			list_of_shaders[1].push_back(entry.path().string());
		for (const auto& entry : filesystem::directory_iterator(dir + "/geometry"))
			list_of_shaders[3].push_back(entry.path().string());
	}
	vector<string> return_compute(){
		return list_of_shaders[2];
	}
	vector<string> list_compute() {
		cout << "Here are the compute shaders:" << endl;
		for (int i = 0; i < list_of_shaders[2].size(); i++) {
			cout << i << ": " << list_of_shaders[2].at(i) << endl;
		};
	}
	vector<string> return_fragment() {
		return list_of_shaders[0];
	}
	vector<string> list_fragment() {
		cout << "Here are the fragment shaders:" << endl;
		for (int i = 0; i < list_of_shaders[0].size(); i++) {
			cout << i << ": " << list_of_shaders[0].at(i) << endl;
		};
	}
	vector<string> return_vertex() {
		return list_of_shaders[1];
	}
	vector<string> list_vertex() {
		cout << "Here are the fragment shaders:" << endl;
		for (int i = 0; i < list_of_shaders[1].size(); i++) {
			cout << i << ": " << list_of_shaders[1].at(i) << endl;
		};
	}vector<string> return_geometry() {
		return list_of_shaders[4];
	}
	vector<string> list_geometry() {
		cout << "Here are the geometry shaders:" << endl;
		for (int i = 0; i < list_of_shaders[3].size(); i++) {
			cout << i << ": " << list_of_shaders[3].at(i) << endl;
		};
	}
	bool queue_compile() {
		compile_is_queued = true;
	}
	bool dequeue_compile() {
		compile_is_queued = false;
	}
	Shader Compile_shader() {
		cout << "what vertex shader would you like to compile?" << endl;
		list_vertex();
		int i = 0;
		cin >> i;
		cout << "what fragment shader would you like to compile?" << endl;
		list_vertex();
		int j = 0;
		cin >> j;
		currently_compiled.push_back(Shader(list_of_shaders[1].at(i - 1).c_str(), list_of_shaders[0].at(j - 1).c_str()));
		return currently_compiled.at(currently_compiled.size() - 1);
	}
	Shader fast_Compile_shader(string path1, string path2) {
		currently_compiled.push_back(Shader(path1.c_str(), path2.c_str()));
		return currently_compiled.at(currently_compiled.size() - 1);
	}
	
};