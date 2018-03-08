// Include C++ headers
#include <iostream>
#include <string>
#include <map>

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Shader loading utilities and other
#include <common/shader.h>
#include <common/util.h>
#include <common/camera.h>
#include <common/ModelLoader.h>
#include <common/skeleton.h>
#include <common/texture.h>
#include <common/stb_image.h>
#include "Sphere.h"
#include "Box.h"
#include "Collision.h"

#define FRONT "negz.jpg"
#define BACK1 "posz.jpg"
#define TOP "posy.jpg"
#define BOTTOM "negy.jpg"
#define LEFT "negx.jpg"
#define RIGHT "posx.jpg"
#define gr 9.80665f

using namespace std;
using namespace glm;

// Function prototypes
void initialize();
void createContext2();
void createContext();
void cutContext();

void mainLoop();
void free();
void pollKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
struct Light; struct Material; 

class Bounding
{
public:

	glm::vec3 max;
	glm::vec3 min;
	glm::vec3 size;
	glm::vec3 center;
	Bounding();
	~Bounding();

};
Bounding::Bounding(){
}
Bounding::~Bounding() {
}

void uploadMaterial(const Material& mtl);
void uploadLight(const Light& light);
map<int, mat4> calculateModelPoseFromCoordinates(map<int, float> q);
vector<mat4> calculateSkinningTransformations(map<int, float> q);
vector<float> calculateSkinningIndices();
GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
vec3 move_forward, direction;
vec3 model_normal(0, 0, -1);
float move_back = 0.0f;
float move_left = 0.0f;
float move_right = 0.0f;
float rotate_left = 0;
float sum = 90.0f;
bool last_pos = false;
bool step1 = false;
bool step_run = false;

float deltaTime;
bool collision = false;
bool aristera = false;
bool deksia = false;
bool stathero_pedio = false;
bool fortwse_pedio = false;
bool ENDIAMESA = false;
bool unbind = false;
float first_pos_sphere;
float planeY = 0.0f;
float planeAngle = 0.0f;
float detachmentCoeff = 0.001f;
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float FoV = 45.0f;
float speed_of_move = 0.5f;
float speed_of_run = 1.0f;
float mouseSpeed = 0.001f;
float fovSpeed = 2.0f;
vec3 position = glm::vec3(3, 0.11, 2.5);
vec3 god_mode = glm::vec3(0, 0.11, 2.5);
vec3 last_position_camera;
GLuint shaderProgram1, cubeProgram;
GLuint CUTshaderProgram;
GLuint projectionMatrixLocation, viewMatrixLocation, modelMatrixLocation;
GLuint cube_V_location, cube_P_location, cube_M_location;
GLuint lightLocation, lightLocation1;
GLuint diffuceColorSampler, specularColorSampler, tex_cube, sand, dummy, eye_colour, heart_colour;
GLuint diffuseTexture, specularTexture, diffuseTexture2, diffuseTexture3;
GLuint objVAO, triangleVAO;
GLuint objVerticiesVBO, objUVVBO, objNormalsVBO;
GLuint objVAO2, triangleVAO2;
GLuint objVerticiesVBO2, objUVVBO2, objNormalsVBO2;
GLuint eyeVAO;
GLuint eyeVerticiesVBO, eyeUVVBO, eyeNormalsVBO;
GLuint heartVAO;
GLuint heartVerticiesVBO, heartUVVBO, heartNormalsVBO;

GLuint triangleVerticesVBO, triangleNormalsVBO;
GLuint planeVAO, planeVerticiesVBO;
GLuint VLocation, PLocation, MLocation;
GLuint planeLocation, detachmentCoeffLocation;
GLuint ylocation;
std::vector<vec3> objVertices, objNormals;
std::vector<vec2> objUVs;
std::vector<vec3> objVertices2, objNormals2;
std::vector<vec2> objUVs2;
std::vector<vec3> eyeVertices, eyeNormals;
std::vector<vec2> eyeUVs;
std::vector<vec3> heartVertices, heartNormals;
std::vector<vec2> heartUVs;

GLuint cubevao;	GLuint cubevbo;
GLuint cube_map_texture;
vec3 size_1, center_1, center_agalma, size_agalma;
vec3 size_2, center_2;
vec3 size_model, center_model;
vec3 min_spiti, max_spiti;
std::vector<std::vector<float>> boundings;
std::vector<vec3> modelVertices, modelNormals;
std::vector<vec2> modelUVs;
std::vector<vec3> b_tree;
GLuint modelVAO, modelVerticiesVBO;
Bounding* agalma_b = new Bounding();
#define RENDER_TRIANGLE 0

bool load_cube_map_side(GLuint texture, GLenum side_target, const char* file_name);
void create_bounding_box(std::vector<vec3> objVertices2, glm::vec3& min, glm::vec3& max);
void newVertices(std::vector<vec3> objVertices2, glm::vec3 center_1, std::vector<vector<vec3>>& all_in);
void lazerbeem();

bool checkForCollision(glm::vec3& pos, const float& r,
	const float& size, glm::vec3& n);

#define W_WIDTH 1024
#define W_HEIGHT 768
#define TITLE "Lab 06"

// global variables
GLFWwindow* window;
Camera* camera;
GLuint shaderProgram;
// light properties
GLuint LaLocation, LdLocation, LsLocation, lightPositionLocation, lightPowerLocation;
// material properties
GLuint KdLocation, KsLocation, KaLocation, NsLocation;

GLuint surfaceVAO, surfaceVerticesVBO, surfacesBoneIndecesVBO, maleBoneIndicesVBO;
Drawable *segment, *skeletonSkin;
GLuint useSkinningLocation, boneTransformationsLocation, scaleLocation;
Skeleton* skeleton;
Sphere* sphere;
Box* box;



struct Light {
	glm::vec4 La;
	glm::vec4 Ld;
	glm::vec4 Ls;
	glm::vec3 lightPosition_worldspace;
	float power;
};

struct Material {
	glm::vec4 Ka;
	glm::vec4 Kd;
	glm::vec4 Ks;
	float Ns;
};

const Material boneMaterial{
	vec4{ 0.1, 0.1, 0.1, 1 },
	vec4{ 1.0, 1.0, 1.0, 1 },
	vec4{ 0.3, 0.3, 0.3, 1 },
	0.1f
};

Light light{
	vec4{ 1, 1, 1, 1 },
	vec4{ 1, 1, 1, 1 },
	vec4{ 1, 1, 1, 1 },
	vec3{ 0, 4, 4 },
	20.0f
};

// Coordinate names for mnemonic indexing
enum CoordinateName {
	PELVIS_SCALE, PELVIS_X, PELVIS_Y, PELVIS_Z,
	PELVIS_TRA_X, PELVIS_TRA_Y, PELVIS_TRA_Z, PELVIS_ROT_X, PELVIS_ROT_Y,
	PELVIS_ROT_Z, HIP_R_FLEX, HIP_R_ADD, HIP_R_ROT, KNEE_R_FLEX, ANKLE_R_FLEX,
	//LEFT FOOT
	HIP_L_FLEX, HIP_L_ADD, HIP_L_ROT, KNEE_L_FLEX, ANKLE_L_FLEX,
	//right arm
	SHOULDER_R_X, SHOULDER_R_Y, SHOULDER_R_Z, ELBOW_R_Z, ELBOW_R_Y, ULNA_R_Y,
	CARPALS_R_Y,
	//left arm
	SHOULDER_L_X, SHOULDER_L_Y, SHOULDER_L_Z, ELBOW_L_Z, ELBOW_L_Y, ULNA_L_Y,
	CARPALS_L_Y,
	LUMBAR_FLEX, LUMBAR_BEND, LUMBAR_ROT, DOFS

};
// Joint names for mnemonic indexing
enum JointName {
	BASE = 0, HIP_R, KNEE_R, ANKLE_R, SUBTALAR_R, MTP_R, BACK,
	//left foot
	HIP_L, KNEE_L, ANKLE_L, SUBTALAR_L, MTP_L,
	//right hand 
	SHOULDER_R, ELBOW_R, SHOULDER_L, ELBOW_L, CARPALS_R, CARPALS_L,
	JOINTS
};
// Body names for mnemonic indexing
enum BodyName {
	PELVIS = 0, FEMUR_R, TIBIA_R, TALUS_R, CALCN_R, TOES_R, TORSO,
	//left foot
	FEMUR_L, TIBIA_L, TALUS_L, CALCN_L, TOES_L,
	//right hand
	HUMERUS_R, RADIUS_R, HAND_R, ULNA_R,
	//left hand
	HUMERUS_L, RADIUS_L, HAND_L, ULNA_L,
	BODIES
};

// default pose used for binding the skeleton and the mesh
static const map<int, float> bindingPose = {

	{ CoordinateName::PELVIS_TRA_X,  0.0 },
{ CoordinateName::PELVIS_TRA_Y, 0.0 },
{ CoordinateName::PELVIS_TRA_Z, 0 },
//pelvis rot
{ CoordinateName::PELVIS_ROT_X, 0 },
{ CoordinateName::PELVIS_ROT_Y, 0 },
{ CoordinateName::PELVIS_ROT_Z, 0 },

{ CoordinateName::HIP_R_FLEX, 3 },
{ CoordinateName::HIP_R_ADD, -5 },
{ CoordinateName::HIP_R_ROT, 0 },
{ CoordinateName::KNEE_R_FLEX, 15 },
{ CoordinateName::ANKLE_R_FLEX, 10 },
//LEFT FOOT

{ CoordinateName::HIP_L_FLEX, -3 },
{ CoordinateName::HIP_L_ADD, 5 },
{ CoordinateName::HIP_L_ROT, 0 },
{ CoordinateName::KNEE_L_FLEX, 5 },
{ CoordinateName::ANKLE_L_FLEX, 10 },
//right arm
{ CoordinateName::SHOULDER_R_X, 0 },
{ CoordinateName::SHOULDER_R_Y, 0 },
{ CoordinateName::SHOULDER_R_Z, 11 },

{ CoordinateName::ELBOW_R_Z, 0 },
{ CoordinateName::ELBOW_R_Y, 0 },
{ CoordinateName::CARPALS_R_Y, 0 },
//left arm
{ CoordinateName::SHOULDER_L_X,0 },
{ CoordinateName::SHOULDER_L_Y, 0 },
{ CoordinateName::SHOULDER_L_Z, 11 },

{ CoordinateName::ELBOW_L_Z, 0 },
{ CoordinateName::ELBOW_L_Y, 0 },
{ CoordinateName::CARPALS_L_Y, 0 },

{ CoordinateName::LUMBAR_FLEX, 0 },
{ CoordinateName::LUMBAR_BEND, 0 },
{ CoordinateName::LUMBAR_ROT, 0 }
};


void uploadMaterial(const Material& mtl) {
	glUniform4f(KaLocation, mtl.Ka.r, mtl.Ka.g, mtl.Ka.b, mtl.Ka.a);
	glUniform4f(KdLocation, mtl.Kd.r, mtl.Kd.g, mtl.Kd.b, mtl.Kd.a);
	glUniform4f(KsLocation, mtl.Ks.r, mtl.Ks.g, mtl.Ks.b, mtl.Ks.a);
	glUniform1f(NsLocation, mtl.Ns);
}

