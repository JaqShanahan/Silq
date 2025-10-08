# ⚡ Silq

![Platform](https://img.shields.io/badge/platform-Windows-blue)
![Language](https://img.shields.io/badge/language-C++-blueviolet)
![License](https://img.shields.io/badge/license-MIT-green)
![Build](https://img.shields.io/badge/build-passing-brightgreen)
![UI](https://img.shields.io/badge/UI-Native-lightgrey)

**Silq** is a fast, minimalist terminal emulator built for **Windows**, designed with **platform-native UI** for a seamless, integrated experience.  
It’s lightweight, elegant, and crafted to be as fast as your workflow — no unnecessary layers, no Electron, just pure native performance.

> ⚡ **Designed for speed. Built for Windows. Minimal by nature.**

---

## 🧭 Table of Contents

1. [Features](#-features)  
2. [Screenshots](#-screenshots)  
3. [Installation](#-installation)  
4. [Usage](#-usage)  
5. [Configuration](#-configuration)  
6. [Architecture Overview](#-architecture-overview)  
7. [Performance Goals](#-performance-goals)  
8. [Contributing](#-contributing)  
9. [Known Issues](#-known-issues)  
10. [License](#-license)  
11. [Roadmap](#-roadmap)  
12. [Credits](#-credits)

---

## ✨ Features

- 🚀 **Ultra-fast startup and rendering**
- 🪟 **Native Windows UI** — lightweight, efficient, and modern
- 💻 **Supports any shell** (PowerShell, CMD, Git Bash, WSL, etc.)
- 🧠 **Written in modern C++20** for performance and safety
- 🧩 **Simple, clean interface** — minimal distractions, just your terminal
- 🔤 **Future theming support** for light/dark modes and custom colors
- ⌨️ **Planned keybindings** and tabbed sessions
- 🧱 **Low memory footprint** and native DPI awareness

---

## 🖼️ Screenshots

> Coming soon — screenshots and UI previews will be added as Silq’s design stabilizes.

---

## ⚙️ Installation

### 🧩 Option 1: Download Prebuilt Executable

1. Go to the [Releases](https://github.com/JaqShanahan/Silq/releases) page.  
2. Download the latest `Silq.zip` or `.exe`.  
3. Extract (if needed).  
4. Run **Silq.exe** — no installation required.

---

### 🛠️ Option 2: Build from Source

#### Requirements
- **Windows 10 or later**
- **Visual Studio 2022** (with *Desktop development with C++*)
- **CMake ≥ 3.20**
- **Git**

#### Steps

```bash
# Clone the repository
git clone https://github.com/JaqShanahan/Silq.git
cd Silq

# Configure the build
cmake -S . -B build

# Build in Release mode
cmake --build build --config Release

# Run Silq
build\Release\Silq.exe
```

---

## 💻 Usage

Once installed or built, simply launch **Silq.exe**.

### Example Commands

```bash
# Launch with PowerShell
silq.exe --shell powershell

# Launch with WSL
silq.exe --shell wsl

# Launch with a custom startup command
silq.exe --cmd "python --version"
```

### Keyboard Shortcuts (planned)
| Shortcut | Action |
|-----------|---------|
| `Ctrl + Shift + T` | Open new tab |
| `Ctrl + Shift + W` | Close tab |
| `Ctrl + + / -` | Increase / decrease font size |
| `Ctrl + Shift + C / V` | Copy / paste |
| `Alt + Enter` | Toggle fullscreen |

---

## ⚙️ Configuration

> Configuration support is under development.  
> Planned configuration file: `silq.json` (stored in `%AppData%\Silq`)

Example configuration (planned):

```json
{
  "shell": "powershell",
  "font": "Cascadia Code",
  "font_size": 14,
  "theme": "dark",
  "opacity": 0.95,
  "startup_directory": "C:\\Users\\YourName"
}
```

---

## 🧩 Architecture Overview

Silq is written in **modern C++**, using **native Windows APIs** and lightweight abstractions.  
It avoids heavy frameworks like Qt or Electron to keep performance tight.

### Core Modules

| Module | Description |
|---------|-------------|
| **Core** | Main entry point, process management, event loop |
| **Renderer** | Handles text rendering and font drawing |
| **Terminal** | Manages shell I/O, buffer, and resizing |
| **UI** | Handles native window creation, input, and layout |
| **Config** | Loads/saves settings (planned) |

### Dependencies
- Windows API / Win32
- DirectWrite (for font rendering)
- CMake build system
- STL (no external runtime dependencies)

---

## ⚡ Performance Goals

| Metric | Target |
|---------|--------|
| Startup time | < 100 ms |
| Memory usage (idle) | < 40 MB |
| Frame latency | < 8 ms |
| Input latency | Virtually instant |
| Binary size | < 10 MB (Release) |

---

## 🤝 Contributing

Contributions are welcome!

1. Fork the repository  
2. Create a feature branch (`feature/add-tabs`, `fix/input-lag`)  
3. Commit your changes  
4. Push to your fork  
5. Open a Pull Request  

### Guidelines
- Follow consistent C++ naming and style conventions  
- Keep dependencies minimal  
- Write clear, descriptive commit messages  
- Test thoroughly before submitting  

---

## 🐛 Known Issues

| Issue | Status |
|--------|---------|
| Missing configuration support | Planned |
| No tabbed interface yet | In development |
| Limited shell detection | Pending improvement |

---

## 🪪 License

Silq is licensed under the **MIT License**.  
See the [LICENSE](LICENSE) file for details.

---

## 🗺️ Roadmap

- [ ] Add tabbed interface  
- [ ] Implement configuration system  
- [ ] Introduce color themes  
- [ ] Add custom keybindings  
- [ ] Add GPU-accelerated rendering  
- [ ] Extend cross-platform support (macOS/Linux)  
- [ ] Plugin API or scripting hooks  
- [ ] Settings UI  

---

## 🙌 Credits

- Developed by **[Jaq Shanahan](https://github.com/JaqShanahan)**  
- Built with ❤️ in C++  
- Inspired by projects like:
  - [Windows Terminal](https://github.com/microsoft/terminal)
  - [Alacritty](https://github.com/alacritty/alacritty)
  - [Hyper](https://github.com/vercel/hyper)

---

**Silq** — fast, native, and elegant.  
> *“Because your terminal should feel as fast as your thoughts.”*
