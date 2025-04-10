#include "pch.h"
#include "RenderSystem.h"

#include <ranges>

#include "CameraSystem.h"
#include "Transform.h"
#include "ECS/ECS.h"
#include "../Components/SpriteRenderer.h"
#include "ECS/Components/Collider2D.h"
#include "ECS/Components/Camera.h"
#include "ECS/Components/Colliders/AABBCollider.h"
#include "ECS/Components/Colliders/CircleCollider.h"
#include "ECS/Components/ui/Image.h"
#include "ECS/Components/Animator.h"
#include "Render/RenderWindow.h"

RenderSystem::RenderSystem(RenderWindow* window): window(window) {}

void RenderSystem::Render(ECS* globalEC)
{
    TRANSFORM* cameraTransform = Engine::GetCameraSystem()->GetActiveCamera()->GetEntity()->GetTransform();
    for (auto const& entity : std::views::values(globalEC->mEntitiesByLayer))
    {
        for(Entity* entities : *entity)
        {
            if (globalEC->HasComponent<SpriteRenderer>(*entities->GetIndex()))
            {
                SpriteRenderer* renderer = globalEC->GetComponent<SpriteRenderer>(*entities->GetIndex());
                sf::Vector2f size = renderer->Image->getGlobalBounds().size * 0.5f;
                TRANSFORM* transform = renderer->GetEntity()->GetTransform();
                renderer->Image->setPosition(transform->position - size);
                renderer->Image->setScale(transform->scale);
                renderer->Image->setRotation(transform->rotation);
            
                if (!renderer->RendererShader)
                    window->Draw(renderer->Image);
                else
                    window->Draw(renderer->Image, renderer->RendererShader);
            }

            if(globalEC->HasComponent<CircleCollider>(*entities->GetIndex()) || globalEC->HasComponent<AABBCollider>(*entities->GetIndex()))
            {
                Collider2D* coll = globalEC->GetComponent<Collider2D>(*entities->GetIndex());
                window->Draw(coll->GetShape());
            }
            if (globalEC->HasComponent<Animator>(*entities->GetIndex()))
            {
                Animator* animator = globalEC->GetComponent<Animator>(*entities->GetIndex());

                if (!animator) continue;
                animator->m_elapsedTime += Engine::GetDeltaTime();

                sf::Vector2f size = animator->mp_SpriteSheet->getGlobalBounds().size * 0.5f;
                TRANSFORM* transform = animator->GetEntity()->GetTransform();

                animator->mp_SpriteSheet->setOrigin(sf::Vector2f(animator->mp_SpriteSheet->getTextureRect().size.x / 2, animator->mp_SpriteSheet->getTextureRect().size.y / 2));
                animator->mp_SpriteSheet->setRotation(transform->rotation);
                animator->mp_SpriteSheet->setScale(transform->scale);
                animator->mp_SpriteSheet->setPosition(transform->position);


                if (animator->m_elapsedTime >= animator->m_timeBetween)
                {
                    animator->m_elapsedTime = 0;

                    animator->m_actualIndex++;
                    if (animator->m_actualIndex >= animator->mp_SpriteSheet->SpriteCount)
                    {
                        animator->m_actualIndex = 0;
                    }

                    animator->mp_SpriteSheet->SetSprite(animator->m_actualIndex);
                }

                window->Draw(animator->mp_SpriteSheet);
            }
        }
    }
}