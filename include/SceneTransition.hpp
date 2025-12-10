#ifndef SCENE_TRANSITION_HPP
#define SCENE_TRANSITION_HPP

using namespace std;
/**
 * the window surface is just a represent, not actually is the window
 * use carefully
*/
class SceneTransition
{
public:
    double time; //time in second, the length of the animation
    bool isDone;
    SceneTransition(double time=1);
    virtual void update(double delta_time) = 0;
    virtual void draw() = 0;
    virtual ~SceneTransition();
};

#endif