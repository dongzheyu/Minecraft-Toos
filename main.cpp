/*
//                            _ooOoo_
//                           o8888888o
//                           88" . "88
//                           (| -_- |)
//                            O\ = /O
//                        ____/`---'\____
//                      .   ' \\| |// `.
//                       / \\||| : |||// \
//                     / _||||| -:- |||||- \
//                       | | \\\ - /// | |
//                     | \_| ''\---/'' | |
//                      \ .-\__ `-` ___/-. /
//                   ___`. .' /--.--\ `. . __
//                ."" '< `.___\_<|>_/___.' >'"".
//               | | : `- \`.;`\ _ /`;.`/ - ` : | |
//                 \ \ `-. \_ __\ /__ _/ .-` / /
//         ======`-.____`-.___\_____/___.-`____.-'======
//                            `=---='
//
//         .............................................
//                  佛祖保佑             永无BUG
*/

#include <bits/stdc++.h>
#include <windows.h>
#include <limits>
using namespace std;
const string CURRENT_VERSION = "6.4.0"; // 当前版本号
stack<int>num;
stack<char>op;
void calc() {
    int a,b,c;
    a=num.top(),num.pop(),b=num.top(),num.pop(),c=op.top(),op.pop(); // NOLINT(*-str34-c)
    int x=c=='+'?a+b:c=='-'?b-a:c=='/'?b/a:a*b;
    num.push(x);
}
bool compare(char a,char b) {
    int x=a=='+'||a=='-'?1:2,y=b=='*'||b=='/'?2:1;
    return x>=y;
}
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayWelcome() {
    cout << "============== Minecraft-Toos ==============\n";
    cout << "============== Login ================\n\n";
}
int main(){
    int n,g;
    system("cls");
    string username, password;
    bool isLoggedIn = false;
    int attempts = 0;
    const int maxAttempts = 3;
    while (!isLoggedIn && attempts < maxAttempts) {
        displayWelcome();

        // 输入用户名
        cout << "用户名: ";
        getline(cin, username);

        // 输入密码
        cout << "密码: ";
        getline(cin, password);

        // 验证凭证
        if (username == "User" && password == "12345678") {
            cout << "\n登录成功！欢迎普通用户使用Minecraft-Toos\n";
            Sleep(3000);
            isLoggedIn = true;
        } else if (username == "Admin" && password == "DZY@013520") {
            cout << "\n登录成功！欢迎管理员使用Minecraft-Toos\n";
            isLoggedIn = true;
            Sleep(3000);
        } else {
            attempts++;
            cout << "\n错误：用户名或密码不正确（剩余尝试次数: "
                 << maxAttempts - attempts << "）\n\n";

            if (attempts < maxAttempts) {
                cout << "请重新输入...\n";
                system("pause");
                system("cls");
                // 清空输入缓冲区
                clearInputBuffer();
            }
        }
    }

    if (!isLoggedIn) {
        cout << "\n错误：超过最大尝试次数，系统即将退出\n";
        Sleep(3000);
        return 1;
    }
    system("cls");
    while(true){
        system("title Minecraft-Toos-主页");
        cout<<endl<<"###############################\n"<<"欢迎使用Minecraft Toos"<<endl<<"###############################\n"<<endl;
        cout<<"\n==============================================\n运行时:C++21      minGW版本：14.0    cmake版本：4.0.0\n编译器版本：Jetbrains Clion 2025.1Beta     当前版本：6.4.0正式版\n==============================================\n\n";
        cout<<"[1]功能大全 [2]赞助作者 [3]关于 [4]退出 [5]百宝箱\n Enter your numbers:";
        cin>>n;
        switch(n){
        case 1:
            system("title Minecraft-Toos-功能大全");
             system("cls");
                cout<<"###########################\n         功能大全           \n###########################\n\n"<<"[1]启动PCL2CE [2]启动Hello Minecraft!Launcher [3]下载基岩版 [4]破解基岩版\n[5]配置java环境 [6]查看教程/问题解答 [7]退出 [8]服务器选项 [9]返回\n[10]有用没啥用的网站 [11]注册微软账户(以后买游戏用微软的功能更方便)"<<endl<<"enter your numbers:";
            cin>>g;
                switch(g){
                case 1:
                    system("cls");
                    cout<<"请稍等，正在启动pcl2 CE启动器（^……^）";
                    Sleep(300);
                    system("start pcl2.exe");
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    cout<<"即将启动...";
                    Sleep(1000);
                    system("start HMCL.exe");
                    cout<<endl<<"启动完成！！！\n";
                    system("pause");
                    system("cls");
                    break;
                case 3: {
                    system("cls");
                    cout<<"即将使用程序包安装Minecraft基岩版";
                    Sleep(300);
                    system("start MinecraftUWP1.21.71.Appx");
                    cout<<"\n请在打开的程序包安装程序中点击安装即可安装Minecraft基岩版\n";
                    system("pause");
                    system("cls");
                    break;
                }
                case 4:
                    system("cls");
                    cout<<"正在启动...";
                    Sleep(300);
                    system("start po.bat");
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    cout<<"请选择安装内容：\n[1]安装java8 [2]安装java17 [3]安装java21 [4]全部安装（建议）\n enter your numbers:";
                    int m;
                    cin>>m;
                    switch(m){
                    case 1:
                        system("cls");
                        system("start JDK-8.exe");
                        cout<<"请等待安装程序完成...";
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        system("start JDK-17.exe");
                        cout<<"请等待安装程序完成...";
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        system("cls");
                        system("start JDK-21.exe");
                        cout<<"请等待安装程序完成...";
                        system("pause");
                        system("cls");
                        break;
                    case 4:
                        system("cls");
                        system("start JDK-8.exe");
                        cout<<"请等待安装程序完成再按任意键！！！";
                        system("pause");
                        system("cls");
                        system("start JDK-17.exe");
                        cout<<"请等待安装程序完成再按任意键！！！";
                        system("pause");
                        system("cls");
                        system("start JDK-21.exe");
                        cout<<"请等待安装程序完成再按任意键！！！";
                        system("pause");
                        system("cls");
                        break;

                    default:
                        system("cls");
                        cout<<"错误命令！\n按任意键返回主界面...";
                        system("pause");
                        system("cls");
                        break;

                    }
                    break;
                case 6:
                    system("cls");
                    system("start https://space.bilibili.com/3546730880567808");
                    cout<<"请再打开的主页内寻找教程和问题解答\n记得点个关注哦！\n如果有其他问题还可以发私信哦！";
                    system("pause");
                    system("cls");
                    break;
                case 7:
                    return 0;
                case 8:
                    system("cls");
                    cout<<"请问您要是用哪个服务器软件？\n [1]MSL [2]MCSL2\n";
                    int x;
                    cin>>x;
                    switch (x){
                    case 1:
                        system("cls");
                        system("start MSL.exe");
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        system("start MCSL2/MCSL2.exe");
                        cout<<"即将返回主页";
                        system("pause");
                        system("cls");
                        break;
                    default:
                        system("cls");
                        cout<<"错误命令！\n按任意键返回主界面...\n";
                        system("pause");
                        system("cls");
                        break;
                    }
                    system("cls");
                    break;
                    default:
                        system("cls");
                        cout<<"错误命令！！！按任意键返回主界面...\n";
                        system("pause");
                        system("cls");
                        break;
                    case 9:
                       system("cls");
                       break;
                    case 10: {
                        system("cls");
                        cout<<"========================\n       有用没啥用的网站\n========================\n";
                        cout<<"[1]MC百科 [2]forge [3]我的世界中文站 [4]3DM [5]返回 [6]购买正版 [7]网站软件大全(第三方)\n enter your numbers:";
                        int d;
                        cin>>d;
                        switch (d) {
                            case 1: {
                                system("cls");
                                system("start https://www.mcmod.cn/");
                                cout<<"打开成功!按任意键返回";
                                system("pause");
                                break;
                            }case 2: {
                                system("cls");
                                system("start https://files.minecraftforge.net/net/minecraftforge/forge/index_1.21.4.html");
                                cout<<"打开成功!按任意键返回";
                                system("pause");
                                break;
                            }
                            case 3: {
                                system("cls");
                                system("start https://www.minecraftzw.com/mods");
                                cout<<"打开成功!按任意键返回";
                                system("pause");
                                break;
                            }
                            case 4: {
                                system("cls");
                                system("start https://mod.3dmgame.com/Minecraft");
                                cout<<"打开成功!按任意键返回";
                                system("pause");
                                break;
                            }
                            case 5: {
                                system("cls");
                                break;
                            }
                            case 6: {
                                system("cls");
                                cout<<"即将打开MC官网进行购买"<<endl;
                                system("pause");
                                system("start https://www.minecraft.net/zh-hans/store/minecraft-deluxe-collection-pc");
                                system("cls");
                                break;
                            }
                            case 7: {
                                system("cls");
                                cout<<"本网站是第三方，未经过作者验证。是否前往？\n[1]是[2]否";
                                int h;
                                cin>>h;
                                if (h==1) system("start https://www.mcnav.net/");
                                else if (h==2) {
                                    system("cls");
                                    break;
                                }
                                else {
                                    system("cls");
                                    cout<<"错误，按任意键返回\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                            }
                            default: {
                                system("cls");
                                cout<<"错误命令！\n按任意键返回主界面...\n";
                                system("pause");
                                system("cls");
                                break;
                            }
                        }
                        break;
                    }
                    case 11: {
                        system("cls");
                        cout<<"即将打开微软账户注册界面！！！";
                        Sleep(1000);
                        system("start https://signup.live.com/signup?client_id=81feaced-5ddd-41e7-8bef-3e20a2689bb7&contextid=7DEDD1D8A4562C09&opid=1603ED0C1B44371E&bk=1738334094&sru=https://login.live.com/oauth20_authorize.srf%3fclient_id%3d81feaced-5ddd-41e7-8bef-3e20a2689bb7%26client_id%3d81feaced-5ddd-41e7-8bef-3e20a2689bb7%26contextid%3d7DEDD1D8A4562C09%26opid%3d1603ED0C1B44371E%26mkt%3dZH-CN%26lc%3d2052%26bk%3d1738334094%26uaid%3d1ea18c1ab2034275b5a43e7be0160aff&lw=easi2&fl=1&uiflavor=web&lic=1&mkt=ZH-CN&lc=2052&uaid=1ea18c1ab2034275b5a43e7be0160aff");
                        system("cls");
                        break;
                    }
                }
            break;
        case 2:
            system("title Minecraft-Toos-赞助作者");
            system("cls");
            int x;
            cout<<"===========\n赞助作者\n===========\n";
            cout<<"请选择主页：\n [1]bilibili [2]GitHub [3]返回\n Enter your numbers:";
            cin>>x;
            switch (x){
               case 1:
                 system("cls");
                 system("start https://space.bilibili.com/3546730880567808");
                 cout<<"B站主页已打开，记得点个关注哦！";
                 system("pause");
                 system("cls");
                 break;
               case 2:
                 system("cls");
                 system("start https://github.com/dongzheyu/Minecraft_Toos");
                 cout<<"GitHub打开成功！不要吝啬您的星星哦~~~~\n按任意键返回\n";
                 system("pause");
                system("cls");
                break;
                case 3:
                    system("cls");
                    break;
                default:
                    system("cls");
                    cout<<"错误（0x45）：未匹配的命令\n按任意键返回";
                    system("pause");
                    system("cls");
                    break;

            }
            break;
        case 3:{
            system("Minecraft-Toos-关于");
            system("cls");
            cout<<"###############         关于        ##############\n 开发人员：bilibili 我是dongle \n 运行时：C++20 \n 开发软件：Visual Studio 2022、Clion \n B站主页：https://space.bilibili.com/3546730880567808 \n GitHub开源主页：https://github.com/dongzheyu/Minecraft-Toos/ \n bilibili 我是dongle(C) 保留所有权利 \n#######################################################\n\n\n\n\n\n记得赞助作者哦~~~";
            system("pause");
                system("cls");
                break;
}
        case 4:
            return 1;
        case 5:
            system("title Minecraft-Toos-百宝箱");
            system("cls");
            cout<<"====================\n百宝箱\n======================\n";
            cout<<"[1]当前时间 [2]闪瞎你的勾眼 [3]返回 [4]new hands攻略(新手攻略)  [5]计算器  [6]代码彩蛋 [7]数字炸弹...(欢迎大家投稿,作者是个C++新手但我会尽量开发的！！！)\n enter your numbers:";
            int c;
            cin>>c;
            switch (c) {
                case 1: {
                    int i=0;
                    while (i<20) {
                        system("cls");
                        time_t nowtime;
                        time(&nowtime); //获取1970年1月1日0点0分0秒到现在经过的秒数
                        tm p; // NOLINT(*-pro-type-member-init)
                        localtime_s(&p,&nowtime); //将秒数转换为本地时间,年从1900算起,需要+1900,月为0-11,所以要+1
                        cout<<"当前本地时间：\n";
                        printf("%04d:%02d:%02d %02d:%02d:%02d\n", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday,p.tm_hour,p.tm_min,p.tm_sec);
                        cout<<"本界面20秒后会自动返回";
                        Sleep(1000);
                        i++;
                    }
                    system("cls");
                    break;
                }
                case 2: {
                    system("cls");
                    cout<<"食用提示：本功能不适用于有光滩病患者和眼睛有问题的选手\n[1]继续  [2]返回\n enter your numbers:";
                    int f;
                    cin>>f;
                    switch (f) {
                        case 1: {
                            system("cls");
                            cout<<"好东西将在三秒后开始";
                            Sleep(1000);
                            system("cls");
                            cout<<"好东西将在二秒后开始";
                            Sleep(1000);
                            system("cls");
                            cout<<"好东西将在一秒后开始";
                            Sleep(1000);
                            system("cls");
                            cout<<"开始了！！！";
                            Sleep(1000);
                            system("cls");
                            int i=0;
                            while (i<50) {
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
                                i++;
                            }
                            system("cls");
                            system("color 07");
                            cout<<"你眼睛瞎了吗？都闪了这么久了\n休息一下吧~~~\n";
                            system("pause");
                            system("cls");
                            system("shutdown /s /t 40");
                            cout<<"为了让您的眼睛休息，computer将在40秒后关机！！！\n如果有工作没保存，赶紧保存去！！！\n(如果你不想关机把这个复制到cmd里吧(shutdown /a))\n";
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 2: {
                            system("cls");
                            system("color 07");
                            cout<<"即将返回";
                            Sleep(3000);
                            system("cls");
                            break;
                        }
                        default: {
                            system("cls");
                            cout<<"错误命令！\n按任意键返回主界面...\n";
                            system("pause");
                            system("cls");
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    system("cls");
                    break;
                }
                case 4: {
                    system("cls");
                    cout<<"新手攻略"
"\n- 了解游戏模式："
"\n- 生存模式：这是游戏的基础模式，你需要收集资源、建造庇护所、抵御怪物攻击，努力生存下去。在这个模式中，你的生命值、饥饿值等属性会不断变化，需要时刻关注并维持。"
"\n- 创造模式：你拥有无限的资源，可以自由地建造各种建筑和设施，不用担心生存问题，主要用于发挥创意和设计。"
"\n- 极限模式：与生存模式类似，但难度更高，只有一条生命，一旦死亡游戏就会结束。"
"\n- 调整游戏设置：进入游戏后，在设置选项中可以根据自己的电脑配置和个人喜好调整画面质量、音效、控制方式等。例如，如果你的电脑性能较低，可以将画面质量调低以提高游戏的流畅度。"
"\n初期生存要点："
"\n- 收集资源："
"\n- 砍树：进入游戏后，首先要找到一棵树，用手或工具敲击树干获取木头。木头是最基础的资源，可用于制作工作台、工具、武器等。尽量多收集一些木头，以备后续使用。"
"\n- 制作工作台：按“E”键打开背包，将收集到的木头转化为木板，然后用木板制作一个工作台。工作台是制作其他物品的重要工具，它提供了更多的合成配方和空间。"
"\n- 挖掘石头：使用木镐（用木板和木棍合成）挖掘地上的石头，获取圆石。圆石可以用来制作石镐、石剑、熔炉等工具和设备。"
"\n- 建造庇护所："
"\n- 选择地点：找一个平坦、安全且资源丰富的地方建造庇护所。最好靠近水源，方便获取水；同时，避免选择在悬崖边、沙漠中心等危险或资源匮乏的地方。"
"\n- 建造房屋：用木头和石头等材料搭建一个简单的房屋，可以是一个小木屋或石头房子。确保房屋有门和窗户，以便进出和采光。在房屋内放置一张床，这样即使死亡也能在家附近复活。"
"\n- 设置照明：在庇护所内和周围放置火把，用火把照亮可以防止怪物在黑暗中生成。你可以用煤炭或木炭（通过烧木头获得）与木棍合成火把。"
"\n食物获取与管理："
"\n- 初期食物来源：在游戏初期，可以通过打猎或采集来获取食物。比如，杀死鸡可以获得鸡肉和羽毛，杀死牛可以获得牛肉和皮革，羊可以提供羊肉和羊毛。此外，还可以采集苹果、胡萝卜等农作物（如果能找到的话）。"
"\n- 烹饪食物：生肉直接食用恢复的饥饿值较少，且可能会有负面效果，所以需要用熔炉将生肉烤熟。将生肉放在熔炉的上面格子，下面放燃料（如煤炭、木头等），等待一段时间后肉就会烤熟。"
"\n- 种植农作物：当你找到合适的土地后，可以用锄头开垦土地，然后种植小麦、胡萝卜等农作物。农作物需要水和光照才能生长，所以要确保种植区域有足够的水源和阳光。"
"\n探索与挖矿："
"\n- 探索周围环境：白天是探索的好时机，你可以四处走走，了解周围的地形和资源分布。注意观察是否有村庄、洞穴、河流等地方，这些地方可能会有有用的资源和宝藏。"
"\n- 挖矿技巧："
"\n- 挖掘工具：随着游戏的进展，不断升级你的挖矿工具。石镐可以挖掘铁矿和煤矿，铁镐可以挖掘更高级的矿石，如钻石矿。制作工具时，注意选择合适的材料和配方。"
"\n- 寻找矿洞：自然生成的矿洞是获取矿石的好地方，但里面也可能存在怪物，所以在进入矿洞前要做好准备，带上武器和足够的火把。在矿洞中挖掘时，要注意观察周围的环境，避免掉进陷阱或迷失方向。"
"\n- 标记路线：在挖矿过程中，很容易迷失方向，所以可以用一些方法标记自己的路线，比如在沿途的墙壁上放置火把或用方块标记。"
"\n安全防范："
"\n- 抵御怪物攻击：夜晚会有各种怪物出现，如僵尸、骷髅、蜘蛛等。制作一把剑和一个盾牌来抵御怪物的攻击。盾牌可以抵挡怪物的近战攻击，剑则用于反击。"
"\n- 设置陷阱：在庇护所周围设置一些简单的陷阱，如陷阱坑、仙人掌陷阱等，可以有效地阻止怪物的靠近。"
"\n- 避免危险行为：不要轻易跳进未知的洞穴或深渊，以免掉进陷阱或受到伤害。在探索陌生区域时，要保持警惕，随时准备应对可能出现的危险。"
"\n后期发展："
"\n- 附魔与药水：当你拥有足够的资源后，可以制作附魔台和药水酿造台。附魔可以为你的工具、武器和装备增加额外的属性，如攻击力、耐久度等；药水可以在战斗中提供各种增益效果，如治疗、加速、力量增强等。"
"\n- 养殖动物：养殖动物可以为你提供稳定的食物来源。建造一个动物农场，用小麦等食物吸引动物进入，然后用围栏将它们围住。定期喂养动物，它们就会繁殖后代。"
"\n- 参与交易：如果你找到村庄，可以与村民进行交易。村民会提供各种物品和服务，你可以用自己的资源与他们交换所需的物品。\n\n\n\n\n\n\n\n"
"(以上内容来源于豆包（doubao.com）)按任意键返回\n";
                    system("pause");
                    system("cls");
                    break;
                }
                case 5: {
                    system("cls");
                    cout<<"计算器(基于bilibili我是dongle的C++计算器改良升级支持小括号和加减乘除运算)\n注意小括号必须是英文的！！！否则会卡崩！！！\n输入：";
                    string s;
                    cin>>s;
                    for (int i=0;i<s.size();i++) {
                        if (s[i]>='0'&&s[i]<='9') {
                            int x=0,j=i;
                            while (j<s.size()&&s[j]>='0'&&s[j]<='9') x=x*10+(s[j++]-'0');
                            num.push(x),i=j-1;
                        }
                        else if (s[i]=='(') op.push(s[i]);
                        else if (s[i]==')') {
                            while (op.top()!='(') calc();
                            op.pop();
                        }
                        else {
                            while (op.size()&&op.top()!='('&&compare(op.top(),s[i])) calc(); // NOLINT(*-container-size-empty)
                            op.push(s[i]);
                        }
                    }
                    while (op.size()) calc(); // NOLINT(*-container-size-empty)
                    cout<<"输出:"<<num.top()<<"\n计算完成，按任意键返回\n";
                    system("pause");
                    system("cls");
                    break;
                }
                default:
                    system("cls");
                system("cls");
                cout<<"错误命令！\n按任意键返回主界面...\n";
                system("pause");
                system("cls");
                break;
                case 6: {
                    system("cls");
                    cout<<"即将跳转...";
                    Sleep(1000);
                    system("start https://github.com/dongzheyu/Minecraft-Toos/blob/main/%E4%BF%9D%E4%BD%91%E6%96%87%E4%BB%B6");
                    system("pause");
                    system("cls");
                    break;
                }
                case 7: {
                    system("cls");
                    int o=0;
                    cout<<"===============数字炸弹=============="<<endl;
                    while (o<=10) {
                        system("cls");
                        cout<<"===============数字炸弹=============="<<endl;
                        cout<<"正在生成随机数(范围：0~100)(需要10s).";
                        Sleep(1000);
                        cout<<".";
                        o++;
                        Sleep(1000);
                        cout<<".";
                        o++;
                        Sleep(1000);
                        cout<<".";
                        o++;
                    }
                    system("cls");
                    while (true) {
                        system("cls");
                        cout<<"===============数字炸弹=============="<<endl<<"输入你的数吧：";
                        int d=rand()%100,f;
                        cin>>f;
                        if (f>d) {
                            cout<<"猜大了！继续加油！";
                            system("pause");
                        }
                        if (f==d) {
                            cout<<"恭喜你猜对了！";
                            system("pause");
                            system("cls");
                            break;
                        }
                        if (f<d) {
                            cout<<"猜小了！继续加油！";
                            system("pause");
                        }
                    }
                    break;
                }
            }
        break;
        default:
            system("cls");
            cout<<"错误命令！\n按任意键返回主界面...\n";
            system("pause");
            system("cls");
            break;
            }
    }
}