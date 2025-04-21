#include <iostream>
#include "Makcu.hpp"

int SerialCom = 10;
int SerialPort = 115200;

void MakcuMonitor() {
	auto Makcu = &Makcu::Get();
	std::cout << ("[M] Makcu 按键监控线程启动") << std::endl;
	while (true) {
		bool success = true;
		for (int i = 0; i < 5; ++i) {
			success &= Makcu->MakcuMouseState(i);
		}
	}
}

bool MakcuInit() {
	std::cout << ("[M] 当前移动方式：Makcu") << std::endl;
	auto Makcu = &Makcu::Get();
	if (!Makcu->myserial.open(SerialCom, SerialPort)) {
		std::cerr << ("[!]  打开串口失败 请检查串口号和端口号是否正确") << std::endl;
		return FALSE;
	}
	else {
		std::cout << ("[M] Makcu 链接成功") << std::endl;
		std::cout << ("[M] MakcuCom: ") << SerialCom << std::endl;
		std::cout << ("[M] MakcuPort: ") << SerialPort << std::endl;
		std::thread Monitor(MakcuMonitor);	Monitor.detach();
		return TRUE;
	}
}
bool GetMouseKeyState(int key, Makcu* Mouse) {
	switch (key) {
	case 0: return (Mouse->MakcuLeft());  ///左键按住
	case 1: return (Mouse->MakcuRight()); ///右键按住
	case 2: return (Mouse->MakcuMiddle());///中键按住
	case 3: return (Mouse->MakcuSide2());///上侧键按住
	case 4: return (Mouse->MakcuSide1());///下侧键按住
	}
}
int main()
{
	std::cout << ("[M] By:ShiHuai Q416465955 制作开源") << std::endl;

	auto Makcu = &Makcu::Get();	

	MakcuInit();

	while(true) {

		if(GetMouseKeyState(0, Makcu))
		{
			Makcu->MakcuMouseMove(15, 15);
		}
		if (GetMouseKeyState(3, Makcu))
		{
			Makcu->MakcuMouseMove(15, 15);

			Makcu->MakcuMouseLeft(1);  ///左键按下
			Sleep(1);
			Makcu->MakcuMouseLeft(0);  ///左键松开
		}
	}
	Makcu->myserial.close();

}



///By:ShiHuai Q416465955 