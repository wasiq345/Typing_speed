#include <raylib.h>
#include <iostream>
#include<vector>
using namespace std;

class TypingSpeed
{
    vector<string> word;
    string SelectedWord;
    string TypedWord;
    float speed;
    Vector2 position;
    Sound wrong, correct;
    int i, score = 0;

public: 
    TypingSpeed();
    void MoveDownward();
    void CheckWord();
    void Draw();
    void Update();
    int RandomIndex();
    int getScore();
    void reset();
};

TypingSpeed :: TypingSpeed()
{
    wrong = LoadSound("beep.wav");
    correct = LoadSound("correct.wav");
    speed = 2.5;
    position = {350, 20};
    word = {"game", "mobile", "sunday", "monday", "tuesday", "wednesday", "thursday", "lion", "tiger", "camel", "laptop",
           "cricket", "ronaldo", "messi", "infinity", "word", "speed", "infrastructure", "military", "pakistan", "india", "base",
           "pythagoras", "theorem", "calculus", "name", "physics", "mathematics", "undefine", "drones", "navalships", "anime"};  
   SelectedWord = word[RandomIndex()];
}

int TypingSpeed :: RandomIndex()
{
   int index;
   index = rand() % word.size();
   i = 0;
   TypedWord.clear();
   return index;
}

void TypingSpeed :: MoveDownward()
{
    position.y += speed;
    if(position.y > GetScreenHeight() - 20)
    {
        position.y = 10;
        SelectedWord = word[RandomIndex()];
        score -= 5;
    }
}

void TypingSpeed :: Draw()
{
   DrawText(SelectedWord.c_str(), position.x, position.y, 30, WHITE);
   DrawText(to_string(score).c_str(),120, 20, 25, WHITE);
   DrawText(to_string(speed).c_str(), 550, 22,  20, WHITE);
   DrawText("Speed : ", 450, 20, 22, SKYBLUE);
   DrawText("Score : ", 20, 20, 22, SKYBLUE);

}

void TypingSpeed :: CheckWord()
{
    if(TypedWord == SelectedWord)
    {
        PlaySound(correct);
        TypedWord.clear();
        speed += 0.2;
        score += 5;
        position.y = 10;
        SelectedWord = word[RandomIndex()];
    }
}

void TypingSpeed :: Update()
{
    char c = GetCharPressed();
    if(isalpha(c))
    {
      if( c == SelectedWord[i])
      {
        ClearBackground(GREEN);
        TypedWord += c;
        i++;
      }
      else
        {
          ClearBackground(RED);
          PlaySound(wrong);
        }
    }
}

int TypingSpeed :: getScore()
{
    return score;
}

void TypingSpeed :: reset()
{
    score = 0;
    TypedWord.clear();
    speed = 2.5;
}


int main() {

    int screenWidth = 800;
    int screenHeight = 600;
    InitAudioDevice();
    
    TypingSpeed t1;
    srand(time(NULL));

    InitWindow(screenWidth, screenHeight, "TypingSpeed");
    SetTargetFPS(60);

bool gameOverSoundPlayed = false;
float gameOverStartTime = 0.0f;
Sound game_over = LoadSound("game_over.wav");
enum GameState { MENU, PLAYING, GAME_OVER };
GameState currentState = MENU;


while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground((Color){ 10, 10, 25, 255 });  

    switch(currentState) {
        case MENU:
            DrawText("Speed Test", 270, 30, 50, GOLD);
            DrawText("Press Enter to play", 20, 150, 18, SKYBLUE);
            if (IsKeyPressed(KEY_ENTER)) {
                currentState = PLAYING;
            }
            break;

        case PLAYING:
            t1.Draw();
            t1.CheckWord();
            t1.MoveDownward();
            t1.Update();

            if(t1.getScore() < 0) {
                currentState = GAME_OVER;
                gameOverStartTime = GetTime();
                gameOverSoundPlayed = false;
            }
            break;

        case GAME_OVER:
            ClearBackground(RED);
            DrawText("Game Over", 300, screenHeight / 2 - 30, 40, BLACK);

            if(!gameOverSoundPlayed) {
                PlaySound(game_over);
                gameOverSoundPlayed = true;
            }

            if (GetTime() - gameOverStartTime > 3.0f) {
                currentState = MENU;  
                t1.reset();         
            }
            break;
    }

    EndDrawing();
}
}
