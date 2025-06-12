#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <ctime>
#include <conio.h>
#include <curl/curl.h>

// 添加函数声明
bool DownloadAndInstallUpdate(const std::string& downloadUrl);

// 托盘图标相关定义
#define TRAY_ICON_ID 100
#define WM_TRAYICON (WM_USER + 1)
#define IDM_RESTORE 2001
#define IDM_EXIT 2002

// 全局变量
NOTIFYICONDATA nid = {};
HWND hwnd = NULL;
HMENU hMenu = NULL;
bool g_inTray = false;
bool g_shouldExit = false;
bool g_trayIconAdded = false; // 跟踪托盘图标是否已添加

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            // 初始化托盘图标
            ZeroMemory(&nid, sizeof(nid));
            nid.cbSize = sizeof(nid);
            nid.hWnd = hWnd;
            nid.uID = TRAY_ICON_ID;
            nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_INFO | NIF_SHOWTIP;
            nid.uCallbackMessage = WM_TRAYICON;

            // 尝试加载自定义图标
            nid.hIcon = (HICON)LoadImage(NULL, L"logo.ico", IMAGE_ICON,
                                          GetSystemMetrics(SM_CXSMICON),
                                          GetSystemMetrics(SM_CYSMICON),
                                          LR_LOADFROMFILE);

            // 如果加载失败，使用默认图标
            if (!nid.hIcon) {
                nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
            }

            wcscpy_s(nid.szTip, L"Minecraft-Toos");

            // 添加托盘图标
            if (Shell_NotifyIcon(NIM_ADD, &nid)) {
                g_trayIconAdded = true;
            } else {
                DWORD err = GetLastError();
                std::cerr << "添加托盘图标失败，错误代码: " << err << std::endl;
            }
            break;

        case WM_TRAYICON:
            if (lParam == WM_RBUTTONDOWN || lParam == WM_CONTEXTMENU) {
                // 获取鼠标位置
                POINT pt;
                GetCursorPos(&pt);

                // 创建右键菜单
                hMenu = CreatePopupMenu();
                if (hMenu) {
                    AppendMenu(hMenu, MF_STRING, IDM_RESTORE, L"显示主界面");
                    AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
                    AppendMenu(hMenu, MF_STRING, IDM_EXIT, L"退出程序");

                    // 设置菜单为前台窗口
                    SetForegroundWindow(hWnd);

                    // 显示菜单
                    UINT clicked = TrackPopupMenu(
                        hMenu,
                        TPM_RETURNCMD | TPM_NONOTIFY | TPM_BOTTOMALIGN | TPM_LEFTALIGN,
                        pt.x, pt.y,
                        0, hWnd, NULL);

                    // 处理菜单选择
                    if (clicked == IDM_RESTORE) {
                        ShowWindow(GetConsoleWindow(), SW_SHOW);
                        SetForegroundWindow(GetConsoleWindow());
                        g_inTray = false;
                    } else if (clicked == IDM_EXIT) {
                        g_shouldExit = true;
                        PostMessage(hWnd, WM_CLOSE, 0, 0);
                    }

                    DestroyMenu(hMenu);
                    hMenu = NULL;
                }
            }
            break;

        case WM_CLOSE:
            // 清理资源
            if (g_trayIconAdded) {
                Shell_NotifyIcon(NIM_DELETE, &nid);
                g_trayIconAdded = false;
            }
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 初始化托盘系统
void InitializeTraySystem() {
    // 1. 注册窗口类
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"MinecraftToosTrayClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        DWORD err = GetLastError();
        std::cerr << "窗口类注册失败! 错误代码: " << err << std::endl;
        return;
    }

    // 2. 创建隐藏窗口
    hwnd = CreateWindowEx(
        0, wc.lpszClassName, L"Minecraft-Toos Tray Window", 0,
        0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);

    if (!hwnd) {
        DWORD err = GetLastError();
        std::cerr << "窗口创建失败! 错误代码: " << err << std::endl;
        return;
    }

    // 3. 确保窗口消息被处理
    MSG msg;
    while (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 4. 显示托盘图标（如果尚未显示）
    if (!g_trayIconAdded) {
        if (Shell_NotifyIcon(NIM_ADD, &nid)) {
            g_trayIconAdded = true;
        }
    }
}