void uploadLight(const Light& light) {
	glUniform4f(LaLocation, light.La.r, light.La.g, light.La.b, light.La.a);
	glUniform4f(LdLocation, light.Ld.r, light.Ld.g, light.Ld.b, light.Ld.a);
	glUniform4f(LsLocation, light.Ls.r, light.Ls.g, light.Ls.b, light.Ls.a);
	glUniform3f(lightPositionLocation, light.lightPosition_worldspace.x,
		light.lightPosition_worldspace.y, light.lightPosition_worldspace.z);
	glUniform1f(lightPowerLocation, light.power);
}

map<int, mat4> calculateModelPoseFromCoordinates(map<int, float> q) {
	map<int, mat4> jointLocalTransformations;

	// base / pelvis joint
	mat4 pelvisTra = translate(mat4(), vec3(
		q[CoordinateName::PELVIS_TRA_X],
		q[CoordinateName::PELVIS_TRA_Y],
		q[CoordinateName::PELVIS_TRA_Z]));
	mat4 pelvis_rot_x = rotate(mat4(), radians(q[CoordinateName::PELVIS_ROT_X]), vec3(1, 0, 0));
	mat4 pelvis_rot_y = rotate(mat4(), radians(q[CoordinateName::PELVIS_ROT_Y]), vec3(0, 1, 0));
	mat4 pelvis_rot_z = rotate(mat4(), radians(q[CoordinateName::PELVIS_ROT_Z]), vec3(0, 0, 1));

	mat4 pelvisRot = pelvis_rot_x * pelvis_rot_y * pelvis_rot_z;
	jointLocalTransformations[JointName::BASE] = pelvisTra * pelvisRot;

	// right hip joint
	vec3 hipROffset = vec3(-0.072, -0.068, 0.086);
	mat4 hipRTra = translate(mat4(), hipROffset);
	mat4 hipRRotX = rotate(mat4(), radians(q[CoordinateName::HIP_R_ADD]), vec3(1, 0, 0));
	mat4 hipRRotY = rotate(mat4(), radians(q[CoordinateName::HIP_R_ROT]), vec3(0, 1, 0));
	mat4 hipRRotZ = rotate(mat4(), radians(q[CoordinateName::HIP_R_FLEX]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::HIP_R] = hipRTra * hipRRotX * hipRRotY * hipRRotZ;

	// right knee joint
	vec3 kneeROffset = vec3(0.0, -0.40, 0.0);
	mat4 kneeRTra = translate(mat4(1.0), kneeROffset);
	mat4 kneeRRotZ = rotate(mat4(), radians(q[CoordinateName::KNEE_R_FLEX]), vec3(0, 0, -1));
	jointLocalTransformations[JointName::KNEE_R] = kneeRTra * kneeRRotZ;

	// right ankle joint
	vec3 ankleROffset = vec3(0, -0.430, 0);
	mat4 ankleRTra = translate(mat4(1.0), ankleROffset);
	mat4 ankleRRotZ = rotate(mat4(), radians(q[CoordinateName::ANKLE_R_FLEX]), vec3(0, 0, 1));
	mat4 talusRModelMatrix = ankleRRotZ;
	jointLocalTransformations[JointName::ANKLE_R] = ankleRTra * ankleRRotZ;

	// right calcn joint
	vec3 calcnROffset = vec3(-0.062, -0.053, 0.010);
	mat4 calcnRTra = translate(mat4(1.0), calcnROffset);
	jointLocalTransformations[JointName::SUBTALAR_R] = calcnRTra;

	// right mtp joint
	vec3 toesROffset = vec3(0.184, -0.002, 0.001);
	mat4 mtpRTra = translate(mat4(1.0), toesROffset);
	jointLocalTransformations[JointName::MTP_R] = mtpRTra;

	///LEFT FOOT
	// LEFT hip joint

	vec3 hipLOffset = vec3(-0.072, -0.068, -0.086);
	mat4 hipLTra = translate(mat4(), hipLOffset);
	mat4 hipLRotX = rotate(mat4(), radians(q[CoordinateName::HIP_L_ADD]), vec3(1, 0, 0));
	mat4 hipLRotY = rotate(mat4(), radians(q[CoordinateName::HIP_L_ROT]), vec3(0, 1, 0));
	mat4 hipLRotZ = rotate(mat4(), radians(q[CoordinateName::HIP_L_FLEX]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::HIP_L] = hipLTra * hipLRotX * hipLRotY * hipLRotZ;


	// LEFT knee joint
	vec3 kneeLOffset = vec3(0.0, -0.40, 0.0);
	mat4 kneeLTra = translate(mat4(1.0), kneeLOffset);
	mat4 kneeLRotZ = rotate(mat4(), radians(q[CoordinateName::KNEE_L_FLEX]), vec3(0, 0, -1));
	jointLocalTransformations[JointName::KNEE_L] = kneeLTra * kneeLRotZ;

	// LEFT ankle joint
	vec3 ankleLOffset = vec3(0, -0.430, 0);
	mat4 ankleLTra = translate(mat4(1.0), ankleLOffset);
	mat4 ankleLRotZ = rotate(mat4(), radians(q[CoordinateName::ANKLE_L_FLEX]), vec3(0, 0, 1));
	mat4 talusLModelMatrix = ankleLRotZ;
	jointLocalTransformations[JointName::ANKLE_L] = ankleLTra * ankleLRotZ;

	// LEFT calcn joint
	vec3 calcnLOffset = vec3(-0.062, -0.053, 0.010);
	mat4 calcnLTra = translate(mat4(1.0), calcnLOffset);
	jointLocalTransformations[JointName::SUBTALAR_L] = calcnLTra;

	// LEFT mtp joint
	vec3 toesLOffset = vec3(0.184, -0.002, 0.001);
	mat4 mtpLTra = translate(mat4(1.0), toesLOffset);
	jointLocalTransformations[JointName::MTP_L] = mtpLTra;

	///right arm
	//right SHOULDER
	vec3 shoulderROffset = vec3(-0.15, 0.43, 0.15);
	mat4 shoulderRTra = translate(mat4(), shoulderROffset);
	mat4 shoulderRRotX = rotate(mat4(), radians(q[CoordinateName::SHOULDER_R_X]), vec3(1, 0, 0));
	mat4 shoulderRRotY = rotate(mat4(), radians(q[CoordinateName::SHOULDER_R_Y]), vec3(0, 1, 0));
	mat4 shoulderRRotZ = rotate(mat4(), radians(q[CoordinateName::SHOULDER_R_Z]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::SHOULDER_R] = shoulderRTra * shoulderRRotX * shoulderRRotY * shoulderRRotZ;

	// right elbow joint
	vec3 elbowROffset = vec3(0.02, -0.27, 0.05);
	mat4 elbowRTra = translate(mat4(1.0), elbowROffset) * rotate(mat4(), 0.2f, vec3(1, 0, 0)) * rotate(mat4(), 0.2f, vec3(0, 0, 1));
	mat4 elbowRRotY = rotate(mat4(), radians(q[CoordinateName::ELBOW_R_Y]), vec3(0, 1, 0));
	mat4 elbowRRotZ = rotate(mat4(), radians(q[CoordinateName::ELBOW_R_Z]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::ELBOW_R] = elbowRTra * elbowRRotZ * elbowRRotY;

	//right hand
	vec3 handROffset = vec3(0.0, -0.02, -0.16);
	mat4 handRTra = translate(mat4(1.0), handROffset) * rotate(mat4(), 3.14f / 2.0f, vec3(0, 1, 0));
	mat4 handRotY = rotate(mat4(), radians(q[CoordinateName::CARPALS_R_Y]), vec3(0, 1, 0));
	jointLocalTransformations[JointName::CARPALS_R] = handRTra * handRotY;


	///LEFT ARM
	//left SHOULDER
	vec3 shoulderLOffset = vec3(-0.15, 0.43, -0.15);
	mat4 shoulderLTra = translate(mat4(), shoulderLOffset);
	mat4 shoulderLRotX = rotate(mat4(), radians(q[CoordinateName::SHOULDER_L_X]), vec3(1, 0, 0));
	mat4 shoulderLRotY = rotate(mat4(), radians(q[CoordinateName::SHOULDER_L_Y]), vec3(0, 1, 0));
	mat4 shoulderLRotZ = rotate(mat4(), radians(q[CoordinateName::SHOULDER_L_Z]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::SHOULDER_L] = shoulderLTra * shoulderLRotX * shoulderLRotY * shoulderLRotZ;

	// left elbow joint
	vec3 elbowLOffset = vec3(0.02, -0.27, -0.05);
	mat4 elbowLTra = translate(mat4(1.0), elbowLOffset)* rotate(mat4(), -0.2f, vec3(1, 0, 0)) * rotate(mat4(), 0.2f, vec3(0, 0, 1));
	mat4 elbowLRotY = rotate(mat4(), radians(q[CoordinateName::ELBOW_L_Y]), vec3(0, 1, 0));
	mat4 elbowLRotZ = rotate(mat4(), radians(q[CoordinateName::ELBOW_L_Z]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::ELBOW_L] = elbowLTra * elbowLRotZ * elbowLRotY;

	//left hand
	vec3 handLOffset = vec3(0.0, -0.02, +0.16);
	mat4 handLTra = translate(mat4(1.0), handLOffset) * rotate(mat4(), -3.14f / 2.0f, vec3(0, 1, 0));
	mat4 handLotY = rotate(mat4(), radians(q[CoordinateName::CARPALS_L_Y]), vec3(0, 1, 0));
	jointLocalTransformations[JointName::CARPALS_L] = handLTra * handLotY;

	///
	// back joint
	vec3 backOffset = vec3(-0.103, 0.09, 0.0);
	mat4 lumbarTra = translate(mat4(1.0), backOffset) * rotate(mat4(), -0.13f, vec3(0, 0, 1));;
	mat4 lumbarRotX = rotate(mat4(), radians(q[CoordinateName::LUMBAR_BEND]), vec3(1, 0, 0));
	mat4 lumbarRotY = rotate(mat4(), radians(q[CoordinateName::LUMBAR_ROT]), vec3(0, 1, 0));
	mat4 lumbarRotZ = rotate(mat4(), radians(q[CoordinateName::LUMBAR_FLEX]), vec3(0, 0, 1));
	jointLocalTransformations[JointName::BACK] = lumbarTra * lumbarRotX * lumbarRotY * lumbarRotZ;

	return jointLocalTransformations;
}

vector<mat4> calculateSkinningTransformations(map<int, float> q) {
	auto jointLocalTransformationsBinding = calculateModelPoseFromCoordinates(bindingPose);
	skeleton->setPose(jointLocalTransformationsBinding);
	auto bindingWorldTransformations = skeleton->getJointWorldTransformations();

	auto jointLocalTransformationsCurrent = calculateModelPoseFromCoordinates(q);
	skeleton->setPose(jointLocalTransformationsCurrent);
	auto currentWorldTransformations = skeleton->getJointWorldTransformations();

	vector<mat4> skinningTransformations(JointName::JOINTS);
	for (auto joint : bindingWorldTransformations) {
		mat4 BInvWorld = glm::inverse(joint.second);
		mat4 JWorld = currentWorldTransformations[joint.first];
		skinningTransformations[joint.first] = JWorld * BInvWorld;
	}
	return skinningTransformations;
}

vector<float> calculateSkinningIndices() {
	// Task 4.3: assign a body index for each vertex in the model (skin) based
	// on its proximity to a body part (e.g. tight)
	vector<float> indices;
	for (auto v : skeletonSkin->indexedVertices) {
		// dummy
		//indices.push_back(1.0);
		if (v.y <= -0.07 && v.y >= -0.5 && v.z > 0.00 && v.z < 0.25) {
			indices.push_back(JointName::HIP_R);
		}
		else if (v.y < -0.5 && v.y > -0.85 && v.z > 0.00 &&  v.z < 0.25) {
			indices.push_back(JointName::KNEE_R);
		}
		else if (v.y <= -0.85 &&  v.y >= -1.0 && v.z > 0.00 && v.z < 0.25) {
			indices.push_back(JointName::ANKLE_R);
		}
		//LEFT
		else if (v.y <= -0.07 && v.y >= -0.5 && v.z < 0.00 && v.z > -0.25) {
			indices.push_back(JointName::HIP_L);
		}
		else if (v.y < -0.5 && v.y > -0.85 && v.z < 0.00 &&  v.z >-0.25) {
			indices.push_back(JointName::KNEE_L);
		}
		else if (v.y <= -0.85 &&  v.y >= -1.0 && v.z < 0.00 && v.z > -0.25) {
			indices.push_back(JointName::ANKLE_L);
		}
		else if (v.y >0.1  &&   v.z > 0.20 && v.z < 0.45) {
			indices.push_back(JointName::SHOULDER_R);
		}
		else if (v.y >-0.3 && v.y < 0.1  &&   v.z > 0.20 && v.z < 0.45) {
			indices.push_back(JointName::ELBOW_R);
		}
		else if (v.y >0.1  &&   v.z < -0.20 && v.z > -0.45) {
			indices.push_back(JointName::SHOULDER_L);
		}
		else if (v.y >-0.3 && v.y < 0.1  &&   v.z < -0.20 && v.z > -0.45) {
			indices.push_back(JointName::ELBOW_L);
		}
		else if (v.y > 0.0 || v.y > -0.4 && v.z > 0.25 || v.y > -0.4 && v.z < -0.25 ) {
			indices.push_back(JointName::BACK);
		}
		else {
			indices.push_back(JointName::BASE);
		}
	}
	return indices;
}

void cutContext()
{
	// Create and compile our GLSL program from the shaders
	CUTshaderProgram = loadShaders1("Shader.vertexshader", "shadertest.fragmentshader", "Shader.geometryshader");

	// Draw wire frame triangles or fill: GL_LINE, or GL_FILL
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Get a pointer location to model matrix in the vertex shader
	PLocation = glGetUniformLocation(CUTshaderProgram, "P");
	VLocation = glGetUniformLocation(CUTshaderProgram, "V");
	MLocation = glGetUniformLocation(CUTshaderProgram, "M");

	lightLocation1 = glGetUniformLocation(CUTshaderProgram, "light_position_worldspace");

	// Task 3.3d: get uniform location of the plane coefficients
	planeLocation = glGetUniformLocation(CUTshaderProgram, "planeCoeffs");
	ylocation = glGetUniformLocation(CUTshaderProgram, "y_of_sphere");
	// Task 4.1b:
	detachmentCoeffLocation = glGetUniformLocation(CUTshaderProgram, "detachmentDisplacement");

	// model
	loadOBJWithTiny("heart.obj", modelVertices, modelUVs, modelNormals);
	glGenVertexArrays(1, &modelVAO);
	glBindVertexArray(modelVAO);
	glGenBuffers(1, &modelVerticiesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVerticiesVBO);
	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(glm::vec3),
		&modelVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// Task 1.1: construct a plane (x-z)
	//*/
	glGenVertexArrays(1, &planeVAO);
	glBindVertexArray(planeVAO);
	glGenBuffers(1, &planeVerticiesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVerticiesVBO);
	float size = 0.5f;
	const GLfloat planeVertices[] = {
		-size, -planeY, -size,
		-size, -planeY,  size,
		size, -planeY,  size,
		size, -planeY, size,
		size, -planeY,  -size,
		-size, -planeY,  -size,

	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices),
		&planeVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	//*/
}
void createContext2() {
	// Create and compile our GLSL program from the shaders
	shaderProgram1 = loadShaders(
		"StandardShading1.vertexshader",
		"StandardShading1.fragmentshader");

	// Create and compile our CUBE GLSL program from the shaders
	cubeProgram = loadShaders(
		"cube.vertexshader",
		"cube.fragmentshader");

	// load obj
	loadOBJWithTiny("farmhouse.obj", objVertices, objUVs, objNormals);
	loadOBJWithTiny("StickFigurea.obj", objVertices2, objUVs2, objNormals2);
	loadOBJWithTiny("eyeball_obj.obj", eyeVertices, eyeUVs, eyeNormals);
	loadOBJWithTiny("Human_Heart.obj", heartVertices, heartUVs, heartNormals);

	// Task 6.2: load diffuse and specular texture maps
	diffuseTexture = loadSOIL("Farmhouse_Texture.jpg");
	//specularTexture = loadSOIL("suzanne_specular.bmp");
	diffuseTexture2 = loadSOIL("gold_texture.jpg");
	sand = loadSOIL("grass.jpg");
	dummy = loadSOIL("dummy_wood.jpg");
	eye_colour = loadSOIL("eyes_green.jpg");
	heart_colour = loadSOIL("HumanHeart-color.jpg");

	// Task 6.3: get a pointer to the texture samplers (diffuseColorSampler, specularColorSampler)
	diffuceColorSampler = glGetUniformLocation(shaderProgram1, "diffuceColorSampler");
	specularColorSampler = glGetUniformLocation(shaderProgram1, "specularColorSampler");

	// get pointers to the uniform variables
	projectionMatrixLocation = glGetUniformLocation(shaderProgram1, "P");
	viewMatrixLocation = glGetUniformLocation(shaderProgram1, "V");
	modelMatrixLocation = glGetUniformLocation(shaderProgram1, "M");

	lightLocation = glGetUniformLocation(shaderProgram1, "light_position_worldspace");

	cube_V_location = glGetUniformLocation(cubeProgram, "V");
	cube_P_location = glGetUniformLocation(cubeProgram, "P");
	cube_M_location = glGetUniformLocation(cubeProgram, "M");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// triangle
	glGenVertexArrays(1, &triangleVAO);
	glBindVertexArray(triangleVAO);

	glGenBuffers(1, &triangleVerticesVBO);    // given
	glBindBuffer(GL_ARRAY_BUFFER, triangleVerticesVBO);
	const GLfloat tirangleVertices[] =
	{
		-1.5, -1.5, 0.0,
		-1.5, 1.5, 0.0,
		1.5, -1.5, 0.0,
		1.5,  -1.5, 0.0,
		-1.5, 1.5, 0.0,
		1.5, 1.5, 0.0
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(tirangleVertices),
		&tirangleVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);


	glGenBuffers(1, &triangleNormalsVBO);    // given
	glBindBuffer(GL_ARRAY_BUFFER, triangleNormalsVBO);

	// define object normals VBO
	const GLfloat triangleNormals[] = {
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
	};


	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleNormals),
		&triangleNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	const GLfloat tirangleUVs[] =
	{
		0.0, 0.0,
		0.0, 500.0,
		500.0, 0.0,
		0.0, 500.0,
		500.0, 0.0,
		0.0, 0.0
	};
	// uvs VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(tirangleUVs),
		&tirangleUVs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);



	// obj
	// bind object vertex positions to attribute 0, UV coordinates
	// to attribute 1 and normals to attribute 2

	glGenVertexArrays(1, &objVAO);
	glBindVertexArray(objVAO);

	// vertex VBO
	glGenBuffers(1, &objVerticiesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objVerticiesVBO);
	glBufferData(GL_ARRAY_BUFFER, objVertices.size() * sizeof(glm::vec3),
		&objVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	//model normals not given
	glGenBuffers(1, &objNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, objNormals.size() * sizeof(glm::vec3),
		&objNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// uvs VBO
	glGenBuffers(1, &objUVVBO);
	glBindBuffer(GL_ARRAY_BUFFER, objUVVBO);
	glBufferData(GL_ARRAY_BUFFER, objUVs.size() * sizeof(glm::vec2),
		&objUVs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);


	//HEART OF SKELETON
	glGenVertexArrays(1, &heartVAO);
	glBindVertexArray(heartVAO);

	glGenBuffers(1, &heartVerticiesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, heartVerticiesVBO);
	glBufferData(GL_ARRAY_BUFFER, heartVertices.size() * sizeof(glm::vec3),
		&heartVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &heartNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, heartNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, heartNormals.size() * sizeof(glm::vec3),
		&heartNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// uvs VBO
	glGenBuffers(1, &heartUVVBO);
	glBindBuffer(GL_ARRAY_BUFFER, heartUVVBO);
	glBufferData(GL_ARRAY_BUFFER, heartUVs.size() * sizeof(glm::vec2),
		&heartUVs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	//EYE OF SKELETON
	// GLuint eyeVAO, eyeVAO;
	//GLuint eyeVerticiesVBO, eyeUVVBO, eyeNormalsVBO;
	// 2nd obj
	glGenVertexArrays(1, &eyeVAO);
	glBindVertexArray(eyeVAO);

	glGenBuffers(1, &eyeVerticiesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, eyeVerticiesVBO);
	glBufferData(GL_ARRAY_BUFFER, eyeVertices.size() * sizeof(glm::vec3),
		&eyeVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &eyeNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, eyeNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, eyeNormals.size() * sizeof(glm::vec3),
		&eyeNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// uvs VBO
	glGenBuffers(1, &eyeUVVBO);
	glBindBuffer(GL_ARRAY_BUFFER, eyeUVVBO);
	glBufferData(GL_ARRAY_BUFFER, eyeUVs.size() * sizeof(glm::vec2),
		&eyeUVs[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	// 2nd obj


	glGenVertexArrays(1, &objVAO2);
	glBindVertexArray(objVAO2);
	glGenBuffers(1, &objVerticiesVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, objVerticiesVBO2);
	glBufferData(GL_ARRAY_BUFFER, objVertices2.size() * sizeof(glm::vec3),
		&objVertices2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &objNormalsVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, objNormalsVBO2);
	glBufferData(GL_ARRAY_BUFFER, objNormals2.size() * sizeof(glm::vec3),
		&objNormals2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// uvs VBO
	glGenBuffers(1, &objUVVBO2);
	glBindBuffer(GL_ARRAY_BUFFER, objUVVBO2);
	glBufferData(GL_ARRAY_BUFFER, objUVs2.size() * sizeof(glm::vec2),
		&objUVs2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(2);

	//agalma_b = nullptr;
	///PLANE
	//Bounding agalma_box;

	/// BOUNDING BOXES
	//agalma
	vec3 min, max;
	vector<int> ind_boxes;
	std::vector<vec3> new_verts;
	std::vector<std::vector<vec3>> all_in;
	//Bounding agalma_b;
	//cout << agalma_b->max.x;

	create_bounding_box(objVertices2, min, max);
	b_tree.push_back(min);
	b_tree.push_back(max);

	size_1 = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
	center_1 = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
	center_agalma = center_1;
	size_agalma = size_1;

	newVertices(objVertices2, center_1, all_in);
	//FIRST LAYER
	for (int i = 0; i < 7; i++) {
		create_bounding_box(all_in[i], min, max);

		b_tree.push_back(min);
		b_tree.push_back(max);
	}
	min = b_tree[6];
	max = b_tree[7];
	center_1 = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
	cout << "                   ";
	cout << b_tree.size();
	cout << "                   ";

	std::vector<std::vector<vec3>> all_in1;
	newVertices(all_in[3], center_1, all_in1);

	for (int i = 0; i < 7; i++) {
		create_bounding_box(all_in1[i], min, max);

		b_tree.push_back(min);
		b_tree.push_back(max);
	}
	min = b_tree[8];
	max = b_tree[9];
	center_1 = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
	cout << "                   ";
	cout << b_tree.size();
	cout << "                   ";

	std::vector<std::vector<vec3>> all_in2;
	newVertices(all_in[4], center_1, all_in2);

	for (int i = 0; i < 7; i++) {
		create_bounding_box(all_in1[i], min, max);

		b_tree.push_back(min);
		b_tree.push_back(max);
	}
	/*
	for (int j=0; j < all_in.size();j ++){
		min = b_tree[j+2];
		max = b_tree[j+3];
		center_1 = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);

		std::vector<std::vector<vec3>> all_in1;
		newVertices(all_in[j], center_1, all_in1);

		for (int i = 0; i < 7; i++) {
			create_bounding_box(all_in1[i], min, max);

			b_tree.push_back(min);
			b_tree.push_back(max);
		}
	}
	*/
	/*
	for (int new1 =0; new1 < all_in.size(); new1++){
		std::vector<std::vector<vec3>> all_in1;
		//FIND CENTERS OF ALL_IN FIRST by using the b_tree
		vec3 center_pls = glm::vec3((b_tree[new1 + 3].x + b_tree[new1 + 2].x) / 2, (b_tree[new1 + 3].y + b_tree[new1 + 2].y) / 2, (b_tree[new1 + 3].z + b_tree[new1 + 2].z) / 2);

		newVertices(all_in[new1], center_pls, all_in1);
		cout << "                   ";
		cout << all_in1[new1].size();
		cout << ".\n";
		for (int i = 0; i < all_in1.size(); i++) {
			vec3 min_pls, max_pls;
			create_bounding_box(all_in1[new1], min_pls, max_pls);

			b_tree.push_back(min_pls);
			b_tree.push_back(max_pls);
		}

	}
	*/
	cout << b_tree.size();
	cout << ".\n";

	//spiti
	create_bounding_box(objVertices, min_spiti, max_spiti);
	size_2 = glm::vec3(max_spiti.x - min_spiti.x, max_spiti.y - min_spiti.y, max_spiti.z - min_spiti.z);
	center_2 = glm::vec3((max_spiti.x + min_spiti.x) / 2, (max_spiti.y + min_spiti.y) / 2, (max_spiti.z + min_spiti.z) / 2);

	//model
	vec3 model_min, model_max;
	size_model = glm::vec3(max.x - min.x, max.y - min.y, 2*(max.z - min.z));
	center_model = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);

	//cubeMAP

	float points[] = {
		-10.0f,  10.0f, -10.0f,
		-10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f, -10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,

		-10.0f, -10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f, -10.0f,  10.0f,
		-10.0f, -10.0f,  10.0f,

		-10.0f,  10.0f, -10.0f,
		10.0f,  10.0f, -10.0f,
		10.0f,  10.0f,  10.0f,
		10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f,  10.0f,
		-10.0f,  10.0f, -10.0f,

		-10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f, -10.0f,
		10.0f, -10.0f, -10.0f,
		-10.0f, -10.0f,  10.0f,
		10.0f, -10.0f,  10.0f
	};
	glGenBuffers(1, &cubevbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubevbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * 36 * sizeof(float), &points, GL_STATIC_DRAW);


	glGenVertexArrays(1, &cubevao);
	glBindVertexArray(cubevao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, cubevbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//BOX AND SPHERE
	box = new Box(8.2);
	// Task 1a: change the parameters of the cube
	// Task 2a: change the initial velocity and position, mass and radius

	// Task 2a: change the initial velocity and position, mass and radius
	sphere = new Sphere(vec3(4, 8, 4), vec3(0, 0, 0), 0.1, 5);

	// Task 3a: change the initial parameters of the system
	//sphere->modelMatrix[3][1] = 15 *center_1.y;
}
void newVertices(std::vector<vec3> objVertices2, glm::vec3 center_1, std::vector<vector<vec3>>& all_in) {
	vector<vec3> vec_null;
	vec_null.push_back(center_1);
	for (int i = 0; i < 8; i++) {

		all_in.push_back(vec_null);
	}
	for (int i = 0; i < objVertices2.size(); i++) {
		if (objVertices2[i].x > center_1.x) {
			if (objVertices2[i].y > center_1.y) {
				if (objVertices2[i].z > center_1.z) {
					all_in[0].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x > center_1.x) {
			if (objVertices2[i].y > center_1.y) {
				if (objVertices2[i].z < center_1.z) {
					all_in[1].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x > center_1.x) {
			if (objVertices2[i].y < center_1.y) {
				if (objVertices2[i].z > center_1.z) {
					all_in[2].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x > center_1.x) {
			if (objVertices2[i].y < center_1.y) {
				if (objVertices2[i].z < center_1.z) {
					all_in[3].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x < center_1.x) {
			if (objVertices2[i].y < center_1.y) {
				if (objVertices2[i].z < center_1.z) {
					all_in[4].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x < center_1.x) {
			if (objVertices2[i].y > center_1.y) {
				if (objVertices2[i].z > center_1.z) {
					all_in[5].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x < center_1.x) {
			if (objVertices2[i].y > center_1.y) {
				if (objVertices2[i].z < center_1.z) {
					all_in[6].push_back(objVertices2[i]);
				}
			}
		}
		if (objVertices2[i].x < center_1.x) {
			if (objVertices2[i].y < center_1.y) {
				if (objVertices2[i].z > center_1.z) {
					all_in[7].push_back(objVertices2[i]);
				}
			}
		}
	}


}

void create_bounding_box(std::vector<vec3> objVertices2, glm::vec3& min, glm::vec3& max) {
	float min_x, min_y, min_z, max_x, max_y, max_z;
	min_x = objVertices2[0].x;
	min_y = objVertices2[0].y;
	min_z = objVertices2[0].z;
	max_x = objVertices2[0].x;
	max_y = objVertices2[0].y;
	max_z = objVertices2[0].z;
	for (int i = 0; i < objVertices2.size(); i++) {
		if (objVertices2[i].x < min_x)  min_x = objVertices2[i].x;
		if (objVertices2[i].y < min_y)  min_y = objVertices2[i].y;
		if (objVertices2[i].z < min_z)  min_z = objVertices2[i].z;
		if (objVertices2[i].x > max_x)  max_x = objVertices2[i].x;
		if (objVertices2[i].y > max_y)  max_y = objVertices2[i].y;
		if (objVertices2[i].z > max_z)  max_z = objVertices2[i].z;
	}
	max = glm::vec3(max_x, max_y, max_z);
	min = glm::vec3(min_x, min_y, min_z);
}
void create_cube_map(
	const char* front,
	const char* back,
	const char* top,
	const char* bottom,
	const char* left,
	const char* right,
	GLuint* tex_cube) {
	// generate a cube-map texture to hold all the sides
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, tex_cube);

	// load each image and copy into a side of the cube-map texture
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, left);
	load_cube_map_side(*tex_cube, GL_TEXTURE_CUBE_MAP_POSITIVE_X, right);
	// format cube map texture
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool load_cube_map_side(GLuint texture, GLenum side_target,
	const char *file_name) {
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int x, y, n;
	int force_channels = 4;
	unsigned char *image_data = stbi_load(file_name, &x, &y, &n, force_channels);
	if (!image_data) {
		fprintf(stderr, "ERROR: could not load %s\n", file_name);
		return false;
	}
	// non-power-of-2 dimensions check
	if ((x & (x - 1)) != 0 || (y & (y - 1)) != 0) {
		fprintf(stderr, "WARNING: image %s is not power-of-2 dimensions\n",
			file_name);
	}

	// copy image data into 'target' side of cube map
	glTexImage2D(side_target, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		image_data);
	free(image_data);
	return true;
}


void createContext() {
	// shader
	shaderProgram = loadShaders(
		"StandardShading.vertexshader",
		"StandardShading.fragmentshader");

	// get pointers to uniforms
	modelMatrixLocation = glGetUniformLocation(shaderProgram, "M");
	viewMatrixLocation = glGetUniformLocation(shaderProgram, "V");
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "P");
	KaLocation = glGetUniformLocation(shaderProgram, "mtl.Ka");
	KdLocation = glGetUniformLocation(shaderProgram, "mtl.Kd");
	KsLocation = glGetUniformLocation(shaderProgram, "mtl.Ks");
	NsLocation = glGetUniformLocation(shaderProgram, "mtl.Ns");
	LaLocation = glGetUniformLocation(shaderProgram, "light.La");
	LdLocation = glGetUniformLocation(shaderProgram, "light.Ld");
	LsLocation = glGetUniformLocation(shaderProgram, "light.Ls");
	lightPositionLocation = glGetUniformLocation(shaderProgram, "light.lightPosition_worldspace");
	lightPowerLocation = glGetUniformLocation(shaderProgram, "light.power");
	useSkinningLocation = glGetUniformLocation(shaderProgram, "useSkinning");
	boneTransformationsLocation = glGetUniformLocation(shaderProgram, "boneTransformations");
	scaleLocation = glGetUniformLocation(shaderProgram, "scaling");


	// segment coordinates using Drawable
	// The Drawable sends the vertices, normals (optional) and UV coordinates
	// (optional) to the GPU and makes the necessary initializations. It can
	// be constructed either by providing a [.obj, .vtp] file or by supplying
	// the verticies, normals and UVs (as in this example).
	
	// Task 2.1a: for each vertex in an model provide an associative index
	// to the appropriate bone transformation
	//*/
	
	// Task 3.1a: define the relations between the bodies and the joints
	// A skeleton is a collection of joints and bodies. Each body is independent
	// of each other (conceptually). Furthermore, each body can  have many
	// drawables (geometries) attached. The joints are related to each other
	// and form a parent child relations. A joint is attached on a body.

	skeleton = new Skeleton(modelMatrixLocation, viewMatrixLocation, projectionMatrixLocation);

	// pelvis
	Joint* baseJoint = new Joint(); // creates a joint
	baseJoint->parent = NULL; // assigns the parent joint (NULL -> no parent)
	skeleton->joints[JointName::BASE] = baseJoint; // adds the joint in the skeleton's dictionary

	Body* pelvisBody = new Body(); // creates a body
	pelvisBody->drawables.push_back(new Drawable("models/sacrum.vtp")); // append 3 geometries
	pelvisBody->drawables.push_back(new Drawable("models/pelvis.vtp"));
	pelvisBody->drawables.push_back(new Drawable("models/l_pelvis.vtp"));
	pelvisBody->joint = baseJoint; // relates to a joint
	skeleton->bodies[BodyName::PELVIS] = pelvisBody; // adds the body in the skeleton's dictionary

													 // right femur
	Joint* hipR = new Joint();
	hipR->parent = baseJoint;
	skeleton->joints[JointName::HIP_R] = hipR;

	Body* femurR = new Body();
	femurR->drawables.push_back(new Drawable("models/femur.vtp"));
	femurR->joint = hipR;
	skeleton->bodies[BodyName::FEMUR_R] = femurR;
	//left

	Joint* hipL = new Joint();
	hipL->parent = baseJoint;
	skeleton->joints[JointName::HIP_L] = hipL;

	Body* femurL = new Body();
	femurL->drawables.push_back(new Drawable("models/l_femur.vtp"));
	femurL->joint = hipL;
	skeleton->bodies[BodyName::FEMUR_L] = femurL;

	// right tibia
	Joint* kneeR = new Joint();
	kneeR->parent = hipR;
	skeleton->joints[JointName::KNEE_R] = kneeR;

	Body* tibiaR = new Body();
	tibiaR->drawables.push_back(new Drawable("models/tibia.vtp"));
	tibiaR->drawables.push_back(new Drawable("models/fibula.vtp"));
	tibiaR->joint = kneeR;
	skeleton->bodies[BodyName::TIBIA_R] = tibiaR;
	//left 

	Joint* kneeL = new Joint();
	kneeL->parent = hipL;
	skeleton->joints[JointName::KNEE_L] = kneeL;

	Body* tibiaL = new Body();
	tibiaL->drawables.push_back(new Drawable("models/l_tibia.vtp"));
	tibiaL->drawables.push_back(new Drawable("models/l_fibula.vtp"));
	tibiaL->joint = kneeL;
	skeleton->bodies[BodyName::TIBIA_L] = tibiaL;

	// right talus
	Joint* ankleR = new Joint();
	ankleR->parent = kneeR;
	skeleton->joints[JointName::ANKLE_R] = ankleR;

	Body* talusR = new Body();
	talusR->drawables.push_back(new Drawable("models/talus.vtp"));
	talusR->joint = ankleR;
	skeleton->bodies[BodyName::TALUS_R] = talusR;
	//left talus

	Joint* ankleL = new Joint();
	ankleL->parent = kneeL;
	skeleton->joints[JointName::ANKLE_L] = ankleL;

	Body* talusL = new Body();
	talusL->drawables.push_back(new Drawable("models/l_talus.vtp"));
	talusL->joint = ankleL;
	skeleton->bodies[BodyName::TALUS_L] = talusL;

	// right calcn
	Joint* subtalarR = new Joint();
	subtalarR->parent = ankleR;
	skeleton->joints[JointName::SUBTALAR_R] = subtalarR;

	Body* calcnR = new Body();
	calcnR->drawables.push_back(new Drawable("models/foot.vtp"));
	calcnR->joint = subtalarR;
	skeleton->bodies[BodyName::CALCN_R] = calcnR;
	// LEFT calcn

	Joint* subtalarL = new Joint();
	subtalarL->parent = ankleL;
	skeleton->joints[JointName::SUBTALAR_L] = subtalarL;

	Body* calcnL = new Body();
	calcnL->drawables.push_back(new Drawable("models/l_foot.vtp"));
	calcnL->joint = subtalarL;
	skeleton->bodies[BodyName::CALCN_L] = calcnL;

	// RIGHT toes
	Joint* mtpR = new Joint();
	mtpR->parent = subtalarR;
	skeleton->joints[JointName::MTP_R] = mtpR;

	Body* toesR = new Body();
	toesR->drawables.push_back(new Drawable("models/bofoot.vtp"));
	toesR->joint = mtpR;
	skeleton->bodies[BodyName::TOES_R] = toesR;

	// LEFT toes

	Joint* mtpL = new Joint();
	mtpL->parent = subtalarL;
	skeleton->joints[JointName::MTP_L] = mtpL;

	Body* toesL = new Body();
	toesL->drawables.push_back(new Drawable("models/l_bofoot.vtp"));
	toesL->joint = mtpL;
	skeleton->bodies[BodyName::TOES_L] = toesL;

	///RIGH HAND
	//right humerus

	Joint* shoulderR = new Joint();
	shoulderR->parent = baseJoint;
	skeleton->joints[JointName::SHOULDER_R] = shoulderR;

	Body* humerusR = new Body();
	humerusR->drawables.push_back(new Drawable("models/humerus.vtp"));
	humerusR->joint = shoulderR;
	skeleton->bodies[BodyName::HUMERUS_R] = humerusR;

	//right ELBOW
	Joint* elbowR = new Joint();
	elbowR->parent = shoulderR;
	skeleton->joints[JointName::ELBOW_R] = elbowR;

	//right radius
	Body* radiusR = new Body();
	radiusR->drawables.push_back(new Drawable("models/radius.vtp"));
	radiusR->joint = elbowR;
	skeleton->bodies[BodyName::RADIUS_R] = radiusR;

	//right ULNA

	Body* ulnaR = new Body();
	ulnaR->drawables.push_back(new Drawable("models/ulna.vtp"));
	ulnaR->joint = elbowR;
	skeleton->bodies[BodyName::ULNA_R] = ulnaR;

	//right carpals
	Joint* carpalsR = new Joint();
	carpalsR->parent = elbowR;
	skeleton->joints[JointName::CARPALS_R] = carpalsR;

	Body* handR = new Body();
	handR->drawables.push_back(new Drawable("models/r_hand.vtp"));
	handR->joint = carpalsR;
	skeleton->bodies[BodyName::HAND_R] = handR;

	///LEFT HAND

	//left humerus

	Joint* shoulderL = new Joint();
	shoulderL->parent = baseJoint;
	skeleton->joints[JointName::SHOULDER_L] = shoulderL;

	Body* humerusL = new Body();
	humerusL->drawables.push_back(new Drawable("models/l_humerus.vtp"));
	humerusL->joint = shoulderL;
	skeleton->bodies[BodyName::HUMERUS_L] = humerusL;

	//left ELBOW
	Joint* elbowL = new Joint();
	elbowL->parent = shoulderL;
	skeleton->joints[JointName::ELBOW_L] = elbowL;

	//left radius
	Body* radiusL = new Body();
	radiusL->drawables.push_back(new Drawable("models/l_radius.vtp"));
	radiusL->joint = elbowL;
	skeleton->bodies[BodyName::RADIUS_L] = radiusL;

	//left ULNA

	Body* ulnaL = new Body();
	ulnaL->drawables.push_back(new Drawable("models/l_ulna.vtp"));
	ulnaL->joint = elbowL;
	skeleton->bodies[BodyName::ULNA_L] = ulnaL;

	//left carpals
	Joint* carpalsL = new Joint();
	carpalsL->parent = elbowL;
	skeleton->joints[JointName::CARPALS_L] = carpalsL;

	Body* handL = new Body();
	handL->drawables.push_back(new Drawable("models/l_hand.vtp"));
	handL->joint = carpalsL;
	skeleton->bodies[BodyName::HAND_L] = handL;

	// torso
	Joint* back = new Joint();
	back->parent = baseJoint;
	skeleton->joints[JointName::BACK] = back;

	Body* torso = new Body();
	torso->drawables.push_back(new Drawable("models/hat_spine.vtp"));
	torso->drawables.push_back(new Drawable("models/hat_jaw.vtp"));
	torso->drawables.push_back(new Drawable("models/hat_skull.vtp"));
	torso->drawables.push_back(new Drawable("models/hat_ribs.vtp"));
	//torso->drawables.push_back(new Drawable("models/eyeball_obj.obj"));
	torso->joint = back;
	skeleton->bodies[BodyName::TORSO] = torso;

	// Homework 1: construct the left leg (similar to the right). The
	// corresponding geometries are located in the models folder.

	// skin
	//loadOBJWithTiny("farmhouse.obj", objVertices, objUVs, objNormals);
	skeletonSkin = new Drawable("models/male.obj");
	skeletonSkin->vertices = skeletonSkin->vertices;
	auto maleBoneIndices = calculateSkinningIndices();
	glGenBuffers(1, &maleBoneIndicesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, maleBoneIndicesVBO);
	glBufferData(GL_ARRAY_BUFFER, maleBoneIndices.size() * sizeof(float),
		&maleBoneIndices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);


}

void free() {
	delete segment;
	// the skeleton owns the bodies and joints so memory is freed when skeleton
	// is deleted
	delete skeleton;
	delete skeletonSkin;

	glDeleteBuffers(1, &surfaceVAO);
	glDeleteVertexArrays(1, &surfaceVerticesVBO);
	glDeleteVertexArrays(1, &surfacesBoneIndecesVBO);

	glDeleteVertexArrays(1, &maleBoneIndicesVBO);

	glDeleteProgram(shaderProgram);
	glfwTerminate();
}

void mainLoop() {
	camera->position = vec3(-2, 0.22, 2.5);
	float maxEnergy = 0;
	float t = glfwGetTime();
	glm::vec3 lightPos = glm::vec3(3, 5, -1);
	//float i = 0.00011;
	//float j = 0.00007;
	float y_of_sphere = 0.0f;
	//T-R-S OF THE HOUSES
	mat4 spiti_scale_1 = glm::scale(mat4(), vec3(0.02, 0.02, 0.02));
	mat4 spiti_rotate_1 = glm::rotate(mat4(), 0.0f, vec3(0, 0, 1));
	mat4 spiti_translate_1 = glm::translate(mat4(), vec3(20, 0, 0));

	mat4 spiti_scale_2 = glm::scale(mat4(), vec3(0.025, 0.025, 0.025));
	mat4 spiti_rotate_2 = glm::rotate(mat4(), 0.785f / 2.0f, vec3(0, 1, 0));
	mat4 spiti_translate_2 = glm::translate(mat4(), vec3(100, 0, 50));

	mat4 spiti_scale_3 = glm::scale(mat4(), vec3(0.02, 0.02, 0.02));
	mat4 spiti_rotate_3 = glm::rotate(mat4(), -1.3f, vec3(0, 1, 0));
	mat4 spiti_translate_3 = glm::translate(mat4(), vec3(-50, 0, 0));

	mat4 spiti_scale_4 = glm::scale(mat4(), vec3(0.02, 0.02, 0.02));
	mat4 spiti_rotate_4 = glm::rotate(mat4(), 3.14f, vec3(0, 1, 0));
	mat4 spiti_translate_4 = glm::translate(mat4(), vec3(50, 0, -160));

	//CREATE CUBE MAP TEXTURE
	create_cube_map(FRONT, BACK1, TOP, BOTTOM, LEFT, RIGHT, &cube_map_texture);

	float i = 0.0f;
	float run = 0.0f;
	vec3 model_normal = vec3(1, 0, 0);
	vec3 last_position1;
	float rex;
	float lazer =0.0f;
	int sum_of_collisions = 0;
	bool KOPSE = false;
	int cut_click = 0;
	mat4 planeTranslation, planeRotation, last_plane_trans, last_plane_rot;
	vec3 planePosition, last_plane_pos;
	float currentTime_now, dt, currentTime;
	bool now_KOPSE = false;;
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		if(KOPSE & fortwse_pedio){
			currentTime = glfwGetTime() - currentTime_now;
			dt = currentTime - t;
			now_KOPSE = true;
			//cout << now_KOPSE;
		}
		else {
			currentTime_now = glfwGetTime();
		}
		vec4 lightPos4 = vec4(lightPos, 1.0); //* rotate(mat4(), i, vec3(0.0, 1.0, 0.0)) * rotate(mat4(), j, vec3(1.0, 0.0, 0.0));
		lightPos = vec3(lightPos4.x, lightPos4.y, lightPos4.z);

		glUseProgram(shaderProgram1);

		// camera
		camera->update();
		// bind
		glBindVertexArray(objVAO);
		mat4 projectionMatrix = camera->projectionMatrix;
		mat4 viewMatrix = camera->viewMatrix;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture);
		glUniform1i(diffuceColorSampler, 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularTexture);
		glUniform1i(specularColorSampler, 1);
		// Task 1.4c: transfer uniforms to GPU
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);

		glm::mat4 modelMatrix = spiti_scale_1 * spiti_rotate_1 *spiti_translate_1;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, objVertices.size());

		glm::mat4 modelMatrix2 = spiti_scale_2 * spiti_rotate_2 *spiti_translate_2;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix2[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, objVertices.size());

		glm::mat4 modelMatrix3 = spiti_scale_3 * spiti_rotate_3 *spiti_translate_3;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix3[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, objVertices.size());

		glm::mat4 modelMatrix4 = spiti_scale_4 * spiti_translate_4 *spiti_rotate_4;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix4[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, objVertices.size());

		glUniform3f(lightLocation, lightPos.x, lightPos.y, lightPos.z); // light

		


		//EDAFOS
		glBindVertexArray(triangleVAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sand);
		glUniform1i(diffuceColorSampler, 0);

		glm::mat4 edafosModel = glm::translate(mat4(), vec3(10, 0, 0)) * glm::scale(mat4(), vec3(20.0f, 20.0f, 20.0f))  * glm::rotate(mat4(), -3.14f / 2.0f, vec3(1, 0, 0)) ;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &edafosModel[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//agalma
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(objVAO2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture2);
		glUniform1i(diffuceColorSampler, 0);
		
		glm::mat4 test = glm::scale(mat4(), vec3(0.003, 0.003, 0.003)) * translate(mat4(), vec3(300, 0, -400));
		
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &test[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, objVertices2.size());
		
		
		/// CUBE
		//allazw to shaderProgram
		//allazw kai ta uniform giati twra exw allo shaderprogram
		//kanw bind to kainourio texture me GL_TEXTURE_CUBE_MAP anti gia GL_TEXTURE_2D
		//transform_1 = glm::translate(glm::mat4(1), center_1) * glm::scale(glm::mat4(1), size_1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDepthMask(GL_FALSE);
		glUseProgram(cubeProgram);

		glUniformMatrix4fv(cube_V_location, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(cube_P_location, 1, GL_FALSE, &projectionMatrix[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		glBindVertexArray(cubevao);

		glm::mat4 huge_cube = glm::scale(mat4(), vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(cube_M_location, 1, GL_FALSE, &huge_cube[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);


		glUseProgram(shaderProgram1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//BOUNDING BOX FOR AGALMA
		
		for (int j=16; j < b_tree.size();j=j+2){
			vec3 min = b_tree[j];
			vec3 max = b_tree[j + 1];
			vec3 size, center;
			size = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
			center = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);

			mat4 transform_1 = test * glm::translate(glm::mat4(1), center)* glm::scale(glm::mat4(1), size);
			glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform_1[0][0]);
			box->draw();
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		/*
		vec3 min = b_tree[8];
		vec3 max = b_tree[8 + 1];
		vec3 size, center;
		size = glm::vec3(max.x - min.x, max.y - min.y, max.z - min.z);
		center = glm::vec3((max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2);
		mat4 transform_1 = test * glm::translate(glm::mat4(1), center)* glm::scale(glm::mat4(1), size);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform_1[0][0]);
		box->draw();
		*/

		// 
		//BOUNDING BOX FOR HOUSE 1
		
		mat4 transform_house_1 = modelMatrix * glm::translate(glm::mat4(1), center_2) * glm::scale(glm::mat4(1), size_2);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform_house_1[0][0]);
		box->draw();
		//BOUNDING BOX FOR HOUSE 2
		mat4 transform_house_2 = modelMatrix2 * glm::translate(glm::mat4(1), center_2) * glm::scale(glm::mat4(1), size_2);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform_house_2[0][0]);
		box->draw();
		

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		glUseProgram(shaderProgram);

		// camera

		// light
		uploadLight(light);
		//glm::vec3 position = camera->position;

		map<int, float> q;
		float speed = 2.0f;
		if (step1) {

			if (i < 0.25) {
				//to prwto tetarto ths kinhshs
				q[CoordinateName::HIP_R_FLEX] = 40 * sin(i * 2 * 3.14);
				q[CoordinateName::KNEE_R_FLEX] = 60 * sin(i * 2 * 3.14);
				q[CoordinateName::ANKLE_R_FLEX] = -20 * sin(i * 2 * 3.14);

				q[CoordinateName::SHOULDER_L_Z] = +30 * sin(i * 2 * 3.14);
				q[CoordinateName::ELBOW_L_Z] = +20 * sin(i * 2 * 3.14);
				//ELBOW_R_Z
			}

			if (i > 0.25 & i<0.5) {
				//2o tetarto
				q[CoordinateName::HIP_R_FLEX] = 40 * sin(i * 2 * 3.14);
				//q[CoordinateName::HIP_R_FLEX] = 40 * sin(i * 2 * 3.14);

				q[CoordinateName::KNEE_R_FLEX] = 60 * sin(i * 2 * 3.14);
				q[CoordinateName::ANKLE_R_FLEX] = -20 * sin(i * 2 * 3.14);

				q[CoordinateName::HIP_L_FLEX] = -40 * cos(i * 2 * 3.14);
				q[CoordinateName::KNEE_L_FLEX] = -60 * cos(i * 2 * 3.14);
				q[CoordinateName::ANKLE_L_FLEX] = +20 * cos(i * 2 * 3.14);

				q[CoordinateName::SHOULDER_R_Z] = -30 * cos(i * 2 * 3.14);
				q[CoordinateName::ELBOW_R_Z] = -20 * cos(i * 2 * 3.14);

				q[CoordinateName::SHOULDER_L_Z] = 30 * sin(i * 2 * 3.14);
				q[CoordinateName::ELBOW_L_Z] = 20 * sin(i * 2 * 3.14);
			}
			if (i > 0.5 & i<0.75) {
				//3o tetarto
				//epanafora aristerou podou sthn arxikh thesi
				q[CoordinateName::HIP_L_FLEX] = -40 * cos(i * 2 * 3.14);
				q[CoordinateName::KNEE_L_FLEX] = -60 * cos(i * 2 * 3.14);
				q[CoordinateName::ANKLE_L_FLEX] = +20 * cos(i * 2 * 3.14);

				q[CoordinateName::SHOULDER_R_Z] = -30 * cos(i * 2 * 3.14);
				q[CoordinateName::ELBOW_R_Z] = -20 * cos(i * 2 * 3.14);
			}
			if (i>0.75) {
				step1 = false;
				i = 0;
			}
			i += 0.02f;
		}
		if (step_run) {

			if (run < 0.25) {
				//to prwto tetarto ths kinhshs
				q[CoordinateName::HIP_R_FLEX] = 60 * sin(run * 2 * 3.14);
				q[CoordinateName::KNEE_R_FLEX] = 80 * sin(run * 2 * 3.14);
				q[CoordinateName::ANKLE_R_FLEX] = -40 * sin(run * 2 * 3.14);

				q[CoordinateName::SHOULDER_L_Z] = +50 * sin(run * 2 * 3.14);
				q[CoordinateName::ELBOW_L_Z] = +40 * sin(run * 2 * 3.14);
				//ELBOW_R_Z
			}

			if (run > 0.25 & run<0.5) {
				//2o tetarto
				q[CoordinateName::HIP_R_FLEX] = 60 * sin(run * 2 * 3.14);
				//q[CoordinateName::HIP_R_FLEX] = 40 * sin(i * 2 * 3.14);

				q[CoordinateName::KNEE_R_FLEX] = 80 * sin(run * 2 * 3.14);
				q[CoordinateName::ANKLE_R_FLEX] = -40 * sin(run * 2 * 3.14);

				q[CoordinateName::HIP_L_FLEX] = -60 * cos(run * 2 * 3.14);
				q[CoordinateName::KNEE_L_FLEX] = -80 * cos(run * 2 * 3.14);
				q[CoordinateName::ANKLE_L_FLEX] = +40 * cos(run * 2 * 3.14);

				q[CoordinateName::SHOULDER_R_Z] = -50 * cos(run * 2 * 3.14);
				q[CoordinateName::ELBOW_R_Z] = -40 * cos(run * 2 * 3.14);

				q[CoordinateName::SHOULDER_L_Z] = 50 * sin(run * 2 * 3.14);
				q[CoordinateName::ELBOW_L_Z] = 40 * sin(run * 2 * 3.14);
			}
			if (run > 0.5 & run<0.75) {
				//3o tetarto
				//epanafora aristerou podou sthn arxikh thesi
				q[CoordinateName::HIP_L_FLEX] = -60 * cos(run * 2 * 3.14);
				q[CoordinateName::KNEE_L_FLEX] = -80 * cos(run * 2 * 3.14);
				q[CoordinateName::ANKLE_L_FLEX] = +40 * cos(run * 2 * 3.14);

				q[CoordinateName::SHOULDER_R_Z] = -50 * cos(run * 2 * 3.14);
				q[CoordinateName::ELBOW_R_Z] = -40 * cos(run * 2 * 3.14);
			}
			if (run>0.75) {
				step1 = false;
				run = 0;
			}
			run += 0.04f;
		}
		///CAMERA TAKE EVERYTHING
		/**/
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentT = glfwGetTime();
		float deltaTime = float(currentT - lastTime);

		// Get mouse position
		
		vec3 direction = camera->direction;
		// Right vector
		
		uploadMaterial(boneMaterial);

		//IF YOU PRESS O THE CAMERA UNBINDS AND MODEL STAYS STABLE
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			step1 = true;
			if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
				step1 = false;
				step_run = true;
				speed_of_move = speed_of_run;
			}
			

			if (collision) {
				
				position = last_position1;
			}
			else {
				last_position1 = position;
				position += vec3(direction.x, 0, direction.z) * deltaTime * speed_of_move;
				
			}
			aristera = false;
			deksia = false;
			
		}
		else {
			// Move backward
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
				//position -= vec3(direction.x, 0, direction.z) * deltaTime * speed_of_move;

			}
			// Strafe right
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
				deksia = true;
				aristera = false;
				step1 = true;

				if (collision) {
					position = last_position1;
				}
				else {
					last_position1 = position;

					position += camera->right * deltaTime * speed_of_move;
				}
				
				
			}
			// Strafe left
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
				if (collision) {
					position = last_position1;
				}
				else {
					last_position1 = position;

					position -= camera->right * deltaTime * speed_of_move;
				}
				aristera = true;
				deksia = false;
				step1 = true;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
				aristera = false;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
				deksia = false;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE) {
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				step1 = true;
			}
			step_run = false;
			speed_of_move = 0.5f;
		}
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (unbind) {
				god_mode += vec3(direction.x, direction.y, direction.z) * deltaTime * speed;
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (unbind) {
				god_mode -= vec3(direction.x, direction.y, direction.z) * deltaTime * speed;

			}
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (unbind) {
				god_mode += camera->right * deltaTime * speed;
			}
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (unbind) {
				god_mode -= camera->right * deltaTime * speed;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
			unbind = true;
			speed_of_move = 2;
		}
		lastTime = currentT;

		//POSITION OF THE CAMERA
		//POSITION OF THE CAMERA CHANGES ACCORDING THE POSITION OF THE MODEL
		vec3 camera_pos = vec3(position.x-0.5 *direction.x, position.y + 0.13f, position.z -0.5*direction.z);
		camera->position = camera_pos;
		

		//REX IS MY FAVOURITE DEGREE OF ROTATION OF THE MODEL
		//ARCCOS OF THE DOT PRODUCT OF THE VECTOR OF THE MODEL AND THE DIRECTION OF THE CAMERA
		//DIRECTION OF THE MODEL
		

		rex = acos(dot(normalize(vec3(direction.x, 0, direction.z)), normalize(model_normal))) * 180 / 3.14;
		
		if (direction.z < 0) {

		}
		if (direction.z < 0) {
			if (aristera) {
				rex = rex + 90.0f;
			}
			else if (deksia) {
				rex = rex - 90.0f;
			}
			q[CoordinateName::PELVIS_ROT_Y] = rex;

		}
		else{
			//IF CAMERA LOOKS AT THE POSITIVES Z THEN IMPLIMENT -REX INSTEAD OF REX
			if (aristera) {
				rex = rex - 90.0f;
			}
			else if(deksia){
				rex = rex + 90.0f;
			}
			rex = -rex;
			q[CoordinateName::PELVIS_ROT_Y] = rex;

		}
		if (unbind) {
			camera->position = god_mode;
			position = vec3(0.5, 0.13, -0.5);
			direction = vec3(0, 0, -1);
			rex = 90;
			q[CoordinateName::PELVIS_ROT_Y] = rex;
		}
		//MAKE A DOT AT THE MODEL
		mat4 model_pos = translate(mat4(), position);
		mat4 model_sca = glm::scale(mat4(), vec3(0.1f, 0.1f, 0.1f));
		mat4 model_dot = model_pos * model_sca;
		//TAKE THE LAST VECTOR OF THE MAT4
		//THIS IS THE MODELS POSITION AS A DOT 
		vec3 model_position = vec3(model_dot[3][0], model_dot[3][1], model_dot[3][2]);
		
		//house size_2 center_2 transform_house_1
		mat4 spiti_max = modelMatrix * translate(mat4(), max_spiti);
		vec3 spiti_position_max = vec3(spiti_max[3][0], spiti_max[3][1], spiti_max[3][2]);

		mat4 spiti_min = modelMatrix * translate(mat4(), min_spiti);
		vec3 spiti_position_min = vec3(spiti_min[3][0], spiti_min[3][1], spiti_min[3][2]);
		collision = false;

		//OTAN TA BOUNDING BOX TEMNONTE
		if ((model_position.z < spiti_position_max.z) & (model_position.z > spiti_position_min.z)) {
			if ((model_position.x < spiti_position_max.x) & (model_position.x > spiti_position_min.x)) {
				collision = true;
				//STAMATAEI TO MONTELO
				q[CoordinateName::PELVIS_TRA_X] = last_position1.x;
				q[CoordinateName::PELVIS_TRA_Y] = last_position1.y;
				q[CoordinateName::PELVIS_TRA_Z] = last_position1.z;
				//STAMAEI H KAMERA 
				//camera->position = last_position_camera;
			}

		}
		if (collision == false) {
			if (last_pos == false) {
				//OTAN DEN UPARXEI SIGKROUSH LEITOURGEI KANONIKA
				q[CoordinateName::PELVIS_TRA_X] = position.x;
				q[CoordinateName::PELVIS_TRA_Y] = position.y;
				q[CoordinateName::PELVIS_TRA_Z] = position.z;
				//PAIRNEI PANTA THN TELEUTAIA THESI ETSI WSTE OTAN XTUPHSEI EMPODIO
				// NA THN EFARMOSEI META OPWS FENETE APO PANW
				last_position1 = position;
				//last_position_camera = camera->position;

			}
			else {
				//OTAN KANW UNBIND THN KAMERA DLD LAST_POS = TRUE
				//PAIRNEI THN TELEUTAIA THESH TOU MONTELOU WSTE NA THN EFARMOSEI 
				//KAI NA MEINEI STATHERO TO MONTELO
				q[CoordinateName::PELVIS_TRA_X] = last_position1.x;
				q[CoordinateName::PELVIS_TRA_Y] = last_position1.y;
				q[CoordinateName::PELVIS_TRA_Z] = last_position1.z;
			}
		}

		q[CoordinateName::ELBOW_R_Y] = -10;
		q[CoordinateName::ELBOW_L_Y] = 10;

		q[CoordinateName::PELVIS_ROT_Z] = 0;
		q[CoordinateName::HIP_R_ADD] = 0;
		q[CoordinateName::HIP_R_ROT] = 0;

		q[CoordinateName::LUMBAR_FLEX] = 10;
		q[CoordinateName::LUMBAR_BEND] = 0;
		q[CoordinateName::LUMBAR_ROT] = 0;

		q[CoordinateName::HIP_L_ADD] = 0;
		q[CoordinateName::HIP_L_ROT] = 0;


		//q[CoordinateName::KNEE_L_FLEX] = 0;

		//RIGHT arm
		//q[CoordinateName::SHOULDER_R_X] = 0;
		//q[CoordinateName::SHOULDER_R_Y] = 0;
		//q[CoordinateName::SHOULDER_R_Z] = 0;


		//LEFT arm
		//q[CoordinateName::SHOULDER_L_X] = 0;
		//q[CoordinateName::SHOULDER_L_Y] = 0;
		//q[CoordinateName::SHOULDER_L_Z] = 0;

		q[CoordinateName::ELBOW_L_Z] = 0;
		q[CoordinateName::ELBOW_L_Y] = 0;
		auto jointLocalTransformations = calculateModelPoseFromCoordinates(q);
		skeleton->setPose(jointLocalTransformations);

		glUniform1i(useSkinningLocation, 0);
		uploadMaterial(boneMaterial);

		skeleton->draw(viewMatrix, projectionMatrix);


		//*/

		// draw the skin using wireframe mode
		/*
		skeletonSkin->bind();

		mat4 maleModelMatrix = mat4();
		mat4 scaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &maleModelMatrix[0][0]);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, &scaleMatrix[0][0]);

		// Task 4.2: calculate the bone transformations
		auto T = calculateSkinningTransformations(q);
		glUniformMatrix4fv(boneTransformationsLocation, T.size(),
			GL_FALSE, &T[0][0][0]);

		glUniform1i(useSkinningLocation, 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


		skeletonSkin->draw();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		*/
		/*
		glUseProgram(cubeProgram);

		glUniformMatrix4fv(cube_V_location, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(cube_P_location, 1, GL_FALSE, &projectionMatrix[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_texture);
		glBindVertexArray(cubevao);
		//BOUNDING BOX FOR MODEL
		mat4 pelvisTra1 = translate(mat4(), vec3(
			position.x,
			position.y - 0.1,
			position.z - 0.3));
		//mat4 pelvis_rot_y1 = rotate(mat4(), radians(rex), vec3(0, 1, 0));

		//mat4 pelvisRot1 = pelvis_rot_y1;//* pelvis_rot_y * pelvis_rot_z;
		//mat4 model_transf = pelvisTra1 ;

		//mat4 transform_model =   glm::translate(glm::mat4(1), center_model)*scale(mat4(), vec3(0.05, 0.05, 0.05)) * glm::scale(glm::mat4(1), size_model);
		mat4 transform_model = pelvisTra1 * glm::scale(mat4(), vec3(0.003, 0.003, 0.003))* scale(mat4(), vec3(0.05, 0.05, 0.05)) * glm::scale(glm::mat4(1), size_model);
		glUniformMatrix4fv(cube_M_location, 1, GL_FALSE, &transform_model[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		*/
		if (unbind) {
			last_position1 = position;
		}
		/// PLANE
		glUseProgram(shaderProgram1);

		//HEART OF SKELETON

		//EYE OF SKELETON
		glBindVertexArray(heartVAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, heart_colour);
		glUniform1i(diffuceColorSampler, 0);
		vec3 heartPosition = vec3(last_position1.x , last_position1.y, last_position1.z);
		mat4 heartTranslation = translate(mat4(), heartPosition);
		float rex_heart_eye = rex;
		if (unbind) {
			rex_heart_eye = 180.0f;
		}
		mat4 heartModel = heartTranslation  * translate(mat4(), vec3(-0.004, 0.03, 0.012))* glm::rotate(mat4(), rex_heart_eye*3.14f/180.0f, vec3(0, 1, 0))*  glm::scale(mat4(), vec3(0.001, 0.001, 0.001));;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &heartModel[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, heartVertices.size());


		//EYE OF SKELETON
		glBindVertexArray(eyeVAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, eye_colour);
		glUniform1i(diffuceColorSampler, 0);
		vec3 eyePosition = vec3(last_position1.x - 0.003, last_position1.y + 0.065, last_position1.z+0.005);
		mat4 eyeTranslation = translate(mat4(), eyePosition);

		mat4 eyeModel = eyeTranslation * glm::rotate(mat4(), rex_heart_eye*3.14f / 180.0f, vec3(0, 1, 0)) * glm::scale(mat4(), vec3(0.004, 0.004, 0.004));;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &eyeModel[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, eyeVertices.size());

		eyePosition = vec3(last_position1.x + 0.003, last_position1.y + 0.065, last_position1.z +0.005);
		eyeTranslation = translate(mat4(), eyePosition);

		eyeModel = eyeTranslation * glm::rotate(mat4(), rex_heart_eye*3.14f / 180.0f, vec3(0, 1, 0)) * glm::scale(mat4(), vec3(0.004, 0.004, 0.004));;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &eyeModel[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, eyeVertices.size());


		///CREATE LAZER BEEM
		//*/*/*//
		///
		mat4 rotate_model_rex = rotate(mat4(), rex, vec3(1, 0, 0));
		vec3 model_normal_rot = vec3(rotate_model_rex * vec4(1, 0, 0, 1));

		//CREATE SPHERE TO PLAY WITH THE FRAMES
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, heart_colour);
		glUniform1i(diffuceColorSampler, 0);
		mat4 lazerscale = glm::scale(mat4(), vec3(0.002, 0.002, 0.002));
		mat4 lazerModel,lazerTranslation;
		vec3 lazerPosition;
		lazer = lazer + 2.5f;
		
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				for (int beem = 0; beem < 500; beem++) {
					
					float siga = 0.001 * beem;
					lazerPosition = vec3(last_position1.x + siga * lazer * direction.x - 0.003, planeY + last_position1.y + 0.065 + siga * lazer * direction.y, last_position1.z + siga * lazer * direction.z - 0.003);
					lazerTranslation = translate(mat4(), lazerPosition);
					lazerModel = lazerTranslation * lazerscale;
					glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &lazerModel[0][0]);
					sphere->draw();
					lazerPosition = vec3(last_position1.x + siga * lazer * direction.x + 0.003, planeY + last_position1.y + 0.065 + siga * lazer * direction.y, last_position1.z + siga * lazer * direction.z + 0.003);
					lazerTranslation = translate(mat4(), lazerPosition);
					lazerModel = lazerTranslation * lazerscale;
					glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &lazerModel[0][0]);
					sphere->draw();
				}
				cout << "I AM KILLING IT MASTER ";
				cout << ".\n";
				if (lazer > 10.0f) {
					lazer = 0.0f;
					cout << "Reloading Master ";
					cout << ".\n";

				}
				//KOPSE TO MODELO
				KOPSE = true;
				//STATHEROPOIHSE TO PEDIO
				stathero_pedio = true;
			}
		
		//*/*/*//
		///
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			//KOPSE = false;
			fortwse_pedio = true;
			cout << "Ready to shoot Master";
			cout << ".\n";
		}

		//*/*/*//
		///
		//PARE THN TELEUTAIA THESI TOU PEDIOU
		//ETSI WSTE OTAN STAMATHSEI TO KLIK NA EXEI "KLEIDWSEI" TO PEDIO STO MONTELO
		float rotAngle = 0.0f;
		if (fortwse_pedio & KOPSE & stathero_pedio) {
			
			planePosition = vec3(last_position1.x , planeY + last_position1.y, last_position1.z);

			planeTranslation = translate(mat4(), planePosition);
			if (direction.z < 0) {
				rotAngle = 3.14f;

			}
			planeRotation = rotate(mat4(), rex*3.14f/180.f +3.14f/2.0f + rotAngle, vec3(0, 1, 0))*rotate(mat4(), planeAngle +3.1415f / 2.0f, vec3(0, 0, 1));
			
			last_plane_trans = planeTranslation;

			last_plane_rot = planeRotation;

			last_plane_pos = planePosition;
			stathero_pedio = false;
		}
		if(KOPSE==false){
			planePosition = vec3(last_position1.x, last_position1.y - 10, last_position1.z);
			planeTranslation = translate(mat4(), planePosition);
			planeRotation = mat4();
			last_plane_pos = planePosition;
			last_plane_rot;
			last_plane_trans = planeTranslation;
		}

		
		planePosition = last_plane_pos;

		planeTranslation = last_plane_trans;

		planeRotation = last_plane_rot;
		

		//CREATE THE PLANE, THE CUTTING SURFACE
		glBindVertexArray(planeVAO);
		
		mat4 planeScale = glm::scale(mat4(), vec3(0.02, 0.01, 0.5));
		mat4 planeModelMatrix = planeTranslation * planeRotation;//* planeScale;
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &planeModelMatrix[0][0]);
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		//BOUNDING BOX OF THE CUTTED MODEL
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glm::mat4 agalma_cut = glm::scale(mat4(), vec3(0.003, 0.003, 0.003)) * translate(mat4(), vec3(0, 0, 0));
		//TRANSFORM OF AGALMA
		mat4 transform_agalma_cut = agalma_cut * glm::translate(glm::mat4(1), center_agalma)* glm::scale(glm::mat4(1), size_agalma);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform_agalma_cut[0][0]);
		box->draw();
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		/// PLANE OF AGALMA
		//glBindVertexArray(triangleVAO);
		//mat4 plane_cut = glm::translate(glm::mat4(1), center_agalma)* glm::scale(glm::mat4(1), size_agalma);
		//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &transform_agalma_cut[0][0]);
		//glDrawArrays(GL_TRIANGLES, 0, 6);

		///CUT
		
		glUseProgram(CUTshaderProgram);
		glUniform3f(lightLocation1, lightPos.x, lightPos.y, lightPos.z); // light

		glBindVertexArray(objVAO2);
		// calculate plane coefficients
		//AGALMA KOPSE
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexture2);
		glUniform1i(diffuceColorSampler, 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		//
		mat4 akrh_agalmatos = agalma_cut * glm::translate(glm::mat4(1), center_agalma+3.0f * size_agalma)* glm::scale(glm::mat4(1), size_agalma);
		mat4 akrh_agalmatos_aristera = agalma_cut * glm::translate(glm::mat4(1), center_agalma - 3.0f * size_agalma)* glm::scale(glm::mat4(1), size_agalma);

		vec3 planeNormal(planeRotation * vec4(0, 1, 0, 1));
		float d = -dot(planeNormal, planePosition);
		vec4 planeCoeffs(planeNormal, d);
		///***
		vec3 center_of_agalma = vec3(transform_agalma_cut[3][0], transform_agalma_cut[3][1], transform_agalma_cut[3][2]);
		vec3 edge_of_agalma = vec3(akrh_agalmatos[3][0], akrh_agalmatos[3][1], akrh_agalmatos[3][2]);
		vec3 edge_of_agalma_aristera = vec3(akrh_agalmatos_aristera[3][0], akrh_agalmatos_aristera[3][1], akrh_agalmatos_aristera[3][2]);

		if (dot(vec4(center_of_agalma,1.0f), transform_agalma_cut * planeCoeffs) > 0) {
			if (dot(vec4(edge_of_agalma, 1.0f), akrh_agalmatos * planeCoeffs) < 0) {
				ENDIAMESA = true;
				cout << 1; 
			}
			
		}
		else if (dot(vec4(center_of_agalma, 1.0f), transform_agalma_cut * planeCoeffs) < 0) {
			if (dot(vec4(edge_of_agalma_aristera, 1.0f), akrh_agalmatos_aristera * planeCoeffs) > 0) {
				ENDIAMESA = true;
				planeAngle = 3.14f;
				
			}
		}

		///***
		glUniform4f(planeLocation, planeCoeffs.x, planeCoeffs.y, planeCoeffs.z, planeCoeffs.w);
		// calculate and transmit the detachment offset to the GPU

		vec4 detachmentDisplacement = vec4(vec3(planeNormal  * detachmentCoeff), 0);
		
		glUniform4f(detachmentCoeffLocation, detachmentDisplacement.x, detachmentDisplacement.y, detachmentDisplacement.z, detachmentDisplacement.w);
		
		y_of_sphere = y_of_sphere -1.5 * transform_agalma_cut[3][1];
		glUniform1f(ylocation, y_of_sphere);
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &agalma_cut[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, objVertices2.size());
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//agalma_cut is the position of the agalma
		//sphere = new Sphere(vec3(0.05, 0.01, 0.05), vec3(0, 0.2, 0), 0.01, 1);

		//vec3 first_pos_sphere = vec3(agalma_cut[3][0], agalma_cut[3][1], agalma_cut[3][2]);
		//sphere = new Sphere(first_pos_sphere, vec3(0, 0.2, 0), 0.001, 1);
		//box = new Box(3);
		//cout << agalma_cut[3][1];
		//SPHERE AND BOX

		
		glUseProgram(shaderProgram1);

		if (now_KOPSE & ENDIAMESA) {
			mat4 box_trans = glm::scale(mat4(), vec3(0.5, 0.5, 0.5)) * translate(mat4(), vec3(0.5,0.5,0.5));
			//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &box_trans[0][0]);
			//box->draw();
			// simulation of a sphere (collision and forces)
			//define the velocity of the sphere after the collision
		
			handleBoxSphereCollision(*box, *sphere);
			// model the force due to gravity
			//gr for gravity
			//cout << t;
			//cout << "                 ";
			vec3 n;
		
			if (checkForCollision(sphere->x, sphere->r, box->size, n) == true) {
				sum_of_collisions = sum_of_collisions + 1;
			}

			if (sum_of_collisions < 15) {
				sphere->forcing = [&](float t, const vector<float>& y)->vector<float> {
					vector<float> f(6, 0.0f);
					f[1] = -gr * sphere->m;
					return f;
				};
				sphere->update(t, dt);
				//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &sphere->modelMatrix[0][0]);
				//sphere->draw();

				// calculate the total energy and comment on the previous
				float KE = sphere->calcKinecticEnergy();
				float PE =sphere->m*gr * sphere->x.y;
				float Total = KE + PE;
				if (Total > maxEnergy) {
					//cout << "Total Energy: " << T << endl;
					maxEnergy = Total;

				}
				y_of_sphere = 0.026 * sphere->modelMatrix[3][1];
			
			}
			else {
				//glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &sphere->modelMatrix[0][0]);
				//sphere->draw();
				y_of_sphere = 0;
			}
			t += dt;
		}
		//cout << y_of_sphere;
		//cout << "         ";
		//first_pos_sphere - sphere->modelMatrix[3][1];
		//*/
		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}
void lazerbeem(){

}
bool checkForCollision(vec3& pos, const float& r, const float& size, vec3& n) {
	if (pos.x - r <= 0) {
		//correction
		float dis = -(pos.x - r);
		pos = pos + vec3(dis, 0, 0);

		n = vec3(-1, 0, 0);
	}
	else if (pos.x + r >= size) {
		//correction
		float dis = size - (pos.x + r);
		pos = pos + vec3(dis, 0, 0);

		n = vec3(1, 0, 0);
	}
	else if (pos.y - r <= 0) {
		//correction
		float dis = -(pos.y - r);
		pos = pos + vec3(0, dis, 0);

		n = vec3(0, -1, 0);
	}
	else if (pos.y + r >= size) {
		//correction
		float dis = size - (pos.y + r);
		pos = pos + vec3(0, dis, 0);

		n = vec3(0, 1, 0);
	}
	else if (pos.z - r <= 0) {
		//correction
		float dis = -(pos.z - r);
		pos = pos + vec3(0, 0, dis);

		n = vec3(0, 0, -1);
	}
	else if (pos.z + r >= size) {
		//correction
		float dis = size - (pos.z + r);
		pos = pos + vec3(0, 0, dis);

		n = vec3(0, 0, 1);
	}
	else {
		return false;
	}
	return true;
}

void pollKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*float move_forward = 0.0f;
	float move_back = 0.0f;
	float move_left = 0.0f;
	float move_right = 0.0f;*/
	if (key == GLFW_KEY_W) {
		step1 = true;
	}
	if (key == GLFW_KEY_G) {
		//move_forward = move_forward - 0.1;
	}

	if (key == GLFW_KEY_F) {
		//rotate_left = rotate_left + 1.0f;
	}
	if (key == GLFW_KEY_H) {
	}

	if (key == GLFW_KEY_U) {
		//last_pos = false;
	}
	if (key == GLFW_KEY_O) {
		//last_pos = true;
	}
	if (key == GLFW_KEY_H) {
		planeY += 0.002;
	}
	if (key == GLFW_KEY_J) {
		planeY -= 0.002;
	}

	// Task 2.2: planeAngle J, L keys
	if (key == GLFW_KEY_K) {
		planeAngle += 0.01f;
	}
	if (key == GLFW_KEY_L) {
		planeAngle -= 0.01f;
	}

	if (key == GLFW_KEY_U) {
		//detachmentCoeff += 0.005f;
	}
	if (key == GLFW_KEY_O) {
		//detachmentCoeff -= 0.005f;
	}
}


void initialize() {
	// Initialize GLFW
	if (!glfwInit()) {
		throw runtime_error("Failed to initialize GLFW\n");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(W_WIDTH, W_HEIGHT, TITLE, NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw runtime_error(string(string("Failed to open GLFW window.") +
			" If you have an Intel GPU, they are not 3.3 compatible." +
			"Try the 2.1 version.\n"));
	}
	glfwMakeContextCurrent(window);

	// Start GLEW extension handler
	glewExperimental = GL_TRUE;

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw runtime_error("Failed to initialize GLEW\n");
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Hide the mouse and enable unlimited movement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, W_WIDTH / 2, W_HEIGHT / 2);

	// Gray background color
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	//glfwSetCursorPosCallback(window, cursor_pos_callback);

	glfwSetKeyCallback(window, pollKeyboard);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normal is not towards the camera
	// glEnable(GL_CULL_FACE);

	// Log
	logGLParameters();

	// Create camera
	camera = new Camera(window);
}

int main(void) {
	try {
		initialize();
		createContext();
		createContext2();
		cutContext();
		mainLoop();
		free();
	}
	catch (exception& ex) {
		cout << ex.what() << endl;
		getchar();
		free();
		return -1;
	}

	return 0;
}