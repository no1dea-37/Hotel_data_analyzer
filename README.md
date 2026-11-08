# 酒店数据分析工具

本仓库包含酒店数据分析 C++ 程序，以及一个可安装的酒店房价分析台 Windows 桌面界面。

## 下载和安装

前往 [Releases 下载最新版本](https://github.com/no1dea-37/Hotel_data_analyzer/releases/latest)，下载 `HotelPricingDashboard-Setup-1.1.0-x64.exe` 安装程序（适用于 Windows 64 位），然后双击运行安装。

安装时不需要 Node.js。当前安装包未签名，Windows 可能显示“未知发布者”提示。

## 功能

- 导入酒店系统导出的入住明细 CSV，按查询日期统计在住订单、修正营业额并给出调价建议。
- 导入“本日将到列表”导出的 .xls / .xlsx / .csv，在右侧并排显示当天预抵订单（房号、房类、住客、到达/离店、房价、备注）。
- 两张表分别导入、各自搜索，互不影响；数据只在本地浏览器/窗口内处理，不上传。

## 项目内容

- [hotel_data_analyzer.cpp](./hotel_data_analyzer.cpp)：C++ 酒店数据分析程序源码。
- [hotelguests_in_demonstration.csv](./hotelguests_in_demonstration.csv)：演示数据。
- [hotel-pricing-dashboard.html](./hotel-pricing-dashboard.html)：房价分析台页面。
- [main.cjs](./main.cjs) 和 [package.json](./package.json)：Electron 桌面窗口与打包配置。
- [xlsx.full.min.js](./xlsx.full.min.js)：SheetJS 本地副本，用于离线解析 Excel 文件。

Windows 安装版启动的是 Electron 桌面界面；它目前与 C++ 命令行程序分开运行。

## 开发和构建

构建桌面安装包需要 Node.js 22 或更高版本。在仓库目录运行：

    npm install
    npm run dist:win

也可以在 GitHub 仓库的 Actions → Build Windows Installer 手动启动构建。推送到 main 分支也会自动构建；Actions 产物保留 14 天，正式安装包见 Releases。

## License

本仓库目前没有添加许可证文件。