// 隐藏到托盘
void HideToTray() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    g_inTray = true;

    // 确保托盘图标可见
    if (!g_trayIconAdded) {
        InitializeTraySystem();
    }
}

// 处理消息循环
void ProcessTrayMessages() {
    if (!hwnd) return;

    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// 控制台关闭事件处理
BOOL WINAPI ConsoleHandler(DWORD event) {
    if (event == CTRL_CLOSE_EVENT || event == CTRL_SHUTDOWN_EVENT) {
        HideToTray();
        return TRUE;
    }
    return FALSE;
}

// 宽字符转换工具
std::wstring s2ws(const std::string& str) {
    if (str.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstr[0], size_needed);
    return wstr;
}

void setConsoleTitle(const std::string& title) {
    SetConsoleTitleW(s2ws(title).c_str());
}

// 常量定义
const std::string CURRENT_VERSION = "6.6.0";
const std::string ERROR_TITLE = "Minecraft-Toos";

// 写入日志函数
void writeLog(const std::string& user, const std::string& action, const std::string& error = "") {
    time_t now = time(0);
    tm p;
    localtime_s(&p, &now);

    char timeStr[20];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &p);

    std::ofstream logFile("Minecraft-Toos.log", std::ios::app | std::ios::binary);
    if (logFile.is_open()) {
        static bool hasBOM = false;
        if (!hasBOM) {
            logFile << "\xEF\xBB\xBF"; // 写入 UTF-8 BOM
            hasBOM = true;
        }

        logFile << "[" << timeStr << "] ";
        logFile << "用户: " << user << " | ";
        logFile << "操作: " << action;
        if (!error.empty()) {
            logFile << " | 错误: " << error;
        }
        logFile << std::endl;
        logFile.close();
    }
}

// 全局变量
std::stack<int> num;
std::stack<char> op;

// 原始函数保留
void convertGameTime(int ticks) {
    int seconds = ticks / 20;
    int minutes = seconds / 60;
    int hours = minutes / 60;
    std::cout << ticks << " ticks = " << hours << "时 " << minutes % 60 << "分 " << seconds % 60 << "秒\n";
}

void calc() {
    if (num.size() < 2 || op.empty()) return;
    int a = num.top(); num.pop();
    int b = num.top(); num.pop();
    char c = op.top(); op.pop();
    int x = (c == '+') ? a + b : (c == '-') ? b - a : (c == '/') ? b / a : a * b;
    num.push(x);
}

bool compare(char a, char b) {
    int x = (a == '+' || a == '-') ? 1 : 2;
    int y = (b == '*' || b == '/') ? 2 : 1;
    return x >= y;
}

void displayWelcome() {
    setConsoleTitle("Minecraft-Toos-登录");
    std::cout << "============== Minecraft-Toos ==============\n"
              << "============== Login ================\n\n";
}

void saveDeathCoord(int x, int y, int z) {
    std::ofstream file("death_log.txt", std::ios::app);
    time_t now = time(0);
    file << ctime(&now) << "坐标：" << x << " " << y << " " << z << "\n\n";
}

// 安全输入优化
std::string securePasswordInput() {
    std::string pwd;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!pwd.empty()) {
                pwd.pop_back();
                std::cout << "\b \b";
            }
        } else {
            pwd.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return pwd;
}

// 宽字符消息框封装
void ShowMessageBox(const std::string& message, const std::string& title = ERROR_TITLE, UINT type = MB_OK | MB_ICONHAND) {
    MessageBoxW(NULL, s2ws(message).c_str(), s2ws(title).c_str(), type);
}

