
// Final project COMP 371
// Names & IDs : Amine Bechrifa (40085342) & Sana Jallouli (40085343)
//
//

// including the needed libraries

#include <iostream>
#include <stdlib.h>
#include <list>
#include<time.h>

#include <vector>
#include <algorithm>
#define GLEW_STATIC 1   //  to link with Static Library on Windows, without DLL
#include <GL/glew.h>    //  OpenGL Extension Wrangler ( Glew)
#include <GLFW/glfw3.h> // necessary for cross-platform interface for creating a graphical context, and initializing OpenGL and binding inputs
#include <glm/glm.hpp>  // GLM ( math library )
#include <glm/gtc/matrix_transform.hpp> // for  transformation matrices
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"// used in the fn to render
#include <string>
#include <fstream>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <ctime>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "shaderloader.h"
using namespace glm;
using namespace std;

using namespace glm;
using namespace std;
bool clear = false;
float cameraHorizontalAngle;
float newcameraPosition;
float cameraVerticalAngle;
float dy;
float dx;
vec3 cameraPosition(0.0f, 0.0f, 5.0f);
vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
vec3 cameraUp(0.0f, 1.0f, 0.0f);
auto oldtime = std::chrono::system_clock::now();
float timer = 600;
auto newtime = std::chrono::system_clock::now();
bool timeron = true;
float worldx = 0;
float worldy = 0;
bool mag1 = false;
bool mag2 = false;
bool mag0 = false;
bool mag3 = false;
int secs;
int tenmin;
int mins;
int tensec;
int secondes;
float scalee;
bool onmenu = true;
bool ontheme = false;
bool newgame = false;
bool continuegame = false;
int testure = 0;
int shadure = 0;
// varaiables used for individual models movements
bool TEST1 = false;
bool TEST2 = false;
bool TEST3 = false;
bool TEST4 = false;
bool TEST_A = false;
bool TEST_D = false;
bool TEST_W = false;
bool TEST_S = false;
int axemov[300];
int dirmov[300];
int indexmov[300];
int nbrmov = 0;
int axedo[300];
int dirdo[300];
int indexdo[300];
bool solving = false;
int ndone;
bool animals;
int shuff = 0;
vec3 shiny_metal_ambiant(0.23f, 0.23125f, 0.23125f);

vec3 shiny_metal_diffuse(0.2775f, 0.2775f, 0.2775f);

vec3 shiny_metal_specular(0.773911f, 0.773911f, 0.773911f);
vec3 lightpos;
vec3 focus;
int cnnt = 0;
vec3 box_ambiant = shiny_metal_ambiant;
vec3 box_diffuse = shiny_metal_diffuse;
vec3 box_specular = shiny_metal_specular;

float angpers = 50.0f;
vec3 floor_ambiant = shiny_metal_ambiant;
vec3 floor_diffuse = shiny_metal_diffuse;
vec3 floor_specular = shiny_metal_specular;

float dis = 0.101f;
// window dimensions
const GLuint WIDTH = 1024, HEIGHT = 1024;

glm::mat4    projectionMatrix;
bool testshader;
int mnm = 0;
GLuint ashader;

void  texture(GLuint faceup) {
    glActiveTexture(GL_TEXTURE2);
    GLuint textureLocation = glGetUniformLocation(ashader, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, faceup);
    glUniform1i(textureLocation, 2);
}


void SetUniformVec3(GLuint shader_id, const char* uniform_name,
    vec3 uniform_value) {
    glUseProgram(shader_id);
    glUniform3fv(glGetUniformLocation(shader_id, uniform_name), 1,
        value_ptr(uniform_value));
}
int pause;
int inde;
int axes;
bool xaxe[6] = { false,false,false,false,false,false };
bool yaxe[6] = { false,false,false,false,false,false };
bool zaxe[6] = { false,false,false,false,false,false };
void resetrest() {
    xaxe[0] = false;
    xaxe[1] = false;
    xaxe[2] = false;
    xaxe[3] = false;
    xaxe[4] = false;
    xaxe[5] = false;

    yaxe[0] = false;
    yaxe[1] = false;
    yaxe[2] = false;
    yaxe[3] = false;
    yaxe[4] = false;
    yaxe[5] = false;

    zaxe[0] = false;
    zaxe[1] = false;
    zaxe[2] = false;
    zaxe[3] = false;
    zaxe[4] = false;
    zaxe[5] = false;
}
GLuint loadTexture(const char* filename)
{
    // Step1 Create and bind textures
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    assert(textureId != 0);

    glBindTexture(GL_TEXTURE_2D, textureId);
    // Step2 Set filter parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Step3 Load Textures with dimension data
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data)
    {
        std::cerr << "Error::Texture could not load texture file:" << filename << std::endl;
        return 0;
    }
    // Step4 Upload the texture to the PU
    GLenum format = 0;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
        0, format, GL_UNSIGNED_BYTE, data);
    // Step5 Free resources
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}

// TEXTURE IDS:

GLuint metalID;
GLuint brickTextureID1;
bool testsound = false;
GLuint tilesTextureId;
bool shuffling;
GLuint wolf[3][3];
GLuint duck[3][3];
GLuint cow[3][3];
GLuint cat[3][3];
GLuint croco[3][3];
GLuint butter[3][3];
GLuint bl[3][3];
GLuint mar[3][3];
GLuint mj[3][3];
GLuint kp[3][3];  
GLuint ed[3][3];
GLuint du[3][3];
GLuint eu[3][3];
GLuint am[3][3];
GLuint amm[3][3];
GLuint as[3][3];
GLuint af[3][3];
GLuint oc[3][3];
GLuint numbers[10];
GLuint menutex;
GLuint soltex;
GLuint blue;
GLuint green;
GLuint red;
GLuint yellow;
GLuint white;
GLuint orange;
GLuint eua;
GLuint amma;
GLuint ama;
GLuint asa;
GLuint afa;
GLuint oca;

int txx;
GLuint cata;
GLuint wolfa;
GLuint ducka;
GLuint crocoa;
GLuint buttera;
GLuint cowa;
GLuint menucubedroit;
GLuint menucubebas;
GLuint mara;
GLuint mja;
GLuint bla;
GLuint kpa;
GLuint dua;
GLuint eda;




GLuint catt;
GLuint wolft;
GLuint duckt;
GLuint crocot;
GLuint buttert;
GLuint cowt;
GLuint ratt;



bool testsounded;
bool testsoundmj;
bool testsoundkp;
bool testsoundmar;
bool testsounddu;
bool testsoundbl;

bool testsoundwolf;
bool testsoundcroco;
bool testsoundcow;
bool testsoundbutter;
bool testsoundcat;
bool testsoundduck;
GLuint themetex;
float onmenuex;
float onmenuey;
float onmenuez;
float angxonmen;
float angzonmen;
int psx = 0;
int psy = 0;
int psz = 0;
int psz2 = 0;
vec3 lightc = vec3(1);
class cubie {
public:
    GLuint faceup;
    GLuint faceleft;
    GLuint facedown;
    GLuint faceright;
    GLuint facefront;
    GLuint facebehind;
    int x;
    int y;
    int z;
    GLuint mWorldMatrixLocation;
    GLuint mshader;
    GLuint mWorldMatrixLocation2;
    mat4 matrice = mat4(1);
    mat4 matricef = mat4(1);


    // Cubie represents the small cubes of the whole Rubiks cube 

    cubie(float a, float b, float c) {
        x = a;
        y = b;
        z = c;



    }

    cubie() {
        x = 0;
        y = 0;
        z = 0;

    }


    void setup(int shaderProgram, int shaderProgram2) {
        mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");
        mWorldMatrixLocation2 = glGetUniformLocation(shaderProgram2, "transform_in_light_space");
        mshader = shaderProgram;

    }

    // draw the cubies 

    void draw(int shaderProgram, int shaderProgram2) {
        setup(shaderProgram, shaderProgram2);
        vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


        vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
        vec3 lightDirection = normalize(lightFocus - lightPosition);

        float lightNearPlane = 0.5f;
        float lightFarPlane = 20.0f;

        mat4 lightProjMatrix = perspective(angpers, (float)1024 / (float)1024, lightNearPlane, lightFarPlane);
        mat4 lightViewMatrix1 = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

        lightProjMatrix = lightProjMatrix * lightViewMatrix1;



        mat4 matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            matricef * glm::translate(glm::mat4(1.0f), glm::vec3(x * dis, y * dis - 0.05, z * dis)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.05, 0)) * matrice * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.05, 0));
        mat4 lightViewMatrix = lightProjMatrix * matric;



        //FACE D EN BAS
        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 6);
        //FACE D EN HAUT
        texture(faceup);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 8, 6);
        //BEHIND FACE
        texture(facebehind);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 14, 6);
        //FRONT FACE
        texture(facefront);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 20, 6);
        //LEFT FACE
        texture(faceleft);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 26, 6);
        //RIGHT FACE
        texture(faceright);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 32, 6);





        mat4 m1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))
            * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.5f, 0.3f));




        mat4 m2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0088f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.5f / 2, 0.3f));



        mat4 m3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.0088f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.5f / 2, 0.3f));



        matric =
            glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(-2 * dis, psy * dis - dis, psz * dis)) *

            m3;



        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);
        matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(-2 * dis, psy * dis - dis, psz * dis)) * m2;
        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);
        matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(-2 * dis, psy * dis - dis, psz * dis)) * m1;
        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);


        m1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f))
            * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.5f, 0.3f));




        m2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0088f, 0.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.5f / 2, 0.3f));



        m3 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0088f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f))

            * glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 1.5f / 2, 0.3f));
        matric =
            glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(psx * dis, dis, psz2 * dis)) *

            m3;



        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);
        matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(psx * dis, dis, psz2 * dis)) * m2;
        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);
        matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.18, 0.0, 1.0)) * glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(psx * dis, dis, psz2 * dis)) * m1;
        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);



    }

    // draw the cube turning on itself on the menu 

    void drawmenu(int shaderProgram, int shaderProgram2) {
        setup(shaderProgram, shaderProgram2);
        vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


        vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
        vec3 lightDirection = normalize(lightFocus - lightPosition);

        float lightNearPlane = 0.5f;
        float lightFarPlane = 20.0f;

        mat4 lightProjMatrix = perspective(angpers, (float)1024 / (float)1024, lightNearPlane, lightFarPlane);
        mat4 lightViewMatrix1 = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

        lightProjMatrix = lightProjMatrix * lightViewMatrix1;


        angzonmen = angzonmen + 0.02;
        mat4 matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.14, -0.12, 3)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(angzonmen), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
            matricef * glm::translate(glm::mat4(1.0f), glm::vec3(x * dis, y * dis - 0.05, z * dis)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.05, 0)) * matrice * glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.05, 0));
        mat4 lightViewMatrix = lightProjMatrix * matric;
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }


        //FACE D EN BAS
        texture(facedown);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 6);
        //FACE D EN HAUT
        texture(faceup);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 8, 6);
        //BEHIND FACE
        texture(facebehind);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 14, 6);
        //FRONT FACE
        texture(facefront);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 20, 6);
        //LEFT FACE
        texture(faceleft);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 26, 6);
        //RIGHT FACE
        texture(faceright);
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 32, 6);






        matric = glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(-dis - dis, psy * dis - 0.05, psz * dis));
        lightViewMatrix = lightProjMatrix * matric;

        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);



        matric = glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(1.0f, 0.0f, 0.0f)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(dis * psx, 2 * dis, psz2 * dis));
        lightViewMatrix = lightProjMatrix * matric;
        if (testshader) {

            glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
        }
        else {

            glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
        }
        glDrawArrays(GL_TRIANGLES, 2, 36);


    }





};


// class that defines the whole rubik's cube 
class cubes {
public:
    cubie cube[3][3][3];

