#include "raylib.h"
#include "SystemInfo.h"
#include <string>
#include <vector>

int main() {
    const int screenWidth = 500;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Simple Task Manager");
    SetTargetFPS(60);

    SystemInfo sys;
    double lastUpdate = 0.0;
    double cpu = 0.0;
    double ram = 0.0;
    std::vector<ProcessInfo> procs;

    while (!WindowShouldClose()) {
        double currentTime = GetTime();
        if (currentTime - lastUpdate >= 1.0) {
            cpu = sys.getCPUUsage();
            ram = sys.getRAMUsage();
            procs = sys.getProcesses();
            lastUpdate = currentTime;
        }

        BeginDrawing();
        ClearBackground({ 30, 30, 35, 255 });

        DrawText("System Performance", 20, 20, 20, LIGHTGRAY);

        DrawText(TextFormat("CPU Usage: %.1f%%", cpu), 20, 60, 20, WHITE);
        DrawRectangleRounded({ 20, 85, 460, 20 }, 0.3f, 10, { 50, 50, 50, 255 });
        DrawRectangleRounded({ 20, 85, (float)(4.6f * cpu), 20 }, 0.3f, 10, BLUE);

        DrawText(TextFormat("RAM Usage: %.1f%%", ram), 20, 120, 20, WHITE);
        DrawRectangleRounded({ 20, 145, 460, 20 }, 0.3f, 10, { 50, 50, 50, 255 });
        DrawRectangleRounded({ 20, 145, (float)(4.6f * ram), 20 }, 0.3f, 10, GREEN);

        DrawText("Active Processes", 20, 190, 20, LIGHTGRAY);
        DrawRectangleLines(20, 215, 460, 2, GRAY);

        float yPos = 230;
        for (const auto& p : procs) {
            if (yPos > 550) break;
            DrawText(TextFormat("PID: %d", p.pid), 20, (int)yPos, 18, GRAY);
            DrawText(p.name.c_str(), 100, (int)yPos, 18, WHITE);
            DrawText(TextFormat("%.1f%%", p.cpuUsage), 400, (int)yPos, 18, LIGHTGRAY);
            yPos += 30;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
