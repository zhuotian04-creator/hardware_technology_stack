# VSCode 中使用 PlatformIO 开发 STM32

本文档记录在 VSCode 中使用 PlatformIO 开发 STM32 项目的基本方法，包括环境安装、项目创建、配置、编译、烧录、串口调试和常见问题处理。

## 一、适用范围

适用于以下 STM32 开发场景：

```text
STM32F103 开发
STM32F103C8T6 开发
STM32F103RCT6 开发
GPIO 控制
PWM 输出
串口通信
定时器控制
编码器读取
电机控制
传感器采集
```

## 二、安装开发环境

### 1. 安装 VSCode

先安装 Visual Studio Code。

### 2. 安装 PlatformIO 插件

在 VSCode 扩展市场搜索：

```text
PlatformIO IDE
```

点击安装。

安装完成后，VSCode 左侧会出现 PlatformIO 图标。第一次启动 PlatformIO 时，会自动下载核心组件和工具链，需要等待。

### 3. 安装 ST-Link 驱动

如果使用 ST-Link 烧录 STM32，需要安装 ST-Link 驱动。

安装完成后，将 ST-Link 接入电脑，并在设备管理器中确认识别正常。

## 三、创建 STM32 项目

点击 VSCode 左侧 PlatformIO 图标，进入：

```text
PIO Home
```

点击：

```text
New Project
```

填写项目信息：

```text
Name: 项目名称
Board: STM32 开发板型号
Framework: 开发框架
Location: 项目保存位置
```

常见开发框架：

```text
Arduino
STM32Cube
CMSIS
```

快速验证可以选择：

```text
Arduino
```

更接近 STM32 工程开发方式可以选择：

```text
STM32Cube
```

## 四、PlatformIO STM32 项目结构

项目结构一般如下：

```text
project-name/
├── platformio.ini
├── include/
├── lib/
├── src/
│   └── main.cpp
├── test/
└── README.md
```

目录说明：

| 文件或目录 | 作用 |
|---|---|
| `platformio.ini` | 项目核心配置文件 |
| `include/` | 头文件目录 |
| `lib/` | 项目私有库目录 |
| `src/` | 主程序目录 |
| `test/` | 测试目录 |
| `README.md` | 项目说明文档 |

最重要的文件：

```text
platformio.ini
src/main.cpp
```

## 五、platformio.ini 基本配置

常用字段：

```text
platform          芯片平台
board             开发板型号
framework         开发框架
upload_protocol   烧录方式
monitor_speed     串口监视器波特率
upload_port       烧录端口
monitor_port      串口监视器端口
lib_deps          第三方库依赖
```

### 1. STM32F103C8T6 配置

```ini
[env:bluepill_f103c8]
platform = ststm32
board = bluepill_f103c8
framework = arduino
upload_protocol = stlink
monitor_speed = 115200
```

### 2. STM32F103RC 配置

```ini
[env:genericSTM32F103RC]
platform = ststm32
board = genericSTM32F103RC
framework = arduino
upload_protocol = stlink
monitor_speed = 115200
```

### 3. 使用 STM32Cube 框架

```ini
[env:bluepill_f103c8]
platform = ststm32
board = bluepill_f103c8
framework = stm32cube
upload_protocol = stlink
monitor_speed = 115200
```

### 4. 指定串口号

Windows 下可以根据设备管理器中的端口号指定串口：

```ini
upload_port = COM26
monitor_port = COM26
```

完整配置示例：

```ini
[env:bluepill_f103c8]
platform = ststm32
board = bluepill_f103c8
framework = arduino
upload_protocol = stlink
upload_port = COM26
monitor_port = COM26
monitor_speed = 115200
```

## 六、编写程序

主程序一般写在：

```text
src/main.cpp
```

如果使用 Arduino Framework，入口函数通常是：

```text
setup()
loop()
```

如果使用 STM32Cube Framework，入口函数通常是：

```text
main()
```

建议将功能拆分到独立文件中：

```text
src/
├── main.cpp
├── motor_control.cpp
├── encoder_reader.cpp
├── uart_debug.cpp
└── sensor_reader.cpp

include/
├── motor_control.h
├── encoder_reader.h
├── uart_debug.h
└── sensor_reader.h
```

## 七、编译项目

点击 VSCode 底部工具栏中的编译按钮：

```text
√
```

或者在终端执行：

```bash
pio run
```

编译成功后会显示：

```text
SUCCESS
```

编译失败时优先检查：