    cubes() {
        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {


                    cube[in + 1][jn + 1][kn + 1] = cubie(in, jn, kn);
                    cout << txx;
                    settext();
                }
            }
        }



    }


    // set the textures : initialisation of all the textures :

    void settext() {

        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {
                    if (txx == 0) {
                        initfaces(0, mj, in + 1, jn + 1, kn + 1);
                        initfaces(1, mar, in + 1, jn + 1, kn + 1);
                        initfaces(2, bl, in + 1, jn + 1, kn + 1);
                        initfaces(3, du, in + 1, jn + 1, kn + 1);
                        initfaces(4, kp, in + 1, jn + 1, kn + 1);
                        initfaces(5, ed, in + 1, jn + 1, kn + 1);
                    }
                    if (txx == 1) {
                        initfaces(0, wolf, in + 1, jn + 1, kn + 1);
                        initfaces(1, duck, in + 1, jn + 1, kn + 1);
                        initfaces(2, cow, in + 1, jn + 1, kn + 1);
                        initfaces(3, butter, in + 1, jn + 1, kn + 1);
                        initfaces(4, cat, in + 1, jn + 1, kn + 1);
                        initfaces(5, croco, in + 1, jn + 1, kn + 1);
                    }
                    if (txx == 2) {
                        initfaces(0, red, in + 1, jn + 1, kn + 1);
                        initfaces(1, blue, in + 1, jn + 1, kn + 1);
                        initfaces(2, green, in + 1, jn + 1, kn + 1);
                        initfaces(3, orange, in + 1, jn + 1, kn + 1);
                        initfaces(4, white, in + 1, jn + 1, kn + 1);
                        initfaces(5, yellow, in + 1, jn + 1, kn + 1);
                    }
                    if (txx == 3) {
                        initfaces(0, eu, in + 1, jn + 1, kn + 1);
                        initfaces(1, as, in + 1, jn + 1, kn + 1);
                        initfaces(2, amm, in + 1, jn + 1, kn + 1);
                        initfaces(3, am, in + 1, jn + 1, kn + 1);
                        initfaces(4, af, in + 1, jn + 1, kn + 1);
                        initfaces(5, oc, in + 1, jn + 1, kn + 1);
                    }
                }
            }
        }
    }

    // each face takes its texture :

    void initfaces(int a, GLuint wolf, int in, int jn, int kn) {
        if (a == 0) {
            cube[in][jn][kn].faceup = wolf;
        }
        if (a == 1) {
            cube[in][jn][kn].facedown = wolf;

        }
        if (a == 2) {


            cube[in][jn][kn].facefront = wolf;

        }
        if (a == 3) {
            cube[in][jn][kn].facebehind = wolf;
        }
        if (a == 4) {

            cube[in][jn][kn].faceleft = wolf;
        }
        if (a == 5) {

            cube[in][jn][kn].faceright = wolf;
        }
    }


    void initfaces(int a, GLuint wolf[3][3], int in, int jn, int kn) {
        if (a == 0) {
            cube[in][jn][kn].faceup = wolf[in][kn];
        }
        if (a == 1) {
            cube[in][jn][kn].facedown = wolf[in][kn];

        }
        if (a == 2) {


            cube[in][jn][kn].facefront = wolf[in][2 - jn];

        }
        if (a == 3) {
            cube[in][jn][kn].facebehind = wolf[in][2 - jn];
        }
        if (a == 4) {

            cube[in][jn][kn].faceleft = wolf[kn][2 - jn];
        }
        if (a == 5) {

            cube[in][jn][kn].faceright = wolf[2 - kn][2 - jn];
        }
    }




    // draws the whole cube :
    // goes through each position in the array cube and draw a small cube there 

    void dessins(int shaderProgram, int shaderProgram2) {


        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {

                    if (in == 1) SetUniformVec3(shaderProgram, "couleur",
                        vec3(0.0f, 1.0f, 0.0f));
                    if (in == 0) SetUniformVec3(shaderProgram, "couleur",
                        vec3(1.0f, 0.0f, 0.0f));
                    if (in == -1) SetUniformVec3(shaderProgram, "couleur",
                        vec3(0.0f, 0.0f, 1.0f));


                    cube[in + 1][jn + 1][kn + 1].draw(shaderProgram, shaderProgram2);




                }
            }
        }


    }



    // draw the menu cube 
    void dessinsmenu(int shaderProgram, int shaderProgram2) {


        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {

                    if (in == 1) SetUniformVec3(shaderProgram, "couleur",
                        vec3(0.0f, 1.0f, 0.0f));
                    if (in == 0) SetUniformVec3(shaderProgram, "couleur",
                        vec3(1.0f, 0.0f, 0.0f));
                    if (in == -1) SetUniformVec3(shaderProgram, "couleur",
                        vec3(0.0f, 0.0f, 1.0f));


                    cube[in + 1][jn + 1][kn + 1].drawmenu(shaderProgram, shaderProgram2);




                }
            }
        }


    }


    // write in the file for the resume :


    bool write(
        const char* path,
        const char notre_array
    ) {




        ofstream savefile;
        savefile.open(path, ios::out | ios::app);
        savefile << notre_array << "\n";
        savefile.close();

        return 0;
    }


    // the animation for the turning cubes on the y : ANIMATION DURING THE GAME 

    void animturny(int index, int dir) {
        cnnt++;
        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {
                    if (cnnt < 61) {

                        if (cube[in + 1][jn + 1][kn + 1].y == (index)) {

                            cube[in + 1][jn + 1][kn + 1].matricef =
                                cube[in + 1][jn + 1][kn + 1].matricef * glm::rotate(glm::mat4(1.0f), glm::radians(dir * 1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
                        }
                    }
                    else {
                        cnnt = 0; resetrest();
                        // cout << "got there\n";
                       //  cout << "is htis ::::  " << cube[in + 1][jn + 1][kn + 1].y << "equal to this :::" << index << "\n";
                        for (int in = -1; in < 2; in++) {
                            for (int jn = -1; jn < 2; jn++) {
                                for (int kn = -1; kn < 2; kn++) {

                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));



                                }
                            }
                        }

                        if (!solving)
                            nbrmov++;

                        if (dir == 1) {
                            turningy(index);
                            const char in = 49; write("../Assets/textes/axe.txt", in);
                            const char in1 = index + 1 + 48; write("../Assets/textes/ind.txt", in1);
                        }
                        if (dir == -1) {
                            turningy(index); turningy(index); turningy(index);
                            const char in = 49; write("../Assets/textes/axe.txt", in);
                            const char in1 = index + 1 + 48; write("../Assets/textes/ind.txt", in1);
                            write("../Assets/textes/axe.txt", in);
                            write("../Assets/textes/axe.txt", in);
                            write("../Assets/textes/ind.txt", in1);
                            write("../Assets/textes/ind.txt", in1);

                        }


                    }


                }
            }
        }




    }



    void animturnx(int index, int dir) {
        cnnt++;
        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {
                    if (cnnt < 61) {

                        if (cube[in + 1][jn + 1][kn + 1].x == (index)) {

                            cube[in + 1][jn + 1][kn + 1].matricef =
                                cube[in + 1][jn + 1][kn + 1].matricef * glm::rotate(glm::mat4(1.0f), glm::radians(-1.5f * dir), glm::vec3(1.0f, 0.0f, 0.0f));
                        }
                    }
                    else {


                        if (!solving)
                            nbrmov++;
                        cnnt = 0; resetrest();
                        //  cout << "got there\n";
                         // cout << "is htis ::::  " << cube[in + 1][jn + 1][kn + 1].y << "equal to this :::" << index << "\n";
                        for (int in = -1; in < 2; in++) {
                            for (int jn = -1; jn < 2; jn++) {
                                for (int kn = -1; kn < 2; kn++) {
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                                }
                            }
                        }
                        if (dir == 1) {


                            turningx(index);
                            const char in = 48; write("../Assets/textes/axe.txt", in);
                            const char in1 = index + 1 + 48; write("../Assets/textes/ind.txt", in1);
                        }
                        if (dir == -1) {
                            turningx(index); turningx(index); turningx(index);
                            const char in = 48; write("../Assets/textes/axe.txt", in);
                            const char in1 = index + 1 + 48; write("../Assets/textes/ind.txt", in1);
                            write("../Assets/textes/axe.txt", in);
                            write("../Assets/textes/ind.txt", in1);
                            write("../Assets/textes/axe.txt", in);
                            write("../Assets/textes/ind.txt", in1);
                        }

                    }


                }
            }
        }




    }


    void animturnz(int index, int dir) {
        cnnt++;
        //cout << cnnt << "   \n";    
        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {
                    if (cnnt < 60) {

                        if (cube[in + 1][jn + 1][kn + 1].z == (index)) {

                            cube[in + 1][jn + 1][kn + 1].matricef =
                                cube[in + 1][jn + 1][kn + 1].matricef * glm::rotate(glm::mat4(1.0f), glm::radians(dir * 1.5f), glm::vec3(0.0f, 0.0f, 1.0f));
                        }
                    }
                    else {
                        if (!solving)
                            nbrmov++;
                        cout << nbrmov << " that was the numb   here the movement " << axemov[nbrmov]
                            << "\nindex  : " << indexmov[nbrmov] << "the direction :  " << dirmov[nbrmov] << "\n\n";
                        cnnt = 0; resetrest();
                        //  cout << "got there\n";
                         // cout << "is htis ::::  " << cube[in + 1][jn + 1][kn + 1].y << "equal to this :::" << index << "\n";

                        if (dir == 1) {
                            turningz(index);
                            const char in = 50; write("../Assets/textes/axe.txt", in);
                            const char in1 = index + 1 + 48; write("../Assets/textes/ind.txt", in1);
                        }
                        if (dir == -1) {
                            turningz(index); turningz(index); turningz(index);
                            const char in = 50; write("../Assets/textes/axe.txt", in);
                            const char in1 = index + 1 + 48; write("../Assets/textes/ind.txt", in1);
                            write("../Assets/textes/axe.txt", in);
                            write("../Assets/textes/axe.txt", in);
                            write("../Assets/textes/ind.txt", in1);
                            write("../Assets/textes/ind.txt", in1);
                        }

                        for (int in = -1; in < 2; in++) {
                            for (int jn = -1; jn < 2; jn++) {
                                for (int kn = -1; kn < 2; kn++) {
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                                    cube[in + 1][jn + 1][kn + 1].matricef = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                                }
                            }
                        }
                    }


                }

            }
        }




    }


    // the actual switch in the position
    void turningx(int index) {


        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {
                    float transitory = cube[in + 1][jn + 1][kn + 1].z;
                    if (cube[in + 1][jn + 1][kn + 1].x == (index)) {
                        if ((cube[in + 1][jn + 1][kn + 1].y == -1))cube[in + 1][jn + 1][kn + 1].z = 1;
                        if ((cube[in + 1][jn + 1][kn + 1].y == 0))cube[in + 1][jn + 1][kn + 1].z = 0;
                        if ((cube[in + 1][jn + 1][kn + 1].y == 1))cube[in + 1][jn + 1][kn + 1].z = -1;
                        cube[in + 1][jn + 1][kn + 1].matrice = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * cube[in + 1][jn + 1][kn + 1].matrice;
                        if ((transitory == -1))cube[in + 1][jn + 1][kn + 1].y = -1;
                        if ((transitory == -0))cube[in + 1][jn + 1][kn + 1].y = 0;
                        if ((transitory == 1))cube[in + 1][jn + 1][kn + 1].y = 1;


                    }


                }
            }
        }

    }


    void turningz(int index) {


        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {
                    float transitory = cube[in + 1][jn + 1][kn + 1].x;
                    if (cube[in + 1][jn + 1][kn + 1].z == (index)) {
                        if ((cube[in + 1][jn + 1][kn + 1].y == -1)) cube[in + 1][jn + 1][kn + 1].x = 1;
                        if ((cube[in + 1][jn + 1][kn + 1].y == -0)) cube[in + 1][jn + 1][kn + 1].x = 0;
                        if ((cube[in + 1][jn + 1][kn + 1].y == 1)) cube[in + 1][jn + 1][kn + 1].x = -1;
                        cube[in + 1][jn + 1][kn + 1].matrice = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * cube[in + 1][jn + 1][kn + 1].matrice;
                        if ((transitory == -1))cube[in + 1][jn + 1][kn + 1].y = -1;
                        if ((transitory == -0))cube[in + 1][jn + 1][kn + 1].y = 0;
                        if ((transitory == 1))cube[in + 1][jn + 1][kn + 1].y = 1;


                    }


                }
            }
        }

    }


    void turningy(int index) {
        TEST4 = false;

        for (int in = -1; in < 2; in++) {
            for (int jn = -1; jn < 2; jn++) {
                for (int kn = -1; kn < 2; kn++) {


                    // cout <<"cube value   :"<< cube[in + 1][jn + 1][kn + 1].y<< "equaaalsss   : " << -0.17f + index * 0.12f <<"\n";
                    if ((cube[in + 1][jn + 1][kn + 1].y) == (index)) {

                        float transitory = cube[in + 1][jn + 1][kn + 1].x;



                        if ((cube[in + 1][jn + 1][kn + 1].z == -1)) {
                            cube[in + 1][jn + 1][kn + 1].x = -1;
                        }
                        if ((cube[in + 1][jn + 1][kn + 1].z == 0)) {
                            cube[in + 1][jn + 1][kn + 1].x = 0;
                        }
                        if ((cube[in + 1][jn + 1][kn + 1].z == 1)) {
                            cube[in + 1][jn + 1][kn + 1].x = 1;
                        }


                        cube[in + 1][jn + 1][kn + 1].matrice = glm::rotate(glm::mat4(1.0f), glm::radians(+90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * cube[in + 1][jn + 1][kn + 1].matrice;

                        if (transitory == -1) {
                            cube[in + 1][jn + 1][kn + 1].z = 1;
                        }
                        if (transitory == 0.0) {
                            cube[in + 1][jn + 1][kn + 1].z = 0;
                        }
                        if (transitory == 1) {
                            cube[in + 1][jn + 1][kn + 1].z = -1;
                        }

                    }


                }
            }
        }

    }






};


//draw the timer 
void timcub(int shaderProgram, int shaderProgram2) {
    GLuint   mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");
    GLuint  mWorldMatrixLocation2 = glGetUniformLocation(shaderProgram2, "transform_in_light_space");
    GLuint mshader = shaderProgram;
    vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


    vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
    vec3 lightDirection = normalize(lightFocus - lightPosition);

    float lightNearPlane = 0.5f;
    float lightFarPlane = 20.0f;

    mat4 lightProjMatrix = perspective(angpers, (float)1024 / (float)1024, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix1 = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

    lightProjMatrix = lightProjMatrix * lightViewMatrix1;

    mat4 matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.44f, 0.13f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(-1, 1, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    mat4 lightViewMatrix = lightProjMatrix * matric;


    texture(numbers[secondes]);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);



    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.44f - 0.08, 0.13f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(-1, 1, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    lightViewMatrix = lightProjMatrix * matric;

    texture(numbers[tensec]);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);


    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.68f, 0.13f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(-1, 1, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    lightViewMatrix = lightProjMatrix * matric;

    texture(numbers[mins]);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);







    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.68f - 0.08, 0.13f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(-1, 1, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    lightViewMatrix = lightProjMatrix * matric;

    texture(numbers[tenmin]);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }

    glDrawArrays(GL_TRIANGLES, 2, 36);


    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.70f - 0.15, 0.46f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.6, 1.6, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    lightViewMatrix = lightProjMatrix * matric;
    if (txx == 0)  texture(dua);
    if (txx == 1)  texture(wolfa);
    if (txx == 2)  texture(red);
    if (txx == 3)  texture(eua);
    if (testshader) { glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]); }
    else { glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]); }
    glDrawArrays(GL_TRIANGLES, 2, 36);

    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.70 - 0.15 + 0.19, 0.46f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.6, 1.6, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    lightViewMatrix = lightProjMatrix * matric;
    if (txx == 0)  texture(mja);
    if (txx == 1)  texture(ducka);
    if (txx == 2)  texture(green);
    if (txx == 3)  texture(amma);
    if (testshader) { glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]); }
    else { glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]); }
    glDrawArrays(GL_TRIANGLES, 2, 36);


    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.70 - 0.15 + 0.38, 0.46f, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.6, 1.6, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    lightViewMatrix = lightProjMatrix * matric;
    if (txx == 0)  texture(kpa);
    if (txx == 1)  texture(buttera);
    if (txx == 2)  texture(yellow);
    if (txx == 3)  texture(ama);
    if (testshader) { glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]); }
    else { glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]); }
    glDrawArrays(GL_TRIANGLES, 2, 36);




    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.70f - 0.15, 0.46f + 0.2, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.6, 1.6, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    lightViewMatrix = lightProjMatrix * matric;
    if (txx == 0)  texture(eda);
    if (txx == 1)  texture(cata);
    if (txx == 2)  texture(white);
    if (txx == 3)  texture(asa);
    if (testshader) { glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]); }
    else { glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]); }
    glDrawArrays(GL_TRIANGLES, 2, 36);

    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.70 - 0.15 + 0.19, 0.46f + 0.2, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.6, 1.6, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    lightViewMatrix = lightProjMatrix * matric;
    if (txx == 0)  texture(bla);
    if (txx == 1)  texture(crocoa);
    if (txx == 2)  texture(blue);
    if (txx == 3)  texture(oca);
    if (testshader) { glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]); }
    else { glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]); }
    glDrawArrays(GL_TRIANGLES, 2, 36);


    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.70 - 0.15 + 0.38, 0.46f + 0.2, -0.146f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.6, 1.6, 0.001)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));;
    lightViewMatrix = lightProjMatrix * matric;
    if (txx == 0)  texture(mara);
    if (txx == 1)  texture(cowa);
    if (txx == 2)  texture(orange);
    if (txx == 3)  texture(afa);
    if (testshader) { glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]); }
    else { glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]); }
    glDrawArrays(GL_TRIANGLES, 2, 36);







}
cubes cub;
// solve the game 

