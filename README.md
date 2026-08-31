# Hotel_data_analyzer
A tool whose function is analyzing CSV document to get precise information summary;

注：文件代码与表格已做脱敏处理，企业名称，人名电话等已手动屏蔽
# 酒店收益管理数据分析工具

一个用于处理酒店订单CSV数据的C++命令行工具，支持脏数据清洗、多日期格式识别、RePar计算与动态调价建议。

## 技术栈
C++ · 标准库（fstream, sstream, filesystem, ctime）

## 核心功能
- 流式解析大体积CSV，支持字段内嵌逗号与跨行拼接
- 封装安全类型转换函数（safe_stoi / safe_stod），处理空字段与异常输入
- 支持多种日期输入格式，自动计算在住天数
- 从备注字段提取每日房价，区分直连与私联房价
- 输出RePar、实时营业额与动态调价建议

## 快速开始
```bash
g++ -std=c++17 hotel_analyzer.cpp -o hotel_analyzer
./hotel_analyzer