```text
开发板型号是否正确
framework 是否正确
platformio.ini 是否配置正确
头文件路径是否正确
第三方库是否安装
代码语法是否正确
```

## 八、烧录程序

连接 ST-Link 和 STM32 开发板后，点击 VSCode 底部工具栏中的上传按钮：

```text
→
```

或者执行：

```bash
pio run --target upload
```

烧录成功后会显示：

```text
SUCCESS
```

## 九、ST-Link 接线

| ST-Link | STM32 |
|---|---|
| 3.3V | 3.3V |
| GND | GND |
| SWDIO | SWDIO |
| SWCLK | SWCLK |
| NRST | NRST，可选 |

注意事项：

```text
必须共地
不要接错 3.3V 和 5V
确认开发板供电正常
确认 ST-Link 驱动正常
SWDIO 和 SWCLK 不要接反
```

## 十、串口调试

打开串口监视器：

```bash
pio device monitor
```

指定波特率：

```bash
pio device monitor -b 115200
```

退出串口监视器：

```text
Ctrl + C
```

查看当前电脑连接的串口设备：

```bash
pio device list
```

串口乱码时，检查程序中的串口波特率是否和 `monitor_speed` 一致。

## 十一、清理编译缓存

如果项目编译异常，可以清理缓存：

```bash
pio run --target clean
```

然后重新编译：

```bash
pio run
```

## 十二、常用命令

| 命令 | 作用 |
|---|---|
| `pio run` | 编译项目 |
| `pio run --target upload` | 烧录程序 |
| `pio device monitor` | 打开串口监视器 |
| `pio device monitor -b 115200` | 指定波特率打开串口监视器 |
| `pio device list` | 查看串口设备 |
| `pio run --target clean` | 清理编译缓存 |
| `pio pkg list` | 查看项目依赖 |
| `pio pkg update` | 更新项目依赖 |

## 十三、常见问题

### 1. 找不到 ST-Link

可能原因：

```text
ST-Link 驱动未安装
USB 数据线异常
ST-Link 接触不良
电脑没有识别设备
```

处理方式：

```text
重新安装 ST-Link 驱动
更换 USB 数据线
重新插拔 ST-Link
检查设备管理器
```

### 2. 烧录失败

可能原因：

```text
upload_protocol 未设置为 stlink
SWDIO 和 SWCLK 接反
开发板未供电
GND 未共地
芯片型号选择错误
```

处理方式：

```text
检查 platformio.ini
检查 ST-Link 接线
确认开发板供电
确认 board 型号
重新执行烧录命令
```

### 3. 编译失败

可能原因：

```text
board 配置错误
framework 选择错误
头文件路径错误
代码语法错误
库依赖缺失
```

处理方式：

```text
检查 platformio.ini
检查 src 和 include 文件
查看错误提示中的文件路径和行号
清理缓存后重新编译
```

### 4. 串口没有输出

可能原因：

```text
串口线未连接
串口号错误
波特率错误
程序没有初始化串口
TX/RX 接反
GND 未共地
```

处理方式：

```text
执行 pio device list 查看串口
检查 monitor_port
检查 monitor_speed
检查 TX/RX 接线
确认程序中已初始化串口
```

### 5. 串口乱码

可能原因：

```text
程序波特率和 monitor_speed 不一致
```

处理方式：

```text
保持程序串口波特率和 monitor_speed 一致
常用波特率为 115200
```

## 十四、Git 提交注意事项

STM32 PlatformIO 项目不建议上传编译缓存和临时文件。

建议 `.gitignore` 添加：

```gitignore
.pio/
.vscode/.browse_c_cpp.db*
.vscode/c_cpp_properties.json
.vscode/launch.json
.vscode/ipch/
build/
Debug/
Release/
Objects/
Listings/
*.o
*.d
*.axf
*.elf
*.hex
*.bin
*.map
*.lst
*.log
*.tmp
.DS_Store
Thumbs.db
```

推荐提交：

```text
platformio.ini
src/
include/
lib/
README.md
.gitignore
```

## 十五、基本开发流程

```text
安装 VSCode
安装 PlatformIO IDE
安装 ST-Link 驱动
创建 STM32 PlatformIO 项目
选择开发板型号
选择开发框架
配置 platformio.ini
编写 src/main.cpp
编译项目
连接 ST-Link
烧录程序
打开串口监视器
查看运行结果
整理 README
提交到 GitHub
```

## 十六、文档维护

后续新增 STM32 项目时，建议记录：

```text
开发板型号
芯片型号
开发框架
烧录方式
串口号
主要外设
引脚连接
测试结果
常见问题
```