void solve() {

    if (cnnt == 0) pause++;
    if ((cnnt == 0)) {


        cout << "the array i m solving of size " << nbrmov << "   \n";
        for (int cum = 0; cum < nbrmov + 1; cum++) {
            cout << "the axe value is : " << axemov[cum] << "    the direction is " << dirmov[cum] << "\n";
        }
        cout << "   \n\n\n";
        nbrmov = nbrmov - 1;
        axes = axemov[nbrmov];
        int direc = dirmov[nbrmov];
        int indic = indexmov[nbrmov];

        pause = 0;
        resetrest();
        if (nbrmov > -1) {
            if ((axes == 0) && (indic == -1) && (direc == -1))   xaxe[0] = true;
            if ((axes == 0) && (indic == 0) && (direc == -1))   xaxe[1] = true;
            if ((axes == 0) && (indic == 1) && (direc == -1))   xaxe[2] = true;
            if ((axes == 0) && (indic == -1) && (direc == 1))   xaxe[3] = true;
            if ((axes == 0) && (indic == 0) && (direc == 1))   xaxe[4] = true;
            if ((axes == 0) && (indic == 1) && (direc == 1))   xaxe[5] = true;

            if ((axes == 1) && (indic == -1) && (direc == -1))   yaxe[0] = true;
            if ((axes == 1) && (indic == 0) && (direc == -1))   yaxe[1] = true;
            if ((axes == 1) && (indic == 1) && (direc == -1))   yaxe[2] = true;
            if ((axes == 1) && (indic == -1) && (direc == 1))   yaxe[3] = true;
            if ((axes == 1) && (indic == 0) && (direc == 1))   yaxe[4] = true;
            if ((axes == 1) && (indic == 1) && (direc == 1))   yaxe[5] = true;


            if ((axes == 2) && (indic == -1) && (direc == -1))   zaxe[0] = true;
            if ((axes == 2) && (indic == 0) && (direc == -1))   zaxe[1] = true;
            if ((axes == 2) && (indic == 1) && (direc == -1))   zaxe[2] = true;
            if ((axes == 2) && (indic == -1) && (direc == 1))   zaxe[3] = true;
            if ((axes == 2) && (indic == 0) && (direc == 1))   zaxe[4] = true;
            if ((axes == 2) && (indic == 1) && (direc == 1))   zaxe[5] = true;

        }






        if (nbrmov < 1) {
            std::ofstream ofs;
            ofs.open("../Assets/textes/axe.txt", std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            ofs.open("../Assets/textes/ind.txt", std::ofstream::out | std::ofstream::trunc);
            ofs.close();
            solving = false; nbrmov = 0;  animals = true;
        }
    }
}

void yturnfr() {
    if (psy == 1)  yaxe[0] = true;
    if (psy == 0)  yaxe[1] = true;
    if (psy == -1)   yaxe[2] = true;


}

void yturnbh() {
    if (psy == 1)  yaxe[3] = true;
    if (psy == 0)  yaxe[4] = true;
    if (psy == -1)   yaxe[5] = true;


}


void zturnfr() {
    if (psz == -1)  zaxe[0] = true;
    if (psz == 0)  zaxe[1] = true;
    if (psz == 1)   zaxe[2] = true;


}

void zturnbh() {
    if (psz == -1)  zaxe[3] = true;
    if (psz == 0)  zaxe[4] = true;
    if (psz == 1)   zaxe[5] = true;


}
void xturnfr() {
    if (psx == 1)  xaxe[0] = true;
    if (psx == 0)  xaxe[1] = true;
    if (psx == -1)   xaxe[2] = true;


}

void xturnbh() {
    if (psx == 1)  xaxe[3] = true;
    if (psx == 0)  xaxe[4] = true;
    if (psx == -1)   xaxe[5] = true;


}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    //music:





    if (key == GLFW_KEY_G && action != GLFW_RELEASE) {
        yturnfr();

    }
    if (key == GLFW_KEY_H && action != GLFW_RELEASE) {
        yturnbh();

    }

    if (key == GLFW_KEY_J && action != GLFW_RELEASE) {
        zturnfr();

    }
    if (key == GLFW_KEY_K && action != GLFW_RELEASE) {
        zturnbh();

    }

    if (key == GLFW_KEY_N && action != GLFW_RELEASE) {
        xturnbh();

    }

    if (key == GLFW_KEY_M && action != GLFW_RELEASE) {
        xturnfr();

    }

    if (key == GLFW_KEY_M && action != GLFW_RELEASE) {
        xturnfr();

    }

    if (key == GLFW_KEY_Y && action != GLFW_RELEASE) {
        testsound = true;

    }
    // --------------SELECTING THE INDIVIDUAL MODEL TO CONTROL"-------------------------------------
    // set the mode to change the model "8I "
    if (key == GLFW_KEY_1 && action != GLFW_RELEASE) {
        if (cnnt == 0)
            xaxe[0] = true;




        // set the mode to change the model "8N "
    }
    if (key == GLFW_KEY_2 && action != GLFW_RELEASE) {
        if (cnnt == 0)
            yaxe[0] = true;

    }
    // set the mode to change the model "A4 "
    if (key == GLFW_KEY_3 && action != GLFW_RELEASE) {
        if (cnnt == 0)
            zaxe[0] = true;


    }
    // set the mode to change the model "Y0 "
    if (key == GLFW_KEY_4 && action != GLFW_RELEASE) {

        TEST4 = true;
    }


    //  SETTING TO DEFAULT = CONTROLING ALL THE MODELS AT ONCE
    if (key == GLFW_KEY_0 && action != GLFW_RELEASE) {
        TEST1 = false;
        TEST2 = false;
        TEST3 = false;
        TEST4 = false;
    }
    if (key == GLFW_KEY_X && action != GLFW_RELEASE) {
        testure = !testure;

    }
    if (key == GLFW_KEY_W && action != GLFW_RELEASE) {
        if (psz > -1)
            psz = psz - 1;

    }
    if (key == GLFW_KEY_S && action != GLFW_RELEASE) {
        if (psz < 1)
            psz = psz + 1;

    }
    if (key == GLFW_KEY_A && action != GLFW_RELEASE) {
        if (psy > -1)
            psy = psy - 1;

    }
    if (key == GLFW_KEY_D && action != GLFW_RELEASE) {
        if (psy < 1)
            psy = psy + 1;

    }


    if (key == GLFW_KEY_9 && action != GLFW_RELEASE) {
        if (psx > -1)
            psx = psx - 1;

    }
    if (key == GLFW_KEY_RIGHT && action != GLFW_RELEASE) {
        if (psx < 1)
            psx = psx + 1;

    }
    if (key == GLFW_KEY_UP && action != GLFW_RELEASE) {
        if (psz2 > -1)
            psz2 = psz2 - 1;

    }
    if (key == GLFW_KEY_DOWN && action != GLFW_RELEASE) {
        if (psz2 < 1)
            psz2 = psz2 + 1;

    }



    // Change world oriontation -----------------------------

    // texture on/off


    // Show line view
    if (key == GLFW_KEY_L && action != GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (key == GLFW_KEY_Z && action != GLFW_RELEASE) {
        TEST_A = !TEST_A;
    }
    // Show vertex view
    if (key == GLFW_KEY_P && action != GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    // Show triangle view
    if (key == GLFW_KEY_T && action != GLFW_RELEASE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (key == GLFW_KEY_T && action != GLFW_RELEASE) {
        shuffling = true;

    }
    if (key == GLFW_KEY_B && action != GLFW_RELEASE) {
        solving = true;


    }
    //Scale UP

    // DEPENDING ON THE SELECTED NUMBER ALL THE MODELS OR EACH ONE IINDIVIDUALLY WILL BE CONTROLED BY ,
    //THE FOLLOWING KEYS :

    //Translate Models up



}
vec3 computeCameraLookAt(double& lastMousePosX, double& lastMousePosY, float dt);

GLuint setupModelVBO(string path, int& vertexCount);

// Sets up a model using an Element Buffer Object to refer to vertex data
GLuint setupModelEBO(string path, int& vertexCount);

// shader variable setters
void SetUniformMat4(GLuint shader_id, const char* uniform_name,
    mat4 uniform_value) {
    glUseProgram(shader_id);
    glUniformMatrix4fv(glGetUniformLocation(shader_id, uniform_name), 1, GL_FALSE,
        &uniform_value[0][0]);
}

template <class T>
void SetUniform1Value(GLuint shader_id, const char* uniform_name,
    T uniform_value) {
    glUseProgram(shader_id);
    glUniform1i(glGetUniformLocation(shader_id, uniform_name), uniform_value);
    glUseProgram(0);
}
GLFWwindow* window = nullptr;
bool InitContext();



struct TexturedColoredVertex
{
    TexturedColoredVertex()
        : position(NULL), color(NULL), uv(NULL), normals(NULL) {}
    TexturedColoredVertex(vec3 _position, vec3 _color, vec2 _uv, vec3 _normals)
        : position(_position), color(_color), uv(_uv), normals(_normals) {}

    vec3 position;
    vec3 color;
    vec2 uv;
    vec3 normals;
};

int createVertexArrayObject()
{




    TexturedColoredVertex vertexArray[300] = {



        //grid points :

         TexturedColoredVertex(vec3(0.0f,  0.0f, 01.00f),  // top center position 0
        vec3(0.93f,0.69f,0.01f),vec2(0.0f, 1.0f),vec3(0.0,0.0,0.0)),  // top center color (red) 1


       TexturedColoredVertex(glm::vec3(0.0f, 0.0f, -1.00f),  // bottom right 2
        glm::vec3(0.93f,0.69f,0.01f),vec2(0.0f, 1.0f),vec3(0.0,0.0,0.0)),  // top center color (red) 1

        // Cube model needed points













//T1   DBL,DBR,DFL,
      TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, -0.05f),
        glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(0.0f,-1.0f,0.0f)),
        //DOWN BACK left DBL

       TexturedColoredVertex(glm::vec3(0.05f, 0.0f,-0.05f),
        glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,-1.0f,0.0f)),
        //DOWN b right DBR

      TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, 0.05f),
        glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,-1.0f,0.0f)),
        //DOWN FRONT l DFL

