#include "Camera.h"

void UpdateCameraCenterGame2(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = { width / 2.0f, height / 2.0f };
    camera->target = player->position;
}

void UpdateCameraCenter(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera->offset = { width / 2.0f, height / 2.0f };
    if (player->position.x < 650) 
    {
        camera->target = { 650, player->position.y - 250 };
    }else
    {
        camera->target = { player->position.x, player->position.y - 250 };
    }
   
}

void UpdateCameraCenterInsideMAPmonde1(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = { width / 2.0f, height / 2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D({ maxX, maxY }, *camera);
    Vector2 min = GetWorldToScreen2D({ minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width / 2);
    if (max.y < height) camera->offset.y = height - (max.y - height / 2);
    if (min.x > 0) camera->offset.x = width / 2 - min.x;
    if (min.y > 0) camera->offset.y = height / 2 - min.y;
}

void UpdateCameraCenterSmoothFollow(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = { width / 2.0f, height / 2.0f };
    Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed * delta / length));
    }
}

void UpdateCameraEvenOutOnLanding(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static float evenOutSpeed = 700;
    static int eveningOut = false;
    static float evenOutTarget;

    camera->offset = { width / 2.0f, height / 2.0f };
    camera->target.x = player->position.x;

    if (eveningOut)
    {
        if (evenOutTarget > camera->target.y)
        {
            camera->target.y += evenOutSpeed * delta;

            if (camera->target.y > evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
        else
        {
            camera->target.y -= evenOutSpeed * delta;

            if (camera->target.y < evenOutTarget)
            {
                camera->target.y = evenOutTarget;
                eveningOut = 0;
            }
        }
    }
    else
    {
        if (player->canJump && (player->speed == 0) && (player->position.y != camera->target.y))
        {
            eveningOut = 1;
            evenOutTarget = player->position.y;
        }
    }
}

void UpdateCameraPlayerBoundsPush(Camera2D* camera, Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height)
{
    static Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D({ (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D({ (1 + bbox.x) * 0.5f * width, (1 + bbox.y) * 0.5f * height }, *camera);
    camera->offset = { (1 - bbox.x) * 0.5f * width, (1 - bbox.y) * 0.5f * height };

    if (player->position.x < bboxWorldMin.x) camera->target.x = player->position.x;
    if (player->position.y < bboxWorldMin.y) camera->target.y = player->position.y;
    if (player->position.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (player->position.x - bboxWorldMax.x);
    if (player->position.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (player->position.y - bboxWorldMax.y);
}


// Store pointers to the multiple update camera functions
void (*cameraUpdaters[])(Camera2D*, Player*, EnvItem*, int, float, int, int) = {
    UpdateCameraCenter,
    UpdateCameraCenterGame2,
    UpdateCameraCenterInsideMAPmonde1,
    UpdateCameraCenterSmoothFollow,
    UpdateCameraEvenOutOnLanding,
    UpdateCameraPlayerBoundsPush
};