# 项目结构

项目结构决定了后期好不好维护。训练营如果一开始就把代码堆在一个文件里，后面一定会越来越难改。

## 1. 推荐目录

一个中等规模的 Arduino 项目可以按功能拆分：

```text
environment_monitor/
├── environment_monitor.ino
├── config.h
├── sensors.h
├── sensors.cpp
├── actuators.h
├── actuators.cpp
├── network.h
└── network.cpp
```

| 文件 | 主要职责 |
| --- | --- |
| `environment_monitor.ino` | 初始化模块，安排主循环和整体流程 |
| `config.h` | 引脚、阈值、采样间隔等配置 |
| `sensors.*` | 初始化和读取传感器 |
| `actuators.*` | 控制 LED、继电器、舵机等输出 |
| `network.*` | Wi-Fi、Web 或 MQTT 连接与重连 |

## 2. 模块只暴露必要操作

头文件描述模块能做什么，源文件保存具体实现。例如 `sensors.h`：

```cpp
#pragma once

bool beginSensors();
bool readEnvironment(float& temperature, float& humidity);
```

主程序只调用这些接口，不直接操作传感器库的内部对象：

```cpp
#include "sensors.h"

void setup() {
  Serial.begin(115200);
  if (!beginSensors()) {
    Serial.println("sensor init failed");
  }
}

void loop() {
  float temperature;
  float humidity;

  if (readEnvironment(temperature, humidity)) {
    Serial.printf("%.1f C, %.1f %%\n", temperature, humidity);
  }

  delay(1000);
}
```

这里的 `delay()` 只用于展示模块边界；综合项目应使用 [Millis 计时](./millis-timing.md) 安排采样。

## 3. 配置和密钥分开

适合放进 `config.h` 的内容：

- GPIO 编号
- 采样周期
- 报警阈值
- MQTT 主题
- 功能开关

Wi-Fi 密码、平台令牌等敏感信息应放进单独的本地配置文件，并提供不含真实值的示例文件。提交代码前检查这些信息没有进入版本记录。

## 4. 推荐习惯

1. 一个功能放一个文件。
2. 头文件和源文件分开。
3. 常量集中管理。
4. 资源文件单独存放。
5. 模块初始化函数返回成功或失败。
6. 主循环负责调度，具体功能由模块完成。
7. 文件和函数名称使用统一风格。

## 5. 什么时候需要拆分

出现下面任一情况时，就应该考虑拆模块：

1. 主程序已经难以快速找到某个功能。
2. 同一组初始化和读取代码在多个位置重复。
3. 更换传感器会影响网络或显示逻辑。
4. 多人协作时经常修改同一个文件。
5. 单个功能无法独立测试。

## 6. 学习目标

1. 认识模块化。
2. 认识配置分离。
3. 认识主程序和功能模块的边界。
4. 能把一个综合项目拆成清晰文件。
5. 能在不改主流程的情况下替换单个模块。
