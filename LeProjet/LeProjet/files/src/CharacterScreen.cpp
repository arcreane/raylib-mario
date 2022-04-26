#include "CharacterScreen.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

CharacterScreen::CharacterScreen(LevelManager& levelManager)
    :Level(LevelName::characterScreen, LevelName::menu, levelManager, "Menu"), name{"\0"}
{
    validTexture = LoadTexture("../LeProjet/LeProjet/files/img/valider.png");
    positionClick = { 0.0f, 0.0f };
    letterCount = 0;
    textBox = { 450, 100, 550, 50 };
    mouseOnText = false;
}

void CharacterScreen::InitLevel()
{
}

void CharacterScreen::UpdateLevel()
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
    else mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < 20))
            {
                name[letterCount] = (char)key;
                name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            name[letterCount] = '\0';
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText) framesCounter++;
    else framesCounter = 0;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        positionClick = GetMousePosition();
        if (positionClick.x > 545 && positionClick.x < 660)
        {
            if (positionClick.y < 650 && positionClick.y > 550)
            {
                //printf("VALIDE\n");

                fstream my_file;
                my_file.open("../LeProjet/LeProjet/files/sauvegarde.txt", ios::out);
                if (!my_file) {
                    cout << "File not created!";
                }
                else {
                    cout << "File created successfully!" << endl;
                    my_file << name << endl;
                    my_file << "1" << endl;
                    my_file << "1" << endl;
                    my_file << "0" << endl;
                    my_file.close();
                }
                levelManager->LoadLevel(LevelName::menu);
            }
        }
    }

}

void CharacterScreen::DrawLevel()
{
    /*char name[13] = "\0";
    Rectangle textBox = { 100, 120, 40, 50 };
    bool mouseOnText = false;*/


    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Nom du joueur :", 100, 100, 40, BLACK);

    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
    else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

    DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

    DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 20), 800, 200, 20, DARKGRAY);
    if (mouseOnText)
    {
        if (letterCount < 20)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
        }
        else DrawText("Nombre limite de charactères atteint, vous pouvez en supprimer", 450, 150, 20, GRAY);
    }
    //printf("%s \n", name);
    DrawRectangle(580, 400, 50, 50, RED);
    //DrawRectangle(700, 400, 50, 50, RED);
    DrawText("Mario", 550, 300, 40, BLACK);
    //DrawText("DK", 700, 300, 40, BLACK);
    DrawTexture(validTexture, 550, 550, WHITE); // Draw button frame

    EndDrawing();
}


