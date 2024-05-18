#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/freeglut.h>


//insert code for global variables here

float ballRadius = 0.05; // Used in drawBall function
float ballSpeed = 0.01;
float rectLength = 0.2;
float rectWidth = 0.2;
int score = 0;
bool gameOver = false; // Initialize as false
bool gameWon = false; // Initialize as false
float playerX = 0.0; // Initialize player position
float coinX, coinY; // Initialize coin positions
bool isGoldCoin = true;


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawRectangle() {
    glBegin(GL_POLYGON);
    glVertex2f(rectLength - rectWidth /2, -0.9);
    glVertex2f(rectLength + rectWidth /2, -0.9);
    glVertex2f(rectLength + rectWidth /2, -0.85);
    glVertex2f(rectLength - rectWidth /2, -0.85);
    glEnd();
    
}

void drawBall(float x, float y, bool isGoldCoin) {
    if (isGoldCoin) {
        glColor3f(1.0, 0.84, 0.0); // Gold color (R, G, B)
    } else {
        glColor3f(1.0, 0.0, 0.0); // Red color (R, G, B)
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i += 10) {
        float angle = i * 3.14159265 / 180.0;
        glVertex2f(x + ballRadius * cos(angle), y + ballRadius * sin(angle));
    }
    glEnd();
}


void drawScore() {
    //insert code here
    glRasterPos2f(-0.9, 0.9);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (gameOver) {
        // Display "Game Over" message
        glRasterPos2f(-0.2, 0.0);
        std::string gameOverText = "Game Over";
        for (char c : gameOverText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
    else if (gameWon) {
        // Display "You Win!" message
        glRasterPos2f(-0.15, 0.0);
        std::string winText = "You Win!";
        for (char c : winText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }
    else {
        // Draw the game elements
        drawRectangle();
        drawBall(coinX, coinY, isGoldCoin);
        drawScore();
    }

    glutSwapBuffers();
}

void update(int value) {
    if (!gameOver && !gameWon) {
        coinY -= ballSpeed;
        if (coinY <= -0.85 && coinX >= rectLength - rectWidth / 2 && coinX <= rectLength + rectWidth / 2) {
            if (isGoldCoin) {
                score++;
            } else {
                score--;
            }
            coinX = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            coinY = 1.0;
            isGoldCoin = (rand() % 2 == 0); // Randomly set coin type
        } else if (coinY < -1.0) {
            coinX = static_cast<float>(rand()) / RAND_MAX * 2 - 1;
            coinY = 1.0;
            isGoldCoin = (rand() % 2 == 0); // Randomly set coin type
        }
        if (score >= 10) {
            gameWon = true;
        }
        if (score < 0) {
            gameOver = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void specialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            rectLength -= 0.1;
            break;
        case GLUT_KEY_RIGHT:
            rectLength += 0.1;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Simple Game");

    glutDisplayFunc(display);
    glutSpecialFunc(specialKey);

    init();
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}
