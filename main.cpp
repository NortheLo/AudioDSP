#include "AudioEngine.h"
#include "SinGenerator.h"
#include "SimplePlot.h"
#include "SimpleDSPProcessor.h"
#include <SupportedFormats.h>

#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <unistd.h>

int main() {
    // Initialize GLFW
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Audio Plot", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui + ImPlot
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Initialize backend bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Your audio code
    auto engine = AudioEngine<float, BUFFERSIZE_128>::create(BufferFormat::Mono);

    auto engine_mono = dynamic_cast<AudioEngineMono<float, BUFFERSIZE_128>*>(engine.get());
    float ampl = 2.f;
    float freq = 440.f;

    auto sinGen = std::make_shared<SinGenerator<float, BUFFERSIZE_128>>(ampl, freq);
    auto proc = std::make_shared<SimpleDSPProcessor<float>>();
    auto plot = std::make_shared<SimplePlot<float>>(BUFFERSIZE_128);

    std::array<float, BUFFERSIZE_128> res{};
    engine_mono->setSource(sinGen);
    engine_mono->addProcessor(proc);
    engine_mono->addSink(plot);

    // GUI loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Your processing and plotting
        engine_mono->processNextBlock(res.data());
        ImGui::Begin("Plot");
        plot->drawPlot();
        ImGui::End();

        // Render
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        usleep(10000); // Slight delay
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImPlot::DestroyContext();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
