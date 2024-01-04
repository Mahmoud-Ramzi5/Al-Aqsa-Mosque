#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <Tcamera.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <model.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Player.h>
#include <Classes/Sun.h>
#include <Classes/SkyBox.h>
#include <Classes/Floor.h>
#include <Classes/Rug.h>
#include <Classes/Octagon.h>
#include <Classes/Cylinder.h>
#include <Classes/Dome.h>
#include <Classes/Qubli.h>
#include <Classes/QubliInside.h>
#include <Classes/Minaret.h>
#include <Classes/Singlewall.h>
#include <Classes/Wall.h>
#include <Classes/Building.h>
#include <Classes/Skyscrapper.h>




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int load_RGBtexture(const char* source);
unsigned int load_RGBAtexture(const char* source);
void processInput(GLFWwindow* window);

void DrawGrass(Floor G, glm::mat4& Model, unsigned int& modelLoc, Shader& shader);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

// camera
Player player;
Camera camera;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// Models
Model Rock;
Model Tree1;
Model Chandelier;
Model MoonStick;

int main(int argc, char* argv[])
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Al-Aqsa_Mosque", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // load shader
    Shader shader = Shader("res/shaders/Basic.shader");


    // load models
    // -----------
    Rock = Model("res/objects/rock/rock.obj");
    Tree1 = Model("res/objects/trees/tree1/Tree.obj");
    Chandelier = Model("res/objects/chandelier/11833_Chandelier_v1_l2.obj");
    MoonStick = Model("res/objects/MoonStick/19759_Crescent_Moon_v1.obj");
    player = Player(glm::vec3(0.0f, 0.0f, -1.0f), "res/objects/player/ninja character.obj");
    camera = Camera((glm::vec3(0.0f, 0.5f, 3.5f)));

    glUniform1i(glGetUniformLocation(shader.ID, "texture0"), 0);

    unsigned int SkyBoxFaces[3]{
        load_RGBtexture("res/textures/sky.png"),
        load_RGBtexture("res/textures/skybox.png"),
        load_RGBtexture("res/textures/down.png")
    };

    Sun sun = Sun(3.5f, 350);
    Sun moon = Sun(1.5f, 350);
    SkyBox S = SkyBox(SkyBoxFaces);
    Floor F = Floor(load_RGBtexture("res/textures/floor.jpg"));
    Floor G = Floor(load_RGBtexture("res/textures/grass.jpg"));
    Floor C = Floor(load_RGBtexture("res/textures/carpet.jpg"));
    Rug R = Rug(load_RGBtexture("res/textures/traditional-persian.jpg"));
    Rug K = Rug(load_RGBtexture("res/textures/graybrick.png"));
    Octagon O = Octagon(load_RGBAtexture("res/textures/Dome.png"));
    Octagon OO = Octagon(load_RGBAtexture("res/textures/inside_Dome.png"));
    Octagon BB = Octagon(load_RGBtexture("res/textures/selsela2.jpg"));
    Dome D = Dome(0.75f, 250, load_RGBtexture("res/textures/yellow_grid.png"));
    Dome BD = Dome(0.75f, 250, load_RGBtexture("res/textures/gray.jpg"));
    Qubli Q = Qubli(load_RGBAtexture("res/textures/fullwall.png"));
    Qubli QQ = Qubli(load_RGBtexture("res/textures/inside_Qubli.jpg"));  
    Singlewall Mehrab = Singlewall(load_RGBtexture("res/textures/Mihrab.png"));
    Cylinder cc = Cylinder(2.64f, 0.8f, load_RGBtexture("res/textures/dome_cylinder.jpg"));
    Cylinder Qc = Cylinder(2.64f, 0.8f, load_RGBtexture("res/textures/qublicylander.jpg"));
    Cylinder Bc = Cylinder(2.64f, 0.8f, load_RGBtexture("res/textures/little_cylinder.jpg"));
    Dome D2 = Dome(0.35f, 250, load_RGBtexture("res/textures/QubliDome.jpg"));
    Minaret m = Minaret(load_RGBtexture("res/textures/complete_minaret.png"));
    Octagon mo = Octagon(load_RGBtexture("res/textures/Metal G6.jpg"));
    Wall W = Wall(load_RGBtexture("res/textures/wall4.jpg"));
    Building B = Building(load_RGBAtexture("res/textures/fullbuilding.png"));
    Skyscrapper B2 = Skyscrapper(load_RGBAtexture("res/textures/full skyscrapper.png"));

    glm::vec3 lightPos(0.0f, 0.0, 0.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    float offset = 0.0f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use the shader program
        shader.use();
        lightPos.x = 100 * sin(offset);
        lightPos.y = 100 * cos(offset);
        glUniform3fv(glGetUniformLocation(shader.ID, "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shader.ID, "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shader.ID, "viewpos"), 1, glm::value_ptr(camera.Position));

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        unsigned int projLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        unsigned int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
        unsigned int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glActiveTexture(GL_TEXTURE0);


        // Start Drawing
        // draw sun
        glUseProgram(sun.getShaderId());
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(51 * sin(offset), 51 * cos(offset), 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(sun.getShaderId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(sun.getShaderId(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(sun.getShaderId(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        sun.DrawSun();

        // draw moon
        glUseProgram(moon.getShaderId());
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(51 * sin(offset), 51 * -cos(offset), 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(moon.getShaderId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(moon.getShaderId(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(moon.getShaderId(), "model"), 1, GL_FALSE, glm::value_ptr(model));
        moon.DrawSun();

        // reuse shader
        shader.use();

        // Draw SkyBox
        model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        S.DrawSkyBox();

        // Draw Floor
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(4.65f, 3.5f, 3.33f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        F.DrawFloor();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.015f, 16.0f));
        model = glm::scale(model, glm::vec3(0.715f, 1.0f, 1.4f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        C.DrawFloor();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(4.27f, 0.02f, 16.0f));
        model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.3f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        R.DrawRug();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.02f, 1.8f));
        model = glm::scale(model, glm::vec3(2.5f, 1.0f, 7.2f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        K.DrawRug();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(4.99f, 0.02f, 16.5f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Mehrab.DrawSinglewall();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(5.0f, 0.0f, -1.5f));
        DrawGrass(G, model, modelLoc, shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-5.0f, 0.0f, -1.5f));
        DrawGrass(G, model, modelLoc, shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(20.0f, 0.0f, -15.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        DrawGrass(G, model, modelLoc, shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-20.0f, 0.0f, -15.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        DrawGrass(G, model, modelLoc, shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -15.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        DrawGrass(G, model, modelLoc, shader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(10.0f, 0.0f, -15.5f));
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        DrawGrass(G, model, modelLoc, shader);

        // Draw Dome of the Rock (outSide)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        model = glm::rotate(model, glm::radians(22.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        O.DrawOct();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.9f, -10.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        cc.DrawCylinder();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.9f, -10.0f));
        model = glm::scale(model, glm::vec3(3.65f, 2.7f, 3.65f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        D.DrawDome();

        // Draw Chandelier
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));  // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Chandelier.Draw(shader);

        // Draw MoonStick
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 4.5f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));  // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        MoonStick.Draw(shader);

        // Draw Dome of the Rock (inSide)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.01f, -10.0f));
        model = glm::scale(model, glm::vec3(9.99f, 9.99f, 9.99f));
        model = glm::rotate(model, glm::radians(22.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        OO.DrawOct();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.05f, -10.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));  // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Rock.Draw(shader);

        // Draw little Dome
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(8.0f, 0.0f, -8.0f));
        model = glm::scale(model, glm::vec3(3.0f, 5.0f, 3.0f));
        model = glm::rotate(model, glm::radians(22.5f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        BB.DrawOct();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(8.0f, 1.41f, -8.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Bc.DrawCylinder();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(8.0f, 1.43f, -8.0f));
        model = glm::scale(model, glm::vec3(1.1f, 0.85f, 1.1f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        BD.DrawDome();

        // Draw MoonStick
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(8.0f, 1.4f, -8.0f)); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.035f));  // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        MoonStick.Draw(shader);

        // Draw Qubli
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 16.0f));
        model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Q.DrawQubli();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.11f, 20.0f));
        model = glm::scale(model, glm::vec3(0.51f, 0.3f, 0.51f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        Qc.DrawCylinder();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.0f, 20.0f));
        model = glm::scale(model, glm::vec3(4.0f, 3.5f, 4.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        D2.DrawDome();

        //Draw Qubli (Inside)
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.01f, 16.0f));
        model = glm::scale(model, glm::vec3(9.99f, 9.99f, 9.99f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        QQ.DrawQubli();

        // Draw MoonStick
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 2.6f, 20.0f)); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));  // it's a bit too big for our scene, so scale it down
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        MoonStick.Draw(shader);

 

        // Draw Minarets
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(23.3f, 1.0f, -23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        m.DrawMinaret();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(23.3f, 3.4f, -23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mo.DrawOct();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-23.3f, 1.0f, -23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        m.DrawMinaret();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-23.3f, 3.4f, -23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mo.DrawOct();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-23.3f, 1.0f, 23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        m.DrawMinaret();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-23.3f, 3.4f, 23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mo.DrawOct();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(23.3f, 1.0f, 23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        m.DrawMinaret();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(23.3f, 3.4f, 23.3f));
        model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        mo.DrawOct();

        // Draw Some Buildings
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(12.0f, 0.0f, 27.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B.DrawBuilding();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-12.0f, 0.0f, 27.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B.DrawBuilding();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(24.0f, 0.0f, 27.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B.DrawBuilding();
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-24.0f, 0.0f, 27.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B.DrawBuilding();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(29.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B.DrawBuilding();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-29.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B.DrawBuilding();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-29.0f, 0.0f, -12.0f));
        model = glm::scale(model, glm::vec3(1.6f, 2.5f, 2.5f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B2.DrawSkyscrapper();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(29.0f, 0.0f, -12.0f));
        model = glm::scale(model, glm::vec3(1.6f, 2.5f, 2.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B2.DrawSkyscrapper();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-29.0f, 0.0f, 12.0f));
        model = glm::scale(model, glm::vec3(1.6f, 2.5f, 2.5f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B2.DrawSkyscrapper();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(29.0f, 0.0f, 12.0f));
        model = glm::scale(model, glm::vec3(1.6f, 2.5f, 2.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        B2.DrawSkyscrapper();
        
        // Draw the Wall
        for (int i = 0; i < 4; i++) {
            W.DrawWall(shader.ID, i);
        }

        // Draw Player
        if (is_FPS) {
            player.DrawPlayer(shader, glm::vec3(0.0f, -1.0f, 0.0f));
        }
        else {
            player.DrawPlayer(shader, camera.GetPlayerPos());
        }
        
        // increse offset
        offset += 0.005;
        if (offset == 1) {
            offset = 0;
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT_SHIFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever a key is pressed, this callback is called
// -------------------------------------------------------
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        if (is_FPS) {
            is_FPS = false;
            camera.ProcessMouseMovement(lastX, lastY);
        }
        else {
            is_FPS = true;
            camera.ChangeView();
        }
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int load_RGBtexture(const char* source) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // get image from source
    unsigned char* data = stbi_load(source, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

unsigned int load_RGBAtexture(const char* source) {
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    // get image from source
    unsigned char* data = stbi_load(source, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

void DrawGrass(Floor G, glm::mat4& Model, unsigned int& modelLoc, Shader& shader) {
    // Draw Grass
    glm::mat4 model = Model;
    model = glm::translate(model, glm::vec3(0.0, 0.015, 3.0));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    G.DrawFloor();

    // render the Tree models
    model = Model;
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 4.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 4.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 6.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 6.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 2.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 2.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);


    model = Model;
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 6.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 6.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 2.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 2.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 4.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 4.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);

    model = Model;
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    Tree1.Draw(shader);
}