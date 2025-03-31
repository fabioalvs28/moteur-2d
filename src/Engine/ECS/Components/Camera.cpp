#include "pch.h"
#include "Camera.h"

Camera::Camera(Entity* entity, int display) : Component(entity), DisplayScreen(display) { }

void Camera::Serialize(json& json)
{
    json["displayScreen"] = DisplayScreen;
    json["ZoomFactor"] = ZoomFactor;  
}

int Camera::GetBitmask()
{
    return BITMASK;
}

void Camera::Deserialize(json& json)
{
    this->DisplayScreen = json["displayScreen"];
    this->ZoomFactor = json["ZoomFactor"] ;

}