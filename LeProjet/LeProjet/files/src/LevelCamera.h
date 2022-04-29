#pragma once
#include "raylib.h"
#include "Player.h"
#include "structures.h"

class LevelCamera
{
private:
	Camera2D camera;
	int cameraOption;

public:
	LevelCamera();
	void UpdateCameraCenter(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
	void UpdateCameraCenterGame2(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
	void UpdateCameraCenterInsideMAPmonde1(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
	void UpdateCameraCenterSmoothFollow(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
	void UpdateCameraEvenOutOnLanding(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
	void UpdateCameraPlayerBoundsPush(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);
	void cameraUpdaters(Player* player, EnvItem* envItems, int envItemsLength, float delta, int width, int height);

	int GetCameraOption();
	Camera2D GetCamera();
	Vector2 GetCameraOffset();
	Vector2 GetCameraTarget();
	float GetCameraRotation();
	float GetCameraZoom();
	void SetCameraOption(int cameraOption);
	void SetCamera(Camera2D camera);
	void SetCameraOffset(Vector2 offset);
	void SetCameraTarget(Vector2 target);
	void SetCameraRotation(float rotation);
	void SetCameraZoom(float zoom);
};
