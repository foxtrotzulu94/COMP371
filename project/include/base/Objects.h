#pragma once

#include <vector>

#include "base/Mesh.h"
#include "Utils.h"

//Just an object that can be handled by the engine and placed in world
class EngineObject {
protected:
	//Main model matrix
	mat4 Model;
	//Cached rotation along each axis (DEBUG)
	vec3 rotations;
	//Cached scale (DEBUG)
	vec3 scales;

public:
	//Retrieve the model matrix
	inline mat4* getModel() { return &Model; }

	//Apply a translation
	void translate(float x, float y, float z);
	void translate(vec3 translation);

	//Rotate the object by a certain amount.
	//Use Degrees. Function will transform to radians
	void rotate(vec3 rotation);
	void rotateX(float amt);
	void rotateY(float amt);
	void rotateZ(float amt);

	//Scale the objects
	void scale(vec3 scale);

	vec3 getTranslation();

	vec3 getRotations() { return rotations; }

	vec3 getScale() { return scales; }
};

//Main object
class WorldGenericObject : public EngineObject {
protected:
	//Primary mesh which makes up this object
	GLMesh mesh;

public:
	GLMesh* getMesh();

	//void assignMesh(GLMesh* newMesh);


	//Commenting out for now - Use only if short on time.
	//friend class Renderer;
};

//Base Procedural Class for creating any Procedural Object
class ProceduralObject : public WorldGenericObject {
private:
	//Seed used to generate object
	long seed;

	//TODO: Incorporate RNG here

	//TODO: Anything else to track state

protected:
	//Function that should be called to instance this object
	//Override and place procedural logic
	virtual void Generate() = 0;

public:
	//Default ctor
	ProceduralObject(); //TODO: Remove and replace with ctor that takes bounds

	//Virt dtor
	virtual ~ProceduralObject();
};