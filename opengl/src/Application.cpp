#include "includes.h"
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    HWND p = FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL);
    HWND* ret = (HWND*)lParam;

    if (p)
    {
        // Gets the WorkerW Window after the current one.
        *ret = FindWindowEx(NULL, hwnd, L"WorkerW", NULL);
    }
    return true;
}



HWND get_wallpaper_window()
{
    // Fetch the Progman window
    HWND progman = FindWindow(L"ProgMan", NULL);
    // Send 0x052C to Progman. This message directs Progman to spawn a 
    // WorkerW behind the desktop icons. If it is already there, nothing 
    // happens.
    SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
    // We enumerate all Windows, until we find one, that has the SHELLDLL_DefView 
    // as a child. 
    // If we found that window, we take its next sibling and assign it to workerw.
    HWND wallpaper_hwnd = nullptr;
    EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
    // Return the handle you're looking for.
    return wallpaper_hwnd;
}
float deltaTime = 0.0f;
float lastFrame = 0.0f;
unsigned int width = 1920;
unsigned int height = 1080;
// Vertices coordinates
GLfloat vertices[] = {
    -1.0f, -1.0f,
    1.0f, -1.0f,
    1.0f,  1.0f,
    1.0f,  1.0f,
    -1.0f,  1.0f,
    -1.0f, -1.0f
};
void iskill(bool& running, int& shad, bool& paused) {
    string temp = "";
    while (temp != "exit") {
        cout << "1. List Shaders" << endl << "2. Exit" << endl;
        cin >> temp;
        if (temp == "1") {
            cout << "Please pick the shader number you want" << endl << "1. Fractal" << endl << "2. NightDrive" << endl << "3. Space" << endl;
            cin >> temp;
            if (temp == "1") {
                shad = 0;
            }
            else if (temp == "2") {
                shad = 1;
            }
            else if (temp == "3") {
                shad = 2;
            }
        }
        else if (temp == "2") {
            running = false;
            break;
        }
    }
}

// Indices for vertices order
POINT GerCursorPosition(HWND hwnd) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    return cursorPos;
}
int main()
{
    // Wait for the sound to finish playing
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
    chrono::time_point initialframe = chrono::high_resolution_clock::now();
    float currentFrame = chrono::duration_cast<std::chrono::milliseconds>(chrono::high_resolution_clock::now() - initialframe).count() / 1000.0f;

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
    


    bool runnin = true;
    std::vector<Shader> shaders;
    
    int shad = 0;
    bool paused = false;
    std::thread thread(iskill, std::ref(runnin), std::ref(shad), std::ref(paused));
    const int windowSize = 1024;
    float maxBassLevel = 1.0f;
    while (runnin)
    {
   
        POINT temp = GerCursorPosition(a);
        currentFrame = chrono::duration_cast<std::chrono::milliseconds>(chrono::high_resolution_clock::now() - initialframe).count() / 1000.0f;
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Normalize the bass level

        // Set the "myTexture" uniform to texture unit 0
        
       
        // Specify the color of the background
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        glUniform1f(glGetUniformLocation(shaders.at(shad).ID, "iMaxSound"), 0);
        glUniform1f(glGetUniformLocation(shaders.at(shad).ID, "iTime"), currentFrame);
        glUniform2f(glGetUniformLocation(shaders.at(shad).ID, "iResolution"), static_cast<float>(width), static_cast<float>(height));
        glUniform2f(glGetUniformLocation(shaders.at(shad).ID, "iMouse"), static_cast<float>(temp.x), static_cast<float>(temp.y));
        glUniformMatrix4fv(glGetUniformLocation(shaders.at(shad).ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        shaders.at(shad).Activate();
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Swap the back buffer with the front buffer

        SwapBuffers(hDC);
        // Take care of all GLFW events
       
    }

    // Delete all the objects we've created
    
    VAO1.Delete();
    VBO1.Delete();
    shaders.at(0).Delete();
    wglMakeCurrent(NULL, NULL); // Release the rendering context
    wglDeleteContext(hRC);
    ReleaseDC(a, hDC);
    thread.join();
    for(int i=0; i< 40;i++){ std::system("RUNDLL32.EXE USER32.DLL,UpdatePerUserSystemParameters 1, True"); }
    // Delete window before ending the program
    return 0;
}