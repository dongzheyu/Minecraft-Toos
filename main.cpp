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
//                  ���汣��             ����BUG
*/

#include <bits/stdc++.h>
#include <windows.h>
#include <limits>
using namespace std;
const string CURRENT_VERSION = "6.4.0"; // ��ǰ�汾��
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

        // �����û���
        cout << "�û���: ";
        getline(cin, username);

        // ��������
        cout << "����: ";
        getline(cin, password);

        // ��֤ƾ֤
        if (username == "User" && password == "12345678") {
            cout << "\n��¼�ɹ�����ӭ��ͨ�û�ʹ��Minecraft-Toos\n";
            Sleep(3000);
            isLoggedIn = true;
        } else if (username == "Admin" && password == "DZY@013520") {
            cout << "\n��¼�ɹ�����ӭ����Աʹ��Minecraft-Toos\n";
            isLoggedIn = true;
            Sleep(3000);
        } else {
            attempts++;
            cout << "\n�����û��������벻��ȷ��ʣ�ೢ�Դ���: "
                 << maxAttempts - attempts << "��\n\n";

            if (attempts < maxAttempts) {
                cout << "����������...\n";
                system("pause");
                system("cls");
                // ������뻺����
                clearInputBuffer();
            }
        }
    }

    if (!isLoggedIn) {
        cout << "\n���󣺳�������Դ�����ϵͳ�����˳�\n";
        Sleep(3000);
        return 1;
    }
    system("cls");
    while(true){
        system("title Minecraft-Toos-��ҳ");
        cout<<endl<<"###############################\n"<<"��ӭʹ��Minecraft Toos"<<endl<<"###############################\n"<<endl;
        cout<<"\n==============================================\n����ʱ:C++21      minGW�汾��14.0    cmake�汾��4.0.0\n�������汾��Jetbrains Clion 2025.1Beta     ��ǰ�汾��6.4.0��ʽ��\n==============================================\n\n";
        cout<<"[1]���ܴ�ȫ [2]�������� [3]���� [4]�˳� [5]�ٱ���\n Enter your numbers:";
        cin>>n;
        switch(n){
        case 1:
            system("title Minecraft-Toos-���ܴ�ȫ");
             system("cls");
                cout<<"###########################\n         ���ܴ�ȫ           \n###########################\n\n"<<"[1]����PCL2CE [2]����Hello Minecraft!Launcher [3]���ػ��Ұ� [4]�ƽ���Ұ�\n[5]����java���� [6]�鿴�̳�/������ [7]�˳� [8]������ѡ�� [9]����\n[10]����ûɶ�õ���վ [11]ע��΢���˻�(�Ժ�����Ϸ��΢��Ĺ��ܸ�����)"<<endl<<"enter your numbers:";
            cin>>g;
                switch(g){
                case 1:
                    system("cls");
                    cout<<"���Եȣ���������pcl2 CE��������^����^��";
                    Sleep(300);
                    system("start pcl2.exe");
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    cout<<"��������...";
                    Sleep(1000);
                    system("start HMCL.exe");
                    cout<<endl<<"������ɣ�����\n";
                    system("pause");
                    system("cls");
                    break;
                case 3: {
                    system("cls");
                    cout<<"����ʹ�ó������װMinecraft���Ұ�";
                    Sleep(300);
                    system("start MinecraftUWP1.21.71.Appx");
                    cout<<"\n���ڴ򿪵ĳ������װ�����е����װ���ɰ�װMinecraft���Ұ�\n";
                    system("pause");
                    system("cls");
                    break;
                }
                case 4:
                    system("cls");
                    cout<<"��������...";
                    Sleep(300);
                    system("start po.bat");
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    cout<<"��ѡ��װ���ݣ�\n[1]��װjava8 [2]��װjava17 [3]��װjava21 [4]ȫ����װ�����飩\n enter your numbers:";
                    int m;
                    cin>>m;
                    switch(m){
                    case 1:
                        system("cls");
                        system("start JDK-8.exe");
                        cout<<"��ȴ���װ�������...";
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        system("cls");
                        system("start JDK-17.exe");
                        cout<<"��ȴ���װ�������...";
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        system("cls");
                        system("start JDK-21.exe");
                        cout<<"��ȴ���װ�������...";
                        system("pause");
                        system("cls");
                        break;
                    case 4:
                        system("cls");
                        system("start JDK-8.exe");
                        cout<<"��ȴ���װ��������ٰ������������";
                        system("pause");
                        system("cls");
                        system("start JDK-17.exe");
                        cout<<"��ȴ���װ��������ٰ������������";
                        system("pause");
                        system("cls");
                        system("start JDK-21.exe");
                        cout<<"��ȴ���װ��������ٰ������������";
                        system("pause");
                        system("cls");
                        break;

                    default:
                        system("cls");
                        cout<<"�������\n�����������������...";
                        system("pause");
                        system("cls");
                        break;

                    }
                    break;
                case 6:
                    system("cls");
                    system("start https://space.bilibili.com/3546730880567808");
                    cout<<"���ٴ򿪵���ҳ��Ѱ�ҽ̳̺�������\n�ǵõ����עŶ��\n������������⻹���Է�˽��Ŷ��";
                    system("pause");
                    system("cls");
                    break;
                case 7:
                    return 0;
                case 8:
                    system("cls");
                    cout<<"������Ҫ�����ĸ������������\n [1]MSL [2]MCSL2\n";
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
                        cout<<"����������ҳ";
                        system("pause");
                        system("cls");
                        break;
                    default:
                        system("cls");
                        cout<<"�������\n�����������������...\n";
                        system("pause");
                        system("cls");
                        break;
                    }
                    system("cls");
                    break;
                    default:
                        system("cls");
                        cout<<"����������������������������...\n";
                        system("pause");
                        system("cls");
                        break;
                    case 9:
                       system("cls");
                       break;
                    case 10: {
                        system("cls");
                        cout<<"========================\n       ����ûɶ�õ���վ\n========================\n";
                        cout<<"[1]MC�ٿ� [2]forge [3]�ҵ���������վ [4]3DM [5]���� [6]�������� [7]��վ�����ȫ(������)\n enter your numbers:";
                        int d;
                        cin>>d;
                        switch (d) {
                            case 1: {
                                system("cls");
                                system("start https://www.mcmod.cn/");
                                cout<<"�򿪳ɹ�!�����������";
                                system("pause");
                                break;
                            }case 2: {
                                system("cls");
                                system("start https://files.minecraftforge.net/net/minecraftforge/forge/index_1.21.4.html");
                                cout<<"�򿪳ɹ�!�����������";
                                system("pause");
                                break;
                            }
                            case 3: {
                                system("cls");
                                system("start https://www.minecraftzw.com/mods");
                                cout<<"�򿪳ɹ�!�����������";
                                system("pause");
                                break;
                            }
                            case 4: {
                                system("cls");
                                system("start https://mod.3dmgame.com/Minecraft");
                                cout<<"�򿪳ɹ�!�����������";
                                system("pause");
                                break;
                            }
                            case 5: {
                                system("cls");
                                break;
                            }
                            case 6: {
                                system("cls");
                                cout<<"������MC�������й���"<<endl;
                                system("pause");
                                system("start https://www.minecraft.net/zh-hans/store/minecraft-deluxe-collection-pc");
                                system("cls");
                                break;
                            }
                            case 7: {
                                system("cls");
                                cout<<"����վ�ǵ�������δ����������֤���Ƿ�ǰ����\n[1]��[2]��";
                                int h;
                                cin>>h;
                                if (h==1) system("start https://www.mcnav.net/");
                                else if (h==2) {
                                    system("cls");
                                    break;
                                }
                                else {
                                    system("cls");
                                    cout<<"���󣬰����������\n";
                                    system("pause");
                                    system("cls");
                                    break;
                                }
                            }
                            default: {
                                system("cls");
                                cout<<"�������\n�����������������...\n";
                                system("pause");
                                system("cls");
                                break;
                            }
                        }
                        break;
                    }
                    case 11: {
                        system("cls");
                        cout<<"������΢���˻�ע����棡����";
                        Sleep(1000);
                        system("start https://signup.live.com/signup?client_id=81feaced-5ddd-41e7-8bef-3e20a2689bb7&contextid=7DEDD1D8A4562C09&opid=1603ED0C1B44371E&bk=1738334094&sru=https://login.live.com/oauth20_authorize.srf%3fclient_id%3d81feaced-5ddd-41e7-8bef-3e20a2689bb7%26client_id%3d81feaced-5ddd-41e7-8bef-3e20a2689bb7%26contextid%3d7DEDD1D8A4562C09%26opid%3d1603ED0C1B44371E%26mkt%3dZH-CN%26lc%3d2052%26bk%3d1738334094%26uaid%3d1ea18c1ab2034275b5a43e7be0160aff&lw=easi2&fl=1&uiflavor=web&lic=1&mkt=ZH-CN&lc=2052&uaid=1ea18c1ab2034275b5a43e7be0160aff");
                        system("cls");
                        break;
                    }
                }
            break;
        case 2:
            system("title Minecraft-Toos-��������");
            system("cls");
            int x;
            cout<<"===========\n��������\n===========\n";
            cout<<"��ѡ����ҳ��\n [1]bilibili [2]GitHub [3]����\n Enter your numbers:";
            cin>>x;
            switch (x){
               case 1:
                 system("cls");
                 system("start https://space.bilibili.com/3546730880567808");
                 cout<<"Bվ��ҳ�Ѵ򿪣��ǵõ����עŶ��";
                 system("pause");
                 system("cls");
                 break;
               case 2:
                 system("cls");
                 system("start https://github.com/dongzheyu/Minecraft_Toos");
                 cout<<"GitHub�򿪳ɹ�����Ҫ������������Ŷ~~~~\n�����������\n";
                 system("pause");
                system("cls");
                break;
                case 3:
                    system("cls");
                    break;
                default:
                    system("cls");
                    cout<<"����0x45����δƥ�������\n�����������";
                    system("pause");
                    system("cls");
                    break;

            }
            break;
        case 3:{
            system("Minecraft-Toos-����");
            system("cls");
            cout<<"###############         ����        ##############\n ������Ա��bilibili ����dongle \n ����ʱ��C++20 \n ���������Visual Studio 2022��Clion \n Bվ��ҳ��https://space.bilibili.com/3546730880567808 \n GitHub��Դ��ҳ��https://github.com/dongzheyu/Minecraft-Toos/ \n bilibili ����dongle(C) ��������Ȩ�� \n#######################################################\n\n\n\n\n\n�ǵ���������Ŷ~~~";
            system("pause");
                system("cls");
                break;
}
        case 4:
            return 1;
        case 5:
            system("title Minecraft-Toos-�ٱ���");
            system("cls");
            cout<<"====================\n�ٱ���\n======================\n";
            cout<<"[1]��ǰʱ�� [2]��Ϲ��Ĺ��� [3]���� [4]new hands����(���ֹ���)  [5]������  [6]����ʵ� [7]����ը��...(��ӭ���Ͷ��,�����Ǹ�C++���ֵ��һᾡ�������ģ�����)\n enter your numbers:";
            int c;
            cin>>c;
            switch (c) {
                case 1: {
                    int i=0;
                    while (i<20) {
                        system("cls");
                        time_t nowtime;
                        time(&nowtime); //��ȡ1970��1��1��0��0��0�뵽���ھ���������
                        tm p; // NOLINT(*-pro-type-member-init)
                        localtime_s(&p,&nowtime); //������ת��Ϊ����ʱ��,���1900����,��Ҫ+1900,��Ϊ0-11,����Ҫ+1
                        cout<<"��ǰ����ʱ�䣺\n";
                        printf("%04d:%02d:%02d %02d:%02d:%02d\n", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday,p.tm_hour,p.tm_min,p.tm_sec);
                        cout<<"������20�����Զ�����";
                        Sleep(1000);
                        i++;
                    }
                    system("cls");
                    break;
                }
                case 2: {
                    system("cls");
                    cout<<"ʳ����ʾ�������ܲ��������й�̲�����ߺ��۾��������ѡ��\n[1]����  [2]����\n enter your numbers:";
                    int f;
                    cin>>f;
                    switch (f) {
                        case 1: {
                            system("cls");
                            cout<<"�ö������������ʼ";
                            Sleep(1000);
                            system("cls");
                            cout<<"�ö������ڶ����ʼ";
                            Sleep(1000);
                            system("cls");
                            cout<<"�ö�������һ���ʼ";
                            Sleep(1000);
                            system("cls");
                            cout<<"��ʼ�ˣ�����";
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
                            cout<<"���۾�Ϲ���𣿶�������ô����\n��Ϣһ�°�~~~\n";
                            system("pause");
                            system("cls");
                            system("shutdown /s /t 40");
                            cout<<"Ϊ���������۾���Ϣ��computer����40���ػ�������\n����й���û���棬�Ͻ�����ȥ������\n(����㲻��ػ���������Ƶ�cmd���(shutdown /a))\n";
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 2: {
                            system("cls");
                            system("color 07");
                            cout<<"��������";
                            Sleep(3000);
                            system("cls");
                            break;
                        }
                        default: {
                            system("cls");
                            cout<<"�������\n�����������������...\n";
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
                    cout<<"���ֹ���"
"\n- �˽���Ϸģʽ��"
"\n- ����ģʽ��������Ϸ�Ļ���ģʽ������Ҫ�ռ���Դ������ӻ������������﹥����Ŭ��������ȥ�������ģʽ�У��������ֵ������ֵ�����Ի᲻�ϱ仯����Ҫʱ�̹�ע��ά�֡�"
"\n- ����ģʽ����ӵ�����޵���Դ���������ɵؽ�����ֽ�������ʩ�����õ����������⣬��Ҫ���ڷ��Ӵ������ơ�"
"\n- ����ģʽ��������ģʽ���ƣ����Ѷȸ��ߣ�ֻ��һ��������һ��������Ϸ�ͻ������"
"\n- ������Ϸ���ã�������Ϸ��������ѡ���п��Ը����Լ��ĵ������ú͸���ϲ�õ���������������Ч�����Ʒ�ʽ�ȡ����磬�����ĵ������ܽϵͣ����Խ��������������������Ϸ�������ȡ�"
"\n��������Ҫ�㣺"
"\n- �ռ���Դ��"
"\n- ������������Ϸ������Ҫ�ҵ�һ���������ֻ򹤾��û����ɻ�ȡľͷ��ľͷ�����������Դ����������������̨�����ߡ������ȡ��������ռ�һЩľͷ���Ա�����ʹ�á�"
"\n- ��������̨������E�����򿪱��������ռ�����ľͷת��Ϊľ�壬Ȼ����ľ������һ������̨������̨������������Ʒ����Ҫ���ߣ����ṩ�˸���ĺϳ��䷽�Ϳռ䡣"
"\n- �ھ�ʯͷ��ʹ��ľ�䣨��ľ���ľ���ϳɣ��ھ���ϵ�ʯͷ����ȡԲʯ��Բʯ������������ʯ�䡢ʯ������¯�ȹ��ߺ��豸��"
"\n- ����ӻ�����"
"\n- ѡ��ص㣺��һ��ƽ̹����ȫ����Դ�ḻ�ĵط�����ӻ�������ÿ���ˮԴ�������ȡˮ��ͬʱ������ѡ�������±ߡ�ɳĮ���ĵ�Σ�ջ���Դ�ѷ��ĵط���"
"\n- ���췿�ݣ���ľͷ��ʯͷ�Ȳ��ϴһ���򵥵ķ��ݣ�������һ��Сľ�ݻ�ʯͷ���ӡ�ȷ���������źʹ������Ա�����Ͳɹ⡣�ڷ����ڷ���һ�Ŵ���������ʹ����Ҳ���ڼҸ������"
"\n- �����������ڱӻ����ں���Χ���û�ѣ��û���������Է�ֹ�����ںڰ������ɡ��������ú̿��ľ̿��ͨ����ľͷ��ã���ľ���ϳɻ�ѡ�"
"\nʳ���ȡ�����"
"\n- ����ʳ����Դ������Ϸ���ڣ�����ͨ�����Ի�ɼ�����ȡʳ����磬ɱ�������Ի�ü������ë��ɱ��ţ���Ի��ţ���Ƥ�������ṩ�������ë�����⣬�����Բɼ�ƻ�������ܲ���ũ���������ҵ��Ļ�����"
"\n- ���ʳ�����ֱ��ʳ�ûָ��ļ���ֵ���٣��ҿ��ܻ��и���Ч����������Ҫ����¯�����⿾�졣�����������¯��������ӣ������ȼ�ϣ���ú̿��ľͷ�ȣ����ȴ�һ��ʱ�����ͻ῾�졣"
"\n- ��ֲũ��������ҵ����ʵ����غ󣬿����ó�ͷ�������أ�Ȼ����ֲС�󡢺��ܲ���ũ���ũ������Ҫˮ�͹��ղ�������������Ҫȷ����ֲ�������㹻��ˮԴ�����⡣"
"\n̽�����ڿ�"
"\n- ̽����Χ������������̽���ĺ�ʱ����������Ĵ����ߣ��˽���Χ�ĵ��κ���Դ�ֲ���ע��۲��Ƿ��д�ׯ����Ѩ�������ȵط�����Щ�ط����ܻ������õ���Դ�ͱ��ء�"
"\n- �ڿ��ɣ�"
"\n- �ھ򹤾ߣ�������Ϸ�Ľ�չ��������������ڿ󹤾ߡ�ʯ������ھ������ú����������ھ���߼��Ŀ�ʯ������ʯ����������ʱ��ע��ѡ����ʵĲ��Ϻ��䷽��"
"\n- Ѱ�ҿ󶴣���Ȼ���ɵĿ��ǻ�ȡ��ʯ�ĺõط���������Ҳ���ܴ��ڹ�������ڽ����ǰҪ����׼���������������㹻�Ļ�ѡ��ڿ����ھ�ʱ��Ҫע��۲���Χ�Ļ�������������������ʧ����"
"\n- ���·�ߣ����ڿ�����У���������ʧ�������Կ�����һЩ��������Լ���·�ߣ���������;��ǽ���Ϸ��û�ѻ��÷����ǡ�"
"\n��ȫ������"
"\n- �������﹥����ҹ����и��ֹ�����֣��罩ʬ�����á�֩��ȡ�����һ�ѽ���һ����������������Ĺ��������ƿ��Եֵ�����Ľ�ս�������������ڷ�����"
"\n- �������壺�ڱӻ�����Χ����һЩ�򵥵����壬������ӡ�����������ȣ�������Ч����ֹ����Ŀ�����"
"\n- ����Σ����Ϊ����Ҫ��������δ֪�Ķ�Ѩ����Ԩ���������������ܵ��˺�����̽��İ������ʱ��Ҫ���־��裬��ʱ׼��Ӧ�Կ��ܳ��ֵ�Σ�ա�"
"\n���ڷ�չ��"
"\n- ��ħ��ҩˮ������ӵ���㹻����Դ�󣬿���������ħ̨��ҩˮ����̨����ħ����Ϊ��Ĺ��ߡ�������װ�����Ӷ�������ԣ��繥�������;öȵȣ�ҩˮ������ս�����ṩ��������Ч���������ơ����١�������ǿ�ȡ�"
"\n- ��ֳ�����ֳ�������Ϊ���ṩ�ȶ���ʳ����Դ������һ������ũ������С���ʳ������������룬Ȼ����Χ��������Χס������ι��������Ǿͻֳᷱ�����"
"\n- ���뽻�ף�������ҵ���ׯ�������������н��ס�������ṩ������Ʒ�ͷ�����������Լ�����Դ�����ǽ����������Ʒ��\n\n\n\n\n\n\n\n"
"(����������Դ�ڶ�����doubao.com��)�����������\n";
                    system("pause");
                    system("cls");
                    break;
                }
                case 5: {
                    system("cls");
                    cout<<"������(����bilibili����dongle��C++��������������֧��С���źͼӼ��˳�����)\nע��С���ű�����Ӣ�ĵģ���������Ῠ��������\n���룺";
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
                    cout<<"���:"<<num.top()<<"\n������ɣ������������\n";
                    system("pause");
                    system("cls");
                    break;
                }
                default:
                    system("cls");
                system("cls");
                cout<<"�������\n�����������������...\n";
                system("pause");
                system("cls");
                break;
                case 6: {
                    system("cls");
                    cout<<"������ת...";
                    Sleep(1000);
                    system("start https://github.com/dongzheyu/Minecraft-Toos/blob/main/%E4%BF%9D%E4%BD%91%E6%96%87%E4%BB%B6");
                    system("pause");
                    system("cls");
                    break;
                }
                case 7: {
                    system("cls");
                    int o=0;
                    cout<<"===============����ը��=============="<<endl;
                    while (o<=10) {
                        system("cls");
                        cout<<"===============����ը��=============="<<endl;
                        cout<<"�������������(��Χ��0~100)(��Ҫ10s).";
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
                        cout<<"===============����ը��=============="<<endl<<"����������ɣ�";
                        int d=rand()%100,f;
                        cin>>f;
                        if (f>d) {
                            cout<<"�´��ˣ��������ͣ�";
                            system("pause");
                        }
                        if (f==d) {
                            cout<<"��ϲ��¶��ˣ�";
                            system("pause");
                            system("cls");
                            break;
                        }
                        if (f<d) {
                            cout<<"��С�ˣ��������ͣ�";
                            system("pause");
                        }
                    }
                    break;
                }
            }
        break;
        default:
            system("cls");
            cout<<"�������\n�����������������...\n";
            system("pause");
            system("cls");
            break;
            }
    }
}