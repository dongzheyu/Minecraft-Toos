#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <ctime>
#include <conio.h>
#include <vector>
#include <random>
#include <sstream>
#include <locale>
#include <codecvt>

#pragma execution_character_set("utf-8")

// 宽字符转换工具
std::wstring s2ws(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.from_bytes(str);
}

// 常量定义
const std::string CURRENT_VERSION = "6.5.0";
const std::string ERROR_TITLE = "Minecraft-Toos";

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

int main() {
    system("chcp 65001 > nul");
    system("cls");

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
        } else if (username == "Admin" && password == "DZY@013520") {
            MessageBoxW(NULL, L"登录成功！欢迎管理员使用Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
            isLoggedIn = true;
        } else {
            attempts++;
            std::ostringstream oss;
            oss << "用户不存在或密码错误，剩余尝试次数：" << (maxAttempts - attempts);
            ShowMessageBox(oss.str(), ERROR_TITLE, MB_OK | MB_ICONHAND);
            if (attempts < maxAttempts) {
                ShowMessageBox("请重新输入", ERROR_TITLE, MB_OK | MB_ICONHAND);
                system("cls");
            }
        }
    }

    if (!isLoggedIn) {
        ShowMessageBox("密码尝试次数已用完，Minecraft-Toos即将退出……", ERROR_TITLE, MB_OK | MB_ICONASTERISK);
        return 1;
    }

    system("cls");

    // 主菜单循环
    int n, g;
    while (true) {
        system("title Minecraft-Toos-主页");
        std::cout << "\n###############################\n欢迎使用Minecraft Toos\n###############################\n"
                  << "\n==============================================\n"
                  << "运行时:C++21      MinGW版本：14.2    cmake版本：4.0.2\n"
                  << "编译器版本：Jetbrains Clion 2025.1.1     当前版本：" << CURRENT_VERSION << "正式版\n"
                  << "==============================================\n\n"
                  << "[1]功能大全 [2]赞助作者 [3]关于 [4]退出 [5]百宝箱\n Enter your numbers:";

        if (!(std::cin >> n)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            ShowMessageBox("输入无效，请重新输入", ERROR_TITLE, MB_OK | MB_ICONHAND);
            system("cls");
            continue;
        }

        switch(n){
            case 1: { // 功能大全
                system("title Minecraft-Toos-功能大全");
                system("cls");
                std::cout << "###########################\n         功能大全           \n###########################\n\n"
                          << "[1]启动PCL2CE [2]启动Hello Minecraft!Launcher [3]下载基岩版 [4]破解基岩版\n"
                          << "[5]配置java环境 [6]查看教程/问题解答 [7]退出 [8]服务器选项 [9]返回\n"
                          << "[10]有用没啥用的网站 [11]注册微软账户 [12]游戏内功能\nenter your numbers:";
                std::cin >> g;

                switch(g){
                    case 1:
                        system("cls");
                        system("start pcl2.exe");
                        MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        system("start HMCL.exe");
                        MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        system("pause");
                        system("cls");
                        break;
                    case 3: {
                        system("cls");
                        MessageBoxW(NULL, L"即将使用程序包安装Minecraft基岩版", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        Sleep(300);
                        system("start MinecraftUWP.Appx");
                        MessageBoxW(NULL, L"安装成功！\n请使用微软商店打开Minecraft基岩版", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        system("pause");
                        system("cls");
                        break;
                    }
                    case 4:
                        system("cls");
                        system("start po.bat");
                        MessageBoxW(NULL, L"破解程序启动成功！\n请点击Install Mode进行破解", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
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
                                MessageBoxW(NULL, L"恭喜，JAVA已安装完成！", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                system("cls");
                                break;
                            case 2:
                                system("cls");
                                system("start JDK-17.exe");
                                MessageBoxW(NULL, L"恭喜，JAVA已安装完成！", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                system("cls");
                                break;
                            case 3:
                                system("cls");
                                system("start JDK-21.exe");
                                MessageBoxW(NULL, L"恭喜，JAVA已安装完成！", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                break;
                            case 4:
                                system("cls");
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
                                break;
                            default:
                                system("cls");
                                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                                system("pause");
                                system("cls");
                        }
                        break;
                    }
                    case 6:
                        system("cls");
                        system("start https://dongzheyu.github.io/Minecraft-Toos_Help.html");
                        MessageBoxW(NULL, L"官方帮助页面已打开！请进行浏览", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                        system("cls");
                        break;
                    case 7:
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
                                system("cls");
                                break;
                            case 2:
                                system("start MCSL2/MCSL2.exe");
                                MessageBoxW(NULL, L"启动成功！\n如果启动失败请重新从官网下载最新版Minecraft-Toos", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
                                system("cls");
                                break;
                            default:
                                system("cls");
                                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                                system("pause");
                                system("cls");
                        }
                        break;
                    case 9:
                        system("cls");
                        break;
                    case 10: {
                        system("cls");
                        std::cout << "========================\n       有用没啥用的网站\n========================\n"
                                  << "[1]MC百科 [2]forge [3]我的世界中文站 [4]3DM [5]返回 [6]购买正版 [7]网站软件大全(第三方)\n enter your numbers:";
                        int d;
                        std::cin >> d;
                        switch(d) {
                            case 1: system("start https://www.mcmod.cn/"); break;
                            case 2: system("start https://files.minecraftforge.net/"); break;
                            case 3: system("start https://www.minecraftzw.com/mods"); break;
                            case 4: system("start https://mod.3dmgame.com/Minecraft"); break;
                            case 6: system("start https://www.xbox.com/zh-CN/games/store/minecraft-java-bedrock-edition-for-pc"); break;
                            case 7: {
                                system("cls");
                                std::cout << "本网站是第三方，未经过作者验证。是否前往？\n[1]是[2]否";
                                int h;
                                std::cin >> h;
                                if (h == 1) system("start https://www.mcnav.net/");
                                break;
                            }
                            default: break;
                        }
                        break;
                    }
                    case 11:
                        system("start https://signup.live.com/signup?client_id=81feaced-5ddd-41e7-8bef-3e20a2689bb7");
                        MessageBoxW(NULL, L"微软账户注册页面已打开！", L"Minecraft-Toos", MB_OK|MB_ICONASTERISK);
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
                                system("pause");
                                system("cls");
                                break;
                            }
                            default:
                                system("cls");
                                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                        }
                    }
                }
                break;
            }
            case 2: { // 赞助作者
                system("title Minecraft-Toos-赞助作者");
                system("cls");
                std::cout << "===========\n赞助作者\n===========\n[1]爱发电(付费) [2]GitHub(免费) [3]返回\n Enter your numbers:";
                int x;
                std::cin >> x;
                switch (x){
                    case 1:
                        system("start https://afdian.tv/a/JetCPP");
                        break;
                    case 2:
                        system("start https://github.com/dongzheyu/Minecraft_Toos");
                        break;
                    case 3:
                        system("cls");
                        break;
                    default:
                        system("cls");
                        MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
                }
                break;
            }
            case 3: { // 关于页面
                system("cls");
                std::cout << "###############         关于        ##############\n"
                          << "开发人员：bilibili 我是dongle \n"
                          << "运行时：C++20 \n"
                          << "开发软件：Visual Studio 2022、Clion \n"
                          << "B站主页：https://space.bilibili.com/3546730880567808 \n"
                          << "GitHub开源主页：https://github.com/dongzheyu/Minecraft-Toos/ \n"
                          << "Copyright ? JetCPP 2024-2025 保留所有权利 \n"
                          << "#######################################################\n\n\n\n\n\n记得赞助作者哦~~~";
                system("pause");
                system("cls");
                break;
            }
            case 4:
                return 0;
            case 5: { // 百宝箱
                system("title Minecraft-Toos-百宝箱");
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
                        break;
                    }
                    case 6: {
                        system("cls");
                        std::cout << "即将跳转...";
                        Sleep(1000);
                        system("start https://github.com/dongzheyu/Minecraft-Toos/blob/main/%E4%BF%9D%E4%BD%91%E6%96%87%E4%BB%B6");
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
                            if (f>d) std::cout << "猜大了！继续加油！";
                            else if (f<d) std::cout << "猜小了！继续加油！";
                            else {
                                std::cout << "恭喜你猜对了！";
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
                }
                break;
            }
            default:
                system("cls");
                MessageBoxW(NULL, L"错误命令，点击确定回到主界面", L"Minecraft-Toos", MB_OK|MB_ICONHAND);
        }
    }
}
