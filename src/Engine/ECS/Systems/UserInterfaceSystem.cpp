#include "pch.h"
#include "UserInterfaceSystem.h"

#include "CameraSystem.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/ui/Button.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/ui/ProgressBar.h"
#include "ECS/Components/ui/Text.h"
#include "Inputs/Mouse.h"
#include "Render/RenderWindow.h"
#include "Render/Sprite.h"
#include "Utils/Debug.h"

UserInterfaceSystem::UserInterfaceSystem(RenderWindow* window): window(window) {}

void UserInterfaceSystem::Render(ECS* globalEC)
{
    Camera* activeCamera = Engine::GetCameraSystem()->GetActiveCamera();
    if (!activeCamera) return;
    TRANSFORM* cameraTransform = activeCamera->GetEntity()->GetTransform();
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if(!globalEC->GetEntity(i)->IsEnable()) continue;
        if (globalEC->HasComponent<Button>(i))
        {
            Button* button = globalEC->GetComponent<Button>(i);
            sf::Vector2f currentPosition = cameraTransform->position + button->ScreenPosition*activeCamera->ZoomFactor;
            button->UIImage->setPosition(currentPosition);
            button->UIImage->setScale({activeCamera->ZoomFactor, activeCamera->ZoomFactor});
            window->Draw(button->UIImage);
            sf::Vector2f mClickPosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            
#ifdef _DEBUG
            button->shape->setPosition(currentPosition*activeCamera->ZoomFactor);
            window->draw(*button->shape);
#endif
            
            if (mClickPosition.x > currentPosition.x
                && mClickPosition.x < currentPosition.x + button->Width
                && mClickPosition.y > currentPosition.y
                && mClickPosition.y < currentPosition.y + button->Height
                && GetButton(Mouse::Left)) {
                button->CallBack();
                button->IsClicked = true;
            }

            if(!button->IsClicked)
                button->IsReleased = true;
            if (button->IsReleased)
            {
                button->ReleaseCallback();
            }
            button->IsReleased = false;
            button->IsClicked = false;
        }
        if (globalEC->HasComponent<Image>(i))
        {
            Image* image = globalEC->GetComponent<Image>(i);
            image->UIImage->setPosition(cameraTransform->position + image->ScreenPosition*activeCamera->ZoomFactor);
            image->UIImage->setScale(image->Scale*activeCamera->ZoomFactor);
            window->Draw(image->UIImage);
        }
        if (globalEC->HasComponent<ProgressBar>(i))
        {
            ProgressBar* progressBar = globalEC->GetComponent<ProgressBar>(i);
            progressBar->BackgroundImage->setPosition(cameraTransform->position + progressBar->ScreenPosition*activeCamera->ZoomFactor);
            progressBar->BackgroundImage->setScale({activeCamera->ZoomFactor * progressBar->Scale.x, activeCamera->ZoomFactor * progressBar->Scale.y});
            progressBar->Bar->setPosition(cameraTransform->position + (progressBar->ScreenPosition + progressBar->BarOffset)*activeCamera->ZoomFactor);
            progressBar->Bar->setScale({progressBar->Progress/progressBar->Maximum*activeCamera->ZoomFactor *  progressBar->Scale.x, 1.0f*activeCamera->ZoomFactor * progressBar->Scale.y});
            window->Draw(progressBar->BackgroundImage);
            window->Draw(progressBar->Bar);
        }
        if (globalEC->HasComponent<Text>(i))
        {
            Text* text = globalEC->GetComponent<Text>(i);
            text->WriteText->setPosition(cameraTransform->position + text->ScreenPosition*activeCamera->ZoomFactor);
            window->Draw(text->WriteText);
        }
    }
}
