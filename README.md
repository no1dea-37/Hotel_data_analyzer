# 酒店房价分析台（Windows 桌面版）

此项目把酒店房价分析页面封装为 Electron 桌面窗口。CSV 文件仍在本机浏览器视图内处理。

## 没有 Windows 电脑时：用 GitHub 云端生成安装包

项目包含 `.github/workflows/build-windows.yml`，由 GitHub 的 Windows 云端运行器构建安装程序。

1. 在 GitHub 创建一个仓库；若源码不想公开，请设为 **Private**。
2. 将解压后的整个项目上传到仓库，确保 `.github/workflows/build-windows.yml` 也上传。
3. 上传到 `main` 分支后，打开仓库的 **Actions** 页面，选择 **Build Windows Installer** 并运行。
4. 等工作流完成，在运行详情页的 **Artifacts** 区下载 `hotel-pricing-windows-installer`。
5. 解压下载的 artifact，即可取到安装程序 `.exe`，再把它发给要安装的人。

构建出来的安装程序面向 x64 Windows。收到安装程序的人无需安装 Node.js。

## 在 Windows 电脑本机打包

安装 Node.js LTS 后，双击 `build-windows.bat`；安装程序会生成在 `dist` 文件夹中。
