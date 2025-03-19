﻿#include "pch.h"
#include "RenderSystem.h"

#include "CameraSystem.h"
#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "ECS/Components/Collider2D.h"
#include "ECS/Components/ui/Image.h"
#include "Render/RenderWindow.h"

RenderSystem::RenderSystem(RenderWindow* window): window(window) {}

void RenderSystem::Render(ECS* globalEC)
{
    TRANSFORM* cameraTransform = Engine::GetCameraSystem()->GetActiveCamera();
    for (int i = 0; i < globalEC->mEntityCount; i++)
    {
        if (globalEC->HasComponent<SpriteRenderer>(i))
        {
            SpriteRenderer* renderer = globalEC->GetComponent<SpriteRenderer>(i);
            sf::Vector2f size = renderer->Image->getGlobalBounds().size;
            size /= 2.0f;
            TRANSFORM* transform = renderer->GetEntity()->GetTransform();
            renderer->Image->setPosition(transform->position);
            renderer->Image->setScale(transform->scale);
            renderer->Image->setRotation(transform->rotation);
            
            renderer->Image->setOrigin(transform->position + size);
            if (!renderer->RendererShader)
                window->Draw(renderer->Image);
            else
                window->Draw(renderer->Image, renderer->RendererShader);
        } else if (globalEC->HasComponent<Image>(i))
        {
            Image* image = globalEC->GetComponent<Image>(i);
            image->UIImage->setPosition(cameraTransform->position);
            window->Draw(image->UIImage);
        }

        if(globalEC->HasComponent<Collider2D>(i))
        {
            Collider2D* coll = globalEC->GetComponent<Collider2D>(i);
            window->Draw(coll->GetShape());
        }
    }
}