// T2 DBR,DFR,DFL ,
   TexturedColoredVertex(glm::vec3(0.05f, 0.0f,-0.05f),
        glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,-1.0f,0.0f)),
        //DOWN b right DBR


       TexturedColoredVertex(glm::vec3(0.05f, 0.0f, 0.05f),
        glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(0.0f,-1.0f,0.0f)),
        //d fr r DFR

            TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, 0.05f),
               glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,-1.0f,0.0f)),
               //DOWN FRONT l DFL
       //T3  HBL,HBR,HFL,    


              TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, -0.05f),
               glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(0.0f,1.0f,0.0f)),
               //HIGH BACK l HBL

             TexturedColoredVertex(glm::vec3(0.05f, 0.1f, -0.05f),
               glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,1.0f,0.0f)),
               //HIGH back r HBR

             TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, 0.05f),
               glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,1.0f,0.0f)),
               //HIGH FRONT left HFL
       //T4 HBR,HFR,HFL ,
         TexturedColoredVertex(glm::vec3(0.05f, 0.1f, -0.05f),
               glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,1.0f,0.0f)),
               //HIGH back r HBR

             TexturedColoredVertex(glm::vec3(0.05f, 0.1f, 0.05f),
               glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(0.0f,1.0f,0.0f)),
               // HFR

                     TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, 0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,1.0f,0.0f)),
                       //HIGH FRONT left HFL

               //T5    DBL,HBL,HBR,
               TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, -0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,0.0f,-1.0f)),
                       //DOWN BACK left DBL

                      TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, -0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(0.0f,0.0f,-1.0f)),
                       //HIGH BACK l HBL

               TexturedColoredVertex(glm::vec3(0.05f, 0.1f, -0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,0.0f,-1.0f)),
                       //HIGH back r HBR

               //T6       DBL,HBR,DBR,

               TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, -0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,0.0f,-1.0f)),
                       //DOWN BACK left DBL

               TexturedColoredVertex(glm::vec3(0.05f, 0.1f, -0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,0.0f,-1.0f)),
                       //HIGH back r HBR

                 TexturedColoredVertex(glm::vec3(0.05f, 0.0f,-0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(0.0f,0.0f,-1.0f)),
                       //DOWN b right DBR

               //T7 DFL,HFL,HFR,

                    TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, 0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,0.0f,1.0f)),
                       //DOWN FRONT l DFL

                     TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, 0.05f),
                       glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(0.0f,0.0f,1.0f)),
                       //HIGH FRONT left HFL

          TexturedColoredVertex(glm::vec3(0.05f, 0.1f, 0.05f),
              glm::vec3(0.79f, 0.93f, 0.90f), vec2(1.0f, 1.0f), vec3(0.0f,0.0f,1.0f)),
              // HFR


              //T8  DFL,HFR,DFR,
                    TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, 0.05f),
                      glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(0.0f,0.0f,1.0f)),
                      //DOWN FRONT l DFL

                   TexturedColoredVertex(glm::vec3(0.05f, 0.1f, 0.05f),
                      glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(0.0f,0.0f,1.0f)),
                      // HFR
                          TexturedColoredVertex(glm::vec3(0.05f, 0.0f, 0.05f),
                              glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(0.0f,0.0f,1.0f)),
                              //d fr r DFR

                             //T9  DBL,HBL,HFL,
                              TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, -0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(-1.0f,0.0f,0.0f)),
                                     //DOWN BACK left DBL

                                    TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, -0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(-1.0f,0.0f,0.0f)),
                                     //HIGH BACK l HBL

                                   TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, 0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(-1.0f,0.0f,0.0f)),
                                     //HIGH FRONT left HFL
                             // T10  DBL,DFL,HFL,
                             TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, -0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(-1.0f,0.0f,0.0f)),
                                     //DOWN BACK left DBL
                                  TexturedColoredVertex(glm::vec3(-0.05f, 0.0f, 0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(-1.0f,0.0f,0.0f)),
                                     //DOWN FRONT l DFL

                                   TexturedColoredVertex(glm::vec3(-0.05f, 0.1f, 0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(-1.0f,0.0f,0.0f)),
                                     //HIGH FRONT left HFL
                             // T11  DBR,HFR,HBR,

                               TexturedColoredVertex(glm::vec3(0.05f, 0.0f,-0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(1.0f,0.0f,0.0f)),
                                     //DOWN b right DBR

                                   TexturedColoredVertex(glm::vec3(0.05f, 0.1f, 0.05f),
                                     glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(1.0f,0.0f,0.0f)),
                                     // HFR

                                     TexturedColoredVertex(glm::vec3(0.05f, 0.1f, -0.05f),
                                             glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 1.0f),vec3(1.0f,0.0f,0.0f)),
                                             //HIGH back r HBR
                                     //T12  DBR,DFR,HFR,

                                       TexturedColoredVertex(glm::vec3(0.05f, 0.0f,-0.05f),
                                             glm::vec3(0.79f, 0.93f, 0.90f),vec2(1.0f, 0.0f),vec3(1.0f,0.0f,0.0f)),
                                             //DOWN b right DBR


                                            TexturedColoredVertex(glm::vec3(0.05f, 0.0f, 0.05f),
                                             glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 0.0f),vec3(1.0f,0.0f,0.0f)),
                                             //d fr r DFR

                                                 TexturedColoredVertex(glm::vec3(0.05f, 0.1f, 0.05f),
                                                    glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.0f, 1.0f),vec3(1.0f,0.0f,0.0f)),// HFR





                                                 TexturedColoredVertex(glm::vec3(0.0f, 0.1f, 1.01f),
                                                    glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.05f, 0.05f), vec3(1.0f, 0.0f, 0.0f)),

                                                  TexturedColoredVertex(glm::vec3(0.0f, 0.0f, 0.0f),
                                                    glm::vec3(0.79f, 0.93f, 0.90f),vec2(0.01f, 0.01f), vec3(1.0f, 0.0f, 0.0f)),







                                                    //AXIS: Z+
                                                    TexturedColoredVertex(glm::vec3(0.0f, 0.0f, 0.00f),
                                                        glm::vec3(0.006f, 0.055f, 0.252f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),

                                                    TexturedColoredVertex(glm::vec3(0.0f, 0.0f, 0.1f),
                                                        glm::vec3(0.006f, 0.055f, 0.252f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),


                                                        //AXIs X+
                                                        TexturedColoredVertex(glm::vec3(0.0f, 0.0f, 0.00f),
                                                            glm::vec3(0.006f, 0.055f, 0.252f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),


                                                        TexturedColoredVertex(glm::vec3(0.1f, 0.0f, 0.00f),
                                                            glm::vec3(0.006f, 0.055f, 0.252f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),

                                                            //axis  y+

                                                            TexturedColoredVertex(glm::vec3(0.0f, 0.0f, 0.00f),
                                                                glm::vec3(0.006f, 0.055f, 0.252f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),


                                                            TexturedColoredVertex(glm::vec3(0.0f, 0.1f, 0.00f),
                                                                glm::vec3(0.006f, 0.055f, 0.252f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
                                                                // index

                                                             // index 46 is the next index



    };


    float thetaa = 0;
    float alphaa = 0;
    float y = 0;
    float x;
    float z = 0;
    float x1 = 0;
    float z1;
    float y1 = 0;
    float x2 = 0;
    float z2;
    float y3 = 0;
    float x3 = 0;
    float z3;
    float y2 = 0;
    float r = 0.5;
    int co = 0;
    vertexArray[46] = TexturedColoredVertex(glm::vec3(0.0f, 0.0f, 0.00f),
        glm::vec4(0.0f, 0.255f, 0.017f, 1.0f), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
    co = 47;
    vec3 normal;
    vec3 normal1;
    for (float thetaa = 0; thetaa <= 180; thetaa = thetaa + 5) {


        z = r * cos(radians(thetaa));
        x = r * sin(radians(thetaa)) * cos(radians(alphaa));
        y = r * sin(radians(thetaa)) * sin(radians(alphaa));

        z1 = r * cos(radians(thetaa + 5));
        x1 = r * sin(radians(thetaa + 5)) * cos(radians(alphaa));
        y1 = r * sin(radians(thetaa + 5)) * sin(radians(alphaa));


        z2 = r * cos(radians(thetaa + 5));
        x2 = r * sin(radians(thetaa + 5)) * cos(radians(alphaa + 5));
        y2 = r * sin(radians(thetaa + 5)) * sin(radians(alphaa + 5));

        z3 = r * cos(radians(thetaa));
        x3 = r * sin(radians(thetaa)) * cos(radians(alphaa + 5));
        y3 = r * sin(radians(thetaa)) * sin(radians(alphaa + 5));
        normal = vec3((x + x1 + x2) / 3, (y + y1 + y2) / 3, (z + z1 + z2) / 3) - vertexArray[46].position;
        normal1 = vec3((x3 + x1 + x2) / 3, (y3 + y1 + y2) / 3, (z3 + z1 + z2) / 3) - vertexArray[46].position;


        vertexArray[co] = TexturedColoredVertex(glm::vec3(x, y, z),
            glm::vec3(0.0f, 0.255f, 0.017f), vec2(0.0f, 0.0f), normal);
        co++;
        vertexArray[co] = TexturedColoredVertex(glm::vec3(x1, y1, z1),
            glm::vec3(0.0f, 0.255f, 0.017f), vec2(0.0f, 0.0f), normal);
        co++;
        vertexArray[co] = TexturedColoredVertex(glm::vec3(x2, y2, z2),
            glm::vec3(0.0f, 0.255f, 0.017f), vec2(0.0f, 0.0f), normal);
        co++;
        vertexArray[co] = TexturedColoredVertex(glm::vec3(x, y, z),
            glm::vec3(0.0f, 0.255f, 0.017f), vec2(0.0f, 0.0f), normal1);
        co++;
        vertexArray[co] = TexturedColoredVertex(glm::vec3(x2, y2, z2),
            glm::vec3(0.0f, 0.255f, 0.017f), vec2(0.0f, 0.0f), normal1);
        co++;
        vertexArray[co] = TexturedColoredVertex(glm::vec3(x3, y3, z3),
            glm::vec3(0.0f, 0.255f, 0.017f), vec2(0.0f, 0.0f), normal1);
        co++;


    }






    // H HIGHT D DOWN B BACK F FRONT L LEFT R RIGHT
    int DBL = 2;
    int DBR = 3;
    int DFL = 4;
    int DFR = 5;
    int HBL = 6;
    int HBR = 7;
    int HFL = 8;
    int HFR = 9;


    GLuint indexArray[] = { DBL,DBR,DFL,
                            DBR,DFR,DFL ,
                            HBL,HBR,HFL,
                            HBR,HFR,HFL ,
                            DBL,HBL,HBR,
                            DBL,HBR,DBR,
                            DFL,HFL,HFR,
                            DFL,HFR,DFR,

                            DBL,HBL,HFL,
                            DBL,DFL,HFL,
                            DBR,HFR,HBR,
                            DBR,DFR,HFR,




    };






    // Create a vertex array
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);


    // Upload Vertex Buffer to the GPU, keep a reference to it (vertexBufferObject)
    GLuint vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);




    GLuint elementBufferObject;
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);


    glVertexAttribPointer(0,                   // attribute 0 matches aPos in Vertex Shader
        3,                   // size
        GL_FLOAT,            // type
        GL_FALSE,            // normalized?
        sizeof(TexturedColoredVertex), // stride - each vertex contain 2 vec3 (position, color)
        (void*)0             // array buffer offset
    );
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1,                            // attribute 1 matches aColor in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)sizeof(vec3)      // color is offseted a vec3 (comes after position)
    );
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)(2 * sizeof(vec3))      // uv is offseted by 2 vec3 (comes after position and color)
    );
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3,                            // attribute 2 matches aUV in Vertex Shader
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(TexturedColoredVertex),
        (void*)(2 * sizeof(vec3) + sizeof(vec2))    // uv is offseted by 2 vec3 (comes after position and color)
    );
    glEnableVertexAttribArray(3);

    return vertexArrayObject;
}

void exec(string moves, string indexes) {


    cout << "asdf0\n";
    string indic = indexes;
    string direc = "1";
    string edo = moves;
    if ((edo == "0") && (indic == "0") && (direc == "1")) { cub.turningx(-1); }
    if ((edo == "0") && (indic == "1") && (direc == "1")) { cub.turningx(0); }
    if ((edo == "0") && (indic == "2") && (direc == "1")) { cub.turningx(1); }
    if ((edo == " 0") && (indic == "0") && (direc == "-1")) { cub.turningx(-1); cub.turningx(-1); cub.turningx(-1); }
    if ((edo == "0") && (indic == "1") && (direc == "-1")) { cub.turningx(0); cub.turningx(0); cub.turningx(0); }
    if ((edo == "0") && (indic == "2") && (direc == "-1")) { cub.turningx(1); cub.turningx(1); cub.turningx(1); }

    if ((edo == "1") && (indic == "0") && (direc == "1")) { cub.turningy(-1); }
    if ((edo == "1") && (indic == "1") && (direc == "1")) { cub.turningy(0); }
    if ((edo == "1") && (indic == "2") && (direc == "1")) { cub.turningy(1); }
    if ((edo == "1") && (indic == "0") && (direc == "-1")) { cub.turningy(-1); cub.turningy(-1); cub.turningy(-1); }
    if ((edo == "1") && (indic == "1") && (direc == "-1")) { cub.turningy(0); cub.turningy(0); cub.turningy(0); }
    if ((edo == "1") && (indic == "2") && (direc == "-1")) { cub.turningy(1); cub.turningy(1); cub.turningy(1); }


    if ((edo == "2") && (indic == "0") && (direc == "1")) { cub.turningz(-1); }
    if ((edo == "2") && (indic == "1") && (direc == "1")) { cub.turningz(0); }
    if ((edo == "2") && (indic == "2") && (direc == "1")) { cub.turningz(1); }
    if ((edo == "2") && (indic == "0") && (direc == "-1")) { cub.turningz(-1); cub.turningz(-1); cub.turningz(-1); }
    if ((edo == "2") && (indic == "1") && (direc == "-1")) { cub.turningz(0); cub.turningz(0); cub.turningz(0); }
    if ((edo == "2") && (indic == "2") && (direc == "-1")) { cub.turningz(1); cub.turningz(1); cub.turningz(1); }



}
bool read() {
    string lineaxe;
    string linedirec;
    string lineindex;
    ifstream axefile("../Assets/textes/axe.txt");

    ifstream indexfile("../Assets/textes/ind.txt");
    if (axefile.is_open() && indexfile.is_open())
    {
        while (getline(axefile, lineaxe) && getline(indexfile, lineindex))
        {


            cout << lineaxe << "\n";

            cout << lineindex;

            exec(lineaxe, lineindex);
        }
        axefile.close();

        indexfile.close();
    }

    else cout << "Unable to open file";

    return true;
}

bool resume = false;










void inmenu(int shaderProgram, int shaderProgram2) {
    GLuint   mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");
    GLuint  mWorldMatrixLocation2 = glGetUniformLocation(shaderProgram2, "transform_in_light_space");
    GLuint mshader = shaderProgram;
    vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


    vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
    vec3 lightDirection = normalize(lightFocus - lightPosition);

    float lightNearPlane = 0.5f;
    float lightFarPlane = 20.0f;

    mat4 lightProjMatrix = perspective(angpers, (float)1024 / (float)1024, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix1 = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

    lightProjMatrix = lightProjMatrix * lightViewMatrix1;

    mat4 matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 4.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(mat4(1.0f), vec3(18.5, 18.5, 0.001)) *
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f));;
    mat4 lightViewMatrix = lightProjMatrix * matric;

    texture(menutex);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);


    cub.dessinsmenu(shaderProgram, shaderProgram2);

}


