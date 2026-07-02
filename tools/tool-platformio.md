# VSCode 中使用 PlatformIO 的安装与基本使用

本文档记录在 VSCode 中安装和使用 PlatformIO 的基本方法，适用于 ESP32、STM32 等嵌入式开发项目。

## 一、安装 VSCode

先安装 Visual Studio Code。

安装完成后打开 VSCode，进入扩展市场。

推荐安装以下插件：

```text
PlatformIO IDE
C/C++
Chinese Language Pack for Visual Studio Code
```

其中必须安装的是：

```text
PlatformIO IDE
```

## 二、安装 PlatformIO IDE 插件

在 VSCode 左侧点击扩展图标，搜索：

```text
PlatformIO IDE
```

点击安装。

安装完成后，VSCode 左侧会出现 PlatformIO 图标。

第一次启动 PlatformIO 时，会自动下载核心组件和工具链，需要等待一段时间。

如果左侧出现 PlatformIO 图标，说明安装成功。

## 三、创建 PlatformIO 项目

点击 VSCode 左侧的 PlatformIO 图标。

进入：

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
Board: 开发板型号
Framework: 开发框架
Location: 项目保存位置
```

常见开发框架：

```text
Arduino
ESP-IDF
STM32Cube
```

填写完成后点击创建，PlatformIO 会自动生成项目结构。

## 四、PlatformIO 项目结构

PlatformIO 项目一般包含以下内容：

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
| `platformio.ini` | 项目配置文件 |
| `include/` | 头文件目录 |
| `lib/` | 项目私有库目录 |
| `src/` | 主程序目录 |
| `test/` | 测试目录 |
| `README.md` | 项目说明文档 |

最常用的文件是：

```text
platformio.ini
src/main.cpp
```

## 五、配置 platformio.ini

`platformio.ini` 是项目的核心配置文件。

常用配置项包括：

```text
platform        芯片平台
board           开发板型号
framework       开发框架
monitor_speed   串口监视器波特率
upload_port     烧录端口
monitor_port    串口监视器端口
lib_deps        第三方库依赖
```

如果需要指定串口，可以在 `platformio.ini` 中添加：

```ini
upload_port = COM端口号
monitor_port = COM端口号
monitor_speed = 115200
```

Windows 下端口号可以在设备管理器中查看。

## 六、编写程序

主程序通常写在：

```text
src/main.cpp
```

每次修改代码后，需要重新编译并烧录到开发板。

## 七、编译项目

可以点击 VSCode 底部工具栏中的编译按钮：

```text
√
```

也可以在终端执行：

```bash
pio run
```

编译成功后会显示：

```text
SUCCESS
```

## 八、烧录程序

连接开发板后，可以点击 VSCode 底部工具栏中的上传按钮：

```text
→
```

也可以在终端执行：

```bash
pio run --target upload
```

烧录成功后会显示：

```text
SUCCESS
```

如果 ESP32 烧录时一直停在 `Connecting`，可以按住开发板的 `BOOT` 键后重新烧录。

## 九、打开串口监视器

可以点击 VSCode 底部工具栏中的串口监视器按钮。

也可以在终端执行：

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

## 十、安装第三方库

### 方式一：通过 PlatformIO 图形界面安装

进入：

```text
PIO Home > Libraries
```

搜索需要的库，选择安装到当前项目。

### 方式二：通过 platformio.ini 安装

在 `platformio.ini` 中添加：

```ini
lib_deps =
  库名称
```

保存后，PlatformIO 会自动下载依赖。

## 十一、查看串口设备

在终端执行：

```bash
pio device list
```

该命令可以查看当前电脑连接的开发板串口。

## 十二、清理编译缓存

如果项目编译异常，可以清理缓存：

```bash
pio run --target clean
```

然后重新编译：

```bash
pio run
```

## 十三、常用命令

| 命令 | 作用 |
|---|---|
| `pio run` | 编译项目 |
| `pio run --target upload` | 烧录程序 |
| `pio device monitor` | 打开串口监视器 |
| `pio device list` | 查看串口设备 |
| `pio run --target clean` | 清理编译缓存 |
| `pio pkg list` | 查看项目依赖 |
| `pio pkg update` | 更新项目依赖 |

## 十四、常见问题

### 1. 找不到串口

可能原因：

```text
USB 数据线不支持数据传输
开发板驱动未安装
开发板未上电
串口被其他软件占用
端口号配置错误
```

处理方式：

```text
更换 USB 数据线
检查设备管理器
关闭其他串口工具
重新插拔开发板
使用 pio device list 查看端口
```

### 2. 烧录失败

可能原因：

```text
开发板型号选择错误
端口号错误
串口被占用
开发板没有进入下载模式
```

处理方式：

```text
检查 board 配置
检查 upload_port
关闭串口监视器
ESP32 可尝试按住 BOOT 键烧录
```

### 3. 串口乱码

可能原因：

```text
程序中的串口波特率与 monitor_speed 不一致
```

处理方式：

```text
保持程序串口波特率和 monitor_speed 一致
常用波特率为 115200
```

### 4. 头文件找不到

可能原因：

```text
第三方库未安装
库名称填写错误
```

处理方式：

```text
检查 lib_deps
重新保存 platformio.ini
重新编译项目
```

## 十五、Git 提交注意事项

PlatformIO 项目不建议上传编译缓存。

建议在 `.gitignore` 中添加：

```gitignore
.pio/
.vscode/.browse_c_cpp.db*
.vscode/c_cpp_properties.json
.vscode/launch.json
.vscode/ipch/
build/
dist/
*.log
*.tmp
.DS_Store
Thumbs.db
```

推荐提交的内容：

```text
platformio.ini
src/
include/
lib/
README.md
.gitignore
```

## 十六、基本使用流程

```text
安装 VSCode
安装 PlatformIO IDE 插件
创建 PlatformIO 项目
选择开发板和开发框架
编写 src/main.cpp
配置 platformio.ini
编译项目
烧录程序
打开串口监视器
查看运行结果
提交代码到 GitHub
```