// 新增函数：检查更新
bool CheckForUpdates(const std::string& currentVersion) {
    CURL *curl;
    CURLcode res;
    std::string updateUrl = "https://example.com/update.txt"; // 替换为实际的更新文件URL
    std::string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, updateUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](char *ptr, size_t size, size_t nmemb, std::string *data) -> size_t {
            data->append(ptr, size * nmemb);
            return size * nmemb;
        });
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // 解析 response，获取最新版本号和下载链接
    std::istringstream iss(response);
    std::string latestVersion, downloadUrl;
    std::getline(iss, latestVersion);
    std::getline(iss, downloadUrl);

    // 比较版本号
    if (latestVersion > currentVersion) {
        std::cout << "发现新版本: " << latestVersion << std::endl;
        std::cout << "当前版本: " << currentVersion << std::endl;

        // 提示用户更新
        if (MessageBoxW(NULL, L"发现新版本，是否立即更新？", L"Minecraft-Toos", MB_YESNO | MB_ICONQUESTION) == IDYES) {
            if (DownloadAndInstallUpdate(downloadUrl)) {
                std::cout << "更新下载成功，安装程序已启动。" << std::endl;
                return true;
            } else {
                std::cout << "更新下载失败，请稍后重试。" << std::endl;
                return false;
            }
        }
    }

    std::cout << "当前已是最新版本" << std::endl;
    return false;
}

