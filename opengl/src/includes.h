#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <cstdlib>
#include <windows.h>
#include <SFML/Audio.hpp>
#include <ShlObj.h>
#include <glad/glad.h>
#include "glad.c"
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Texture.h"
#include "shaderClass.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "fluid_simulation.h"

using namespace std;

#include <fstream>
#include <cstring>
#include "rand.h"