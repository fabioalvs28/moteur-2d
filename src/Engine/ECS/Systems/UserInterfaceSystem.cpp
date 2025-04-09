#include "pch.h"
#include "UserInterfaceSystem.h"

#include <iostream>
#include <ranges>

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
    for (auto const& entities : std::views::values(globalEC->mEntitiesByLayer))
    {
        for(Entity* entity : *entities)
        {
            if (entity->Bitmask >= 0)
            {
                Camera* activeCamera = Engine::GetCameraSystem()->GetActiveCamera();
                if (!activeCamera) return;
                TRANSFORM* cameraTransform = activeCamera->GetEntity()->GetTransform();
                if (!entity->IsEnable()) continue;
        
                if (entity->HasComponent<Button>())
                {
                    Button* button = entity->GetComponent<Button>();
                    sf::Vector2f currentPosition = cameraTransform->position + button->ScreenPosition*activeCamera->ZoomFactor;
                    button->UIImage->setPosition(currentPosition);
                    button->UIImage->setScale({activeCamera->ZoomFactor, activeCamera->ZoomFactor});
                    window->Draw(button->UIImage);
                    sf::Vector2f mClickPosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
                    
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
                if (entity->HasComponent<Image>())
                {
                    Image* image = entity->GetComponent<Image>();
                    if (!image->UIImage) continue;
                    image->UIImage->setPosition(cameraTransform->position + image->ScreenPosition*activeCamera->ZoomFactor);
                    image->UIImage->setScale(image->Scale*activeCamera->ZoomFactor);
                    window->Draw(image->UIImage);
                }
                if (entity->HasComponent<ProgressBar>())
                {
                    ProgressBar* progressBar = entity->GetComponent<ProgressBar>();
                    progressBar->BackgroundImage->setPosition(cameraTransform->position + progressBar->ScreenPosition*activeCamera->ZoomFactor);
                    progressBar->BackgroundImage->setScale({ activeCamera->ZoomFactor * progressBar->Scale.x, activeCamera->ZoomFactor * progressBar->Scale.y });
                    progressBar->Bar->setPosition(cameraTransform->position + (progressBar->ScreenPosition + progressBar->BarOffset)*activeCamera->ZoomFactor);
                    progressBar->Bar->setScale({ progressBar->Progress / progressBar->Maximum * activeCamera->ZoomFactor * progressBar->Scale.x, 1.0f * activeCamera->ZoomFactor * progressBar->Scale.y });                    
                    window->Draw(progressBar->BackgroundImage);
                    window->Draw(progressBar->Bar);
                }
                if (entity->HasComponent<Text>())
                {
                    Text* text = entity->GetComponent<Text>();
                    if (!text->WriteText) continue;
                    text->WriteText->setPosition(cameraTransform->position + text->ScreenPosition*activeCamera->ZoomFactor);
                    window->Draw(text->WriteText);
                }
            }
        }
    }
}