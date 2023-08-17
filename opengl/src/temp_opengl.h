#pragma once
HWND a = get_wallpaper_window();
RECT rect;
GetClientRect(a, &rect);

// Calculate the resolution
int width = rect.right - rect.left;
int height = rect.bottom - rect.top;

// Output the resolution
std::cout << "Window Resolution: " << width << "x" << height << std::endl;
HDC hDC = GetDC(a);
// Initialize GLFW
PIXELFORMATDESCRIPTOR pfd;


// Set up a pixel format descriptor
ZeroMemory(&pfd, sizeof(pfd));
pfd.nSize = sizeof(pfd);
pfd.nVersion = 1;
pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
pfd.iPixelType = PFD_TYPE_RGBA;
pfd.cColorBits = 24;
pfd.cDepthBits = 16; // Adjust if needed
pfd.iLayerType = PFD_MAIN_PLANE;
int format;
// Choose a pixel format that matches the descriptor
format = ChoosePixelFormat(hDC, &pfd);

// Set the pixel format for the window's device context
SetPixelFormat(hDC, format, &pfd);

// Create an OpenGL rendering context and make it current
HGLRC hRC = wglCreateContext(hDC);
wglMakeCurrent(hDC, hRC);

// Load GLAD so it configures OpenGL
gladLoadGL();

// Specify the viewport of OpenGL in the Window
// In this case, the viewport goes from x = 0, y = 0, to x = 800, y = 800
glViewport(0, 0, width, height);



// Generates Shader object using shaders default.vert and default.frag
Shader shaderProgram1("./resources/shaders/experimenting.vert", "./resources/shaders/Space.frag");
Shader shaderProgram2("./resources/shaders/experimenting.vert", "./resources/shaders/NightDrive.frag");
Shader shaderProgram3("./resources/shaders/experimenting.vert", "./resources/shaders/Fractal.frag");

glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) / static_cast<float>(height), 0.0f, 100.0f);
// Generates Vertex Array Object and binds it
VAO VAO1;
VAO1.Bind();

// Generates Vertex Buffer Object and links it to vertices
VBO VBO1(vertices, sizeof(vertices));

// Links VBO attributes such as coordinates and colors to VAO
VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 2 * sizeof(float), nullptr);
// Unbind all to prevent accidentally modifying them
VAO1.Unbind();
VBO1.Unbind();
// Main while loop
chrono::time_point initialframe = chrono::high_resolution_clock::now();
bool runnin = true;
std::vector<Shader> shaders;
shaders.push_back(shaderProgram1);
shaders.push_back(shaderProgram2);
shaders.push_back(shaderProgram3);
int shad = 0;
bool paused = false;
std::thread thread(iskill, std::ref(runnin), std::ref(shad), std::ref(paused));
const int windowSize = 1024;
float maxBassLevel = 1.0f;