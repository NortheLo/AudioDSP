//
// Created by louis on 17/06/25.
//

#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "imgui.h"
#include "implot.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "IGuiElement.h"
#include "GuiBridgeSink.h"

template<typename SampleType, size_t BufferSize>
class Gui {
    public:
    Gui(std::shared_ptr<GuiBridgeSink<SampleType, BufferSize>> bridge) : bridgeSink_(std::move(bridge)){
        init();
    }
    ~Gui() {
        clean();
    }

    void addElement(std::shared_ptr<IGuiElement<SampleType>> elem) {
        guiElements_.push_back(std::move(elem));
    }


    void loop() {
        if (guiElements_.empty()) {
            std::cerr << "No gui elements found" << std::endl;
            return;
        }

        while (!glfwWindowShouldClose(window_)) {
            auto data = bridgeSink_->getBufferCopy();
            glfwPollEvents();

            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Plot");

            for (auto& elem : guiElements_) {
                elem->draw(data.data(), data.size());
            }

            ImGui::End();

            // Render
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window_, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window_);
        }
    }

    private:
        void init() {
            if (!glfwInit()){
                std::cerr << "Failed to initialize GLFW" << std::endl;
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // or GLFW_OPENGL_COMPAT_PROFILE
            #ifdef __APPLE__
                        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
            if (!window_) {
                glfwTerminate();
                std::cerr << "Could not create window!" << std::endl;
            }
            glfwMakeContextCurrent(window_);
            glfwSwapInterval(1); // Enable vsync

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImPlot::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;

            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL(window_, true);
            ImGui_ImplOpenGL3_Init("#version 330 core");
        }

    void clean() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImPlot::DestroyContext();
            ImGui::DestroyContext();
            glfwDestroyWindow(window_);
            glfwTerminate();
        }
    std::vector<std::shared_ptr<IGuiElement<SampleType>>> guiElements_;
    std::shared_ptr<GuiBridgeSink<SampleType, BufferSize>> bridgeSink_;
    GLFWwindow* window_ = nullptr;

    int width_ = 1280;
    int height_ = 720;
    std::string title_ = "Audio Plot";
};