void intheme(int shaderProgram, int shaderProgram2) {
    GLuint   mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");
    GLuint  mWorldMatrixLocation2 = glGetUniformLocation(shaderProgram2, "transform_in_light_space");
    GLuint mshader = shaderProgram;
    vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


    vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
    vec3 lightDirection = normalize(lightFocus - lightPosition);

    float lightNearPlane = 0.5f;
    float lightFarPlane = 20.0f;

    mat4 lightProjMatrix = perspective(angpers, (float)1024 / (float)1024, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix1 = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

    lightProjMatrix = lightProjMatrix * lightViewMatrix1;

    mat4 matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 4.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::scale(mat4(1.0f), vec3(18.5, 18.5, 0.001)) *
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f));;
    mat4 lightViewMatrix = lightProjMatrix * matric;

    texture(themetex);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);

    // drawsmall cubes
    float scaa = 0;
    if (mag1) {
        scaa = 0.4;
    }
    angzonmen = angzonmen + 0.8;
    matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.14f, 3.0f)) *

        glm::rotate(glm::mat4(1.0f), glm::radians(angzonmen), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0), vec3(1.0 + scaa)) *
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f));


    lightViewMatrix = lightProjMatrix * matric;

    //FACE D EN BAS

    texture(wolfa);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 6);
    //FACE D EN HAUT
    texture(ducka);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 8, 6);
    //BEHIND FACE
    texture(cowa);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 14, 6);
    //FRONT FACE
    texture(crocoa);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 20, 6);
    //LEFT FACE
    texture(buttera);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 26, 6);
    //RIGHT FACE
    texture(cata);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 32, 6);





    float scaa1 = 0;
    if (mag0) {
        scaa1 = 0.4;
    }

    matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.3f, -0.14f, 3.0f)) *

        glm::rotate(glm::mat4(1.0f), glm::radians(angzonmen + 15), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0), vec3(1.0 + scaa1)) *
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f));


    lightViewMatrix = lightProjMatrix * matric;
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    //FACE D EN BAS
    texture(mja);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 6);
    //FACE D EN HAUT
    texture(dua);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 8, 6);
    //BEHIND FACE
    texture(kpa);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 14, 6);
    //FRONT FACE
    texture(eda);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 20, 6);
    //LEFT FACE
    texture(bla);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 26, 6);
    //RIGHT FACE
    texture(mara);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 32, 6);



    float scaa2 = 0;
    if (mag3) {
        scaa2 = 0.4;
    }

    matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, -0.14f, 3.0f)) *

        glm::rotate(glm::mat4(1.0f), glm::radians(-angzonmen + 19), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0), vec3(1.0 + scaa2)) *
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f));


    lightViewMatrix = lightProjMatrix * matric;

    //FACE D EN BAS
    texture(eua);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 6);
    //FACE D EN HAUT
    texture(amma);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 8, 6);
    //BEHIND FACE
    texture(ama);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 14, 6);
    //FRONT FACE
    texture(asa);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 20, 6);
    //LEFT FACE
    texture(oca);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 26, 6);
    //RIGHT FACE
    texture(afa);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 32, 6);






    float scaa3 = 0;
    if (mag2) {
        scaa3 = 0.4;
    }

    matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.13f, 3.0f)) *

        glm::rotate(glm::mat4(1.0f), glm::radians(-angzonmen), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::scale(glm::mat4(1.0), vec3(1.0 + scaa3)) *
        glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05f, 0.0f));


    lightViewMatrix = lightProjMatrix * matric;

    //FACE D EN BAS
    texture(red);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 6);
    //FACE D EN HAUT
    texture(green);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 8, 6);
    //BEHIND FACE
    texture(yellow);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 14, 6);
    //FRONT FACE
    texture(white);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 20, 6);
    //LEFT FACE
    texture(blue);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 26, 6);
    //RIGHT FACE
    texture(orange);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 32, 6);




}

