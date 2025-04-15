// FactoryMethod.hpp
#ifndef FACTORY_METHOD_HPP
#define FACTORY_METHOD_HPP

#include <iostream>
#include <memory>
#include <functional>
#include <stdexcept>
#include <string>

// ----------- Product Interface --------------
class Button {
public:
    virtual void render() const = 0;
    virtual void onClick(std::function<void()> f) = 0;
    virtual ~Button() = default;
};

// ----------- Concrete Product: WindowsButton --------------
class WindowsButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering Windows-style button.\n";
    }

    void onClick(std::function<void()> f) override {
        std::cout << "Binding Windows OS click event.\n";
        f();
    }
};

// ----------- Concrete Product: HTMLButton --------------
class HTMLButton : public Button {
public:
    void render() const override {
        std::cout << "Rendering HTML button.\n";
    }

    void onClick(std::function<void()> f) override {
        std::cout << "Binding web click event.\n";
        f();
    }
};

// ----------- Creator: Dialog --------------
class Dialog {
public:
    virtual std::unique_ptr<Button> createButton() const = 0;

    void render() const {
        auto button = createButton();
        button->onClick([]() {
            std::cout << "Dialog closed.\n";
        });
        button->render();// Calls the render method on the button, printing the button's message
    }

    virtual ~Dialog() = default;
};

// ----------- Concrete Creator: WindowsDialog --------------
class WindowsDialog : public Dialog {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
};

// ----------- Concrete Creator: WebDialog --------------
class WebDialog : public Dialog {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<HTMLButton>();
    }
};

// ----------- Application Logic --------------
class Application {
    std::unique_ptr<Dialog> dialog;

public:
    void initialize(const std::string& os) {
        if (os == "Windows")
            dialog = std::make_unique<WindowsDialog>();
        else if (os == "Web")
            dialog = std::make_unique<WebDialog>();
        else
            throw std::runtime_error("Unknown OS");
    }

    void main() const {
        if (dialog)
            dialog->render();
    }
};

#endif // FACTORY_METHOD_HPP
