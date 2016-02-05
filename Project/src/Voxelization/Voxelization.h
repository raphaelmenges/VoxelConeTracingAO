/* Voxelization of scene. Creates list of fragments containing world position, normal and color.
Scene is taken and projected orthogonal. Then, for every triangle the rotation which maximizes
the projection area is found and applied in the geometry shader. In addition, the triangle is
moved to the center of projection to take advantage of the available rasterization area. Results
are save to buffer textures, collection world position, normal and color of each fragment. */

#ifndef VOXELIZATION_H_
#define VOXELIZATION_H_

#include "Scene/Scene.h"
#include "FragmentList.h"

// TODO
// -Create own framebuffer to be independend from screen resoluation

class Voxelization : public Controllable
{
public:

    enum VoxelizeResolutions {RES_256, RES_384, RES_512, RES_1024};
    int VOXELIZE_RESOLUTION = RES_1024;

    Voxelization(App *pApp);
    ~Voxelization();

    void voxelize(glm::vec3 center, float extent, Scene const * pScene, FragmentList *fragmentList);

private:

    // Members
    std::unique_ptr<ShaderProgram> mVoxelizationShader;
    GLuint mAtomicBuffer;

    void resetAtomicCounter() const;
    GLuint readAtomicCounter() const;

    unsigned int determineVoxeliseResolution(int res);

    void fillGui();
};

#endif // VOXELIZATION_H_