// 新增函数：下载并安装更新
bool DownloadAndInstallUpdate(const std::string& downloadUrl) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    std::string tempFilePath = "Minecraft-Toos_Update.exe";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        fp = fopen(tempFilePath.c_str(), "wb");
        if(fp) {
            curl_easy_setopt(curl, CURLOPT_URL, downloadUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

            res = curl_easy_perform(curl);

            fclose(fp);

            if(res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                curl_easy_cleanup(curl);
                curl_global_cleanup();
                return false;
            }
        } else {
            std::cerr << "无法创建临时文件: " << tempFilePath << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    // 启动安装程序
    std::string installCommand = "start " + tempFilePath;
    system(installCommand.c_str());

    return true;
}

int main() {
    // 设置控制台编码
    system("chcp 65001 > nul");
    system("cls");

    // 检查更新
    if (CheckForUpdates(CURRENT_VERSION)) {
        std::cout << "请等待安装程序完成更新后重启程序。" << std::endl;
        system("pause");
        return 0; // 如果有更新并成功下载，直接退出程序
    }

    // 设置控制台关闭事件处理
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    // 初始化托盘系统 - 在程序启动时创建
    InitializeTraySystem();

    // 登录模块
    std::string username, password;
    bool isLoggedIn = false;
    int attempts = 0;
    const int maxAttempts = 3;

    while (!isLoggedIn && attempts < maxAttempts) {
        displayWelcome();
        std::cout << "用户名: ";
        std::getline(std::cin, username);
        std::cout << "密码: ";
        password = securePasswordInput();

        if (username == "User" && password == "12345678") {
            MessageBoxW(NULL, L"登录成功！欢迎普通用户使用Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
            isLoggedIn = true;
            writeLog(username, "登录成功");
        } else if (username == "Admin" && password == "DZY@013520") {
            MessageBoxW(NULL, L"登录成功！欢迎管理员使用Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
            isLoggedIn = true;
            writeLog(username, "登录成功");
        } else {
            attempts++;
            std::ostringstream oss;
            oss << "用户不存在或密码错误，剩余尝试次数：" << (maxAttempts - attempts);
            ShowMessageBox(oss.str(), ERROR_TITLE, MB_OK | MB_ICONHAND);
            writeLog(username, "登录失败", "用户名或密码错误");
            if (attempts < maxAttempts) {
                ShowMessageBox("请重新输入", ERROR_TITLE, MB_OK | MB_ICONHAND);
                system("cls");
            }
        }
    }

    if (!isLoggedIn) {
        ShowMessageBox("密码尝试次数已用完，Minecraft-Toos即将退出……", ERROR_TITLE, MB_OK | MB_ICONASTERISK);
        writeLog("未知用户", "登录失败", "尝试次数用尽");

        // 清理托盘图标
        if (g_trayIconAdded) {
            Shell_NotifyIcon(NIM_DELETE, &nid);
        }
        return 1;
    }

    system("cls");

    // 主菜单循环
    int n, g;
    while (true) {
        // 检查托盘消息
        ProcessTrayMessages();

        if (g_shouldExit) {
            writeLog(username, "退出程序");

            // 清理托盘图标
            if (g_trayIconAdded) {
                Shell_NotifyIcon(NIM_DELETE, &nid);
            }
            return 0;
        }

        if (g_inTray) {
            // 在托盘状态时减少CPU占用
            Sleep(100);
            continue;
        }

        setConsoleTitle("Minecraft-Toos-主页");
        std::cout << "\n###############################\n欢迎使用Minecraft Toos\n###############################\n"
                  << "\n==============================================\n"
                  << "运行时:C++21      MinGW版本：14.2    cmake版本：4.0.2\n"
                  << "编译器版本：Jetbrains Clion 2025.1.1     当前版本：" << CURRENT_VERSION << "正式版\n"
                  << "==============================================\n\n"
                  << "[1]功能大全 [2]赞助作者 [3]关于 [4]退出 [5]百宝箱 [6]最终用户许可协议\n Enter your numbers:";

        if (!(std::cin >> n)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            ShowMessageBox("输入无效，请重新输入", ERROR_TITLE, MB_OK | MB_ICONHAND);
            writeLog(username, "输入无效", "主菜单选项错误");
            system("cls");
            continue;
        }

        switch(n){
            case 1: { // 功能大全
                setConsoleTitle("Minecraft-Toos-功能大全");
                system("cls");
                std::cout << "###########################\n         功能大全           \n###########################\n\n"
                          << "[1]启动PCL2CE [2]启动Hello Minecraft!Launcher [3]下载基岩版 [4]破解基岩版\n"
                          << "[5]配置java环境 [6]查看教程/问题解答 [7]退出 [8]服务器选项 [9]返回\n"
                          << "[10]有用没啥用的网站 [11]注册微软账户 [12]游戏内功能\nenter your numbers:";
                std::cin >> g;

                switch(g) {
                    case 1:
                        system("cls");
                        system("start pcl2.exe");
                        MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        writeLog(username, "启动了 PCL2CE");
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        system("start HMCL.exe");
                        MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        writeLog(username, "启动了 Hello Minecraft! Launcher");
                        system("cls");
                        break;
                    case 3: {
                        system("cls");
                        system("start https://remyod-my.sharepoint.com/personal/mcappx_od_remyyyz_com/Documents/Minecraft%20%e7%89%88%e6%9c%ac%e5%ba%93/archive/Windows/Microsoft.MinecraftUWP_1.21.8201.0_x64__8wekyb3d8bbwe.Appx?ga=1");
                        if (MessageBoxW(NULL,L"请查看是否开始下载！\n若未下载，请点击“否”",L"Minecraft-Toos",MB_YESNO|MB_ICONASTERISK)==IDNO) {
                            system("start https://www.mcappx.com/index.html#__tabbed_3_3");
                            MessageBoxW(NULL,L"MCAPPX版本库已打开！请选择您的游戏版本和下载节点!",L"Minecraft-Toos",MB_OK|MB_ICONASTERISK);
                            writeLog(username, "下载我的世界基岩版(备选方案)","主方案使用失败");
                            system("cls");
                        }
                        else {
                            writeLog(username, "下载我的世界基岩版(主方案)");
                            system("cls");
                        }
                        break;
                    }
                    case 4:
                        system("cls");
                        system("start po.bat");
                        MessageBoxW(NULL, L"破解程序启动成功！\n请点击Install Mode进行破解", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        writeLog(username, "启动了基岩版破解工具");
                        system("cls");
                        break;
                    case 5: {
                        system("cls");
                        std::cout << "请选择安装内容：\n[1]安装java8 [2]安装java17 [3]安装java21 [4]全部安装（建议）\n enter your numbers:";
                        int m;
                        std::cin >> m;
                        switch(m){
                            case 1:
                                system("cls");
                                system("start JDK-8.exe");
                                MessageBoxW(NULL, L"JAVA8安装程序已启动", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                writeLog(username, "安装了 JAVA8");
                                system("cls");
                                break;
                            case 2:
                                system("cls");
                                system("start JDK-17.exe");
                                MessageBoxW(NULL, L"JAVA17安装程序已启动", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                writeLog(username, "安装了 JAVA17");
                                system("cls");
                                break;
                            case 3:
                                system("cls");
                                system("start JDK-21.exe");
                                MessageBoxW(NULL, L"JAVA21安装程序已启动", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                writeLog(username, "安装了 JAVA21");
                                system("cls");
                                break;
                            case 4:
                                system("cls");
                                writeLog(username, "开始批量安装 Java 环境");
                                system("start JDK-8.exe");
                                MessageBoxW(NULL, L"正在安装JAVA8,请稍等……\n请等待安装程序结束再按确定", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                system("cls");
                                system("start JDK-17.exe");
                                MessageBoxW(NULL, L"正在安装JAVA17,请稍等……\n请等待安装程序结束再按确定", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                system("cls");
                                system("start JDK-21.exe");
                                MessageBoxW(NULL, L"正在安装JAVA21,请稍等……\n请等待安装程序结束再按确定", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                system("cls");
                                MessageBoxW(NULL, L"恭喜，JAVA已安装完成！", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                writeLog(username,"批量安装JAVA结束");
                                system("cls");
                                break;
                            default:
                                system("cls");
                                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                                writeLog(username, "Java安装失败", "无效选项");
                                system("pause");
                                system("cls");
                        }
                        break;
                    }
                    case 6:
                        system("cls");
                        system("start https://dongzheyu.github.io/Minecraft-Toos_Help.html");
                        MessageBoxW(NULL, L"官方帮助页面已打开！请进行浏览\n若内容不全，请私信作者补充", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        writeLog(username, "打开了帮助页面");
                        system("cls");
                        break;
                    case 7:
                        writeLog(username, "退出程序");
                        if (g_trayIconAdded) {
                            Shell_NotifyIcon(NIM_DELETE, &nid);
                        }
                        return 0;
                    case 8:
                        system("cls");
                        std::cout << "请问您要是用哪个服务器软件？\n [1]MSL [2]MCSL2\n";
                        int x;
                        std::cin >> x;
                        switch (x){
                            case 1:
                                system("cls");
                                system("start MSL.exe");
                                MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                writeLog(username, "启动了 MSL 服务器");
                                system("cls");
                                break;
                            case 2:
                                system("start MCSL2/MCSL2.exe");
                                MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                writeLog(username, "启动了 MCSL2 服务器");
                                system("cls");
                                break;
                            default:
                                system("cls");
                                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                                writeLog(username, "服务器启动失败", "无效选项");
                                system("cls");
                        }
                        break;
                    case 9:
                        system("cls");
                        writeLog(username, "从功能大全返回主菜单");
                        break;
                    case 10: {
                        system("cls");
                        std::cout << "========================\n       有用没啥用的网站\n========================\n"
                                  << "[1]MC百科 [2]forge [3]我的世界中文站 [4]3DM [5]返回 [6]购买正版 [7]网站软件大全(第三方)\n enter your numbers:";
                        int d;
                        std::cin >> d;
                        switch(d) {
                            case 1:
                                system("start https://www.mcmod.cn/");
                                writeLog(username, "访问了 MC百科");
                                break;
                            case 2:
                                system("start https://files.minecraftforge.net/");
                                writeLog(username, "访问了 Forge官网");
                                break;
                            case 3:
                                system("start https://www.minecraftzw.com/mods");
                                writeLog(username, "访问了 我的世界中文站");
                                break;
                            case 4:
                                system("start https://mod.3dmgame.com/Minecraft");
                                writeLog(username, "访问了 3DM模组站");
                                break;
                            case 6:
                                system("start https://www.xbox.com/zh-CN/games/store/minecraft-java-bedrock-edition-for-pc");
                                writeLog(username, "访问了 Xbox商店购买页面");
                                break;
                            case 7: {
                                system("cls");
                                std::cout << "本网站是第三方，未经过作者验证。是否前往？\n[1]是[2]否";
                                int h;
                                std::cin >> h;
                                if (h == 1) {
                                    system("start https://www.mcnav.net/");
                                    writeLog(username, "访问了 第三方资源网站");
                                }
                                break;
                            }
                            default: break;
                        }
                        break;
                    }
                    case 11:
                        system("start https://signup.live.com/signup?client_id=81feaced-5ddd-41e7-8bef-3e20a2689bb7");
                        MessageBoxW(NULL, L"微软账户注册页面已打开！", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        writeLog(username, "打开了微软注册页面");
                        system("cls");
                        break;
                    case 12:{
                        system("title Minecraft-Toos-游戏内功能");
                        system("cls");
                        std::cout << "========================\n       游戏内功能\n========================\n"
                                  << "[1]游戏时刻转换 [2]死亡坐标记录器\nenter your numbers:";
                        int d;
                        std::cin >> d;
                        switch (d) {
                            case 1: {
                                int input;
                                std::cout << "输入游戏刻数（1现实秒=20游戏刻）: ";
                                std::cin >> input;
                                convertGameTime(input);
                                writeLog(username, "执行了游戏时间转换", "输入值：" + std::to_string(input));
                                system("pause");
                                system("cls");
                                break;
                            }
                            case 2: {
                                int x, y, z;
                                std::cout << "记录死亡坐标：\nX: ";
                                std::cin >> x;
                                std::cout << "Y: ";
                                std::cin >> y;
                                std::cout << "Z: ";
                                std::cin >> z;
                                saveDeathCoord(x, y, z);
                                std::cout << "坐标已保存到 death_log.txt\n";
                                writeLog(username, "保存了死亡坐标", "坐标：" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z));
                                system("pause");
                                system("cls");
                                break;
                            }
                            default:
                                system("cls");
                                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                                writeLog(username, "游戏内功能操作失败", "无效选项");
                        }
                    }
                    default: {
                        system("cls");
                        MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                        writeLog(username, "功能大全操作失败", "无效选项");
                    }
                }
                break;
            }
            case 2: { // 赞助作者
                setConsoleTitle("Minecraft-Toos-赞助作者");
                system("cls");
                std::cout << "===========\n赞助作者\n===========\n[1]爱发电(付费) [2]GitHub(免费) [3]返回\n Enter your numbers:";
                int x;
                std::cin >> x;
                switch (x){
                    case 1:
                        system("start https://afdian.tv/a/JetCPP");
                        writeLog(username, "访问了爱发电赞助页面");
                        break;
                    case 2:
                        system("start https://github.com/dongzheyu/Minecraft_Toos");
                        writeLog(username, "访问了GitHub开源页面");
                        break;
                    case 3:
                        system("cls");
                        writeLog(username, "从赞助页面返回");
                        break;
                    default:
                        system("cls");
                        MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                        writeLog(username, "赞助页面操作失败", "无效选项");
                }
                break;
            }
            case 3: { // 关于页面
                setConsoleTitle("Minecraft-Toos-关于");
                system("cls");
                std::cout << "###############         关于        ##############\n"
                          << "开发人员：bilibili 我是dongle \n"
                          << "运行时：C++20 \n"
                          << "开发软件：Visual Studio 2022、Clion \n"
                          << "B站主页：https://space.bilibili.com/3546730880567808 \n"
                          << "GitHub开源主页：https://github.com/dongzheyu/Minecraft-Toos/ \n"
                          << "Copyright © JetCPP 2024-2025 保留所有权利 \n"
                          << "#######################################################\n\n\n\n\n\n记得赞助作者哦~~~";
                system("pause");
                system("cls");
                writeLog(username, "查看了关于页面");
                break;
            }
            case 4:
                writeLog(username, "退出程序");
                if (g_trayIconAdded) {
                    Shell_NotifyIcon(NIM_DELETE, &nid);
                }
                return 0;
            case 5: { // 百宝箱
                setConsoleTitle("Minecraft-Toos-百宝箱");
                system("cls");
                std::cout << "====================\n百宝箱\n======================\n"
                          << "[1]当前时间 [2]闪瞎你的勾眼 [3]返回 [4]新手攻略\n"
                          << "[5]计算器 [6]代码彩蛋 [7]数字炸弹 [8]游戏时间转换器\n"
                          << "请输入选项编号:";
                int c;
                std::cin >> c;

                switch (c) {
                    case 1: {
                        int i = 0;
                        while (i < 20) {
                            system("cls");
                            time_t nowtime;
                            time(&nowtime);
                            tm p; // NOLINT(*-pro-type-member-init)
                            localtime_s(&p, &nowtime);
                            printf("%04d:%02d:%02d %02d:%02d:%02d\n",
                                p.tm_year + 1900, p.tm_mon + 1, p.tm_mday, p.tm_hour, p.tm_min, p.tm_sec);
                            std::cout << "本界面20秒后会自动返回";
                            Sleep(1000);
                            i++;
                        }
                        system("cls");
                        writeLog(username, "查看了实时时间");
                        break;
                    }
                    case 2: {
                        system("cls");
                        if (MessageBoxW(NULL, L"食用提示：本功能不适用于有光瘫病患者和眼睛有问题的选手", L"Minecraft-Toos", MB_OKCANCEL|MB_ICONQUESTION) == IDOK) {
                            for (int i = 0; i < 50; i++) {
                                system("color 07");
                                system("color 17");
                                system("color 27");
                                system("color 37");
                                system("color 47");
                                system("color 57");
                                system("color 67");
                                system("color 76");
                                system("color 87");
                                system("color 97");
                                system("color A7");
                                system("color B7");
                                system("color C7");
                                system("color E7");
                                system("color F7");
                            }
                            system("color 07");
                            std::cout << "你眼睛瞎了吗？都闪了这么久了\n休息一下吧~~~\n";
                            system("shutdown /s /t 40");
                            std::cout << "为了让您的眼睛休息，computer将在40秒后关机！！！\n";
                            writeLog(username, "使用了炫彩特效功能");
                            system("pause");
                        }
                        system("cls");
                        break;
                    }
                    case 4: { // 新手攻略
                        system("cls");
                        std::cout << "===== 我的世界新手生存指南 =====\n"
                                  << "1. 初始目标：收集木材（按住左键破坏树木）\n"
                                  << "2. 制作工作台：4块木板合成2x2网格\n"
                                  << "3. 优先制作石镐（3石头+2木棍）\n"
                                  << "4. 收集食物和煤炭\n"
                                  << "5. 建造庇护所\n"
                                  << "6. 夜晚必须携带火把\n"
                                  << "7. 制作熔炉\n"
                                  << "8. 探索村庄\n"
                                  << "9. 下界传送\n"
                                  << "10. 击败末影龙\n"
                                  << "===============================\n";
                        system("pause");
                        system("cls");
                        writeLog(username, "查看了新手攻略");
                        break;
                    }
                    case 5: { // 计算器
                        system("cls");
                        std::cout << "计算器(支持小括号和加减乘除)\n输入：";
                        std::string s;
                        std::cin >> s;
                        for (int i=0;i<s.size();i++) {
                            if (s[i]>='0'&&s[i]<='9') {
                                int x=0,j=i;
                                while (j<s.size()&&s[j]>='0'&&s[j]<='9') x=x*10+(s[j++]-'0');
                                num.push(x),i=j-1;
                            }
                            else if (s[i] == '(') op.push(s[i]);
                            else if (s[i] == ')') {
                                while (op.top() != '(') calc();
                                op.pop();
                            }
                            else {
                                while (!op.empty() && op.top() != '(' && compare(op.top(), s[i])) calc();
                                op.push(s[i]);
                            }
                        }
                        while (!op.empty()) calc();
                        std::cout << "输出:" << num.top() << "\n计算完成，按任意键返回\n";
                        system("pause");
                        system("cls");
                        writeLog(username, "使用了计算器功能", "表达式：" + s + " 结果：" + std::to_string(num.top()));
                        break;
                    }
                    case 6: {
                        system("cls");
                        std::cout << "即将跳转...";
                        Sleep(1000);
                        system("start https://github.com/dongzheyu/Minecraft-Toos/blob/main/%E4%BF%9D%E5%AE%88%E6%96%87%E4%BB%B6");
                        writeLog(username, "访问了代码彩蛋页面");
                        system("pause");
                        system("cls");
                        break;
                    }
                    case 7: { // 数字炸弹
                        system("cls");
                        int d = rand()%100;
                        while (true) {
                            system("cls");
                            std::cout << "===============数字炸弹==============" << std::endl << "输入你的数吧：";
                            int f;
                            std::cin >> f;
                            if (f>d) {
                                std::cout << "猜大了！继续加油！";
                                writeLog(username, "数字炸弹游戏", "猜测值：" + std::to_string(f) + " 偏大");
                            }
                            else if (f<d) {
                                std::cout << "猜小了！继续加油！";
                                writeLog(username, "数字炸弹游戏", "猜测值：" + std::to_string(f) + " 偏小");
                            }
                            else {
                                std::cout << "恭喜你猜对了！";
                                writeLog(username, "数字炸弹游戏", "正确猜中数字：" + std::to_string(d));
                                system("pause");
                                break;
                            }
                            system("pause");
                        }
                        break;
                    }
                    default:
                        system("cls");
                        MessageBoxW(NULL, L"错误命令！\n按任意键返回主界面...", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                        writeLog(username, "百宝箱操作失败", "无效选项");
                }
                break;
            }
            case 6: {
                setConsoleTitle("Minecraft-Toos-最终用户许可协议（EULA）");
                std::cout << R"(Minecraft-Toos 最终用户许可协议（EULA） 版本：1.0 生效日期：2025年5月21日
本协议由 JetCPP开发团队（以下简称“我们”）与用户（以下简称“您”）签订，约定您使用 Minecraft-Toos 软件及相关服务的条款。请仔细阅读本协议，使用本软件即表示您接受并同意本协议的所有条款。

第一条 接受协议
? 许可授予
我们授予您非独占、不可转让、可撤销的许可，用于在个人非商业目的下安装、运行本软件。
? 适用范围
本协议适用于本软件的所有版本（包括后续更新、补丁和衍生版本），以及随附的文档、工具和资源。

第二条 使用限制
? 禁止行为
您不得：
? 修改、反编译、反向工程本软件（除非法律允许）。
? 通过非官方渠道分发本软件（如破解版本或未经许可的衍生作品）。
? 将本软件用于商业活动（如提供付费服务、批量分发等）。
? 基岩版破解模块
本软件包含的“基岩版破解功能”仅限于个人学习研究用途，不得用于商业用途或侵权行为。
? 您必须遵守所在国家/地区的法律法规，不得利用本功能规避版权保护措施。

第三条 知识产权
? 所有权
本软件及其所有源代码、文档、图标、品牌标识等均属于我们或其授权第三方的财产，受国际版权法保护。
? 开源组件
本软件部分代码采用 MIT License 开源协议（详见 LICENSE 文件），但基岩版破解模块因涉及第三方代码，需遵守另行约定的条款（详见 docs/LICENSE-BREAKER.md）。

第四条 责任限制
? 免责声明
本软件按“现状”提供，不附带任何形式的担保（包括但不限于适销性、特定用途适用性和非侵权性）。
? 我们不对以下情况承担任何责任：
? 因软件使用导致的硬件损坏、数据丢失或系统崩溃。
? 因用户违反本协议（如破解功能滥用）引发的法律纠纷。
? 最高赔偿额
在任何情况下，我们对您的总赔偿责任不得超过您为本软件支付的费用（若为免费软件，则为零）。

第五条 终止条款
? 协议终止
若您违反本协议，我们有权立即终止您的使用权限，并要求您删除本软件及其副本。
? 终止后义务
即使协议终止，您仍需遵守本协议中的知识产权条款和保密义务。

第六条 适用法律
本协议受 中华人民共和国法律 管辖。如发生争议，双方应协商解决；协商不成的，提交 项目发布方所在地人民法院 诉讼解决。

第七条 其他条款
? 协议变更
我们有权随时更新本协议，更新内容将通过项目官网（https://github.com/dongzheyu/Minecraft-Toos）或B站主页（https://space.bilibili.com/3546730880567808）公告。
? 完整协议
本协议构成您与我们之间的完整协议，取代此前所有相关口头或书面协议。

请勿继续使用本软件，除非您完全接受本协议的所有条款。
JetCPP开发团队
2025年5月21日)" << std::endl;
                writeLog(username, "查看了最终用户许可协议");
                system("pause");
                system("cls");
                break;
            }
            default:
                system("cls");
                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                writeLog(username, "主菜单操作失败", "无效选项");
        }
    }
}