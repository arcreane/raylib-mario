#include "LevelCamera.h"

LevelCamera::LevelCamera()
{
    camera = { 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    cameraOption = 0;
}

void LevelCamera::UpdateCameraCenter(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera.offset = { width / 2.0f, height / 2.0f };
    if (player->GetPosition().x < 650)
    {
        camera.target = { 650,  - 250 };
    }
    else
    {
        camera.target = { player->GetPosition().x, - 250 };
    }
}

void LevelCamera::UpdateCameraCenterGame2(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera.offset = { width / 2.0f, height / 2.0f };
    camera.target = player->GetPosition();
}

void LevelCamera::UpdateCameraCenterInsideMAPmonde1(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera.target = player->GetPosition();
    camera.offset = { width / 2.0f, height / 2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D({ maxX, maxY }, camera);
    Vector2 min = GetWorldToScreen2D({ minX, minY }, camera);

    if (max.x < width) camera.offset.x = width - (max.x - width / 2);
    if (max.y < height) camera.offset.y = height - (max.y - height / 2);
    if (min.x > 0) camera.offset.x = width / 2 - min.x;
    if (min.y > 0) camera.offset.y = height / 2 - min.y;
}

void LevelCamera::UpdateCameraCenterSmoothFollow(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera.offset = { width / 2.0f, height / 2.0f };
    Vector2 diff = Vector2Subtract(player->GetPosition(), camera.target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        camera.target = Vector2Add(camera.target, Vector2Scale(diff, speed * delta / length));
    }
}

void LevelCamera::UpdateCameraEvenOutOnLanding(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera.offset = { width / 2.0f, height / 2.0f };
    camera.target.x = player->GetPosition().x;

    if (eveningOut)
    {
        if (evenOutTarget > camera.target.y)
        {
            camera.target.y += evenOutSpeed * delta;

            if (camera.target.y > evenOutTarget)
            {
                camera.target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
        else
        {
            camera.target.y -= evenOutSpeed * delta;

            if (camera.target.y < evenOutTarget)
            {
                camera.target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
    }
    else
    {
        if (player->GetCanJump() && (player->GetVUnitSpeed() == 0) && (player->GetPosition().y != camera.target.y))
        {
            eveningOut = 1;
            evenOutTarget = player->GetPosition().y;
        }
    }
}

void LevelCamera::UpdateCameraPlayerBoundsPush(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D({ (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height }, camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D({ (1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height }, camera);
    camera.offset = { (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height };

    if (player->GetPosition().x < bboxWorldMin.x) camera.target.x = player->GetPosition().x;
    if (player->GetPosition().y < bboxWorldMin.y) camera.target.y = player->GetPosition().y;
    if (player->GetPosition().x > bboxWorldMax.x) camera.target.x = bboxWorldMin.x + (player->GetPosition().x - bboxWorldMax.x);
    if (player->GetPosition().y > bboxWorldMax.y) camera.target.y = bboxWorldMin.y + (player->GetPosition().y - bboxWorldMax.y);
}

void LevelCamera::cameraUpdaters(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    switch (this->cameraOption)
    {
    case 0:
        UpdateCameraCenter(player, envItems, envItemsLength, delta, width, height);
        break;
    case 1:
        UpdateCameraCenterGame2(player, envItems, envItemsLength, delta, width, height);
        break;
    case 2:
        UpdateCameraCenterInsideMAPmonde1(player, envItems, envItemsLength, delta, width, height);
        break;
    case 3:
        UpdateCameraCenterSmoothFollow(player, envItems, envItemsLength, delta, width, height);
        break;
    case 4:
        UpdateCameraEvenOutOnLanding(player, envItems, envItemsLength, delta, width, height);
        break;
    case 5:
        UpdateCameraPlayerBoundsPush(player, envItems, envItemsLength, delta, width, height);
        break;
    default:
        UpdateCameraCenter(player, envItems, envItemsLength, delta, width, height);
    }
}

int LevelCamera::GetCameraOption()
{
    return cameraOption;
}

Camera2D LevelCamera::GetCamera()
{
    return camera;
}

Vector2 LevelCamera::GetCameraOffset()
{
    return camera.offset;
}

Vector2 LevelCamera::GetCameraTarget()
{
    return camera.target;
}

float LevelCamera::GetCameraRotation()
{
    return camera.rotation;
}

float LevelCamera::GetCameraZoom()
{
    return camera.zoom;
}

void LevelCamera::SetCameraOption(int cameraOption)
{
    this->cameraOption = cameraOption;
}

void LevelCamera::SetCamera(Camera2D camera)
{
    this->camera = camera;
}

void LevelCamera::SetCameraOffset(Vector2 offset)
{
    this->camera.offset = offset;
}

void LevelCamera::SetCameraTarget(Vector2 target)
{
    this->camera.target = target;
}

void LevelCamera::SetCameraRotation(float rotation)
{
    this->camera.rotation = rotation;
}

void LevelCamera::SetCameraZoom(float zoom)
{
    this->camera.zoom = zoom;
}
