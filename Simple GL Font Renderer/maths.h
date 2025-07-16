#ifndef MATHS_H
#define MATHS_H
#define GLM_ENABLE_EXPERIMENTAL
#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/gtx/rotate_vector.hpp"
#include "lib/glm/gtx/vector_angle.hpp"
#include "lib/glm/vec2.hpp"
#include "lib/glm/vec3.hpp"
#include "lib/glm/vec4.hpp"
#define lookat(a, b, c) glm::lookAt(a, b, c)
#define perspective(a, b, c, d) glm::perspective(a, b, c, d)
#define ortho(a, b, c, d, e, f) glm::ortho(a, b, c, d, e, f)

inline glm::mat4 createMatrix(int windowWidth, int windowHeight, const glm::vec3& view=glm::vec3(0.0f), const glm::vec3& model=glm::vec3(0.0f))
{
    glm::mat4 m = glm::translate(glm::mat4(1.0f), model);
    glm::mat4 v = glm::translate(glm::mat4(1.0f), view);
    glm::mat4 p = ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
    return (m*v*p);
}

namespace Maths
{
    inline float toRadians(float degrees)
    {
        return degrees * (M_PI / 180.0f);
    }
}

#endif // MATHS_H