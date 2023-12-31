#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    FAST_FORWARD
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.5f;
const float SENSITIVITY = 0.1f;
const float DISTANCE = 4.5f;
const float ZOOM = 45.0f;

bool is_FPS = true;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    float Gravity = 9.81f;
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 PlayerPos;
    glm::vec3 cameraHeight;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float DistanceFromPlayer;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 1.5f, 3.5f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), PlayerPos(glm::vec3(0.0f, 0.0f, -1.0f)), cameraHeight(glm::vec3(0.0f, 1.5f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), DistanceFromPlayer(DISTANCE), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), PlayerPos(glm::vec3(0.0f, 0.0f, -1.0f)), cameraHeight(glm::vec3(0.0f, 1.0f, 0.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        if (is_FPS) {
            return glm::lookAt(Position, Position + Front, Up);
        }
        else {
            return glm::lookAt(Position, PlayerPos, Up);
        }
    }

    glm::vec3 GetCameraPos()
    {
        return Position;
    }

    glm::vec3 GetPlayerPos()
    {
        return PlayerPos;
    }
    //switching from tps to fps
    void ChangeView() {
        updateCameraVectors();
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        float velocitywow = velocity * 7;

        if (direction == FAST_FORWARD) {
            if (is_FPS) {
                Position += Front * velocitywow;
                PlayerPos.x += (Front.x * velocitywow);
                PlayerPos.z += (Front.z * velocitywow);
            }
            else {
                PlayerPos += Front * velocitywow;
            }
        }
        if (direction == FORWARD) {
            if (is_FPS) {
                Position += Front * velocity;
                PlayerPos.x += (Front.x * velocity);
                PlayerPos.z += (Front.z * velocity);
            }
            else {
                PlayerPos += Front * velocity;
            }
        }
        if (direction == BACKWARD) {
            if (is_FPS) {
                Position -= Front * velocity;
                PlayerPos.x -= (Front.x * velocity);
                PlayerPos.z -= (Front.z * velocity);
            }
            else {
                PlayerPos -= Front * velocity;
            }
        }
        if (direction == LEFT) {
            if (is_FPS) {
                Position -= Right * velocity;
                PlayerPos.x -= (Right.x * velocity);
                PlayerPos.z -= (Right.z * velocity);
            }
            else {
                PlayerPos -= Right * velocity;
            }
        }
        if (direction == RIGHT) {
            if (is_FPS) {
                Position += Right * velocity;
                PlayerPos.x += (Right.x * velocity);
                PlayerPos.z += (Right.z * velocity);
            }
            else {
                PlayerPos += Right * velocity;
            }
        }
        if (is_FPS) {
            Position.y = 0.5f;
            if (Position.x > 23) {
                Position.x = 23;
            }
            if (Position.x < -23) {
                Position.x = -23;
            }
            if (Position.z > 23) {
                Position.z = 23;
            }
            if (Position.z < -23) {
                Position.z = -23;
            }
        }
        else {
            if (PlayerPos.x > 23) {
                PlayerPos.x = 23;
            }
            if (PlayerPos.x < -23) {
                PlayerPos.x = -23;
            }
            if (PlayerPos.z > 23) {
                PlayerPos.z = 23;
            }
            if (PlayerPos.z < -23) {
                PlayerPos.z = -23;
            }
            Position = (PlayerPos + cameraHeight) - DistanceFromPlayer * Front;
        }

    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (is_FPS) {
                if (Pitch > 89.0f)
                    Pitch = 89.0f;
                if (Pitch < -89.0f)
                    Pitch = -89.0f;
            }
            else {
                if (Pitch > PITCH)
                    Pitch = PITCH;
                if (Pitch < PITCH)
                    Pitch = PITCH;
            }
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 30.0f)
            Zoom = 30.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        if (!is_FPS) {
            Position = (PlayerPos + cameraHeight) - DistanceFromPlayer * Front;
        }
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};
#endif

