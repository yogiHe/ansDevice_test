#include "testthread.h"
#include "hidcomm.h"
#include "functional"
#include <QTextCodec>
#include <QDebug>
#include "hidbasehandle.h"

TestThread::TestThread()
{
    start();
}

void TestThread::ledTest(const int &deviceID)
{
    HidComm& handle = HidComm::get_instance();
    handle.send_led_action(deviceID,  handle.get_hid_handle());
    msleep(500);
    handle.send_led_action(deviceID,  handle.get_hid_handle());
    msleep(500);
    handle.send_led_action(deviceID,  handle.get_hid_handle());
}

void TestThread::beepTest(const int &deviceID)
{
    HidComm& handle = HidComm::get_instance();
    handle.send_beep_action(deviceID,  handle.get_hid_handle());
}

void TestThread::motorTest(const int &deviceID)
{
    HidComm& handle = HidComm::get_instance();
    handle.send_motor_action(deviceID,  handle.get_hid_handle());
}
bool TestThread::keyTest(const int &deviceID)
{
    int Sta=0;
    QTextCodec *gb2312 = QTextCodec::codecForName("gb2312");
    QByteArray showmessage;
    HidComm& handle = HidComm::get_instance();
    handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    按键测试"), handle.get_hid_handle());
    handle.send_anserkey_quesion(deviceID,  handle.get_hid_handle());
    if(handle.get_key_value(deviceID, HidComm::keyA) == HidComm::keyPress){
        testInfo.append("按键A测试通过");
        handle.send_beep_action(deviceID, handle.get_hid_handle());
    }

    if(handle.get_key_value(deviceID, HidComm::keyA) == HidComm::keyPress){
         testInfo.append("按键B测试通过");
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按按键B"), handle.get_hid_handle());
    }

    if(handle.get_key_value(deviceID, HidComm::keyB) == HidComm::keyPress){
        testInfo.append("按键C测试通过");
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按按键C"), handle.get_hid_handle());
        Sta++;
    }

    if(handle.get_key_value(deviceID, HidComm::keyC) == HidComm::keyPress){
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按按键D"), handle.get_hid_handle());
        Sta++;
    }

    if(handle.get_key_value(deviceID, HidComm::keyD) == HidComm::keyPress){
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按按键T"), handle.get_hid_handle());
        Sta++;
    }
    if(handle.get_key_value(deviceID, HidComm::keyT) == HidComm::keyPress){
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按按键F"), handle.get_hid_handle());
        Sta++;
    }

    if(handle.get_key_value(deviceID, HidComm::keyF) == HidComm::keyPress){
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按语音按键"), handle.get_hid_handle());
        Sta++;
    }

    if(handle.get_key_value(deviceID, HidComm::keyG) == HidComm::keyPress){
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("    请按语音按键"), handle.get_hid_handle());
        Sta++;
    }

    if(Sta < 8){
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode("按键测试失败---超时"), handle.get_hid_handle());
        return false;
    }
    return true;
}

bool TestThread::writeTest(const int &deviceID)
{
    HidComm& handle = HidComm::get_instance();
    QTextCodec *gb2312 = QTextCodec::codecForName("gb2312");
    QByteArray showmessage;
    QString rate_gooddot;
    for (;;) {
        rate_gooddot= QString("手写点拾取率 %f").arg(double(handle.get_dot_right_rate()));
        handle.send_show_message(deviceID, showmessage=gb2312->fromUnicode(rate_gooddot), handle.get_hid_handle());
    }


}

void TestThread::run(void)
{
    qDebug()<<"testthread run";
    HidComm& handle = HidComm::get_instance();
    for (;handle.get_hid_open_status()==false;sleep(1));
    forever{
        for(auto &it : handle.get_deviceID_map()){
            for (auto it_info : it.second) {
                if(it_info.first == HidBaseHandle::testReady && it_info.second == HidBaseHandle::testReady){
                    testInfo.append(it.first);
                    ledTest(it.first);
                    testInfo.append(": poppin可以绑定/可以充电/电池电量OK/led测试指令已下发");
                    beepTest(it.first);
                    testInfo.append(": poppin可以绑定/可以充电/电池电量OK/led测试指令已下发/蜂鸣器测试指令已下发");
                    motorTest(it.first);
                    testInfo.append(": poppin可以绑定/可以充电/电池电量OK/led测试指令已下发/蜂鸣器测试指令已下发/震动马达测试指令已下发");
                    qDebug()<<"thread it"<<it.first;
                }
            }
            msleep(200);
        }
    }

}