void incube(int shaderProgram, int shaderProgram2) {


    GLuint   mWorldMatrixLocation = glGetUniformLocation(shaderProgram, "model_matrix");
    GLuint  mWorldMatrixLocation2 = glGetUniformLocation(shaderProgram2, "transform_in_light_space");
    GLuint mshader = shaderProgram;
    vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


    vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
    vec3 lightDirection = normalize(lightFocus - lightPosition);

    float lightNearPlane = 0.5f;
    float lightFarPlane = 20.0f;

    mat4 lightProjMatrix = perspective(angpers, (float)1024 / (float)1024, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix1 = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

    lightProjMatrix = lightProjMatrix * lightViewMatrix1;

    mat4 matric = glm::translate(glm::mat4(1.0f), glm::vec3(-0.95, 0.0f, -0.15f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(mat4(1.0f), vec3(-14.5, 15.5, 0.001))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05, 0.0f));



    mat4 lightViewMatrix = lightProjMatrix * matric;

    texture(menucubedroit);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);



    matric = glm::translate(glm::mat4(1.0f), glm::vec3(0.37, -1.2, -0.149f)) *
        glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(mat4(1.0f), vec3(-13, 13, 0.001))
        * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.05, 0.0f));



    lightViewMatrix = lightProjMatrix * matric;

    texture(menucubebas);
    if (testshader) {

        glUniformMatrix4fv(mWorldMatrixLocation2, 1, GL_FALSE, &lightViewMatrix[0][0]);
    }
    else {

        glUniformMatrix4fv(mWorldMatrixLocation, 1, GL_FALSE, &matric[0][0]);
    }
    glDrawArrays(GL_TRIANGLES, 2, 36);

    timcub(shaderProgram, shaderProgram2);




}
bool loadOBJ2(
    const char* path,
    std::vector<int>& vertexIndices,
    std::vector<glm::vec3>& temp_vertices,
    std::vector<glm::vec3>& out_normals,
    std::vector<glm::vec2>& out_uvs) {

    std::vector<int> uvIndices, normalIndices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE* file;
    file = fopen(path, "r");
    if (!file) {
        printf("Impossible to open the file ! Are you in the right path ?\n");
        getchar();
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            res = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            res = fscanf(file, "%f %f\n", &uv.x, &uv.y);
            if (res != 2) {
                printf("Missing uv information!\n");
            }
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            res = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            if (res != 3) {
                printf("Missing normal information!\n");
            }
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            char* getRes;
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            bool uv = true;
            bool norm = true;
            char line[128];
            getRes = fgets(line, 128, file);
            if (getRes == 0) {
                printf("incomplete face\n");
            }

            //vertex, uv, norm
            int matches = sscanf(line, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                //vertex, norm
                matches = sscanf(line, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                if (matches != 6) {
                    //vertex, uv
                    matches = sscanf(line, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                    if (matches != 6) {
                        //vertex
                        matches = sscanf(line, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
                        if (matches != 3) {
                            printf("File can't be read by our simple parser. 'f' format expected: d/d/d d/d/d d/d/d || d/d d/d d/d || d//d d//d d//d\n");
                            printf("Character at %ld", ftell(file));
                            return false;
                        }
                        uv, norm = false;
                    }
                    else {
                        norm = false;
                    }
                }
                else {
                    uv = false;
                }
            }
            vertexIndices.push_back(abs(vertexIndex[0]) - 1);
            vertexIndices.push_back(abs(vertexIndex[1]) - 1);
            vertexIndices.push_back(abs(vertexIndex[2]) - 1);
            if (norm) {
                normalIndices.push_back(abs(normalIndex[0]) - 1);
                normalIndices.push_back(abs(normalIndex[1]) - 1);
                normalIndices.push_back(abs(normalIndex[2]) - 1);
            }
            if (uv) {
                uvIndices.push_back(abs(uvIndex[0]) - 1);
                uvIndices.push_back(abs(uvIndex[1]) - 1);
                uvIndices.push_back(abs(uvIndex[2]) - 1);
            }
        }
        else {
            char clear[1000];
            char* getsRes = fgets(clear, 1000, file);
        }
    }
    if (normalIndices.size() != 0)
        out_normals.resize(temp_normals.size());
    if (uvIndices.size() != 0)
        out_uvs.resize(uvIndices.size());
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        int vi = vertexIndices[i];

        if (uvIndices.size() != 0 && i < uvIndices.size()) {
            int ui = uvIndices[i];
            out_uvs[vi] = temp_uvs[ui];
        }


    }

    return true;
}


GLuint setupModelEBO(string path, int& vertexCount)
{
    vector<int> vertexIndices; //The contiguous sets of three indices of vertices, normals and UVs, used to make a triangle
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> UVs;

    //read the vertices from the cube.obj file
    //We won't be needing the normals or UVs for this program
    loadOBJ2(path.c_str(), vertexIndices, vertices, normals, UVs);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); //Becomes active VAO
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

    //Vertex VBO setup
    GLuint vertices_VBO;
    glGenBuffers(1, &vertices_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //couleur

    GLuint colors_VBO;
    glGenBuffers(1, &colors_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, colors_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);



    //UVs VBO setup
    GLuint uvs_VBO;
    glGenBuffers(1, &uvs_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvs_VBO);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    //Normals VBO setup


    GLuint normals_VBO;
    glGenBuffers(1, &normals_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(3);


    //EBO setup
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(int), &vertexIndices.front(), GL_STATIC_DRAW);

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
    vertexCount = vertexIndices.size();
    return VAO;
}







// load object function
bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec3>& out_normals,
    std::vector<glm::vec2>& out_uvs) {

    std::vector<int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE* file;
    file = fopen(path, "r");
    if (!file) {
        printf("Impossible to open the file ! Are you in the right path ?\n");
        printf(path);
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            int vertexIndex[3], uvIndex[3], normalIndex[3];
            bool uv = true;
            bool norm = true;
            char line[128];
            fgets(line, 128, file);
            //vertex, uv, norm
            int matches = sscanf(line, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                //vertex, norm
                matches = sscanf(line, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                if (matches != 6) {
                    //vertex, uv
                    matches = sscanf(line, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                    if (matches != 6) {
                        //vertex
                        matches = sscanf(line, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
                        if (matches != 6) {
                            printf("File can't be read by our simple parser. 'f' format expected: d/d/d d/d/d d/d/d || d/d d/d d/d || d//d d//d d//d\n");
                            printf("Character at %ld", ftell(file));
                            return false;
                        }
                        uv, norm = false;
                    }
                    else {
                        norm = false;
                    }
                }
                else {
                    uv = false;
                }
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            if (norm) {
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
            if (uv) {
                uvIndices.push_back(uvIndex[0]);
                uvIndices.push_back(uvIndex[1]);
                uvIndices.push_back(uvIndex[2]);
            }
        }
        else {
            char clear[1000];
            fgets(clear, 1000, file);
        }

    }
    //std::cout << "Vertex indices: " << vertexIndices.size() << std::endl;
    //std::cout << "UV indices: " << uvIndices.size() << std::endl;
    //std::cout << "Normal indices: " << normalIndices.size() << std::endl;
    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {
        if (uvIndices.size() != 0) {
            if (i < uvIndices.size()) {
                unsigned int uvIndex = abs(uvIndices[i]);
                glm::vec2 uv = temp_uvs[uvIndex - 1];
                out_uvs.push_back(uv);
            }
        }
        if (normalIndices.size() != 0) {
            if (i < normalIndices.size()) {
                unsigned int normalIndex = abs(normalIndices[i]);
                glm::vec3 normal = temp_normals[normalIndex - 1];
                out_normals.push_back(normal);
            }
        }

        unsigned int vertexIndex = abs(vertexIndices[i]);
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        out_vertices.push_back(vertex);
    }

    return true;
}



// fill the vbo with the data of the object loaded

GLuint setupModelVBO(string path, int& vertexCount) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> UVs;

    //read the vertex data from the model's OBJ file
    loadOBJ(path.c_str(), vertices, normals, UVs);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); //Becomes active VAO
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

    //Vertex VBO setup
    GLuint vertices_VBO;
    glGenBuffers(1, &vertices_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //color vbo setup
    GLuint color_VBO;
    glGenBuffers(1, &color_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), NULL, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    //UVs VBO setup
    GLuint uvs_VBO;
    glGenBuffers(1, &uvs_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvs_VBO);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    //Normals VBO setup
    GLuint normals_VBO;
    glGenBuffers(1, &normals_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(3);




    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs, as we are using multiple VAOs)
    vertexCount = vertices.size();
    return VAO;
}




int main(int argc, char* argv[]) {
    // PlaySound("essai.wav", NULL, SND_ASYNC | SND_FILENAME);

    if (!InitContext()) return -1;
    int moves[128];
    int indexes[128];
    int directions[128];
    int sizearray[1];


    numbers[0] = loadTexture("../Assets/Textures/0.png");
    numbers[1] = loadTexture("../Assets/Textures/1.png");
    numbers[2] = loadTexture("../Assets/Textures/2.png");
    numbers[3] = loadTexture("../Assets/Textures/3.png");
    numbers[4] = loadTexture("../Assets/Textures/4.png");
    numbers[5] = loadTexture("../Assets/Textures/5.png");
    numbers[6] = loadTexture("../Assets/Textures/6.png");
    numbers[7] = loadTexture("../Assets/Textures/7.png");
    numbers[8] = loadTexture("../Assets/Textures/8.png");
    numbers[9] = loadTexture("../Assets/Textures/9.png");

    menutex = loadTexture("../Assets/Textures/menu/menu.png");
    themetex = loadTexture("../Assets/Textures/menu/theme.jpg");

    // soltex = loadTexture("../Assets/Textures/menu/sol.jpg");
    menucubedroit = loadTexture("../Assets/Textures/menu/menucubedroit.jpg");
    menucubebas = loadTexture("../Assets/Textures/menu/mcb.png");

    blue = loadTexture("../Assets/Textures/blue.png");
    red = loadTexture("../Assets/Textures/red.png");
    yellow = loadTexture("../Assets/Textures/yellow.png");
    orange = loadTexture("../Assets/Textures/orange.png");
    green = loadTexture("../Assets/Textures/green.png");
    white = loadTexture("../Assets/Textures/white.png");

    bla = loadTexture("../Assets/Textures/all/bla.png");
    buttera = loadTexture("../Assets/Textures/all/buttera.jpg");
    cata = loadTexture("../Assets/Textures/all/cata.jpg");
    cowa = loadTexture("../Assets/Textures/all/cowa.jpg");
    wolfa = loadTexture("../Assets/Textures/all/wolfa.jpg");
    crocoa = loadTexture("../Assets/Textures/all/crocoa.jpg");
    dua = loadTexture("../Assets/Textures/all/dua.jpg");
    ducka = loadTexture("../Assets/Textures/all/ducka.jpg");
    eda = loadTexture("../Assets/Textures/all/eda.jpg");
    kpa = loadTexture("../Assets/Textures/all/kpa.jpg");
    mara = loadTexture("../Assets/Textures/all/mara.jpg");
    mja = loadTexture("../Assets/Textures/all/mja.jpg");

    bl[0][0] = loadTexture("../Assets/Textures/bl00.jpg");
    bl[0][1] = loadTexture("../Assets/Textures/bl01.jpg");
    bl[0][2] = loadTexture("../Assets/Textures/bl02.jpg");
    bl[1][0] = loadTexture("../Assets/Textures/bl10.jpg");
    bl[1][1] = loadTexture("../Assets/Textures/bl11.jpg");
    bl[1][2] = loadTexture("../Assets/Textures/bl12.jpg");
    bl[2][0] = loadTexture("../Assets/Textures/bl20.jpg");
    bl[2][1] = loadTexture("../Assets/Textures/bl21.jpg");
    bl[2][2] = loadTexture("../Assets/Textures/bl22.jpg");
    mj[0][0] = loadTexture("../Assets/Textures/mj00.jpg");
    mj[0][1] = loadTexture("../Assets/Textures/mj01.jpg");
    mj[0][2] = loadTexture("../Assets/Textures/mj02.jpg");
    mj[1][0] = loadTexture("../Assets/Textures/mj10.jpg");
    mj[1][1] = loadTexture("../Assets/Textures/mj11.jpg");
    mj[1][2] = loadTexture("../Assets/Textures/mj12.jpg");
    mj[2][0] = loadTexture("../Assets/Textures/mj20.jpg");
    mj[2][1] = loadTexture("../Assets/Textures/mj21.jpg");
    mj[2][2] = loadTexture("../Assets/Textures/mj22.jpg");
    du[0][0] = loadTexture("../Assets/Textures/du00.jpg");
    du[0][1] = loadTexture("../Assets/Textures/du01.jpg");
    du[0][2] = loadTexture("../Assets/Textures/du02.jpg");
    du[1][0] = loadTexture("../Assets/Textures/du10.jpg");
    du[1][1] = loadTexture("../Assets/Textures/du11.jpg");
    du[1][2] = loadTexture("../Assets/Textures/du12.jpg");
    du[2][0] = loadTexture("../Assets/Textures/du20.jpg");
    du[2][1] = loadTexture("../Assets/Textures/du21.jpg");
    du[2][2] = loadTexture("../Assets/Textures/du22.jpg");
    ed[0][0] = loadTexture("../Assets/Textures/ed00.jpg");
    ed[0][1] = loadTexture("../Assets/Textures/ed01.jpg");
    ed[0][2] = loadTexture("../Assets/Textures/ed02.jpg");
    ed[1][0] = loadTexture("../Assets/Textures/ed10.jpg");
    ed[1][1] = loadTexture("../Assets/Textures/ed11.jpg");
    ed[1][2] = loadTexture("../Assets/Textures/ed12.jpg");
    ed[2][0] = loadTexture("../Assets/Textures/ed20.jpg");
    ed[2][1] = loadTexture("../Assets/Textures/ed21.jpg");
    ed[2][2] = loadTexture("../Assets/Textures/ed22.jpg");
    kp[0][0] = loadTexture("../Assets/Textures/kp00.jpg");
    kp[0][1] = loadTexture("../Assets/Textures/kp01.jpg");
    kp[0][2] = loadTexture("../Assets/Textures/kp02.jpg");
    kp[1][0] = loadTexture("../Assets/Textures/kp10.jpg");
    kp[1][1] = loadTexture("../Assets/Textures/kp11.jpg");
    kp[1][2] = loadTexture("../Assets/Textures/kp12.jpg");
    kp[2][0] = loadTexture("../Assets/Textures/kp20.jpg");
    kp[2][1] = loadTexture("../Assets/Textures/kp21.jpg");
    kp[2][2] = loadTexture("../Assets/Textures/kp22.jpg");
    mar[0][0] = loadTexture("../Assets/Textures/mar00.jpg");
    mar[0][1] = loadTexture("../Assets/Textures/mar01.jpg");
    mar[0][2] = loadTexture("../Assets/Textures/mar02.jpg");
    mar[1][0] = loadTexture("../Assets/Textures/mar10.jpg");
    mar[1][1] = loadTexture("../Assets/Textures/mar11.jpg");
    mar[1][2] = loadTexture("../Assets/Textures/mar12.jpg");
    mar[2][0] = loadTexture("../Assets/Textures/mar20.jpg");
    mar[2][1] = loadTexture("../Assets/Textures/mar21.jpg");
    mar[2][2] = loadTexture("../Assets/Textures/mar22.jpg");

    wolf[0][0] = loadTexture("../Assets/Textures/wolf00.jpg");
    wolf[0][1] = loadTexture("../Assets/Textures/wolf01.jpg");
    wolf[0][2] = loadTexture("../Assets/Textures/wolf02.jpg");
    wolf[1][0] = loadTexture("../Assets/Textures/wolf10.jpg");
    wolf[1][1] = loadTexture("../Assets/Textures/wolf11.jpg");
    wolf[1][2] = loadTexture("../Assets/Textures/wolf12.jpg");
    wolf[2][0] = loadTexture("../Assets/Textures/wolf20.jpg");
    wolf[2][1] = loadTexture("../Assets/Textures/wolf21.jpg");
    wolf[2][2] = loadTexture("../Assets/Textures/wolf22.jpg");
    duck[0][0] = loadTexture("../Assets/Textures/duck00.jpg");
    duck[0][1] = loadTexture("../Assets/Textures/duck01.jpg");
    duck[0][2] = loadTexture("../Assets/Textures/duck02.jpg");
    duck[1][0] = loadTexture("../Assets/Textures/duck10.jpg");
    duck[1][1] = loadTexture("../Assets/Textures/duck11.jpg");
    duck[1][2] = loadTexture("../Assets/Textures/duck12.jpg");
    duck[2][0] = loadTexture("../Assets/Textures/duck20.jpg");
    duck[2][1] = loadTexture("../Assets/Textures/duck21.jpg");
    duck[2][2] = loadTexture("../Assets/Textures/duck22.jpg");
    cow[0][0] = loadTexture("../Assets/Textures/cow00.jpg");
    cow[0][1] = loadTexture("../Assets/Textures/cow01.jpg");
    cow[0][2] = loadTexture("../Assets/Textures/cow02.jpg");
    cow[1][0] = loadTexture("../Assets/Textures/cow10.jpg");
    cow[1][1] = loadTexture("../Assets/Textures/cow11.jpg");
    cow[1][2] = loadTexture("../Assets/Textures/cow12.jpg");
    cow[2][0] = loadTexture("../Assets/Textures/cow20.jpg");
    cow[2][1] = loadTexture("../Assets/Textures/cow21.jpg");
    cow[2][2] = loadTexture("../Assets/Textures/cow22.jpg");
    croco[0][0] = loadTexture("../Assets/Textures/croco00.jpg");
    croco[0][1] = loadTexture("../Assets/Textures/croco01.jpg");
    croco[0][2] = loadTexture("../Assets/Textures/croco02.jpg");
    croco[1][0] = loadTexture("../Assets/Textures/croco10.jpg");
    croco[1][1] = loadTexture("../Assets/Textures/croco11.jpg");
    croco[1][2] = loadTexture("../Assets/Textures/croco12.jpg");
    croco[2][0] = loadTexture("../Assets/Textures/croco20.jpg");
    croco[2][1] = loadTexture("../Assets/Textures/croco21.jpg");
    croco[2][2] = loadTexture("../Assets/Textures/croco22.jpg");
    cat[0][0] = loadTexture("../Assets/Textures/cat00.jpg");
    cat[0][1] = loadTexture("../Assets/Textures/cat01.jpg");
    cat[0][2] = loadTexture("../Assets/Textures/cat02.jpg");
    cat[1][0] = loadTexture("../Assets/Textures/cat10.jpg");
    cat[1][1] = loadTexture("../Assets/Textures/cat11.jpg");
    cat[1][2] = loadTexture("../Assets/Textures/cat12.jpg");
    cat[2][0] = loadTexture("../Assets/Textures/cat20.jpg");
    cat[2][1] = loadTexture("../Assets/Textures/cat21.jpg");
    cat[2][2] = loadTexture("../Assets/Textures/cat22.jpg");
    butter[0][0] = loadTexture("../Assets/Textures/butter00.jpg");
    butter[0][1] = loadTexture("../Assets/Textures/butter01.jpg");
    butter[0][2] = loadTexture("../Assets/Textures/butter02.jpg");
    butter[1][0] = loadTexture("../Assets/Textures/butter10.jpg");
    butter[1][1] = loadTexture("../Assets/Textures/butter11.jpg");
    butter[1][2] = loadTexture("../Assets/Textures/butter12.jpg");
    butter[2][0] = loadTexture("../Assets/Textures/butter20.jpg");
    butter[2][1] = loadTexture("../Assets/Textures/butter21.jpg");
    butter[2][2] = loadTexture("../Assets/Textures/butter22.jpg");



    eu[0][0] = loadTexture("../Assets/Textures/eu00.jpg");
    eu[0][1] = loadTexture("../Assets/Textures/eu01.jpg");
    eu[0][2] = loadTexture("../Assets/Textures/eu02.jpg");
    eu[1][0] = loadTexture("../Assets/Textures/eu10.jpg");
    eu[1][1] = loadTexture("../Assets/Textures/eu11.jpg");
    eu[1][2] = loadTexture("../Assets/Textures/eu12.jpg");
    eu[2][0] = loadTexture("../Assets/Textures/eu20.jpg");
    eu[2][1] = loadTexture("../Assets/Textures/eu21.jpg");
    eu[2][2] = loadTexture("../Assets/Textures/eu22.jpg");


    am[0][0] = loadTexture("../Assets/Textures/am00.jpg");
    am[0][1] = loadTexture("../Assets/Textures/am01.jpg");
    am[0][2] = loadTexture("../Assets/Textures/am02.jpg");
    am[1][0] = loadTexture("../Assets/Textures/am10.jpg");
    am[1][1] = loadTexture("../Assets/Textures/am11.jpg");
    am[1][2] = loadTexture("../Assets/Textures/am12.jpg");
    am[2][0] = loadTexture("../Assets/Textures/am20.jpg");
    am[2][1] = loadTexture("../Assets/Textures/am21.jpg");
    am[2][2] = loadTexture("../Assets/Textures/am22.jpg");

    amm[0][0] = loadTexture("../Assets/Textures/amm00.jpg");
    amm[0][1] = loadTexture("../Assets/Textures/amm01.jpg");
    amm[0][2] = loadTexture("../Assets/Textures/amm02.jpg");
    amm[1][0] = loadTexture("../Assets/Textures/amm10.jpg");
    amm[1][1] = loadTexture("../Assets/Textures/amm11.jpg");
    amm[1][2] = loadTexture("../Assets/Textures/amm12.jpg");
    amm[2][0] = loadTexture("../Assets/Textures/amm20.jpg");
    amm[2][1] = loadTexture("../Assets/Textures/amm21.jpg");
    amm[2][2] = loadTexture("../Assets/Textures/amm22.jpg");


    as[0][0] = loadTexture("../Assets/Textures/as00.jpg");
    as[0][1] = loadTexture("../Assets/Textures/as01.jpg");
    as[0][2] = loadTexture("../Assets/Textures/as02.jpg");
    as[1][0] = loadTexture("../Assets/Textures/as10.jpg");
    as[1][1] = loadTexture("../Assets/Textures/as11.jpg");
    as[1][2] = loadTexture("../Assets/Textures/as12.jpg");
    as[2][0] = loadTexture("../Assets/Textures/as20.jpg");
    as[2][1] = loadTexture("../Assets/Textures/as21.jpg");
    as[2][2] = loadTexture("../Assets/Textures/as22.jpg");



    af[0][0] = loadTexture("../Assets/Textures/af00.jpg");
    af[0][1] = loadTexture("../Assets/Textures/af01.jpg");
    af[0][2] = loadTexture("../Assets/Textures/af02.jpg");
    af[1][0] = loadTexture("../Assets/Textures/af10.jpg");
    af[1][1] = loadTexture("../Assets/Textures/af11.jpg");
    af[1][2] = loadTexture("../Assets/Textures/af12.jpg");
    af[2][0] = loadTexture("../Assets/Textures/af20.jpg");
    af[2][1] = loadTexture("../Assets/Textures/af21.jpg");
    af[2][2] = loadTexture("../Assets/Textures/af22.jpg");

    oc[0][0] = loadTexture("../Assets/Textures/OC 00.jpg");
    oc[0][1] = loadTexture("../Assets/Textures/OC 01.jpg");
    oc[0][2] = loadTexture("../Assets/Textures/OC 02.jpg");
    oc[1][0] = loadTexture("../Assets/Textures/OC 10.jpg");
    oc[1][1] = loadTexture("../Assets/Textures/OC 11.jpg");
    oc[1][2] = loadTexture("../Assets/Textures/OC 12.jpg");
    oc[2][0] = loadTexture("../Assets/Textures/OC 20.jpg");
    oc[2][1] = loadTexture("../Assets/Textures/OC 21.jpg");
    oc[2][2] = loadTexture("../Assets/Textures/OC 22.jpg");

    oca = loadTexture("../Assets/Textures/oca.jpg");
    afa = loadTexture("../Assets/Textures/afa.jpg");
    eua = loadTexture("../Assets/Textures/eua.jpg");
    asa = loadTexture("../Assets/Textures/asa.jpg");
    ama = loadTexture("../Assets/Textures/ama.jpg");
    amma = loadTexture("../Assets/Textures/amma.jpg");


    catt = loadTexture("../Assets/Textures/cat20.jpg");
    wolft = loadTexture("../Assets/Textures/wolf00.jpg");
    duckt = loadTexture("../Assets/Textures/duckt.jpg");
    crocot = loadTexture("../Assets/Textures/croco01.jpg");
    ratt = loadTexture("../Assets/Textures/ratt.jpg");
    cowt = loadTexture("../Assets/Textures/cat20.jpg");



    metalID = loadTexture("../Assets/Textures/metal.jpg");
    brickTextureID1 = loadTexture("../Assets/Textures/cement.jpg");
    tilesTextureId = loadTexture("../Assets/Textures/cub.jpg");




    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    srand(time(NULL));
#if defined(PLATFORM_OSX)
    std::string shaderPathPrefix = "Shaders/";
#else
    std::string shaderPathPrefix = "../Assets/Shaders/";
#endif

    // shadow shader: put the buffer for rendering the z value to the ..
    // scene shader render the color of the scene = this is the normal shader pg used until now

    GLuint shaderScene = loadSHADER(shaderPathPrefix + "scene_vertex.glsl",
        shaderPathPrefix + "scene_fragment.glsl");

    GLuint shaderShadow = loadSHADER(shaderPathPrefix + "shadow_vertex.glsl",
        shaderPathPrefix + "shadow_fragment.glsl");
    // create texture to store the z values, for every pixel , store the z value ,
    // use texture unit to tore it
    // Setup models



    int activeVAO = createVertexArrayObject();

    ashader = shaderScene;


    const unsigned int DEPTH_MAP_TEXTURE_SIZE = 1024;


    GLuint depth_map_texture;

    glGenTextures(1, &depth_map_texture);

    glBindTexture(GL_TEXTURE_2D, depth_map_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, DEPTH_MAP_TEXTURE_SIZE,
        DEPTH_MAP_TEXTURE_SIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


    GLuint depth_map_fbo;

    glGenFramebuffers(1, &depth_map_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
        depth_map_texture, 0);
    glDrawBuffer(GL_NONE);

    glfwSetKeyCallback(window, key_callback);
    // Camera parameters for view transform

    cameraPosition = vec3(0.0f, 0.0f, 2.0f);
    cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
    cameraUp = vec3(0.0f, 1.0f, 0.0f);
    dy = 0;
    cameraHorizontalAngle = -90;
    newcameraPosition = 0;
    cameraVerticalAngle = 0;


    // Other camera parameters
    float cameraSpeed = 1.0f;
    float cameraFastSpeed = 3 * cameraSpeed;

    // For spinning model
    float spinningAngle = 0.0f;

    // For frame time
   //loat lastFrameTime = glfwGetTime();
    int lastMouseLeftState = GLFW_RELEASE;
    double lastMousePosX, lastMousePosY;
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    // Set projection matrix for shader, this won't change
    projectionMatrix =
        glm::perspective(70.0f,                  // field of view in degrees
            WIDTH * 1.0f / HEIGHT,  // aspect ratio
            0.01f, 800.0f);         // near and far (near > 0)

// Set initial view matrix on both shaders
    mat4 viewMatrix = lookAt(cameraPosition,                 // eye
        cameraPosition + cameraLookAt,  // center
        cameraUp);                      // up

// Set projection matrix on both shaders
    SetUniformMat4(shaderScene, "projection_matrix", projectionMatrix);

    // Set view matrix on both shaders
    SetUniformMat4(shaderScene, "view_matrix", viewMatrix);

    float lightAngleOuter = radians(50.0f);
    float lightAngleInner = radians(40.0f);


    // Set light cutoff angles on scene shader
    SetUniform1Value(shaderScene, "light_cutoff_inner", cos(lightAngleInner));// light spot
    SetUniform1Value(shaderScene, "light_cutoff_outer", cos(lightAngleOuter));

    // Set light color on scene shader
    SetUniformVec3(shaderScene, "light_color", vec3(1));

    // Set object color on scene shader
    SetUniformVec3(shaderScene, "object_color", vec3(1));

    // For frame time
    float
        lastFrameTime = glfwGetTime();
    //t lastMouseLeftState = GLFW_RELEASE;
   //ouble lastMousePosX, lastMousePosY;
   //lfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);


       //Setup models
#if defined(PLATFORM_OSX)ti
    string cubePath = "Models/cube.obj";
    string heraclesPath = "Models/heracles.obj";
#else
    string cubePath = "../Assets/Models/rat.obj";
    string cowPath = "../Assets/Models/cow.obj";
    string wolfPath = "../Assets/Models/wolf.obj";
    string duckPath = "../Assets/Models/duck.obj";
    string catPath = "../Assets/Models/cat.obj";
    string crocoPath = "../Assets/Models/croco.obj";
#endif


    int cubeVertices;
    GLuint cubeVAO = setupModelEBO(cubePath, cubeVertices);

    int cubeVertices2;
    GLuint cowVAO = setupModelEBO(cowPath, cubeVertices2);

    int cubeVertices3;
    GLuint wolfVAO = setupModelEBO(wolfPath, cubeVertices3);

    int cubeVertices4;
    GLuint duckVAO = setupModelEBO(duckPath, cubeVertices4);

    int cubeVertices5;
    GLuint catVAO = setupModelEBO(catPath, cubeVertices5);

    int cubeVertices6;
    GLuint crocoVAO = setupModelEBO(crocoPath, cubeVertices6);





    // Other OpenGL states to set once
    // Enable Backface culling
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Entering Main Loop
    // get the light position, compute z from light position to the objects of the scene
    cub = cubes();


    while (!glfwWindowShouldClose(window)) {
        if (resume) {
            read();
            resume = false;

        }



        if (clear) {
            std::ofstream ofs;
            ofs.open("../Assets/textes/axe.txt", std::ofstream::out | std::ofstream::trunc);
            ofs.close();

            ofs.open("../Assets/textes/ind.txt", std::ofstream::out | std::ofstream::trunc);
            ofs.close();
            clear = false;
        }
        if (onmenu || ontheme) {
            focus = vec3(0, 0, 4);

            cameraPosition = vec3(0.0f, 0.0f, 2.0f);
            cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
            cameraUp = vec3(0.0f, 1.0f, 0.0f);
            dy = 0;
            cameraHorizontalAngle = -90;
            newcameraPosition = 0;
            cameraVerticalAngle = 0;
        }
        else {
            focus = vec3(0, 0, -4);
        }

        if (testsounded) {
            PlaySound("ed.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsounded = false;
        }
        if (testsoundmj) {
            PlaySound("mj.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundmj = false;
        }
        if (testsounddu) {
            PlaySound("du.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsounddu = false;
        }
        if (testsoundbl) {
            PlaySound("bl.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundbl = false;
        }
        if (testsoundkp) {
            PlaySound("kp.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundkp = false;
        }
        if (testsoundmar) {
            PlaySound("mar.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundmar = false;
        }
        if (testsoundcat) {
            PlaySound("cat.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundcat = false;
        }
        if (testsoundbutter) {
            PlaySound("butter.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundbutter = false;
        }
        if (testsoundwolf) {
            PlaySound("wolf.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundwolf = false;
        }
        if (testsoundcroco) {
            PlaySound("croco.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundcroco = false;
        }
        if (testsoundcow) {
            PlaySound("cow.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundcow = false;
        }
        if (testsoundduck) {
            PlaySound("duck.wav", NULL, SND_ASYNC | SND_FILENAME);
            testsoundduck = false;
        }


        newtime = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = newtime - oldtime;


        if (timeron) timer = timer - elapsed_seconds.count();
        // cout <<"elapsed time: " << div(round(timer),3).quot << "s\n";
        oldtime = newtime;
        GLint  booloc = glGetUniformLocation(shaderScene, "testtext");


        glUniform1i(booloc, testure);

        SetUniformVec3(shaderScene, "light_color", lightc);
        booloc = glGetUniformLocation(shaderScene, "shadow_or_not");


        glUniform1i(booloc, shadure);
        // Set the view matrix for first person camera and send to both shaders
     //  mat4 viewMatrix = lookAt(cameraPosition, cameraPosition + cameraLookAt, cameraUp);
    //    SetUniformMat4(shaderScene, "view_matrix", viewMatrix);// normal matrice


        // Set view position on scene shader
        SetUniformVec3(shaderScene, "view_position", cameraPosition);

        testshader = true;
        // Frame time calculation
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        //float dt = glfwGetTime() - lastFrameTime;
        //lastFrameTime = glfwGetTime();

          // light parameters
        if (onmenu || ontheme) { lightpos = vec3(0, 10, -10); }
        if (!onmenu && !ontheme) lightpos = vec3(0, 10, 10);
        vec3 lightPosition = lightpos; // the location of the light in 3D space: fixed position


        vec3 lightFocus = focus;  // the point in 3D space the light "looks" at
        vec3 lightDirection = normalize(lightFocus - lightPosition);

        float lightNearPlane = 0.5f;
        float lightFarPlane = 20.0f;

        mat4 lightProjMatrix = //frustum(-1.0f, 1.0f, -1.0f, 1.0f, lightNearPlane, lightFarPlane);
            perspective(angpers, (float)DEPTH_MAP_TEXTURE_SIZE / (float)DEPTH_MAP_TEXTURE_SIZE, lightNearPlane, lightFarPlane);
        mat4 lightViewMatrix = lookAt(lightPosition, lightFocus, vec3(0, 0, 1));

        SetUniformMat4(shaderScene, "light_proj_view_matrix", lightProjMatrix * lightViewMatrix);
        SetUniform1Value(shaderScene, "light_near_plane", lightNearPlane);
        SetUniform1Value(shaderScene, "light_far_plane", lightFarPlane);
        SetUniformVec3(shaderScene, "light_position", lightPosition);
        SetUniformVec3(shaderScene, "light_direction", lightDirection);


        mat4   modelMatrix = mat4(1);
        SetUniformMat4(shaderScene, "model_matrix", modelMatrix);

        // glActiveTexture(GL_TEXTURE5);// numbered fron 0 -31 // sometimes more available
            // have to enable the texture
      //   GLuint textureLocation = glGetUniformLocation(shaderScene, "textureSampler");// texture location is the location of out texture Sampler
      // type sampler2D





      // bind => tell him that we want to use for the next

         // bind to the buffer and pass the id to the texture location


        glEnable(GL_DEPTH_TEST);

        {
            // Use proper shader
            glUseProgram(shaderShadow);
            // Use proper image output size
            //put the viewport

            glViewport(0, 0, DEPTH_MAP_TEXTURE_SIZE, DEPTH_MAP_TEXTURE_SIZE);
            // Bind depth map texture as output framebuffer for the depth maps
            glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
            // Clear depth data on the framebuffer, since we only render steps values
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Bind geometry




    //Setup models


            // POUR DESSINER ; rat ////////
           // int activeVAOVertices = 2 * cubeVertices;
           // GLuint activeVAO2 = cubeVAO;
           //draw GLuint activeVAO2 = cubeVAO;
            //Draw the stored vertex objects

            //glBindVertexArray(activeVAO2);
/*
            //TODO3 Draw model as elements, instead of as arrays
            mat4 carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.05));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(ratt);
            glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

            //glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            // cow/////////////////////////
             activeVAOVertices = 2 * cubeVertices2;
             activeVAO2 = cowVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
             carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(cowt);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);



            // wolf/////////////////////////////////

             activeVAOVertices = 2 * cubeVertices3;
             activeVAO2 = wolfVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
             carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(wolft);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            //duck//////////////////////////////
             activeVAOVertices = 2 * cubeVertices4;
             activeVAO2 = duckVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
             carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(duckt);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            //cat//////////////////////////////////
             activeVAOVertices = 2 * cubeVertices5;
             activeVAO2 = catVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
             carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(catt);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            //croco////////////
             activeVAOVertices = 2 * cubeVertices6;
             activeVAO2 = crocoVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
             carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(crocot);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            */
            glBindVertexArray(activeVAO);
            // Draw geometry
            // all the objects we want shadows on it !

            if (onmenu) {
                inmenu(shaderScene, shaderShadow);


            }
            else if (ontheme) {
                intheme(shaderScene, shaderShadow);


            }
            else
            
                incube(shaderScene, shaderShadow);

                cub.dessins(shaderScene, shaderShadow);
            



            if (solving) {
                solve();
            }

            if (shuffling) {
                if (cnnt == 0)
                    if ((cnnt == 0)) {
                        shuff++;
                        axes = rand() % 18;

                        pause = 0;
                        resetrest();
                        if (axes == 0) xaxe[0] = true;
                        if (axes == 1) xaxe[1] = true;
                        if (axes == 2) xaxe[2] = true;
                        if (axes == 3) xaxe[3] = true;
                        if (axes == 4) xaxe[4] = true;
                        if (axes == 5) xaxe[5] = true;

                        if (axes == 6) yaxe[0] = true;
                        if (axes == 7) yaxe[1] = true;
                        if (axes == 8) yaxe[2] = true;
                        if (axes == 9) yaxe[3] = true;
                        if (axes == 10) yaxe[4] = true;
                        if (axes == 11) yaxe[5] = true;

                        if (axes == 12) zaxe[0] = true;
                        if (axes == 13) zaxe[1] = true;
                        if (axes == 14) zaxe[2] = true;
                        if (axes == 15) zaxe[3] = true;
                        if (axes == 16) zaxe[4] = true;
                        if (axes == 17) zaxe[5] = true;


                        if (shuff == 15) { shuff = 0; shuffling = false; }
                    }
            }

            if (xaxe[0]) {
                cub.animturnx(-1, 1);   if (!solving) {
                    axemov[nbrmov] = 0; indexmov[nbrmov] = -1; dirmov[nbrmov] = 1;
                }
            }
            if (xaxe[1]) {
                cub.animturnx(0, 1);  if (!solving) {
                    axemov[nbrmov] = 0; indexmov[nbrmov] = 0; dirmov[nbrmov] = 1;

                }
            }

            if (xaxe[2]) {
                cub.animturnx(1, 1);   if (!solving) {
                    axemov[nbrmov] = 0; indexmov[nbrmov] = 1; dirmov[nbrmov] = 1;
                }
            }
            if (xaxe[3]) {
                cub.animturnx(-1, -1); if (!solving) {
                    axemov[nbrmov] = 0; indexmov[nbrmov] = -1; dirmov[nbrmov] = -1;
                }
            }
            if (xaxe[4]) {
                cub.animturnx(0, -1);  if (!solving) {
                    axemov[nbrmov] = 0; indexmov[nbrmov] = 0; dirmov[nbrmov] = -1;
                }
            }

            if (xaxe[5]) {
                cub.animturnx(1, -1);   if (!solving) {
                    axemov[nbrmov] = 0; indexmov[nbrmov] = 1; dirmov[nbrmov] = -1;
                }
            }

            if (yaxe[0]) {
                cub.animturny(-1, 1);   if (!solving) {
                    axemov[nbrmov] = 1; indexmov[nbrmov] = -1; dirmov[nbrmov] = 1;
                }
            }
            if (yaxe[1]) {
                cub.animturny(0, 1);   if (!solving) {
                    axemov[nbrmov] = 1; indexmov[nbrmov] = 0; dirmov[nbrmov] = 1;
                }
            }
            if (yaxe[2]) {
                cub.animturny(1, 1);   if (!solving) {
                    axemov[nbrmov] = 1; indexmov[nbrmov] = 1; dirmov[nbrmov] = 1;
                }
            }
            if (yaxe[3]) {
                cub.animturny(-1, -1); if (!solving) {
                    axemov[nbrmov] = 1; indexmov[nbrmov] = -1; dirmov[nbrmov] = -1;
                }
            }
            if (yaxe[4]) {
                cub.animturny(0, -1);  if (!solving) {
                    axemov[nbrmov] = 1; indexmov[nbrmov] = 0; dirmov[nbrmov] = -1;
                }
            }
            if (yaxe[5]) {
                cub.animturny(1, -1); if (!solving) {
                    axemov[nbrmov] = 1; indexmov[nbrmov] = 1; dirmov[nbrmov] = -1;
                }
            }

            if (zaxe[0]) {
                cub.animturnz(-1, 1);  if (!solving) {
                    axemov[nbrmov] = 2; indexmov[nbrmov] = -1; dirmov[nbrmov] = 1;
                }
            }
            if (zaxe[1]) {
                cub.animturnz(0, 1);   if (!solving) {
                    axemov[nbrmov] = 2; indexmov[nbrmov] = 0; dirmov[nbrmov] = 1;
                }
            }
            if (zaxe[2]) {
                cub.animturnz(1, 1);  if (!solving) {
                    axemov[nbrmov] = 2; indexmov[nbrmov] = 1; dirmov[nbrmov] = 1;
                }
            }
            if (zaxe[3]) {
                cub.animturnz(-1, -1); if (!solving) {
                    axemov[nbrmov] = 2; indexmov[nbrmov] = -1; dirmov[nbrmov] = -1;
                }
            }
            if (zaxe[4]) {
                cub.animturnz(0, -1);  if (!solving) {
                    axemov[nbrmov] = 2; indexmov[nbrmov] = 0; dirmov[nbrmov] = -1;
                }
            }
            if (zaxe[5]) {
                cub.animturnz(1, -1);  if (!solving) {
                    axemov[nbrmov] = 2; indexmov[nbrmov] = 1; dirmov[nbrmov] = -1;
                }
            }



            // Unbind geometry
            glBindVertexArray(0);
        }
        testshader = false;
        // pass 2
        {
            // Use proper shader
            glUseProgram(shaderScene);

            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);
            // Bind screen as output framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            // Clear color and depth data on framebuffer
            glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            // Bind depth map texture: not needed, by default it is active
            glActiveTexture(GL_TEXTURE0);

            // activate any texture unit you use or your object or models







    //Setup models


            // POUR DESSINER ; rat ////////
            int activeVAOVertices = 2 * cubeVertices;
            GLuint activeVAO2 = cubeVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
            mat4 carre1 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f, 0.5, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.005))
                * glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(0.0f, 0.0f, 1.0f));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(ratt);
            if (animals) {
                if (txx == 1)
                    glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);
            }

            //glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            // cow/////////////////////////
            activeVAOVertices = 2 * cubeVertices2;
            activeVAO2 = cowVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
            carre1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.6f, 0.4, 0.0)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.0005))
                * glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(0.0f, 0.0f, 1.0f));;

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(cowt);
            if (animals) {
                if (txx == 1)
                    glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);
            }

            // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);



            // wolf/////////////////////////////////

            activeVAOVertices = 2 * cubeVertices3;
            activeVAO2 = wolfVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
            carre1 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.7f, 0.65, 0.0))
                * glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(0.0005));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(wolft);
            if (animals && txx == 1)
                glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

            // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            //duck//////////////////////////////
            activeVAOVertices = 2 * cubeVertices4;
            activeVAO2 = duckVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
            carre1 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.4f, -0.45, 1.0)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(worldy), glm::vec3(0.0f, 1.0f, 0.0f)) *
                glm::rotate(glm::mat4(1.0f), glm::radians(worldx), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.7));;

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(duckt);
            if (animals && (txx == 1))
                glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

            // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            //cat//////////////////////////////////
            activeVAOVertices = 2 * cubeVertices5;
            activeVAO2 = catVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
            carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(catt);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);


            //croco////////////
            activeVAOVertices = 2 * cubeVertices6;
            activeVAO2 = crocoVAO;
            //Draw the stored vertex objects

            glBindVertexArray(activeVAO2);

            //TODO3 Draw model as elements, instead of as arrays
            carre1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5));

            SetUniformMat4(shaderScene, "model_matrix", carre1);
            texture(crocot);
            // glDrawElements(GL_TRIANGLES, activeVAOVertices, GL_UNSIGNED_INT, 0);

             // glDrawArrays(GL_TRIANGLES, 0, activeVAOVertices);
            glBindVertexArray(0);



            // Bind geometry
            glBindVertexArray(activeVAO);
            // Draw geometry
            //glDrawElements(GL_TRIANGLES, activeVertices, GL_UNSIGNED_INT, 0);
           //SetUniformMat4(shaderShadow, "transform_in_light_space", lightProjMatrix* lightViewMatrix);


            secs = round(timer);
            tenmin = div(secs, 600).quot;
            mins = div(secs, 60).quot % 10;
            tensec = div(secs % 60, 10).quot;
            secondes = secs % 10;






            if (onmenu) {
                inmenu(shaderScene, shaderShadow);


            }
            else if (ontheme) {
                intheme(shaderScene, shaderShadow);


            }
            else
            
                incube(shaderScene, shaderShadow);
                cub.dessins(shaderScene, shaderShadow);
            

            // Unbind geometry
            glBindVertexArray(0);
        }



        glfwSwapBuffers(window);
        glfwPollEvents();



        double mousePosX, mousePosY;
        // get the position of the cursor
        glfwGetCursorPos(window, &mousePosX, &mousePosY);
        // cout << lightpos.x << "   " << lightpos.y << "    " << lightpos.z << "   \n";
        // cout << mousePosX << "              " << mousePosY << "\n";
        dx = mousePosX - lastMousePosX;
        dy = mousePosY - lastMousePosY;

        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;

        // Convert to spherical coordinates
        const float cameraAngularSpeed = 60.0f;
        if (TEST_A) {
            worldy = (worldy - 45);
            TEST_A = false;
        }
        if (worldy > 180) worldy = -180;
        if (worldy < -180) worldy = 180;
        if (worldx > 180) worldx = -180;
        if (worldx < -180) worldx = 180;

        //move camera on x axis
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            // cout << worldx << "            \n\n";
            if ((!onmenu) && (!ontheme)) {
                if ((worldx < 90) && (worldx > -90)) {

                    worldy = worldy + dx;
                }
                else {
                    worldy = worldy - dx;

                }

                worldx = worldx + dy;
            }
        }
        // move camera on y axis : 2 possibilities :

        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
            PlaySound("essai.wav", NULL, SND_ASYNC | SND_FILENAME);
        }

        if (ontheme) {
            if ((mousePosX < 288) && (mousePosX > 30) && (mousePosY > 500) && mousePosY < 838) {
                mag3 = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                    ontheme = false;
                    txx = 3;
                    cub.settext();
                    cameraPosition = vec3(0.0f, 0.0f, 2.0f);
                    cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
                    cameraUp = vec3(0.0f, 1.0f, 0.0f);
                    dy = 0;
                    cameraHorizontalAngle = 90;
                    newcameraPosition = 0;
                    cameraVerticalAngle = 0;

                }

            }
            else {
                mag3 = false;
            }
            if ((mousePosX < 670) && (mousePosX > 380) && (mousePosY > 500) && mousePosY < 838) {
                mag1 = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                    ontheme = false;
                    txx = 1;
                    cub.settext();
                    cameraPosition = vec3(0.0f, 0.0f, 2.0f);
                    cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
                    cameraUp = vec3(0.0f, 1.0f, 0.0f);
                    dy = 0;
                    cameraHorizontalAngle = 90;
                    newcameraPosition = 0;
                    cameraVerticalAngle = 0;
                }
            }
            else {
                mag1 = false;
            }
            //cout << mousePosX << "      " << mousePosY << "\n";
            if ((mousePosX < 670) && (mousePosX > 380) && (mousePosY > 270) && mousePosY < 470) {
                mag2 = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                    ontheme = false;
                    txx = 2;
                    cub.settext();
                    cameraPosition = vec3(0.0f, 0.0f, 2.0f);
                    cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
                    cameraUp = vec3(0.0f, 1.0f, 0.0f);
                    dy = 0;
                    cameraHorizontalAngle = 90;
                    newcameraPosition = 0;
                    cameraVerticalAngle = 0;
                }
            }
            else {
                mag2 = false;
            }


            if ((mousePosX < 974) && (mousePosX > 730) && (mousePosY > 500) && mousePosY < 838) {
                mag0 = true;
                if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                    ontheme = false;
                    txx = 0;
                    cub.settext();
                    cameraPosition = vec3(0.0f, 0.0f, 2.0f);
                    cameraLookAt = vec3(0.0f, 0.0f, 0.0f);
                    cameraUp = vec3(0.0f, 1.0f, 0.0f);
                    dy = 0;
                    cameraHorizontalAngle = 90;
                    newcameraPosition = 0;
                    cameraVerticalAngle = 0;

                }
            }
            else {
                mag0 = false;
            }



        }
        else if (onmenu) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX < 968) && (mousePosX > 578) && (mousePosY > 817) && mousePosY < 879) {
                    onmenu = false;
                    ontheme = true;
                    newgame = true;
                    clear = true;

                }
                if ((mousePosX < 968) && (mousePosX > 587) && (mousePosY > 909) && mousePosY < 965) {
                    onmenu = false;
                    ontheme = true;
                    resume = true;
                }
            }
        }
        if (cameraHorizontalAngle > 360)
        {
            cameraHorizontalAngle -= 360;
        }
        else if (cameraHorizontalAngle < -360)
        {
            cameraHorizontalAngle += 360;
        }
        if (!onmenu && !ontheme) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX < 317) && (mousePosX > 116) && (mousePosY > 546) && mousePosY < 624) {
                    cub = cubes();
                    timeron = true;
                    timer = 0;
                    animals = false;

                }
            }


            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX < 317) && (mousePosX > 116) && (mousePosY > 654) && mousePosY < 712) {
                    timeron = false;
                }
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX < 317) && (mousePosX > 116) && (mousePosY > 738) && mousePosY < 795) {
                    timeron = true;
                }
            }



            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX < 317) && (mousePosX > 116) && (mousePosY > 814) && mousePosY < 900) {
                    timeron = true;
                    timer = 0;
                }
            }




            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX < 562) && (mousePosX > 380) && (mousePosY > 828) && mousePosY < 883) {
                    shuffling = true;
                }
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX > 605) && (mousePosX < 795) && (mousePosY > 828) && mousePosY < 880) {
                    solving = true;
                }
            }
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                if ((mousePosX > 829) && (mousePosX < 1016) && (mousePosY > 828) && mousePosY < 880) {

                    cub = cubes();
                    onmenu = true;
                    animals = false;
                }
            }
        }




        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if ((mousePosX < 96) && (mousePosX > 46) && (mousePosY > 197) && mousePosY < 260) {
                if (txx == 0) testsounded = true;
                if (txx == 1) testsoundcat = true;
                if (txx == 2) lightc = vec3(1, 1, 1);
                // ed or cat

            }
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if ((mousePosX < 217) && (mousePosX > 137) && (mousePosY > 197) && mousePosY < 260) {
                // rhaina or crocoa
                if (txx == 0) testsoundbl = true;
                if (txx == 1) testsoundcroco = true;
                if (txx == 2) lightc = vec3(0, 0.6, 0);
            }
        }


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if ((mousePosX < 317) && (mousePosX > 236) && (mousePosY > 197) && mousePosY < 260) {
                //cow or maroon5
                if (txx == 0) testsoundmar = true;
                if (txx == 1) testsoundcow = true;
                if (txx == 2) lightc = vec3(0.6, 0.6, 0.2);
            }
        }


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if ((mousePosX < 96) && (mousePosX > 46) && (mousePosY > 280) && mousePosY < 360) {
                // wolfor dualipa
                if (txx == 0) testsounddu = true;
                if (txx == 1) testsoundwolf = true;
                if (txx == 2) lightc = vec3(0.6, 0.1, 0.1);
            }
        }

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if ((mousePosX < 217) && (mousePosX > 137) && (mousePosY > 280) && mousePosY < 360) {
                //mj or duck
                if (txx == 0) testsoundmj = true;
                if (txx == 1) testsoundduck = true;
                if (txx == 2) lightc = vec3(0.1, 0.1, 0.6);
            }
        }


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            if ((mousePosX < 317) && (mousePosX > 236) && (mousePosY > 280) && mousePosY < 360) {
                //katy perry or rat
                if (txx == 0) testsoundkp = true;
                if (txx == 1) testsoundbutter = true;
                if (txx == 2) lightc = vec3(0.1, 0.3, 0.3);
            }
        }








        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        {
            cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
        }
        // move camera on y axis : 2 possibilities :


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        {
            cameraVerticalAngle -= dy * cameraAngularSpeed * dt;
        }
        float theta = radians(cameraHorizontalAngle);
        float phi = radians(cameraVerticalAngle);

        cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        vec3 cameraSideVector = glm::cross(cameraLookAt, vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector);
        vec3 camup = cameraSideVector;

        // zoom where the camera is looking
       /* if ((!ontheme) && (!onmenu)) {
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) // move camera up
            {
                //if ((!onmenu)&&(!ontheme))
                {
                    cameraPosition.z += (-vec3(0,0,2)+vec3(0.25,0,1)).z * dy * 5 * dt;
                    cameraPosition.y += (-vec3(0, 0, 2)+  vec3(0.25, 0, 1)).y * dy * 5 * dt;
                    cameraPosition.x += (-vec3(0, 0, 2) + vec3(0.25, 0, 1)).x * dy * 5 * dt;
                }
            }
        }*/
        //updating the camera
        cameraLookAt = cameraPosition + cameraLookAt;
        viewMatrix = lookAt(cameraPosition, cameraLookAt, cameraUp);
        SetUniformMat4(shaderScene, "view_matrix", viewMatrix);

        // setProjectionMatrix(colorShaderProgram, projectionMatrix);
         //setProjectionMatrix(texturedShaderProgram, projectionMatrix);




    }

    glfwTerminate();

    return 0;
}

vec3 computeCameraLookAt(double& lastMousePosX, double& lastMousePosY, float dt) {
    // - Calculate mouse motion dx and dy
  // - Update camera horizontal and vertical angle
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    double dx = mousePosX - lastMousePosX;
    double dy = mousePosY - lastMousePosY;

    lastMousePosX = mousePosX;
    lastMousePosY = mousePosY;

    // Convert to spherical coordinates
    const float cameraAngularSpeed = 60.0f;
    static float cameraHorizontalAngle = 90.0f;
    static float cameraVerticalAngle = 0.0f;
    cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
    cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

    //
    cameraVerticalAngle = max(-85.0f, min(85.0f, cameraVerticalAngle));

    float theta = radians(cameraHorizontalAngle);
    float phi = radians(cameraVerticalAngle);

    return vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
}


bool InitContext() {
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    // On windows, we set OpenGL version to 2.1, to support more hardware
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

    // Create Window and rendering context using GLFW, resolution is 800x600
    window = glfwCreateWindow(WIDTH, HEIGHT, "Comp371 - Lab 08", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true;  // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return false;
    }

    return true;
}
